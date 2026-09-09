// ?addGroupRoom@GameSpyInfo@@UAEXVGameSpyGroupRoom@@@Z
// partial score=0.72 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistringsetoutofline /Ireference/shims/psplayerstats /Ireference/shims/peerdefs /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _BFME_RETAIL_PLAYER_INFO_LAYOUT
#define __PLACEMENT_VEC_NEW_INLINE
#include <map>
#include <vector>

#include "PreRTS.h"

#include "Common/GameState.h"
#include "Common/RandomValue.h"
#include "Common/IgnorePreferences.h"
#include "Common/CustomMatchPreferences.h"
#include "Common/GameSpyMiscPreferences.h"
#include "Common/Recorder.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/PlayerTemplate.h"
#include "GameClient/MapUtil.h"
#include "GameClient/ShellHooks.h"
#include "GameClient/GameText.h"
#include "GameNetwork/GameSpy/LadderDefs.h"
#include "GameNetwork/GameSpy/PeerDefsImplementation.h"
#include "GameNetwork/GameSpy/BuddyThread.h"
#include "GameNetwork/GameSpy/PeerThread.h"
#include "GameNetwork/GameSpy/PingThread.h"
#include "GameNetwork/GameSpy/PersistentStorageThread.h"
#include "GameNetwork/GameSpy/GSConfig.h"
#include "GameNetwork/GameSpyOverlay.h"
#include "GameNetwork/RankPointValue.h"
#include "GameLogic/GameLogic.h"
#include "string_base.h"

// ?addGroupRoom@GameSpyInfo@@UAEXVGameSpyGroupRoom@@@Z present-unmatched
void GameSpyInfo::addGroupRoom( GameSpyGroupRoom room )
{
	if (room.m_groupID == 0)
	{
		m_gotGroupRoomList = TRUE;

		GroupRoomMap::iterator iter;

		// figure out how many good strings we've got
		std::vector<UnicodeString> names;
		Int numRooms = 0;
		for (iter = getGroupRoomList()->begin(); iter != getGroupRoomList()->end(); ++iter)
		{
			GameSpyGroupRoom room = iter->second;
			if (room.m_groupID != TheGameSpyConfig->getQMChannel())
			{
				++numRooms;

				AsciiString groupLabel;
				groupLabel.format("GUI:%s", room.m_name.str());

				Bool exists = FALSE;
				UnicodeString groupName = TheGameText->fetch(groupLabel, &exists);
				if (exists)
				{
					names.push_back(groupName);
				}
			}
		}

		if (!names.empty() && names.size() != numRooms)
		{
			// didn't get all names.  fix up
			Int nameIndex = 0;
			Int timesThrough = 1; // start with USA Lobby 1
			for (iter = TheGameSpyInfo->getGroupRoomList()->begin(); iter != TheGameSpyInfo->getGroupRoomList()->end(); ++iter)
			{
				GameSpyGroupRoom room = iter->second;
				if (room.m_groupID != TheGameSpyConfig->getQMChannel())
				{
					room.m_translatedName.format(L"%ls %d", names[nameIndex].str(), timesThrough);
					nameIndex = (nameIndex+1)%names.size();
					m_groupRooms[room.m_groupID] = room;
					if (!nameIndex)
					{
						// we've looped through the name list already.  increment the timesThrough counter
						++timesThrough;
					}
				}
			}
		}
	}
	else
	{
		DEBUG_LOG(("Adding group room %d (%s)\n", room.m_groupID, room.m_name.str()));
		AsciiString groupLabel;
		groupLabel.format("GUI:%s", room.m_name.str());
		room.m_translatedName = TheGameText->fetch(groupLabel);
		m_groupRooms[room.m_groupID] = room;
		if ( !stricmp("quickmatch", room.m_name.str()) )
		{
			DEBUG_LOG(("Group room %d (%s) is the QuickMatch room\n", room.m_groupID, room.m_name.str()));
			TheGameSpyConfig->setQMChannel(room.m_groupID);
		}
	}
}
