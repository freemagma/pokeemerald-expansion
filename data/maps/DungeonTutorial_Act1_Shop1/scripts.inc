DungeonTutorial_Act1_Shop1_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DungeonTutorial_Act1_Shop1_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DungeonTutorial_Act1_Shop1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DungeonTutorial_Act1_Shop1_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	genrandomshop 0
	setvar VAR_TEMP_0, 0
	return

DungeonTutorial_Act1_Shop1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_0, 0, DungeonTutorial_Act1_Shop1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0
	.2byte 0

DungeonTutorial_Act1_Shop1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0:
	lock
	applymovement OBJ_EVENT_ID_PLAYER, Intro_Gift1_UpOne
	waitmovement 0
	msgbox DungeonTutorial_Act1_Shop1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0
	setvar VAR_TEMP_0, 1
	release
	return


DTutorial_A1_Shop1_Sign::
	lockall
	msgbox DTutorial_A1_Shop1_Sign_Text_0
	releaseall
	return


DTutorial_A1_Shop1_FixedMerchant::
	lock
	faceplayer
	message DTutorial_A1_Shop1_FixedMerchant_Text_0
	waitmessage
	fixedshop 0
	msgbox DTutorial_A1_Shop1_FixedMerchant_Text_1
	release
	return


DTutorial_A1_Shop1_RandomMerchant::
	lock
	faceplayer
	message DTutorial_A1_Shop1_RandomMerchant_Text_0
	waitmessage
	randomshop
	msgbox DTutorial_A1_Shop1_RandomMerchant_Text_1
	release
	return


DungeonTutorial_Act1_Shop1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0:
	.string "The room behind you collapsed!\p"
	.string "...\p"
	.string "Two merchants seem to have taken up\n"
	.string "shop here.$"

DTutorial_A1_Shop1_Sign_Text_0:
	.string "In shop rooms, there will be merchants\n"
	.string "selling an assortment of items.\p"
	.string "One merchant will always sell the same\n"
	.string "basic items, while another will have a\l"
	.string "random selection of stronger ones.$"

DTutorial_A1_Shop1_FixedMerchant_Text_0:
	.string "Welcome to my humble store. I hope my\n"
	.string "wares can be of use.$"

DTutorial_A1_Shop1_FixedMerchant_Text_1:
	.string "Just let me know if you need anything\n"
	.string "else.$"

DTutorial_A1_Shop1_RandomMerchant_Text_0:
	.string "Let me know if one of my knick-knacks\n"
	.string "catches your eye.$"

DTutorial_A1_Shop1_RandomMerchant_Text_1:
	.string "I'll be here if you decide you want\n"
	.string "something more.$"
