DungeonTutorial_Act1_Battle1_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DungeonTutorial_Act1_Battle1_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DungeonTutorial_Act1_Battle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DungeonTutorial_Act1_Battle1_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setvar VAR_TEMP_0, 0
	callnative DungeonTutorial_GenerateBattle
	copyvar VAR_TEMP_A, VAR_0x8000
	setflag FLAG_DISABLE_BAG
	return

DungeonTutorial_Act1_Battle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_0, 0, DungeonTutorial_Act1_Battle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0
	.2byte 0

DungeonTutorial_Act1_Battle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0:
	lock
	applymovement OBJ_EVENT_ID_PLAYER, Common_UpOne
	waitmovement 0
	msgbox DungeonTutorial_Act1_Battle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0
	setvar VAR_TEMP_0, 1
	release
	return


DungeonTutorial_Act1_Battle1_Trainer::
	trainerbattle_single VAR_TEMP_A, DungeonTutorial_Act1_Battle1_Trainer_Text_0, DungeonTutorial_Act1_Battle1_Trainer_Text_1
	msgbox DungeonTutorial_Act1_Battle1_Trainer_Text_2, MSGBOX_AUTOCLOSE
	return


DungeonTutorial_Act1_Battle1_SignDirections::
	lock
	callnative BufferTrainerName
	msgbox DungeonTutorial_Act1_Battle1_SignDirections_Text_0, MSGBOX_SIGN
	release
	return


DungeonTutorial_Act1_Battle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0:
	.string "The room behind you collapsed!\p"
	.string "...\p"
	.string "There seems to be a trainer in this\n"
	.string "room.$"

DungeonTutorial_Act1_Battle1_Trainer_Text_0:
	.string "I challenge you to a battle!$"

DungeonTutorial_Act1_Battle1_Trainer_Text_1:
	.string "Guess I need to get stronger.$"

DungeonTutorial_Act1_Battle1_Trainer_Text_2:
	.string "...$"

DungeonTutorial_Act1_Battle1_SignDirections_Text_0:
	.string "In battle rooms, you will have to face\n"
	.string "an opposing trainer.\p"
	.string "You'll recieve some money after you win!\p"
	.string "{STR_VAR_1} {STR_VAR_2} will be\n"
	.string "your opponent in this room.$"
