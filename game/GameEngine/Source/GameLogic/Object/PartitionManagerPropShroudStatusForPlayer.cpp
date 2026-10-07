// cl: /Igame/Libraries/Include
// ?getPropShroudStatusForPlayer@PartitionManager@@QBE?AW4ObjectShroudStatus@@HPBUCoord3D@@@Z
// BFME PartitionManager::getPropShroudStatusForPlayer, RVA 0x008F7440, 8 bytes:
// loads the shroud implementation at +0x0C and tail-jumps to the matched
// four-corner query ShroudManagerImpl::GetPropShroudStatusForPlayer
// (0x008F95A0, ShroudManagerImpl008FBA40.cpp). The sibling 0x008F7430
// getShroudStatusForPlayer forwarder (PartitionManagerShroudStatusForPlayer.cpp)
// reads the same +0x0C pointer.

#include "Lib/Coord3D.h"

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID,
	OBJECTSHROUD_CLEAR,
	OBJECTSHROUD_PARTIAL_CLEAR,
	OBJECTSHROUD_FOGGED,
	OBJECTSHROUD_SHROUDED
};

class ShroudManagerImpl
{
public:
	ObjectShroudStatus GetPropShroudStatusForPlayer(int playerIndex, const Coord3D *loc) const;
};

class PartitionManager
{
public:
	ObjectShroudStatus getPropShroudStatusForPlayer(int playerIndex, const Coord3D *loc) const;
	char m_lead[0x0C];
	ShroudManagerImpl *m_shroud;
};

ObjectShroudStatus PartitionManager::getPropShroudStatusForPlayer(int playerIndex, const Coord3D *loc) const
{
	return m_shroud->GetPropShroudStatusForPlayer(playerIndex, loc);
}
