DungeonTutorial_Act1_Gift1_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DungeonTutorial_Act1_Gift1_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DungeonTutorial_Act1_Gift1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DungeonTutorial_Act1_Gift1_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setvar VAR_TEMP_0, 0
	setvar VAR_TEMP_A, 0
	callnative DungeonTutorial_GetGiftMon
	return

DungeonTutorial_Act1_Gift1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_0, 0, DungeonTutorial_Act1_Gift1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0
	.2byte 0

DungeonTutorial_Act1_Gift1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0:
	lock
	applymovement OBJ_EVENT_ID_PLAYER, Common_UpOne
	waitmovement 0
	msgbox DungeonTutorial_Act1_Gift1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0
	setvar VAR_TEMP_0, 1
	release
	return


DTutorial_A1_Gift1_SignDirections::
	lock
	msgbox DTutorial_A1_Gift1_SignDirections_Text_0, MSGBOX_SIGN
	release
	return


DungeonTutorial_Act1_Gift1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0:
	.string "The room behind you collapsed!\p"
	.string "...\p"
	.string "There seem to be some Pokéballs out in\n"
	.string "the open.$"

DTutorial_A1_Gift1_SignDirections_Text_0:
	.string "In gift rooms, you will be given some\n"
	.string "free Pokémon to choose from.\p"
	.string "It's that simple!$"
