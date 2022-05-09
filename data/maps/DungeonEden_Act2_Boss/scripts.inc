DungeonEden_Act2_Boss_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DungeonEden_Act2_Boss_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DungeonEden_Act2_Boss_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DungeonEden_Act2_Boss_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setvar VAR_TEMP_0, 0
	callnative DungeonEden_Act2_GenerateBossBattle
	copyvar VAR_TEMP_A, VAR_0x8000
	setflag FLAG_DISABLE_BAG
	return

DungeonEden_Act2_Boss_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_0, 0, DungeonEden_Act2_Boss_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0
	.2byte 0

DungeonEden_Act2_Boss_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0:
	lock
	applymovement OBJ_EVENT_ID_PLAYER, Common_UpTwo
	waitmovement 0
	msgbox DungeonEden_Act2_Boss_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0
	setvar VAR_TEMP_0, 1
	release
	return


Eden_A2_Boss_Trainer::
	trainerbattle_single VAR_TEMP_A, Eden_A2_Boss_Trainer_Text_0, Eden_A2_Boss_Trainer_Text_1, Common_GiveHeartScale
	goto_if_unset FLAG_TEMP_A, Eden_A2_Boss_Trainer_2
Eden_A2_Boss_Trainer_1:
	msgbox Eden_A2_Boss_Trainer_Text_2, MSGBOX_AUTOCLOSE
	return

Eden_A2_Boss_Trainer_2:
	call Common_GiveHeartScale
	goto Eden_A2_Boss_Trainer_1


DungeonEden_Act2_Boss_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0:
	.string "It seems like you'll have to brave the\n"
	.string "ice in order to continue.$"

Eden_A2_Boss_Trainer_Text_0:
	.string "...$"

Eden_A2_Boss_Trainer_Text_1:
	.string "Hmph.$"

Eden_A2_Boss_Trainer_Text_2:
	.string "You may pass.$"
