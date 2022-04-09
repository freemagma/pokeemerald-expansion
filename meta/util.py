def _reformat_words(words):
    words = words.replace("-", " ").replace(".", "")
    words = " ".join(s.capitalize() for s in words.split())
    return words


STANDARD_CORRECTIONS = {
    _reformat_words(a): a
    for a in [
        "Mr. Mime",
        "Mr. Rime",
        "Mime Jr.",
        "Arceus-Bug",
        "Arceus-Dark",
        "Arceus-Dragon",
        "Arceus-Electric",
        "Arceus-Fighting",
        "Arceus-Fire",
        "Arceus-Flying",
        "Arceus-Ghost",
        "Arceus-Grass",
        "Arceus-Ground",
        "Arceus-Ice",
        "Arceus-Poison",
        "Arceus-Psychic",
        "Arceus-Rock",
        "Arceus-Steel",
        "Arceus-Water",
        "Nidoran-M",
        "Ho-Oh",
        "Giratina-Origin",
        "Porygon-Z",
        "Shaymin-Sky",
        "Wormadam-Sandy",
        "Wormadam-Trash",
        "Rotom-Fan",
        "Rotom-Frost",
        "Rotom-Heat",
        "Rotom-Mow",
        "Rotom-Wash",
        "Basculin-Blue-Striped",
        "Darmanitan-Zen",
        "Genesect-Burn",
        "Genesect-Chill",
        "Genesect-Douse",
        "Genesect-Shock",
        "Keldeo-Resolute",
        "Landorus-Therian",
        "Meloetta-Pirouette",
        "Thundurus-Therian",
        "Tornadus-Therian",
        "Kyurem-Black",
        "Kyurem-White",
        "Hoopa-Unbound",
        "Lycanroc-Dusk",
        "Lycanroc-Midnight",
        "Necrozma-Dawn-Wings",
        "Necrozma-Dusk-Mane",
        "Necrozma-Ultra",
        "Oricorio-Pom-Pom",
        "Oricorio-Sensu",
        "Silvally-Bug",
        "Silvally-Dark",
        "Silvally-Dragon",
        "Silvally-Electric",
        "Silvally-Fairy",
        "Silvally-Fighting",
        "Silvally-Fire",
        "Silvally-Flying",
        "Silvally-Ghost",
        "Silvally-Grass",
        "Silvally-Ground",
        "Silvally-Ice",
        "Silvally-Poison",
        "Silvally-Psychic",
        "Silvally-Rock",
        "Silvally-Steel",
        "Silvally-Water",
        "Zarude-Dada",
        # moves
        "Will-O-Wisp",
        "U-turn",
        "Double-Edge",
        "Self-Destruct",
        "Soft-Boiled",
        "Lock-On",
        "Mud-Slap",
        "Wake-Up Slap",
        "X-Scissor",
        "Baby-Doll Eyes",
        "Freeze-Dry",
        "Power-Up Punch",
        "Topsy-Turvy",
        "Multi-Attack",
        "V-create",
        "Trick-or-Treat",
        # abilities
        "Soul-Heart"
    ]
}

WORD_CORRECTIONS = {
    "Dragons Maw": "Dragon's Maw",
    "Aegislash": "Aegislash-Blade",
    "Oricorio Pau": "Oricorio-Pa'u",
    "Calyrex Ice Rider": "Calyrex-Ice",
    "Calyrex Shadow Rider": "Calyrex-Shadow",
    "Ideedee Female": "Indeedee-F",
    "Sirfetchd": "Sirfetch\u2019d",
    "Urshifu Rapid Stride Style": "Urshifu-Rapid-Strike",
    "Zacian Crowned Sword": "Zacian-Crowned",
    "Zamazenta Crowned Shield": "Zamazenta-Crowned",
    "Mr Mime Galarian": "Mr. Mime-Galar",
    **STANDARD_CORRECTIONS,
}


def correct_words(word):
    if word in WORD_CORRECTIONS:
        return WORD_CORRECTIONS[word]
    if word.endswith(" Alolan"):
        return word.replace(" Alolan", "-Alola")
    if word.endswith(" Galarian"):
        return word.replace(" Galarian", "-Galar")
    return word
