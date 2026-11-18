/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

// Existing BFME1 enum contract from inputs/reference/shims/gamewindow/GameClient/GameWindow.h.
// Original provider contexts remain intact; this narrow header is for proven consumers.
enum GameWindowMessage
{

	GWM_NONE = 0,

	GWM_CREATE,									GWM_DESTROY,
	GWM_ACTIVATE,								GWM_ENABLE,
	GWM_LEFT_DOWN,							GWM_LEFT_UP,
	GWM_LEFT_DOUBLE_CLICK,			GWM_LEFT_DRAG,
	GWM_MIDDLE_DOWN,						GWM_MIDDLE_UP,
	GWM_MIDDLE_DOUBLE_CLICK,		GWM_MIDDLE_DRAG,
	GWM_RIGHT_DOWN,							GWM_RIGHT_UP,
	GWM_RIGHT_DOUBLE_CLICK,			GWM_RIGHT_DRAG,
	GWM_MOUSE_ENTERING,					GWM_MOUSE_LEAVING,
	GWM_WHEEL_UP,								GWM_WHEEL_DOWN,
	GWM_CHAR,										GWM_SCRIPT_CREATE,
	// note that GWM_MOUSE_POS is only actually propogated to windows if the static
	// sendMousePosMessages is set to true in the window manager file.  See the
	// comment on the static declaration for addtional info
	GWM_INPUT_FOCUS,						GWM_MOUSE_POS,
	GWM_IME_CHAR,								GWM_IME_STRING

};
