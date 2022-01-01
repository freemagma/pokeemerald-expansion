Intro_Encounter1_MapScripts::
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_RETURN_TO_FIELD
	map_script MAP_SCRIPT_ON_TRANSITION, Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_RETURN_TO_FIELD:
	setvar VAR_ENCOUNTERS_LEFT, 0
	return

Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setvar VAR_TEMP_0, 0
	setvar VAR_ENCOUNTERS_LEFT, 1
	return

Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_0, 0, Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0
	.2byte 0

Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0:
	lock
	applymovement OBJ_EVENT_ID_PLAYER, UpOne
	waitmovement 0
	msgbox Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0
	setvar VAR_TEMP_0, 1
	release
	return


SignDirections::
	lockall
	msgbox SignDirections_Text_0
	releaseall
	return


UpOne:
	walk_up
	step_end

Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0:
	.string "The room behind you collapsed!\p"
	.string "...\p"
	.string "There seem to be a couple Pokémon\n"
	.string "hiding in the grass.$"

SignDirections_Text_0:
	.string "In encounter rooms, you will have the\n"
	.string "opportunity to catch a Pokémon. Your\l"
	.string "encounter will be a double battle\l"
	.string "containing two wild Pokémon you\l"
	.string "haven't caught yet. But be careful,\l"
	.string "since you can't try again if you fail!$"
