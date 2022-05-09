DungeonEden_Act2_EliteBattle1_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DungeonEden_Act2_EliteBattle1_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DungeonEden_Act2_EliteBattle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DungeonEden_Act2_EliteBattle1_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setvar VAR_TEMP_0, 0
	callnative DungeonEden_Act2_GenerateEliteBattle
	copyvar VAR_TEMP_A, VAR_0x8000
	setflag FLAG_DISABLE_BAG
	return

DungeonEden_Act2_EliteBattle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_0, 0, DungeonEden_Act2_EliteBattle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0
	.2byte 0

DungeonEden_Act2_EliteBattle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0:
	lock
	applymovement OBJ_EVENT_ID_PLAYER, Common_UpTwo
	waitmovement 0
	msgbox DungeonEden_Act2_EliteBattle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0
	setvar VAR_TEMP_0, 1
	release
	return


Eden_A2_EliteBattle1_Trainer::
	trainerbattle_single VAR_TEMP_A, Eden_A2_EliteBattle1_Trainer_Text_0, Eden_A2_EliteBattle1_Trainer_Text_1
	msgbox Eden_A2_EliteBattle1_Trainer_Text_2, MSGBOX_AUTOCLOSE
	return


DungeonEden_Act2_EliteBattle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0:
	.string "The snow and ice are much too cold to\n"
	.string "stand on!$"

Eden_A2_EliteBattle1_Trainer_Text_0:
	.string "Nobody's gotten past me yet, and you\n"
	.string "won't be the first.$"

Eden_A2_EliteBattle1_Trainer_Text_1:
	.string "How the hell are you so strong?$"

Eden_A2_EliteBattle1_Trainer_Text_2:
	.string "...$"
