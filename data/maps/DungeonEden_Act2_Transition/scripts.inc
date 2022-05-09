DungeonEden_Act2_Transition_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DungeonEden_Act2_Transition_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DungeonEden_Act2_Transition_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

DungeonEden_Act2_Transition_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setvar VAR_TEMP_0, 0
	return

DungeonEden_Act2_Transition_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_0, 0, DungeonEden_Act2_Transition_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0
	.2byte 0

DungeonEden_Act2_Transition_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0:
	lock
	applymovement OBJ_EVENT_ID_PLAYER, Common_UpOne
	waitmovement 0
	msgbox DungeonEden_Act2_Transition_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0
	setvar VAR_TEMP_0, 1
	release
	return


Eden_A2_Dawn_Stone::
	compare VAR_TEMP_A, 1
	goto_if_eq Eden_A2_Dawn_Stone_2
	msgbox Eden_A2_Dawn_Stone_Text_1, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Eden_A2_Dawn_Stone_5
Eden_A2_Dawn_Stone_1:
	releaseall
	end

Eden_A2_Dawn_Stone_2:
	msgbox Eden_A2_Dawn_Stone_Text_0
	goto Eden_A2_Dawn_Stone_1

Eden_A2_Dawn_Stone_5:
	finditem ITEM_DAWN_STONE
	setvar VAR_TEMP_A, 1
	goto Eden_A2_Dawn_Stone_1


Eden_A2_Dusk_Stone::
	compare VAR_TEMP_A, 1
	goto_if_eq Eden_A2_Dusk_Stone_2
	msgbox Eden_A2_Dusk_Stone_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Eden_A2_Dusk_Stone_5
Eden_A2_Dusk_Stone_1:
	releaseall
	end

Eden_A2_Dusk_Stone_2:
	msgbox Eden_A2_Dawn_Stone_Text_0
	goto Eden_A2_Dusk_Stone_1

Eden_A2_Dusk_Stone_5:
	finditem ITEM_DUSK_STONE
	setvar VAR_TEMP_A, 1
	goto Eden_A2_Dusk_Stone_1


DungeonEden_Act2_Transition_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE_0_Text_0:
	.string "The forest is too thick to turn back.$"

Eden_A2_Dawn_Stone_Text_0:
	.string "It would be greedy to take another\n"
	.string "item.$"

Eden_A2_Dawn_Stone_Text_1:
	.string "Will you take the Dawn Stone?\p"
	.string "You can use it to evolve your Applin\n"
	.string "into Flapple.$"

Eden_A2_Dusk_Stone_Text_0:
	.string "Will you take the Dusk Stone?\p"
	.string "You can use it to evolve your Applin\n"
	.string "into Appletun.$"
