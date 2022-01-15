DungeonEden_Act1_Gift1_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DungeonEden_Act1_Gift1_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DungeonEden_Act1_Gift1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DungeonEden_Act1_Gift1_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setvar VAR_TEMP_0, 0
	setvar VAR_TEMP_A, 0
	callnative DungeonEden_GetGiftMon
	return

DungeonEden_Act1_Gift1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_0, 0, DungeonEden_Act1_Gift1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0
	.2byte 0

DungeonEden_Act1_Gift1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0:
	lock
	applymovement OBJ_EVENT_ID_PLAYER, Common_UpOne
	waitmovement 0
	msgbox DungeonEden_Act1_Gift1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0
	setvar VAR_TEMP_0, 1
	release
	return


Eden_A1_Gift1_GiftBall1::
	showmonpic VAR_0x8001, 10, 3
	compare VAR_TEMP_A, 1
	goto_if_eq Eden_A1_Gift1_GiftBall1_2
	bufferspeciesname STR_VAR_1, VAR_0x8001
	msgbox Eden_A1_Gift1_GiftBall1_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Eden_A1_Gift1_GiftBall1_5
Eden_A1_Gift1_GiftBall1_1:
	hidemonpic
	releaseall
	end

Eden_A1_Gift1_GiftBall1_2:
	msgbox Eden_A1_Gift1_GiftBall1_Text_0
	goto Eden_A1_Gift1_GiftBall1_1

Eden_A1_Gift1_GiftBall1_5:
	givemon VAR_0x8001, 0, ITEM_NONE
	removeobject 1
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Eden_A1_Gift1_GiftBall1_8
Eden_A1_Gift1_GiftBall1_7:
	setvar VAR_TEMP_A, 1
	goto Eden_A1_Gift1_GiftBall1_1

Eden_A1_Gift1_GiftBall1_8:
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto Eden_A1_Gift1_GiftBall1_7


Eden_A1_Gift1_GiftBall2::
	showmonpic VAR_0x8002, 10, 3
	compare VAR_TEMP_A, 1
	goto_if_eq Eden_A1_Gift1_GiftBall2_2
	bufferspeciesname STR_VAR_1, VAR_0x8002
	msgbox Eden_A1_Gift1_GiftBall1_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Eden_A1_Gift1_GiftBall2_5
Eden_A1_Gift1_GiftBall2_1:
	hidemonpic
	releaseall
	end

Eden_A1_Gift1_GiftBall2_2:
	msgbox Eden_A1_Gift1_GiftBall1_Text_0
	goto Eden_A1_Gift1_GiftBall2_1

Eden_A1_Gift1_GiftBall2_5:
	givemon VAR_0x8002, 0, ITEM_NONE
	removeobject 2
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Eden_A1_Gift1_GiftBall2_8
Eden_A1_Gift1_GiftBall2_7:
	setvar VAR_TEMP_A, 1
	goto Eden_A1_Gift1_GiftBall2_1

Eden_A1_Gift1_GiftBall2_8:
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto Eden_A1_Gift1_GiftBall2_7


Eden_A1_Gift1_GiftBall3::
	showmonpic VAR_0x8003, 10, 3
	compare VAR_TEMP_A, 1
	goto_if_eq Eden_A1_Gift1_GiftBall3_2
	bufferspeciesname STR_VAR_1, VAR_0x8003
	msgbox Eden_A1_Gift1_GiftBall1_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Eden_A1_Gift1_GiftBall3_5
Eden_A1_Gift1_GiftBall3_1:
	hidemonpic
	releaseall
	end

Eden_A1_Gift1_GiftBall3_2:
	msgbox Eden_A1_Gift1_GiftBall1_Text_0
	goto Eden_A1_Gift1_GiftBall3_1

Eden_A1_Gift1_GiftBall3_5:
	givemon VAR_0x8003, 0, ITEM_NONE
	removeobject 3
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Eden_A1_Gift1_GiftBall3_8
Eden_A1_Gift1_GiftBall3_7:
	setvar VAR_TEMP_A, 1
	goto Eden_A1_Gift1_GiftBall3_1

Eden_A1_Gift1_GiftBall3_8:
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto Eden_A1_Gift1_GiftBall3_7


DungeonEden_Act1_Gift1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0:
	.string "The forest is too thick to turn back.\p"
	.string "...\p"
	.string "There seem to be some Pokéballs out in\n"
	.string "the open.$"

Eden_A1_Gift1_GiftBall1_Text_0:
	.string "It would be greedy to take another\n"
	.string "Pokémon.$"

Eden_A1_Gift1_GiftBall1_Text_1:
	.string "Will you take {STR_VAR_1}?$"
