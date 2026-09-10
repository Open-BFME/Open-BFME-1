// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib
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

// Open-BFME5: clean C++ reconstruction of the CampaignManager constructor.
// Retail boundary: RVA 0x005BC400, 0x98 bytes (the Ghidra size stops three
// bytes before the complete epilogue ends). Padding begins at 0x005BC498;
// separate small methods begin at 0x005BC4C0 and 0x005BC4D0.

#include <list>

typedef bool Bool;
typedef int Int;
class Campaign;
class Mission;
class Xfer;

// This is the BFME interface, not the later reference Snapshot interface.
// Retail vtable VA 0x0110F660 contains four entries followed by a null word:
//   0: ILT 0x00026D0F -> scalar-deleting destructor 0x005BC970, which calls
//      the independently matched CampaignManager destructor at 0x005BC4E0;
//   1: ILT 0x00029A7D -> 0x005BC4C0, a no-argument plain return;
//   2: ILT 0x0002EAAF -> 0x005BC4D0, returning "CampaignManager";
//   3: ILT 0x0004ADDB -> 0x005BCDA0, the campaign-state Xfer body.
// Only the proven interface is declared here. The no-op slot's original name
// is unresolved; the reference crc(Xfer*) and loadPostProcess slots do not
// describe this table. All virtual methods remain declaration-only.
// Layout: vptr +0, one-pointer STLport list +4, scalar state +8 through +18.
// The reference version's extra challenge-player field is absent in BFME.
// The empty Snapshot construction is retained: retail's EH states distinguish
// the constructed base from the list. Its reference constructor is empty,
// while this TU declares only the four virtual slots proven in BFME above.
class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot();
	virtual void rva005BC4C0();
	virtual const char *rva005BC4D0();
	virtual void xfer(Xfer *xfer);
};

class CampaignManager : public Snapshot
{
public:
	CampaignManager();
	virtual ~CampaignManager();
	virtual void rva005BC4C0();
	virtual const char *rva005BC4D0();
	virtual void xfer(Xfer *xfer);

private:
	std::list<Campaign *> m_campaignList;
	Campaign *m_currentCampaign;
	Mission *m_currentMission;
	Bool m_victorious;
	Int m_currentRankPoints;
	Int m_difficulty;
};

// ??0CampaignManager@@QAE@XZ
CampaignManager::CampaignManager()
{
	m_campaignList.clear();
	m_currentCampaign = 0;
	m_currentMission = 0;
	m_victorious = false;
	m_currentRankPoints = 0;
	m_difficulty = 1;
}

void CampaignManager::rva005BC4C0()
{
}

const char *CampaignManager::rva005BC4D0()
{
	return "CampaignManager";
}
