// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob1 /Ireference/shims/ini_inline /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
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
// Clean BFME INI field-parser body.  The former implementation was a literal
// __emit lift of the 0x00850E70 retail body; this TU keeps the canonical
// parser callback in a real C++ definition.
#include "PreRTS.h"
#include "Common/INI.h"

// ?parseBitString32@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseBitString32( INI* ini, void * /*instance*/, void *store, const void* userData )
{
	ConstCharPtrArray flagList = (ConstCharPtrArray)userData;
	UnsignedInt *bits = (UnsignedInt *)store;

	if( flagList == NULL || flagList[ 0 ] == NULL)
	{
		DEBUG_ASSERTCRASH( flagList, ("INTERNAL ERROR! parseBitString32: No flag list provided!\n") );
		throw INIException( 2, "INTERNAL ERROR! parseBitString32: No flag list provided!" );
	}

	volatile Bool foundNormal = false;
	Bool foundAddOrSub = false;

	for (const char *token = ini->getNextTokenOrNull(); token != NULL; token = ini->getNextTokenOrNull())
	{
		if (stricmp(token, "NONE") == 0)
		{
			if (foundNormal || foundAddOrSub)
			{
				DEBUG_CRASH(("you may not mix normal and +- ops in bitstring lists"));
				throw INIException( 2, "you may not mix normal and +- ops in bitstring lists" );
			}
			*bits = 0;
			break;
		}

		if (token[0] == '+')
		{
			if (foundNormal)
			{
				DEBUG_CRASH(("you may not mix normal and +- ops in bitstring lists"));
				throw INIException( 2, "you may not mix normal and +- ops in bitstring lists" );
			}
			Int bitIndex = INI::scanIndexList(token + 1, flagList);
			*bits |= (1 << bitIndex);
			foundAddOrSub = true;
		}
		else if (token[0] == '-')
		{
			if (foundNormal)
			{
				DEBUG_CRASH(("you may not mix normal and +- ops in bitstring lists"));
				throw INIException( 2, "you may not mix normal and +- ops in bitstring lists" );
			}
			Int bitIndex = INI::scanIndexList(token + 1, flagList);
			*bits &= ~(1 << bitIndex);
			foundAddOrSub = true;
		}
		else
		{
			if (foundAddOrSub)
			{
				DEBUG_CRASH(("you may not mix normal and +- ops in bitstring lists"));
				throw INIException( 2, "you may not mix normal and +- ops in bitstring lists" );
			}

			if (!foundNormal)
				*bits = 0;

			Int bitIndex = INI::scanIndexList(token, flagList);
			*bits |= (1 << bitIndex);
			foundNormal = true;
		}
	}
}
