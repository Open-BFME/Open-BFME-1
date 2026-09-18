// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
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

////////////////////////////////////////////////////////////////////////////////
//	(c) 2001-2003 Electronic Arts Inc.																//
////////////////////////////////////////////////////////////////////////////////

// Real C++ body recovered from the canonical donor:
// reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Source/GameClient/System/CampaignManager.cpp
// The donor is the named Campaign parser registered by the Campaign block.
// Retail body: Code/masm_dumps/INI_parseCampaignDefinition_5BCF20.asm (172B).

#include "PreRTS.h"
#include "Common/INI.h"
#include "GameClient/CampaignManager.h"

// The retail callee at 0x005BCBF0 is generic in the ledger.  Its raw
// prologue/epilogue and this caller prove the ABI, but not the historical
// method spelling; keep the call's identity address-derived with a direct
// body pin. Full340B ends5BCD44CC; takes a by-value4B AsciiString and ret4.
// It removes any same-name entry before allocating and registering a new
// 0x18-byte campaign. This is not a borrowed lookup.
class Rva005BCBF0CampaignHelper
{
public:
	Campaign *rva005BCBF0(AsciiString name);
};


extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)

// CampaignManager's retail local uses the WWLib pointer-and-length setter;
// keep this layout shim TU-local so the shared AsciiString header is untouched.
class RetailLayoutString
{
public:
	RetailLayoutString() : m_data(0) {}
	~RetailLayoutString() { releaseBuffer(); }
	void set(const char *text, int length);
	const char *str() const;

private:
	void releaseBuffer();
	void *m_data;
};

// ?parseCampaignDefinition@INI@@SAXPAV1@@Z
void INI::parseCampaignDefinition(INI *ini)
{
	RetailLayoutString name;
	Campaign *campaign;

	// read the name
	const char *c = ini->getNextToken();
	int length = c ? (int)strlen(c) : 0;
	name.set(c, length);

	// Parse only when the campaign manager exists.
	DEBUG_ASSERTCRASH(TheCampaignManager, ("parseCampaignDefinition: Unable to Get TheCampaignManager\n"));
	if (!TheCampaignManager)
		return;

	// The callee's semantic method name is not proven by its generic ledger row.
	// Its thiscall/value-argument ABI is established by the raw body and caller.
	campaign = ((Rva005BCBF0CampaignHelper *)TheCampaignManager)->rva005BCBF0(*(AsciiString *)&name);

	// sanity
	DEBUG_ASSERTCRASH(campaign, ("parseCampaignDefinition: Unable to allocate campaign '%s'\n", name.str()));

	// parse the ini definition
	ini->initFromINI(campaign, TheCampaignManager->getFieldParse());
}
