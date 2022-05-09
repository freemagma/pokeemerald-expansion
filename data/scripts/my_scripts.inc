Common_UpOne:
	walk_up
	step_end

Common_UpTwo:
	walk_up
	walk_up
	step_end

Common_RoutingSign::
	lock
	callnative BufferRouteText
	msgbox Common_RoutingSign_Text_0, MSGBOX_SIGN
	release
	return


Common_TrainerNameSign::
	lock
	callnative BufferTrainerName
	msgbox Common_TrainerNameSign_Text_0, MSGBOX_SIGN
	release
	return


Common_GiftBall1::
	showmonpic VAR_0x8001, 10, 3
	compare VAR_TEMP_A, 1
	goto_if_eq Common_GiftBall1_2
	bufferspeciesname STR_VAR_1, VAR_0x8001
	msgbox Common_GiftBall1_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Common_GiftBall1_5
Common_GiftBall1_1:
	hidemonpic
	releaseall
	end

Common_GiftBall1_2:
	msgbox Common_GiftBall1_Text_0
	goto Common_GiftBall1_1

Common_GiftBall1_5:
	givemon VAR_0x8001, 0, ITEM_NONE
	removeobject 1
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Common_GiftBall1_8
Common_GiftBall1_7:
	setvar VAR_TEMP_A, 1
	goto Common_GiftBall1_1

Common_GiftBall1_8:
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto Common_GiftBall1_7


Common_GiftBall2::
	showmonpic VAR_0x8002, 10, 3
	compare VAR_TEMP_A, 1
	goto_if_eq Common_GiftBall2_2
	bufferspeciesname STR_VAR_1, VAR_0x8002
	msgbox Common_GiftBall1_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Common_GiftBall2_5
Common_GiftBall2_1:
	hidemonpic
	releaseall
	end

Common_GiftBall2_2:
	msgbox Common_GiftBall1_Text_0
	goto Common_GiftBall2_1

Common_GiftBall2_5:
	givemon VAR_0x8002, 0, ITEM_NONE
	removeobject 2
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Common_GiftBall2_8
Common_GiftBall2_7:
	setvar VAR_TEMP_A, 1
	goto Common_GiftBall2_1

Common_GiftBall2_8:
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto Common_GiftBall2_7


Common_GiftBall3::
	showmonpic VAR_0x8003, 10, 3
	compare VAR_TEMP_A, 1
	goto_if_eq Common_GiftBall3_2
	bufferspeciesname STR_VAR_1, VAR_0x8003
	msgbox Common_GiftBall1_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Common_GiftBall3_5
Common_GiftBall3_1:
	hidemonpic
	releaseall
	end

Common_GiftBall3_2:
	msgbox Common_GiftBall1_Text_0
	goto Common_GiftBall3_1

Common_GiftBall3_5:
	givemon VAR_0x8003, 0, ITEM_NONE
	removeobject 3
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Common_GiftBall3_8
Common_GiftBall3_7:
	setvar VAR_TEMP_A, 1
	goto Common_GiftBall3_1

Common_GiftBall3_8:
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto Common_GiftBall3_7


Common_RoutingSign_Text_0:
	.string "{LEFT_ARROW} {STR_VAR_1} Room\n"
	.string "{RIGHT_ARROW} {STR_VAR_2} Room$"

Common_TrainerNameSign_Text_0:
	.string "{STR_VAR_1} {STR_VAR_2}$"

Common_GiftBall1_Text_0:
	.string "It would be greedy to take another\n"
	.string "Pokémon.$"

Common_GiftBall1_Text_1:
	.string "Will you take {STR_VAR_1}?$"
