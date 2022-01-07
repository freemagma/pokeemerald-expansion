DungeonTutorial_Entrance_MapScripts::
	.byte 0


StarterBall::
	showmonpic SPECIES_DIGLETT, 10, 3
	compare VAR_INTRO_STATE, 0
	goto_if_ne StarterBall_2
	msgbox StarterBall_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq StarterBall_5
StarterBall_1:
	hidemonpic
	releaseall
	end

StarterBall_2:
	msgbox StarterBall_Text_0
	goto StarterBall_1

StarterBall_5:
	bufferspeciesname STR_VAR_1, SPECIES_DIGLETT
	givemon SPECIES_DIGLETT, 5, ITEM_NONE
	removeobject 1
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq StarterBall_8
StarterBall_7:
	setvar VAR_INTRO_STATE, 1
	setflag FLAG_SYS_POKEMON_GET
	goto StarterBall_1

StarterBall_8:
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto StarterBall_7


StarterBall_Text_0:
	.string "It would be greedy to take another\n"
	.string "Pokémon.$"

StarterBall_Text_1:
	.string "Will you take Diglet?$"
