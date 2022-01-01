Entrance_MapScripts::
	.byte 0


StarterBall1::
	showmonpic SPECIES_BULBASAUR, 10, 3
	compare VAR_INTRO_STATE, 0
	goto_if_ne StarterBall1_2
	msgbox StarterBall1_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq StarterBall1_5
StarterBall1_1:
	hidemonpic
	releaseall
	end

StarterBall1_2:
	msgbox StarterBall1_Text_0
	goto StarterBall1_1

StarterBall1_5:
	bufferspeciesname STR_VAR_1, SPECIES_BULBASAUR
	givemon SPECIES_BULBASAUR, 5, ITEM_NONE
	removeobject 1
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq StarterBall1_8
StarterBall1_7:
	setvar VAR_STARTER_MON, 0
	setvar VAR_INTRO_STATE, 1
	setflag FLAG_SYS_POKEMON_GET
	goto StarterBall1_1

StarterBall1_8:
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto StarterBall1_7


StarterBall2::
	showmonpic SPECIES_CHIMCHAR, 10, 3
	compare VAR_INTRO_STATE, 0
	goto_if_ne StarterBall2_2
	msgbox StarterBall2_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq StarterBall2_5
StarterBall2_1:
	hidemonpic
	releaseall
	end

StarterBall2_2:
	msgbox StarterBall1_Text_0
	goto StarterBall2_1

StarterBall2_5:
	bufferspeciesname STR_VAR_1, SPECIES_CHIMCHAR
	givemon SPECIES_CHIMCHAR, 5, ITEM_NONE
	removeobject 2
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq StarterBall2_8
StarterBall2_7:
	setvar VAR_STARTER_MON, 1
	setvar VAR_INTRO_STATE, 1
	setflag FLAG_SYS_POKEMON_GET
	goto StarterBall2_1

StarterBall2_8:
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto StarterBall2_7


StarterBall3::
	showmonpic SPECIES_FROAKIE, 10, 3
	compare VAR_INTRO_STATE, 0
	goto_if_ne StarterBall3_2
	msgbox StarterBall3_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq StarterBall3_5
StarterBall3_1:
	hidemonpic
	releaseall
	end

StarterBall3_2:
	msgbox StarterBall1_Text_0
	goto StarterBall3_1

StarterBall3_5:
	bufferspeciesname STR_VAR_1, SPECIES_FROAKIE
	givemon SPECIES_FROAKIE, 5, ITEM_NONE
	removeobject 3
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq StarterBall3_8
StarterBall3_7:
	setvar VAR_STARTER_MON, 2
	setvar VAR_INTRO_STATE, 1
	setflag FLAG_SYS_POKEMON_GET
	goto StarterBall3_1

StarterBall3_8:
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto StarterBall3_7


StarterBall1_Text_0:
	.string "It would be greedy to take another\n"
	.string "Pokémon.$"

StarterBall1_Text_1:
	.string "Will you take Bulbasaur?$"

StarterBall2_Text_0:
	.string "Will you take Chimchar?$"

StarterBall3_Text_0:
	.string "Will you take Froakie?$"
