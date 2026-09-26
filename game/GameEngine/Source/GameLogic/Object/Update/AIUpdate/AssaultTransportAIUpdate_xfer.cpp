// cl: /DNDEBUG /MD /EHsc
// Retail 0x002B44E0: AssaultTransportAIUpdate's BFME Xfer override.
//
// Identity is established independently of the byte shape: the constructor
// at 0x002B46F0 installs 0x010C6120 at the primary view, and that complete
// table's slot 3 thunk 0x0001A983 jumps to 0x002B44E0.  The constructor stores
// m_currentMembers at +0x398 and the retail body serializes the object fields
// beginning at +0x344.

#include "../../../../Common/System/xfer.h"

typedef int ObjectID;
typedef unsigned int UnsignedInt;

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

enum AssaultStateTypes
{
	ASSAULT_STATE_VALUE_0 = 0,
	ASSAULT_STATE_VALUE_1 = 1
};

class BfmeSeedTarget;

// The retail base serializer is the existing ILT 0x00043441 candidate for
// Gen_002B5250.  This class has the proven 0x344-byte base span only to keep
// the derived object's field offsets honest; it emits no vtable.
class Gen_002B5250
{
private:
	void bfmeAccept(BfmeSeedTarget *target);
	friend class AssaultTransportAIUpdate;

	unsigned char m_base[0x340];

	// The constructor's primary view is the inherited polymorphic subobject;
	// keeping that vptr in this base leaves the derived fields at +0x344.
	virtual void baseSlot00() = 0;
	virtual void baseSlot01() = 0;
	virtual void baseSlot02() = 0; // xfer follows at primary slot 3
};

// Existing ILT 0x0000C9B4: canonical ObjectID transfer helper.  Its ABI is
// cdecl(target, pointer), and the target body calls it once per member ID and
// once for the designated target.
void __cdecl bfmeHandOver_0000C9B4(BfmeSeedTarget *target, void *item);

class AssaultTransportAIUpdate : public Gen_002B5250
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_memberIDs[10];
	bool m_memberHealing[10];
	bool m_newMember[10];
	Coord3DBase m_attackMoveGoalPos;
	ObjectID m_designatedTarget;
	AssaultStateTypes m_state;
	UnsignedInt m_framesRemaining;
	int m_currentMembers;
	bool m_isAttackMove;
	bool m_isAttackObject;
	bool m_newOccupantsAreNewMembers;
};

// ?xfer@AssaultTransportAIUpdate@@MAEXPAVXfer@@@Z
void AssaultTransportAIUpdate::xfer(Xfer *xfer)
{
	bfmeAccept(reinterpret_cast<BfmeSeedTarget *>(xfer));
	if (xfer->IsLightCRC())
		return;

	{
		Xfer::Version version;
		version.data[0] = 1;
		version.data[1] = 1;
		*xfer == version;
	}
	*xfer == m_currentMembers;

	{
		for (int i = 0; i < m_currentMembers; ++i)
		{
			bfmeHandOver_0000C9B4(
				reinterpret_cast<BfmeSeedTarget *>(xfer), &m_memberIDs[i]);
			*xfer == m_memberHealing[i];
		}
	}

	*xfer == m_attackMoveGoalPos;
	bfmeHandOver_0000C9B4(
		reinterpret_cast<BfmeSeedTarget *>(xfer), &m_designatedTarget);

	int state = (int)m_state;
	*xfer == state;
	m_state = (AssaultStateTypes)state;

	*xfer == m_framesRemaining;
	*xfer == m_isAttackMove;
	*xfer == m_isAttackObject;
	*xfer == m_newOccupantsAreNewMembers;
}
