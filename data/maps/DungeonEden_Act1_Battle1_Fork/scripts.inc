DungeonEden_Act1_Battle1_Fork_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DungeonEden_Act1_Battle1_Fork_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DungeonEden_Act1_Battle1_Fork_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DungeonEden_Act1_Battle1_Fork_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setvar VAR_TEMP_0, 0
	callnative DungeonEden_GenerateBattle
	copyvar VAR_TEMP_A, VAR_0x8000
	setflag FLAG_DISABLE_BAG
	return

DungeonEden_Act1_Battle1_Fork_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_0, 0, DungeonEden_Act1_Battle1_Fork_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0
	.2byte 0

DungeonEden_Act1_Battle1_Fork_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0:
	lock
	applymovement OBJ_EVENT_ID_PLAYER, Common_UpOne
	waitmovement 0
	msgbox DungeonEden_Act1_Battle1_Fork_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0
	setvar VAR_TEMP_0, 1
	release
	return


DungeonEden_Act1_Battle1_Fork_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0:
	.string "The forest is too thick to turn back\p"
	.string "...\p"
	.string "There seems to be a trainer waiting on\n"
	.string "the bridge.$"
