Lobby_LevelSelect_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Lobby_LevelSelect_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

Lobby_LevelSelect_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	callnative LobbyResetState
	return


Lobby_Computer1::
	lock
	msgbox Lobby_Computer1_Text_0
	release
	return


Lobby_Computer2::
	lock
	msgbox Lobby_Computer2_Text_0
	release
	return


Lobby_Computer1_Text_0:
	.string "1. Diglett Dungeon (Tutorial)\n"
	.string "1/5 Difficulty$"

Lobby_Computer2_Text_0:
	.string "2. Dungeon In Progress...$"
