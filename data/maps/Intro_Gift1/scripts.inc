Intro_Gift1_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Intro_Gift1_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Intro_Gift1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

Intro_Gift1_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setvar VAR_TEMP_0, 0
	setvar VAR_TEMP_1, 0
	return

Intro_Gift1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_0, 0, Intro_Gift1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0
	.2byte 0

Intro_Gift1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0:
	lock
	applymovement OBJ_EVENT_ID_PLAYER, Intro_Gift1_UpOne
	waitmovement 0
	msgbox Intro_Gift1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0
	giveitem ITEM_RARE_CANDY, 3
	giveitem ITEM_POTION, 1
	setvar VAR_TEMP_0, 1
	release
	return


Intro_Gift1_GiftBall1::
	showmonpic SPECIES_MAKUHITA, 10, 3
	compare VAR_TEMP_1, 1
	goto_if_eq Intro_Gift1_GiftBall1_2
	msgbox Intro_Gift1_GiftBall1_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Intro_Gift1_GiftBall1_5
Intro_Gift1_GiftBall1_1:
	hidemonpic
	releaseall
	end

Intro_Gift1_GiftBall1_2:
	msgbox Intro_Gift1_GiftBall1_Text_0
	goto Intro_Gift1_GiftBall1_1

Intro_Gift1_GiftBall1_5:
	bufferspeciesname STR_VAR_1, SPECIES_MAKUHITA
	givemon SPECIES_MAKUHITA, 5, ITEM_NONE
	removeobject 1
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Intro_Gift1_GiftBall1_8
Intro_Gift1_GiftBall1_7:
	setvar VAR_TEMP_1, 1
	goto Intro_Gift1_GiftBall1_1

Intro_Gift1_GiftBall1_8:
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto Intro_Gift1_GiftBall1_7


Intro_Gift1_GiftBall2::
	showmonpic SPECIES_STUNKY, 10, 3
	compare VAR_TEMP_1, 1
	goto_if_eq Intro_Gift1_GiftBall2_2
	msgbox Intro_Gift1_GiftBall2_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Intro_Gift1_GiftBall2_5
Intro_Gift1_GiftBall2_1:
	hidemonpic
	releaseall
	end

Intro_Gift1_GiftBall2_2:
	msgbox Intro_Gift1_GiftBall1_Text_0
	goto Intro_Gift1_GiftBall2_1

Intro_Gift1_GiftBall2_5:
	bufferspeciesname STR_VAR_1, SPECIES_STUNKY
	givemon SPECIES_STUNKY, 5, ITEM_NONE
	removeobject 2
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Intro_Gift1_GiftBall2_8
Intro_Gift1_GiftBall2_7:
	setvar VAR_TEMP_1, 1
	goto Intro_Gift1_GiftBall2_1

Intro_Gift1_GiftBall2_8:
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto Intro_Gift1_GiftBall2_7


Intro_Gift1_GiftBall3::
	showmonpic SPECIES_ELECTRIKE, 10, 3
	compare VAR_TEMP_1, 1
	goto_if_eq Intro_Gift1_GiftBall3_2
	msgbox Intro_Gift1_GiftBall3_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Intro_Gift1_GiftBall3_5
Intro_Gift1_GiftBall3_1:
	hidemonpic
	releaseall
	end

Intro_Gift1_GiftBall3_2:
	msgbox Intro_Gift1_GiftBall1_Text_0
	goto Intro_Gift1_GiftBall3_1

Intro_Gift1_GiftBall3_5:
	bufferspeciesname STR_VAR_1, SPECIES_ELECTRIKE
	givemon SPECIES_ELECTRIKE, 5, ITEM_NONE
	removeobject 3
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Intro_Gift1_GiftBall3_8
Intro_Gift1_GiftBall3_7:
	setvar VAR_TEMP_1, 1
	goto Intro_Gift1_GiftBall3_1

Intro_Gift1_GiftBall3_8:
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto Intro_Gift1_GiftBall3_7


Intro_Gift1_SignDirections::
	lockall
	msgbox Intro_Gift1_SignDirections_Text_0
	releaseall
	return


Intro_Gift1_UpOne:
	walk_up
	step_end

Intro_Gift1_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0:
	.string "The room behind you collapsed!\p"
	.string "...\p"
	.string "There seem to be some Pokéballs out in\n"
	.string "the open.$"

Intro_Gift1_GiftBall1_Text_0:
	.string "It would be greedy to take another\n"
	.string "Pokémon.$"

Intro_Gift1_GiftBall1_Text_1:
	.string "Will you take Makuhita?$"

Intro_Gift1_GiftBall2_Text_0:
	.string "Will you take Stunky?$"

Intro_Gift1_GiftBall3_Text_0:
	.string "Will you take Electrike?$"

Intro_Gift1_SignDirections_Text_0:
	.string "In gift rooms, you will be given some\n"
	.string "free Pokémon to choose from.\p"
	.string "It's that simple!$"
