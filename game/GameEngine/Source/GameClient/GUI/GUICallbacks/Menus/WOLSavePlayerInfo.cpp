// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/nat /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// Retail 0x004F1330, 198 bytes: save the local GameSpy slot's preferences.
// The named caller is WOLGameSetupMenuUpdate at 0x004F5D10, which reaches this
// body at both retail save paths.  The shipped GameSpyStagingRoom/GameSpySlot
// declarations supply the data-bearing slot/map/prefs types.  BFME moved the
// two GameInfo virtuals to slots 0x10 and 0x14; this private view spells only
// those proven slots and leaves all object data in the real class declarations.

#include "PreRTS.h"
#include "Common/CustomMatchPreferences.h"
#include "GameNetwork/GameSpy/PeerDefs.h"

class BfmeSaveStagingRoomVtable
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00C() = 0;
	virtual Bool amIHost() = 0;
	virtual Int getLocalSlotNum() = 0;
};

static void savePlayerInfo( void )
{
	if (TheGameSpyGame)
	{
		Int slotNum = ((BfmeSaveStagingRoomVtable *)TheGameSpyGame)->getLocalSlotNum();
		if (slotNum >= 0)
		{
			GameSpyGameSlot *slot = TheGameSpyGame->getGameSpySlot(slotNum);
			if (slot)
			{
				// save off some prefs
				CustomMatchPreferences pref;
				pref.setPreferredColor(slot->getColor());
				pref.setPreferredFaction(slot->getPlayerTemplate());
				if (((BfmeSaveStagingRoomVtable *)TheGameSpyGame)->amIHost())
				{
					pref.setPreferredMap(TheGameSpyGame->getMap());
				}
				pref.write();
			}
		}
	}
}

// Keep the TU-local body materialized for the object-level conversion gate;
// the external pointer is data only and does not participate in the body.
void (*bfmeSavePlayerInfoAnchor)( void ) = savePlayerInfo;
