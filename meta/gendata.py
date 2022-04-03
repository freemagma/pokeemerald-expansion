import json
import re
import sys
from collections import defaultdict, namedtuple


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


def parse_trainerdata():
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

    with open("src/data/text/trainer_class_names.h") as f:
        lines = [l.strip() for l in f.readlines()]

    class_to_name = {}
    for line in lines:
        if not line.startswith("[TRAINER"):
            continue
        m = re.search(r"\[(.*)\]\s*=.*\"(.*)\"", line)
        class_key, class_name = m.group(1), m.group(2)
        class_name.replace("{PKMN}", "PKMN")
        class_to_name[class_key] = class_name

    with open("src/data/trainers.h") as f:
        lines = [l.strip() for l in f.readlines()]

    trainer_key = None
    trainerdata = defaultdict(lambda: dict())
    for line in lines:
        if line.startswith("["):
            trainer_key = re.search(r"\[(.*)\]", line).group(1)
            if trainer_key == "TRAINER_NONE" or not (
                trainer_key.startswith("TRAINER_TU_")
                or trainer_key.startswith("TRAINER_ED_")
            ):
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
            party_key = re.search(r"(sParty.*)\}", line).group(1)
            trainerdata[trainer_key]["party"] = party_team[party_key]

    return trainerdata


def parse_movedata():
    lines = []
    with open("src/data/battle_moves.h") as f:
        lines = [l.strip() for l in f.readlines()]

    move_key = None
    movedata = defaultdict(lambda: dict())
    for line in lines:
        if line.startswith("[MOVE_"):
            move_key = re.search(r"\[(.*)\]", line).group(1)
            continue
        if move_key is None:
            continue
        if line and line[0] == ".":
            m = re.search(r"\.(\S*)\s*=\s*(.*\w)", line)
            key, value = m.group(1), m.group(2)
            value = format_value(value)
            if key not in movedata[move_key]:
                movedata[move_key][key] = value

    return movedata


def parse_pokedata():
    lines = []
    with open("src/data/pokemon/base_stats.h") as f:
        lines = [l.strip() for l in f.readlines()]

    poke_key = None
    pokedata = defaultdict(lambda: dict())
    for line in lines:
        if "SPECIES" in line:
            poke_key = re.search(r"\[(.*)\]", line).group(1)
            continue
        if poke_key is None:
            continue
        if line and line[0] == ".":
            m = re.search(r"\.(\S*)\s*=\s*(.*),", line)
            key, value = m.group(1), m.group(2)
            value = format_value(value)
            if key not in pokedata[poke_key]:
                pokedata[poke_key][key] = value

    return pokedata


def parse_names():
    lines = []
    with open("src/data/text/species_names.h") as f:
        lines = [l.strip() for l in f.readlines()]

    species_name = dict()
    name_species = defaultdict(lambda: list())
    for line in lines:
        if "SPECIES" in line and "SPECIES_NONE" not in line:
            m = re.search(r"\[(.*)\]\s*=\s*_\(\"(.*)\"\),", line)
            key, value = m.group(1), m.group(2)
            value = format_value(value)
            name_species[value].append(key)
            species_name[key] = value

    lines = []
    with open("include/constants/species.h") as f:
        lines = [l.strip() for l in f.readlines()]

    pokedex = []
    for line in lines:
        if (
            line.startswith("#define SPECIES")
            and "SPECIES_NONE" not in line
            and "SPECIES_EGG" not in line
            and "FORMS_START" not in line
        ):
            m = re.search(r"(SPECIES_\S*)\s*(\S*)", line)
            spec, num = m.group(1), m.group(2)
            name = species_name[spec]
            pokedex.append((name, name_species[name]))

    return pokedex


def parse_level_up():
    lines = []
    with open("src/data/pokemon/level_up_learnsets.h") as f:
        lines = [l.strip() for l in f.readlines()]

    poke_key = None
    raw_learnsets = defaultdict(lambda: list())
    for line in lines:
        if "LevelUpMove" in line:
            poke_key = re.search(r"LevelUpMove\s*(\S*)\[", line).group(1)
            continue
        if poke_key is None:
            continue
        if "LEVEL_UP_MOVE" in line:
            m = re.search(r"LEVEL_UP_MOVE\s*\(\s*(\S*),\s*(\S*)\s*\),", line)
            level, move = int(m.group(1)), m.group(2)
            raw_learnsets[poke_key].append((level, move))

    with open("src/data/pokemon/level_up_learnset_pointers.h") as f:
        lines = [l.strip() for l in f.readlines()]

    learnsets = dict()
    for line in lines:
        if line.startswith("[SPECIES"):
            m = re.search(r"\[(.*)\]\s*=\s*(\S*),", line)
            key, value = m.group(1), m.group(2)
            learnsets[key] = raw_learnsets[value]

    return learnsets


def parse_evolution():
    lines = []
    with open("src/data/pokemon/evolution.h") as f:
        lines = [l.strip() for l in f.readlines()]

    poke_key = None
    evo_methods = defaultdict(lambda: list())
    for line in lines:
        if line.startswith("[SPECIES"):
            poke_key = re.search(r"^\[(.*)\]", line).group(1)
        if "EVO_" in line:
            m = re.search(r"\{(EVO_\S*),\s*(\S*)\s*,\s*(\S*\w)\}", line)
            evo_methods[poke_key].append((m.group(1), m.group(2), m.group(3)))

    return evo_methods


def main():
    if len(sys.argv) == 1:
        print("filename required")
        return
    filename = f"meta/data/{sys.argv[1]}.json"

    movedata = parse_movedata()
    pokedata = parse_pokedata()
    trainerdata = parse_trainerdata()
    pokedex = parse_names()
    learnsets = parse_level_up()
    evo_methods = parse_evolution()
    d = {
        "movedata": movedata,
        "pokedata": pokedata,
        "trainerdata": trainerdata,
        "pokedex": pokedex,
        "learnsets": learnsets,
        "evo_methods": evo_methods,
    }
    with open(filename, "w") as f:
        json.dump(d, f)


if __name__ == "__main__":
    main()
