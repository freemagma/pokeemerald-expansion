from collections import namedtuple, defaultdict
import re
import json
import sys

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
    raw_learnsets = defaultdict(lambda: dict())
    for line in lines:
        if "LevelUpMove" in line:
            poke_key = re.search(r"LevelUpMove\s*(\S*)\[", line).group(1)
            continue
        if poke_key is None:
            continue
        if "LEVEL_UP_MOVE" in line:
            m = re.search(r"LEVEL_UP_MOVE\s*\(\s*(\S*),\s*(\S*)\s*\),", line)
            level, move = m.group(1), m.group(2)
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


def main():
    if len(sys.argv) == 1:
        print("filename required")
        return
    filename = f"meta/data/{sys.argv[1]}.json"

    movedata = parse_movedata()
    pokedata = parse_pokedata()
    pokedex = parse_names()
    learnsets = parse_level_up()
    evo_methods = parse_evolution()
    d = {
        "movedata": movedata,
        "pokedata": pokedata,
        "pokedex": pokedex,
        "learnsets": learnsets,
        "evo_methods": evo_methods,
    }
    with open(filename, "w") as f:
        json.dump(d, f)

if __name__ == "__main__":
    main()
