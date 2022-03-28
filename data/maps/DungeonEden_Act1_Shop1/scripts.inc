DungeonEden_Act1_Shop1_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DungeonEden_Act1_Shop1_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DungeonEden_Act1_Shop1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DungeonEden_Act1_Shop1_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	genrandomshop 1
	setvar VAR_TEMP_0, 0
	return

DungeonEden_Act1_Shop1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_0, 0, DungeonEden_Act1_Shop1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0
	.2byte 0

DungeonEden_Act1_Shop1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0:
	lock
	applymovement OBJ_EVENT_ID_PLAYER, Common_UpOne
	waitmovement 0
	msgbox DungeonEden_Act1_Shop1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0
	setvar VAR_TEMP_0, 1
	release
	return


Eden_A1_Shop1_FixedMerchant::
	lock
	faceplayer
	message Eden_A1_Shop1_FixedMerchant_Text_0
	waitmessage
	fixedshop 0
	msgbox Eden_A1_Shop1_FixedMerchant_Text_1
	release
	return


Eden_A1_Shop1_RandomMerchant::
	lock
	faceplayer
	message Eden_A1_Shop1_RandomMerchant_Text_0
	waitmessage
	randomshop
	msgbox Eden_A1_Shop1_RandomMerchant_Text_1
	release
	return


DungeonEden_Act1_Shop1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0:
	.string "The forest is too thick to turn back.\p"
	.string "...\p"
	.string "Two merchants seem to have taken up\n"
	.string "shop here.$"

Eden_A1_Shop1_FixedMerchant_Text_0:
	.string "Welcome to my humble store. I hope my\n"
	.string "wares can be of use.$"

Eden_A1_Shop1_FixedMerchant_Text_1:
	.string "Just let me know if you need anything\n"
	.string "else.$"

Eden_A1_Shop1_RandomMerchant_Text_0:
	.string "Let me know if one of my knick-knacks\n"
	.string "catches your eye.$"

Eden_A1_Shop1_RandomMerchant_Text_1:
	.string "I'll be here if you decide you want\n"
	.string "something more.$"
