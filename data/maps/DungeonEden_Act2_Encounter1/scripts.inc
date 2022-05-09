DungeonEden_Act2_Encounter1_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DungeonEden_Act2_Encounter1_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DungeonEden_Act2_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DungeonEden_Act2_Encounter1_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setvar VAR_TEMP_0, 0
	setvar VAR_ENCOUNTERS_LEFT, 1
	clearflag FLAG_DISABLE_BAG
	return

DungeonEden_Act2_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_0, 0, DungeonEden_Act2_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0
	.2byte 0

DungeonEden_Act2_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0:
	lock
	applymovement OBJ_EVENT_ID_PLAYER, Common_UpTwo
	waitmovement 0
	msgbox DungeonEden_Act2_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0
	setvar VAR_TEMP_0, 1
	release
	return


DungeonEden_Act2_Encounter1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0:
	.string "The snow and ice are much too cold to\n"
	.string "stand on!$"
