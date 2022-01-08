DungeonTutorial_Act1_Encounter1_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DungeonTutorial_Act1_Encounter1_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DungeonTutorial_Act1_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DungeonTutorial_Act1_Encounter1_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setvar VAR_TEMP_0, 0
	setvar VAR_ENCOUNTERS_LEFT, 1
	return

DungeonTutorial_Act1_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_0, 0, DungeonTutorial_Act1_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0
	.2byte 0

DungeonTutorial_Act1_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0:
	lock
	applymovement OBJ_EVENT_ID_PLAYER, Common_UpOne
	waitmovement 0
	msgbox DungeonTutorial_Act1_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0
	setvar VAR_TEMP_0, 1
	release
	return


Intro_Encounter1_SignDirections::
	lockall
	msgbox Intro_Encounter1_SignDirections_Text_0
	releaseall
	return


DungeonTutorial_Act1_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0:
	.string "The room behind you collapsed!\p"
	.string "...\p"
	.string "There seem to be a couple Pokémon\n"
	.string "hiding in the grass.$"

Intro_Encounter1_SignDirections_Text_0:
	.string "In encounter rooms, you will have the\n"
	.string "opportunity to catch a Pokémon.\p"
	.string "Your encounter will contain two wild\n"
	.string "Pokémon you haven't caught yet, and\l"
	.string "will be a double battle if possible.\p"
	.string "But be careful; you can't try again if\n"
	.string "you fail!$"
