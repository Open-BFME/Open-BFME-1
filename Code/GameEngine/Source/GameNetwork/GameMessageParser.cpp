// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////


#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameNetwork/GameMessageParser.h"

//----------------------------------------------------------------------------
GameMessageParser::GameMessageParser() 
{
	m_first = NULL;
	m_last = NULL;
	m_argTypeCount = 0;
}

// The exact retail message-taking constructor is emitted by GameMessageParserCtorThunk.cpp.

//----------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/GameMessageParserDtor.cpp
// ??1GameMessageParser@@MAE@XZ present-unmatched
GameMessageParser::~GameMessageParser() 
{
	GameMessageParserArgumentType *temp = NULL;
	while (m_first != NULL) {
		temp = m_first->getNext();
		m_first->deleteInstance();
		m_first = temp;
	}
}

//----------------------------------------------------------------------------
void GameMessageParser::addArgType(GameMessageArgumentDataType type, Int argCount) 
{
	if (m_first == NULL) {
		m_first = newInstance(GameMessageParserArgumentType)(type, argCount);
		m_last = m_first;
		return;
	}

	m_last->setNext(newInstance(GameMessageParserArgumentType)(type, argCount));
	m_last = m_last->getNext();
}

//----------------------------------------------------------------------------
GameMessageParserArgumentType::GameMessageParserArgumentType(GameMessageArgumentDataType type, Int argCount) 
{
	m_next = NULL;
	m_type = type;
	m_argCount = argCount;
}

//----------------------------------------------------------------------------
// ??1GameMessageParserArgumentType@@MAE@XZ present-unmatched
GameMessageParserArgumentType::~GameMessageParserArgumentType() 
{
}

