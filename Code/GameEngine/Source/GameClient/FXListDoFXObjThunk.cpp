// Open-BFME5: readable BFME body of FXList::doFXObj.
//
// This TU keeps the BFME-only FXList/FXNugget and Object slices local.  The
// retail method is the public-decorated QBEX body reached by the UpgradeMuxData
// call site, while the upstream ZH header puts the same method under
// `protected:` and would therefore emit IBEX here.

typedef bool Bool;
typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CellShroudStatus
{
	CELLSHROUD_CLEAR,
	CELLSHROUD_FOGGED,
	CELLSHROUD_SHROUDED
};

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID,
	OBJECTSHROUD_CLEAR,
	OBJECTSHROUD_PARTIAL_CLEAR,
	OBJECTSHROUD_FOGGED,
	OBJECTSHROUD_SHROUDED
};

class PartitionData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }

private:
	char m_unknown[0x24];
	Int m_playerIndex;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_localPlayer; }

private:
	char m_unknown[0x0c];
	Player *m_localPlayer;
};

extern PlayerList *ThePlayerList;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex, const Coord3D *position) const;
};

extern PartitionManager *ThePartitionManager;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	ObjectShroudStatus getShroudedStatus(Int playerIndex) const;
	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this) + 0x38);
	}

private:
	char m_prefix[0x3b0];

public:
	PartitionData *m_partitionData;
};

// FXNugget's BFME shared base has four virtual slots between the inherited
// MemoryPoolObject slot and the filter slot.  Its shared stop flag is at +B0.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXNugget
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void doFXObj(const Object *primary, const Object *secondary) const = 0;
	virtual void slot3() = 0;
	virtual Bool isVisible(const Object *primary, const Object *secondary) const = 0;

private:
	char m_shared[0xac];

public:
	Bool m_stopIfNuggetPlayed;
};

// The VC7 STL list base is one pointer to its circular sentinel; each node is
// [next, prev, value].  BFME appends its play-even-if-shrouded flag at +10.
struct FXNuggetNode
{
	FXNuggetNode *next;
	FXNuggetNode *prev;
	FXNugget *value;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXList
{
public:
	virtual ~FXList();
	void doFXObj(const Object *primary, const Object *secondary) const;

private:
	FXNuggetNode *m_nuggetSentinel;
	char m_bfmeFields[8];
	Bool m_playEvenIfShrouded;
};

// ?doFXObj@FXList@@QBEXPBVObject@@0@Z
void FXList::doFXObj(const Object *primary, const Object *secondary) const
{
	if (!m_playEvenIfShrouded && primary)
	{
		if (primary->m_partitionData)
		{
			if (primary->getShroudedStatus(ThePlayerList->getLocalPlayer()->getPlayerIndex()) > OBJECTSHROUD_PARTIAL_CLEAR)
				return;
		}
		else if (ThePartitionManager->getShroudStatusForPlayer(
			ThePlayerList->getLocalPlayer()->getPlayerIndex(), primary->getPosition()) != CELLSHROUD_CLEAR)
		{
			return;
		}
	}

	for (FXNuggetNode *it = m_nuggetSentinel->next; it != m_nuggetSentinel; it = it->next)
	{
		FXNugget *nugget = it->value;
		if (nugget->isVisible(primary, secondary))
		{
			nugget->doFXObj(primary, secondary);
			if (nugget->m_stopIfNuggetPlayed)
				break;
		}
	}
}
