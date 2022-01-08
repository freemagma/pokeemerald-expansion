Common_UpOne:
	walk_up
	step_end

Common_RoutingSign::
	lock
	callnative BufferRouteText
	msgbox Common_RoutingSign_Text_0, MSGBOX_SIGN
	release
	return


Common_RoutingSign_Text_0:
	.string "{LEFT_ARROW} {STR_VAR_1} Room\n"
	.string "{RIGHT_ARROW} {STR_VAR_2} Room$"
