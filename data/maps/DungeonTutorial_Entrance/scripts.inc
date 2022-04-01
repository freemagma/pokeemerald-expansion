DungeonTutorial_Entrance_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DungeonTutorial_Entrance_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

DungeonTutorial_Entrance_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	callnative DungeonTutorial_GenerateRoute
	additem ITEM_MAX_POTION, 3
	additem ITEM_RARE_CANDY, 5
	additem ITEM_FULL_HEAL, 2
	additem ITEM_POKE_BALL, 20
	addmoney 500
	setvar VAR_LEVEL_SCALE, 12
	setvar VAR_EXP_MULTIPLIER_NUMERATOR, 5
	setvar VAR_EXP_MULTIPLIER_DENOMINATOR, 1
	setvar VAR_GIFT_LEVEL_DIFF, 2
	return


StarterBall::
	showmonpic SPECIES_DIGLETT, 10, 3
	msgbox StarterBall_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq StarterBall_2
StarterBall_1:
	hidemonpic
	releaseall
	end

StarterBall_2:
	bufferspeciesname STR_VAR_1, SPECIES_DIGLETT
	givemon SPECIES_DIGLETT, 12, ITEM_NONE
	removeobject 1
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq StarterBall_5
StarterBall_4:
	setflag FLAG_SYS_POKEMON_GET
	goto StarterBall_1

StarterBall_5:
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto StarterBall_4


StarterBall_Text_0:
	.string "Will you take Diglet?$"
