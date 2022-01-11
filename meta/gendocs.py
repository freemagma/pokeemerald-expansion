from collections import namedtuple, defaultdict
import re


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
            species_name[key] = value
            name_species[value].append(key)

    return species_name, name_species


def parse_level_up():
    lines = []
    with open("src/data/pokemon/level_up_learnsets.h") as f:
        lines = [l.strip() for l in f.readlines()]

    poke_key = None
    raw_learnsets = defaultdict(lambda: dict())
    for line in lines:
        if "LevelUpMove" in line:
            poke_key = re.search(r"LevelUpMove\s*(\S*)\[", line).group(1)
            continue
        if poke_key is None:
            continue
        if "LEVEL_UP_MOVE" in line:
            m = re.search(r"LEVEL_UP_MOVE\s*\(\s*(\S*),\s*(\S*)\s*\),", line)
            level, move = int(m.group(1)), m.group(2)
            raw_learnsets[poke_key][level] = move

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


def format_words(words, remove=""):
    words = words.replace(remove, "").replace("_", " ").strip()
    words = " ".join(s.capitalize() for s in words.split())
    return words


def print_pokedata(data, f):
    print(
        "_Stats_: {}/{}/{}/{}/{}/{}".format(
            data["baseHP"],
            data["baseAttack"],
            data["baseDefense"],
            data["baseSpAttack"],
            data["baseSpDefense"],
            data["baseSpeed"],
        ),
        file=f,
    )
    abilities = (
        data["abilities"][1:-1].replace("ABILITY", "").replace("_", " ").split(",")
    )
    print(
        "_Abilities_: "
        + ", ".join(
            " ".join(s.capitalize() for s in a.strip().split()) for a in abilities
        ),
        file=f,
    )


def print_learnset(learnset, f):
    for lvl in sorted(learnset.keys()):
        lvltxt = " " + str(lvl) if lvl < 10 else str(lvl)
        move = format_words(learnset[lvl], remove="MOVE_")
        print(f"{lvltxt}. {move}", file=f)


def print_evolution(evo_methods, f):
    if len(evo_methods) == 0:
        return

    sentences = []
    for evo_type, evo_arg, into_spec in evo_methods:
        format_spec = format_words(into_spec, remove="SPECIES_")
        if evo_type == "EVO_LEVEL":
            sentences.append(f"into {format_spec} at level {evo_arg}")
        elif evo_type == "EVO_LEVEL_ATK_GT_DEF":
            sentences.append(f"into {format_spec} at level {evo_arg} if Atk > Def")
        elif evo_type == "EVO_LEVEL_ATK_EQ_DEF":
            sentences.append(f"into {format_spec} at level {evo_arg} if Atk = Def")
        elif evo_type == "EVO_LEVEL_ATK_LT_DEF":
            sentences.append(f"into {format_spec} at level {evo_arg} if Atk < Def")
        elif evo_type == "EVO_LEVEL_FEMALE":
            sentences.append(f"into {format_spec} at level {evo_arg} if female")
        elif evo_type == "EVO_LEVEL_MALE":
            sentences.append(f"into {format_spec} at level {evo_arg} if male")
        elif evo_type == "EVO_LEVEL_DAY":
            sentences.append(f"into {format_spec} at level {evo_arg} during the day")
        elif evo_type == "EVO_LEVEL_NIGHT":
            sentences.append(f"into {format_spec} at level {evo_arg} at night")
        elif evo_type == "EVO_LEVEL_DUSK":
            sentences.append(f"into {format_spec} at level {evo_arg} at dusk")
        elif evo_type.startswith("EVO_LEVEL"):
            sentences.append(f"into {format_spec} at level {evo_arg}")
        elif evo_type == "EVO_ITEM":
            format_item = format_words(evo_arg, remove="ITEM_")
            sentences.append(f"into {format_spec} via {format_item}")
        elif evo_type == "EVO_ITEM_FEMALE":
            format_item = format_words(evo_arg, remove="ITEM_")
            sentences.append(f"into {format_spec} via {format_item} if female")
        elif evo_type == "EVO_ITEM_MALE":
            format_item = format_words(evo_arg, remove="ITEM_")
            sentences.append(f"into {format_spec} via {format_item} if male")
        elif evo_type == "EVO_ITEM_HOLD_DAY":
            format_item = format_words(evo_arg, remove="ITEM_")
            sentences.append(
                f"into {format_spec} while holding {format_item} during the day"
            )
        elif evo_type == "EVO_ITEM_HOLD_NIGHT":
            format_item = format_words(evo_arg, remove="ITEM_")
            sentences.append(f"into {format_spec} while holding {format_item} at night")
        elif evo_type == "EVO_FRIENDSHIP":
            sentences.append(f"into {format_spec} with high friendship")
        elif evo_type == "EVO_FRIENDSHIP_DAY":
            sentences.append(f"into {format_spec} with high friendship during the day")
        elif evo_type == "EVO_FRIENDSHIP_NIGHT":
            sentences.append(f"into {format_spec} with high friendship at night")
        elif evo_type == "EVO_TRADE":
            sentences.append(f"into {format_spec} when traded")
        elif evo_type == "EVO_TRADE_ITEM":
            format_item = format_words(evo_arg, remove="ITEM_")
            sentences.append(
                f"into {format_spec} when traded while holding {format_item}"
            )
        elif evo_type == "EVO_MOVE_TYPE":
            format_type = format_words(evo_arg, remove="TYPE_")
            sentences.append(f"into {format_spec} while knowing a {format_type}-type move")
        else:
            print(evo_type)
            sentences.append(f"into {format_spec}")
    if len(sentences) == 1:
        print(f"_Evolves_: {sentences[0]}", file=f)
    else:
        print("_Evolves_:", file=f)
        for sentence in sentences:
            print(" - " + sentence, file=f)


def main():
    pokedata = parse_pokedata()
    species_name, name_species = parse_names()
    learnsets = parse_level_up()
    evo_methods = parse_evolution()

    with open("meta/docs/pokemon_data.md", "w") as f:
        for name in sorted(name_species.keys()):
            print(f"## {name}", file=f)
            for e, species in enumerate(name_species[name]):
                if len(name_species[name]) > 1:
                    print(
                        "**{}**".format(format_words(species, remove="SPECIES_")),
                        file=f,
                    )
                print_pokedata(pokedata[species], f)
                print_evolution(evo_methods[species], f)
                print(file=f)
                print_learnset(learnsets[species], f)
                if e != len(name_species[name]) - 1:
                    print(file=f)
            print(file=f)


if __name__ == "__main__":
    main()
