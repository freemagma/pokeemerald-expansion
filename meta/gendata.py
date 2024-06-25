import json
import re
import sys
from collections import defaultdict
import subprocess


def parse_trainerdata():
    def format_value(value):
        if value.isdigit():
            return int(value)
        elif value.startswith("{"):
            return [format_value(s.strip()) for s in value[1:-1].split(",")]
        elif "|" in value:
            return [format_value(s.strip()) for s in value.split("|")]
        elif "_NONE" in value:
            return None
        return value

    lines = []
    with open("src/data/trainer_parties.h") as f:
        lines = [l.strip() for l in f.readlines()]

    party_key = None
    party_team = defaultdict(lambda: list())
    for line in lines:
        if line.startswith("static const struct"):
            party_key = re.search(r"(sParty.*)\[\]", line).group(1)
        elif line == "{":
            party_team[party_key].append({})
        elif line.startswith("."):
            m = re.search(r"\.(\S*)\s*=\s*(.*[^,]),?$", line)
            key, value = m.group(1), m.group(2)
            value = format_value(value)
            party_team[party_key][-1][key] = value

    with open("src/battle_main.c") as f:
        lines = [l.strip() for l in f.readlines()]

    class_to_name = {}
    for line in lines:
        if not line.startswith("TRAINER_CLASS("):
            continue
        m = re.search(r"TRAINER_CLASS\(([^,]*),\s*\"([^\"]*)\"", line)
        class_key, class_name = f"TRAINER_CLASS_{m.group(1)}", m.group(2)
        class_name = class_name.replace("{PKMN}", "PKMN")
        class_to_name[class_key] = class_name

    with open("src/data/trainers.h") as f:
        lines = [l.strip() for l in f.readlines()]

    trainer_key = None
    trainerdata = defaultdict(lambda: dict())
    for line in lines:
        if line.startswith("["):
            trainer_key = re.search(r"\[(.*)\]", line).group(1)
            if trainer_key == "TRAINER_NONE":
                trainer_key = None

        if trainer_key is None:
            continue

        if line.startswith(".trainerClass"):
            class_key = re.search(r"=\s*(.*),", line).group(1)
            trainerdata[trainer_key]["class"] = class_to_name[class_key]
        elif line.startswith(".trainerName"):
            name = re.search(r"\"(.*)\"", line).group(1)
            trainerdata[trainer_key]["name"] = name
        elif line.startswith(".party "):
            party_key = re.search(r"(sParty.*)\)", line).group(1)
            trainerdata[trainer_key]["party"] = party_team[party_key]

    return trainerdata


def value_or_ternary(s):
    if "?" not in s:
        return s

    s = s.strip()
    while s.startswith("(") and s.endswith(")"):
        s = s[1:-1].strip()

    condition, options = s.split("?")
    option_1, option_2 = options.split(":")
    return option_1 if eval(condition) else option_2


def int_or_ternary(s):
    value = value_or_ternary(s)
    if value.isdigit():
        return int(value)
    else:
        return int(value.split(",")[0])


def parse_movedata():
    def clean_info_str(info_str):
        interleaved = re.split(r"\.(\w*)\s*=", info_str)[1:]

        info_raw = {"moveEffect": [], "chance": []}
        awaiting_chance = False
        for k, v in zip(interleaved[0::2], interleaved[1::2]):
            v = v.strip()[:-1]

            if k == "moveEffect":
                if awaiting_chance:
                    info_raw["chance"].append("100")
                info_raw[k].append(v)
                awaiting_chance = True
            elif k == "chance":
                info_raw[k].append(v)
                awaiting_chance = False
            else:
                info_raw[k] = v

        if awaiting_chance:
            info_raw["chance"].append("100")

        return info_raw

    out = subprocess.run(
        """pcpp --passthru-unfound-includes --passthru-unknown-exprs \
        include/gba/defines.h include/config.h include/config/*.h src/data/moves_info.h""",
        capture_output=True,
        cwd="/home/cgunn/dev/pokemon/emerald",
        shell=True,
    )

    s = " ".join(out.stdout.decode("utf-8").split("\n"))

    interleaved = re.split(r"\[(MOVE_[^\]]*)\]\s*=", s)[1:]
    move_and_info_str = zip(interleaved[0::2], interleaved[1::2])

    movedata = {}
    for move, info_str in move_and_info_str:
        info_raw = clean_info_str(info_str)

        info = {}
        info["name"] = info_raw["name"][len('COMPOUND_STRING("') : -2]
        info["power"] = int_or_ternary(info_raw["power"])
        info["accuracy"] = int_or_ternary(info_raw["accuracy"])
        info["pp"] = int_or_ternary(info_raw["pp"])
        info["priority"] = int_or_ternary(info_raw["priority"])
        info["type"] = value_or_ternary(info_raw["type"])
        info["effect"] = (
            value_or_ternary(info_raw["effect"]) if "effect" in info_raw else None
        )
        info["target"] = value_or_ternary(info_raw["target"])
        info["additional_effects"] = (
            {
                value_or_ternary(effect): int_or_ternary(chance)
                for effect, chance in zip(info_raw["moveEffect"], info_raw["chance"])
            }
            if "moveEffect" in info_raw
            else {}
        )

        movedata[move] = info

    return movedata


