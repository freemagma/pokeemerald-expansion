DungeonEden_Act1_Entrance_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DungeonEden_Act1_Entrance_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

DungeonEden_Act1_Entrance_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	callnative DungeonEden_GenerateRoute
	additem ITEM_MAX_POTION, 6
	additem ITEM_RARE_CANDY, 8
	additem ITEM_FULL_HEAL, 2
	additem ITEM_POKE_BALL, 20
	addmoney 500
	setvar VAR_LEVEL_SCALE, 5
	setvar VAR_EXP_MULTIPLIER_NUMERATOR, 3
	setvar VAR_EXP_MULTIPLIER_DENOMINATOR, 2
	setvar VAR_GIFT_LEVEL_DIFF, 0
	return


Eden_StarterBall::
	showmonpic SPECIES_APPLIN, 10, 3
	msgbox Eden_StarterBall_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Eden_StarterBall_2
Eden_StarterBall_1:
	hidemonpic
	releaseall
	end

Eden_StarterBall_2:
	bufferspeciesname STR_VAR_1, SPECIES_APPLIN
	givemon SPECIES_APPLIN, 5, ITEM_NONE
	removeobject 1
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Eden_StarterBall_5
Eden_StarterBall_4:
	setflag FLAG_SYS_POKEMON_GET
	goto Eden_StarterBall_1

Eden_StarterBall_5:
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto Eden_StarterBall_4


Eden_StarterBall_Text_0:
	.string "Will you take Applin?$"
