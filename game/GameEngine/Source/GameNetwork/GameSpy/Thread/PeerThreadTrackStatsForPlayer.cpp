// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
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
//
// PeerThreadClass::trackStatsForPlayer is called by the registered
// roomKeyChangedCallback.  The complete retail body is
// 0x0064E7B0-0x0064E8AB (252 bytes), including both SEH cleanup tails.
// The raw switch uses the authentic Peer.h values TitleRoom=0, GroupRoom=1,
// StagingRoom=2.  Its two map operands are the already-proven PeerThread
// layout at +0x94 and +0xA0; packStatKey is the named ILT at 0x00006190.

#include <cstdlib>
#include <map>
#include <string>

typedef int Int;

enum RoomType
{
	TitleRoom,
	GroupRoom,
	StagingRoom
};

typedef std::map<std::string, Int> PlayerStatMap;

class PeerThreadClass
{
public:
	void trackStatsForPlayer(RoomType roomType, const char *nick,
		const char *key, const char *val);

private:
	std::string packStatKey(const char *nick, const char *key);

	char m_beforeStats[0x94];
	PlayerStatMap m_groupRoomStats;
	PlayerStatMap m_stagingRoomStats;
};

#pragma optimize("y", on)
void PeerThreadClass::trackStatsForPlayer(RoomType roomType, const char *nick,
	const char *key, const char *val)
{
	switch (roomType)
	{
		case GroupRoom:
			m_groupRoomStats[packStatKey(nick, key)] = atoi(val);
			break;
		case StagingRoom:
			m_stagingRoomStats[packStatKey(nick, key)] = atoi(val);
			break;
	}
}
#pragma optimize("y", off)
