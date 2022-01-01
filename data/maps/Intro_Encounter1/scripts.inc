Intro_Encounter1_MapScripts::
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_RETURN_TO_FIELD
	map_script MAP_SCRIPT_ON_TRANSITION, Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_RETURN_TO_FIELD:
	setvar VAR_ENCOUNTER_FLAG, 1
	return

Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setvar VAR_ENCOUNTER_FLAG, 0
	return

Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	lockall
	msgbox Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_Text_0
	releaseall
	return


Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_Text_0:
	.string "The room behind you collapsed!\p"
	.string "...\p"
	.string "There seems to be one Pokémon hiding in\n"
	.string "the grass.$"
