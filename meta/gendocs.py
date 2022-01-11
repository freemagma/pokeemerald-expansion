import json
import sys


def format_words(words, remove=""):
    words = words.replace(remove, "").replace("_", " ").strip()
    words = " ".join(s.capitalize() for s in words.split())
    return words


def print_pokedata(data, f):
    type1 = format_words(data["type1"], remove="TYPE_")
    type2 = format_words(data["type2"], remove="TYPE_")
    typetext = f"{type1}/{type2}" if type1 != type2 else f"{type1}"
    print(f"__Type__: {typetext} \\", file=f)
    print(
        "__Stats__: {}/{}/{}/{}/{}/{} \\".format(
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
        "__Abilities__: "
        + ", ".join(
            " ".join(s.capitalize() for s in a.strip().split()) for a in abilities
        ) + " \\",
        file=f,
    )


def print_learnset(learnset, f):
    for lvl in sorted(map(int, learnset.keys())):
        lvltxt = " " + str(lvl) if lvl < 10 else str(lvl)
        move = format_words(learnset[str(lvl)], remove="MOVE_")
        print(f"{lvltxt}. {move}", file=f)


def print_evolution(evo_methods, f):
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
        elif evo_type == "EVO_TRADE_SPECIFIC_MON":
            format_spec2 = format_words(evo_arg, remove="SPECIES_")
            sentences.append(f"into {format_spec} when traded for a {format_spec2}")
        elif evo_type == "EVO_MOVE_TYPE":
            format_type = format_words(evo_arg, remove="TYPE_")
            sentences.append(
                f"into {format_spec} while knowing a {format_type}-type move"
            )
        elif evo_type == "EVO_MOVE":
            format_move = format_words(evo_arg, remove="MOVE_")
            sentences.append(f"into {format_spec} while knowing {format_move}")
        elif evo_type == "EVO_SPECIFIC_MON_IN_PARTY":
            format_spec2 = format_words(evo_arg, remove="SPECIES_")
            sentences.append(
                f"into {format_spec} when a {format_spec2} is in the party"
            )
        elif evo_type == "EVO_BEAUTY":
            sentences.append(f"into {format_spec} with high beauty")

    if len(sentences) == 0:
        return
    if len(sentences) == 1:
        print(f"__Evolves__: {sentences[0]}", file=f)
    else:
        print("__Evolves__:", file=f)
        for sentence in sentences:
            print(" - " + sentence, file=f)


def get_modified_species(j, jc):
    modified = set()
    for name, species in j["pokedex"]:
        for spec in species:
            if spec not in jc["learnsets"]:
                modified.add(spec)
                continue
            learnset = j["learnsets"][spec]
            c_learnset = jc["learnsets"][spec]
            if set(learnset.keys()) | {0} != set(c_learnset.keys()) | {0}:
                modified.add(spec)
                continue
            if j["evo_methods"].get(spec) != jc["evo_methods"].get(spec):
                modified.add(spec)
                continue
            data = j["pokedata"][spec]
            c_data = jc["pokedata"][spec]
            for key in set(data.keys()) | set(c_data.keys()):
                if key in ("item1", "item2"):
                    continue
                if data.get(key) != c_data.get(key):
                    modified.add(spec)
                    break
    modified.add("SPECIES_EEVEE")
    return modified


def print_move_changes(movedata, c_movedata, f):
    for move in movedata:
        if move not in c_movedata:
            # TODO add this case if necessary
            continue
        format_move = format_words(move, remove="MOVE_")
        data = movedata[move]
        c_data = c_movedata[move]
        lines = []
        if data["type"] != c_data["type"]:
            format_type = format_words(data["type"], remove="TYPE_")
            lines.append(f"{format_type} type")
        if data["power"] != c_data["power"]:
            diff = int(data["power"]) - int(c_data["power"])
            lines.append(f"{data['power']} Power ({diff:+})")
        if data["accuracy"] != c_data["accuracy"]:
            diff = int(data["accuracy"]) - int(c_data["accuracy"])
            lines.append(f"{data['accuracy']} Accuracy ({diff:+}%)")
        if lines:
            print(f"## {format_move}", file=f)
            for line in lines:
                print(line, file=f)
            print(file=f)


def main():
    if len(sys.argv) == 1:
        print("filename required")
        return

    filename = f"meta/data/{sys.argv[1]}.json"
    with open(filename) as f:
        j = json.load(f)

    species_modified = None
    if len(sys.argv) > 2:
        file_compare = f"meta/data/{sys.argv[2]}.json"
        with open(file_compare) as f:
            j_compare = json.load(f)
        species_modified = get_modified_species(j, j_compare)
        with open("meta/docs/move_changes.md", "w") as f:
            print_move_changes(j["movedata"], j_compare["movedata"], f)

    pokedata = j["pokedata"]
    pokedex = j["pokedex"]
    learnsets = j["learnsets"]
    evo_methods = j["evo_methods"]

    with open("meta/docs/pokemon_data.md", "w") as f:
        for name, species in pokedex:
            if species_modified is not None and not any(
                spec in species_modified for spec in species
            ):
                continue
            print(f"## {name}", file=f)
            past_learnsets = []
            actual_species = (
                species
                if species_modified is None
                else [spec for spec in species if spec in species_modified]
            )
            for e, spec in enumerate(actual_species):
                if e != 0:
                    print(
                        "**{}**".format(format_words(spec, remove="SPECIES_")),
                        file=f,
                    )
                print_pokedata(pokedata[spec], f)
                if spec in evo_methods:
                    print_evolution(evo_methods[spec], f)
                print(file=f)
                if learnsets[spec] not in past_learnsets:
                    print_learnset(learnsets[spec], f)
                    past_learnsets.append(learnsets[spec])
                if e != len(species) - 1:
                    print(file=f)
            print(file=f)


if __name__ == "__main__":
    main()
