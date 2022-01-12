DungeonTutorial_Act1_EliteBattle1_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DungeonTutorial_Act1_EliteBattle1_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DungeonTutorial_Act1_EliteBattle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DungeonTutorial_Act1_EliteBattle1_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setvar VAR_TEMP_0, 0
	callnative DungeonTutorial_GenerateEliteBattle
	copyvar VAR_TEMP_A, VAR_0x8000
	setflag FLAG_DISABLE_BAG
	return

DungeonTutorial_Act1_EliteBattle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_0, 0, DungeonTutorial_Act1_EliteBattle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0
	.2byte 0

DungeonTutorial_Act1_EliteBattle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0:
	lock
	applymovement OBJ_EVENT_ID_PLAYER, Common_UpOne
	waitmovement 0
	msgbox DungeonTutorial_Act1_EliteBattle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0
	setvar VAR_TEMP_0, 1
	release
	return


DungeonTutorial_Act1_EliteBattle1_Trainer::
	trainerbattle_single VAR_TEMP_A, DungeonTutorial_Act1_EliteBattle1_Trainer_Text_0, DungeonTutorial_Act1_EliteBattle1_Trainer_Text_1
	msgbox DungeonTutorial_Act1_EliteBattle1_Trainer_Text_2, MSGBOX_AUTOCLOSE
	return


DungeonTutorial_Act1_EliteBattle1_SignDirections::
	lock
	msgbox DungeonTutorial_Act1_EliteBattle1_SignDirections_Text_0, MSGBOX_SIGN
	release
	return


DungeonTutorial_Act1_EliteBattle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0:
	.string "The room behind you collapsed!\p"
	.string "...\p"
	.string "There seems to be a powerful trainer in\n"
	.string "this room.$"

DungeonTutorial_Act1_EliteBattle1_Trainer_Text_0:
	.string "Nobody's gotten past me yet, and you\n"
	.string "won't be the first.$"

DungeonTutorial_Act1_EliteBattle1_Trainer_Text_1:
	.string "How the hell are you so strong?$"

DungeonTutorial_Act1_EliteBattle1_Trainer_Text_2:
	.string "...$"

DungeonTutorial_Act1_EliteBattle1_SignDirections_Text_0:
	.string "In Elite battle rooms, you'll face a\n"
	.string "tough opponent.\p"
	.string "If you win, you'll receive a greater\n"
	.string "prize than usual.$"
