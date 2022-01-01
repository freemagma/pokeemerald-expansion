Intro_Encounter1_MapScripts::
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_RETURN_TO_FIELD
	map_script MAP_SCRIPT_ON_TRANSITION, Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_RETURN_TO_FIELD:
	setvar VAR_ENCOUNTER_FLAG, 1
	return

Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setvar VAR_TEMP_0, 0
	setvar VAR_ENCOUNTER_FLAG, 0
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


UpOne:
	walk_up
	step_end

Intro_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0:
	.string "The room behind you collapsed!\p"
	.string "...\p"
	.string "There seems to be one Pokémon hiding in\n"
	.string "the grass.$"
