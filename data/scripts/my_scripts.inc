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


Common_MoveRelearner::
	lock
	faceplayer
	msgbox Common_MoveRelearner_Text_0
	checkitem ITEM_HEART_SCALE
	compare VAR_RESULT, TRUE
	goto_if_eq Common_MoveRelearner_2
Common_MoveRelearner_1:
	msgbox Common_MoveRelearner_Text_6
	release
	end

Common_MoveRelearner_2:
	msgbox Common_MoveRelearner_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Common_MoveRelearner_4
	goto Common_MoveRelearner_1

Common_MoveRelearner_4:
Common_MoveRelearner_6:
	msgbox Common_MoveRelearner_Text_2
	special ChooseMonForMoveRelearner
	waitstate
	compare VAR_0x8004, PARTY_NOTHING_CHOSEN
	goto_if_eq Common_MoveRelearner_9
	special IsSelectedMonEgg
	compare VAR_RESULT, TRUE
	goto_if_eq Common_MoveRelearner_12
	compare VAR_0x8005, 0
	goto_if_eq Common_MoveRelearner_12
	msgbox Common_MoveRelearner_Text_4
	special TeachMoveRelearnerMove
	waitstate
	compare VAR_0x8004, 0
	goto_if_eq Common_MoveRelearner_17
	msgbox Common_MoveRelearner_Text_5
	removeitem ITEM_HEART_SCALE
	goto Common_MoveRelearner_1

Common_MoveRelearner_9:
	goto Common_MoveRelearner_1

Common_MoveRelearner_12:
	msgbox Common_MoveRelearner_Text_3
	goto Common_MoveRelearner_6

Common_MoveRelearner_17:
	goto Common_MoveRelearner_6


Common_GiveHeartScale::
	giveitem ITEM_HEART_SCALE
	setflag FLAG_TEMP_A
	end


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

Common_MoveRelearner_Text_0:
	.string "I'm the Move Relearner! I can teach a\n"
	.string "move to a Pokémon for a Heart Scale.$"

Common_MoveRelearner_Text_1:
	.string "Looks like you have a Heart Scale! Would\n"
	.string "you like me to teach a move?$"

Common_MoveRelearner_Text_2:
	.string "Which Pokémon needs tutoring?$"

Common_MoveRelearner_Text_3:
	.string "Unfortunately, I cannot teach that\n"
	.string "Pokémon any moves.$"

Common_MoveRelearner_Text_4:
	.string "Which move should I teach?$"

Common_MoveRelearner_Text_5:
	.string "{PLAYER} handed over one Heart Scale\n"
	.string "in exchange$"

Common_MoveRelearner_Text_6:
	.string "If your Pokémon need to learn a move,\n"
	.string "come back with a Heart Scale.$"
