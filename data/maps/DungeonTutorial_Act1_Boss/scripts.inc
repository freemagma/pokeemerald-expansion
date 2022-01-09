DungeonTutorial_Act1_Boss_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DungeonTutorial_Act1_Boss_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DungeonTutorial_Act1_Boss_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DungeonTutorial_Act1_Boss_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setvar VAR_TEMP_0, 0
	callnative DungeonTutorial_GenerateBossBattle
	copyvar VAR_TEMP_A, VAR_0x8000
	return

DungeonTutorial_Act1_Boss_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_0, 0, DungeonTutorial_Act1_Boss_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0
	.2byte 0

DungeonTutorial_Act1_Boss_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0:
	lock
	applymovement OBJ_EVENT_ID_PLAYER, Common_UpOne
	waitmovement 0
	msgbox DungeonTutorial_Act1_Boss_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0
	setvar VAR_TEMP_0, 1
	release
	return


DungeonTutorial_Act1_Boss_Trainer::
	trainerbattle_single VAR_TEMP_A, DungeonTutorial_Act1_Boss_Trainer_Text_0, DungeonTutorial_Act1_Boss_Trainer_Text_1
	msgbox DungeonTutorial_Act1_Boss_Trainer_Text_2
	return


DungeonTutorial_Act1_Boss_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0:
	.string "The room behind you collapsed!\p"
	.string "...\p"
	.string "A fierce enemy awaits.$"

DungeonTutorial_Act1_Boss_Trainer_Text_0:
	.string "...$"

DungeonTutorial_Act1_Boss_Trainer_Text_1:
	.string "Hmph.$"

DungeonTutorial_Act1_Boss_Trainer_Text_2:
	.string "You may pass.$"
