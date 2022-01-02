Intro_Battle1_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Intro_Battle1_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Intro_Battle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

Intro_Battle1_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setvar VAR_TEMP_0, 0
	callnative GenerateBattleIntro
	copyvar VAR_TEMP_A, VAR_0x8000
	return

Intro_Battle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_0, 0, Intro_Battle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0
	.2byte 0

Intro_Battle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0:
	lock
	applymovement OBJ_EVENT_ID_PLAYER, Intro_Gift1_UpOne
	waitmovement 0
	msgbox Intro_Battle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0
	setvar VAR_TEMP_0, 1
	release
	return


Intro_Battle1_Trainer::
	trainerbattle_single VAR_TEMP_A, Intro_Battle1_Trainer_Text_0, Intro_Battle1_Trainer_Text_1
	msgbox Intro_Battle1_Trainer_Text_2, MSGBOX_AUTOCLOSE
	return


Intro_Battle1_SignDirections::
	lockall
	msgbox Intro_Battle1_SignDirections_Text_0
	releaseall
	return


Intro_Battle1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0:
	.string "The room behind you collapsed!\p"
	.string "...\p"
	.string "There seems to be a trainer in this\n"
	.string "room.$"

Intro_Battle1_Trainer_Text_0:
	.string "HELLO$"

Intro_Battle1_Trainer_Text_1:
	.string "DEFEAT$"

Intro_Battle1_Trainer_Text_2:
	.string "POST BATTLE$"

Intro_Battle1_SignDirections_Text_0:
	.string "In battle rooms, you will have to face\n"
	.string "an opposing trainer.\p"
	.string "You'll recieve some rewards after you\n"
	.string "win!$"
