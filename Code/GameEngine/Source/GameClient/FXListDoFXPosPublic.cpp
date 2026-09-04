// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5: public four-arg FXList::doFXPos at 0x004280D0 (133B).
// Same BFME FXList / FXNugget slice as FXListDoFXObjThunk.cpp: sentinel at
// +4, play-even-if-shrouded at +0x10, nugget stop flag at +0xB0.  Cell-shroud
// gates on the primary position; each nugget is asked isVisible(0, 0) before
// the four-arg doFXPos virtual.  ret 0x10.

typedef bool Bool;
typedef int Int;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Matrix3D;

enum CellShroudStatus
{
	CELLSHROUD_CLEAR,
	CELLSHROUD_FOGGED,
	CELLSHROUD_SHROUDED
};

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

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXNugget
{
public:
	virtual void slot0() = 0;
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, Real primarySpeed, const Coord3D *secondary) const = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual Bool isVisible(const Object *primary, const Object *secondary) const = 0;

private:
	char m_shared[0xac];

public:
	Bool m_stopIfNuggetPlayed;
};

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
	void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, Real primarySpeed, const Coord3D *secondary) const;

private:
	FXNuggetNode *m_nuggetSentinel;
	char m_bfmeFields[8];
	Bool m_playEvenIfShrouded;
};

// ?doFXPos@FXList@@QBEXPBUCoord3D@@PBVMatrix3D@@M0@Z
void FXList::doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, Real primarySpeed, const Coord3D *secondary) const
{
	const FXList *self = this;
	if (!m_playEvenIfShrouded && primary)
	{
		if (ThePartitionManager->getShroudStatusForPlayer(
			ThePlayerList->getLocalPlayer()->getPlayerIndex(), primary) != CELLSHROUD_CLEAR)
			return;
	}

	FXNuggetNode *it = m_nuggetSentinel->next;
	if (it != m_nuggetSentinel)
	{
		const Coord3D *sec = secondary;
		do
		{
			FXNugget *nugget = it->value;
			if (nugget->isVisible(0, 0))
			{
				nugget->doFXPos(primary, primaryMtx, primarySpeed, sec);
				if (nugget->m_stopIfNuggetPlayed)
					break;
			}
			it = it->next;
		} while (it != self->m_nuggetSentinel);
	}
}
