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
        if "SPECIES" in line:
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

def main():
    pokedata = parse_pokedata()
    species_name, name_species = parse_names()
    learnsets = parse_level_up()

    with open("meta/docs/pokemon_data.md", "w") as f:
        for name in ("Rattata", "Raticate", "Calyrex"):
            print(f"## {name}", file=f)
            for e, species in enumerate(name_species[name]):
                if len(name_species[name]) > 1:
                    print("**{}**".format(format_words(species, remove="SPECIES_")), file=f)
                print_pokedata(pokedata[species], f)
                print(file=f)
                print_learnset(learnsets[species], f)
                if e != len(name_species[name]) - 1:
                    print(file=f)
            print(file=f)


if __name__ == "__main__":
    main()