def parse_num_to_move():
    with open("include/constants/moves.h") as f:
        lines = [l.strip() for l in f.readlines()]

    num_to_move = {}
    for line in lines:
        if line.startswith("#define MOVE") and "MOVES_COUNT" not in line:
            m = re.search(r"(MOVE_\S*)\s*(\S*)", line)
            move, num_or_alias = m.group(1), m.group(2)
            if num_or_alias.isdigit():
                num_to_move[int(num_or_alias)] = move

    return num_to_move


def parse_learnsets():
    lines = []
    with open(f"src/data/pokemon/level_up_learnsets/gen_9.h") as f:
        lines.extend([l.strip() for l in f.readlines()])

    key = None
    learnsets = defaultdict(lambda: list())
    for line in lines:
        if "LevelUpMove" in line:
            key = re.search(r"LevelUpMove\s*(\S*)\[", line).group(1)
            if key in learnsets:
                key = None
        if key is None:
            continue
        if line.startswith("LEVEL_UP_MOVE"):
            m = re.search(r"LEVEL_UP_MOVE\s*\(\s*(\S*),\s*(\S*)\s*\),", line)
            level, move = int(m.group(1)), m.group(2)
            learnsets[key].append((level, move))

    return learnsets


def parse_pokedata():
    def de_underscore(s):
        return s.strip()[3:-2]

    def de_bracket(s):
        return s.strip().replace("{", "").replace("}", "")

    def clean_info_str(info_str):
        intellisense_str = "#ifdef __INTELLISENSE__"
        if intellisense_str in info_str:
            info_str = info_str.split(intellisense_str)[0]

        interleaved = re.split(r"\.(\w*)\s*=", info_str)[1:]
        interleaved[-1] = interleaved[-1].rsplit(",", maxsplit=1)[0] + ","
        return {k: v.strip()[:-1] for k, v in zip(interleaved[0::2], interleaved[1::2])}

    learnsets = parse_learnsets()

    out = subprocess.run(
        """pcpp --passthru-unfound-includes --passthru-unknown-exprs \
        include/gba/defines.h include/config.h include/config/*.h src/data/pokemon/species_info/*.h""",
        capture_output=True,
        cwd="/home/cgunn/dev/pokemon/emerald",
        shell=True,
    )

    s = " ".join(out.stdout.decode("utf-8").split("\n"))

    interleaved = re.split(r"\[(SPECIES_[^\]]*)\]\s*=", s)[1:]
    species_and_info_str = zip(interleaved[0::2], interleaved[1::2])

    pokedata = {}
    for species, info_str in species_and_info_str:
        info_raw = clean_info_str(info_str)

        info = {}
        info["hp"] = int_or_ternary(info_raw["baseHP"])
        info["atk"] = int_or_ternary(info_raw["baseAttack"])
        info["def"] = int_or_ternary(info_raw["baseDefense"])
        info["spa"] = int_or_ternary(info_raw["baseSpAttack"])
        info["spd"] = int_or_ternary(info_raw["baseSpDefense"])
        info["spe"] = int_or_ternary(info_raw["baseSpeed"])
        info["types"] = [
            value_or_ternary(s).strip()
            for s in info_raw["types"].strip()[len("MON_TYPES(") : -1].split(",")
        ]
        info["abilities"] = [
            s.strip() for s in info_raw["abilities"].strip()[1:-1].split(",")
        ]
        info["name"] = de_underscore(info_raw["speciesName"])
        info["learnset"] = learnsets[info_raw["levelUpLearnset"]]
        info["teachable_key"] = info_raw["teachableLearnset"]

        if "evolutions" in info_raw:
            interleaved = [
                de_bracket(s)
                for s in info_raw["evolutions"]
                .rsplit(")", maxsplit=1)[0][len("EVOLUTION(") :]
                .split(",")
            ]
            info["evolutions"] = list(
                zip(interleaved[0::3], interleaved[1::3], interleaved[2::3])
            )
        else:
            info["evolutions"] = None

        pokedata[species] = info

    return pokedata


def parse_num_to_species():
    lines = []
    with open("include/constants/species.h") as f:
        lines = [l.strip() for l in f.readlines()]

    num_to_species = {}
    for line in lines:
        if (
            line.startswith("#define SPECIES")
            and "SPECIES_NONE" not in line
            and "SPECIES_EGG" not in line
        ):
            m = re.search(r"(SPECIES_\S*)\s*(\S*)", line)
            species, num = m.group(1), m.group(2)
            if num.isdigit():
                num_to_species[int(num)] = species

    return num_to_species


def main():
    if len(sys.argv) == 1:
        print("filename required")
        return
    filename = f"meta/data/{sys.argv[1]}.json"

    d = {
        "trainerdata": parse_trainerdata(),
        "movedata": parse_movedata(),
        "num_to_move": parse_num_to_move(),
        "pokedata": parse_pokedata(),
        "num_to_species": parse_num_to_species(),
    }
    with open(filename, "w") as f:
        json.dump(d, f, indent=1)


if __name__ == "__main__":
    main()
