// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/gameinfo /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
// stlport
/*
** Copyright 2025 Electronic Arts Inc.
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
// BFME GameInfo::clearSlotList, RVA 0x0061F520, complete 218-byte body.
// RecorderClass::bfmeInit names this call through ILT 0x00026418.
// The final RET at 0x0061F5F9 is followed by alignment padding.
// These inline GameSlot helpers retain the original GameInfo.cpp structure;
// the BFME StringBase adapter supplies the independently matched string calls.
#define Matrix4x4 Matrix4
#include "PreRTS.h"
#include "GameClient/GameText.h"
#include "GameNetwork/GameInfo.h"
inline Bool GameSlot::isAI() const
{
    return m_state == SLOT_EASY_AI || m_state == SLOT_MED_AI || m_state == SLOT_BRUTAL_AI;
}

inline void GameSlot::setState( SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo )
{
	if (!(isAI() &&  (state == SLOT_EASY_AI || state == SLOT_MED_AI || state == SLOT_BRUTAL_AI)))
	{
		m_color = -1;
		m_startPos = -1;
		m_playerTemplate = -1;
		m_teamNumber = -1;

	}
	if (state == SLOT_PLAYER)
	{
		reset();
		m_state = state;
		m_name = name;
	}// state == SLOT_PLAYER
	else
	{
		m_state = state;
		m_isAccepted = true;
		m_hasMap = true;
		switch(state)
		{
		case SLOT_OPEN:
			m_name = TheGameText->fetch("GUI:Open");
			break;
		case SLOT_EASY_AI:
			m_name = TheGameText->fetch("GUI:EasyAI");
			break;
		case SLOT_MED_AI:
			m_name = TheGameText->fetch("GUI:MediumAI");
			break;
		case SLOT_BRUTAL_AI:
			m_name = TheGameText->fetch("GUI:HardAI");
			break;
		case SLOT_CLOSED:
		default:
			m_name = TheGameText->fetch("GUI:Closed");
			break;
		}
	}

	m_connectInfo = *connectInfo;
}

void GameInfo::clearSlotList( void )
{
	for (int i=0; i<MAX_SLOTS; ++i)
	{
		if (m_slot[i])
		{
			GameSlotConnectInfo info;
			info.m_nat = FirewallHelperClass::FIREWALL_TYPE_UNKNOWN;
			info.m_port = 0;
			m_slot[i]->setState(SLOT_CLOSED, UnicodeString::TheEmptyString, &info);
		}
	}
}
