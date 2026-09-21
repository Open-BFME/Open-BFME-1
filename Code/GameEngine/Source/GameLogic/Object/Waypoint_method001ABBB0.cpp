// cl: /DNDEBUG /MD

// Retail 0x001ABBB0, 168 bytes. Owning class is proven: shares vtable
// 0x0109C3DC / ctor 0x001AB600 / dtor 0x001ABA80 with the banked
// Waypoint::~Waypoint() (reverse/attempts/0x001aba80.cpp, score 0.97),
// whose recovered layout (m_pathLabel1/2/3 at +0x50/+0x54/+0x58, class ends
// at +0x68) this body continues past. The method name itself is unproven
// (no caller, string, or declaration names it), so it stays address-derived
// on the proven class.
//
// Behavior: takes an Object* argument (the stack arg), gates on two
// KindOfType include/exclude masks (m_68/m_6c include, m_84/m_88 exclude,
// via Thing::isAnyKindOf -- pinned ?bfmeTestLB@BfmeOwnerLB@@... => ILT ->
// Thing::isAnyKindOf), then, unless the arg object itself is a special kind
// (own exclude mask bit 0x200 AND arg->+0x128 bit 0x800), looks up a linked
// object by ID (m_a8) via GameLogic::findObjectByID, requires ALLIES
// relationship with the argument object (unless m_a0 says to skip that),
// and finally requires TheGameLogic's current frame to have reached a
// stored threshold (m_ac), returning true when threshold<=0 or already
// reached, and true unconditionally when there is no linked object id or
// m_a0 is set.

typedef bool Bool;

template <int N>
class BitFlags
{
};

class Thing
{
public:
	Bool isAnyKindOf(const BitFlags<69> &) const;
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Object : public Thing
{
public:
	Relationship getRelationship(const Object *) const;

	unsigned char m_pad128[0x128];
	unsigned int m_kindOf128;	// +0x128, tested bit 0x800
};

class GameLogic
{
public:
	Object *findObjectByID(int id);

	unsigned char m_pad3c[0x3c];
	unsigned int m_frame;		// +0x3c
};

extern GameLogic *TheGameLogic;	// 0x012F0898

class Waypoint
{
public:
	Bool method001ABBB0(Object *obj);

private:
	unsigned char m_pad00[0x68];
	Bool m_hasInclude;		// +0x68
	unsigned char m_pad69[3];
	unsigned char m_includeMask[0x84 - 0x6c];	// +0x6c
	Bool m_hasExclude;		// +0x84
	unsigned char m_pad85[3];
	unsigned char m_excludeMask[0xa0 - 0x88];	// +0x88
	Bool m_skipRelationship;	// +0xa0
	unsigned char m_pada1[7];
	int m_linkedObjectId;		// +0xa8
	int m_frameThreshold;		// +0xac
};

Bool Waypoint::method001ABBB0(Object *obj)
{
	if (m_hasInclude && !obj->isAnyKindOf(*(const BitFlags<69> *)m_includeMask))
		return false;

	if (m_hasExclude)
	{
		if (obj->isAnyKindOf(*(const BitFlags<69> *)m_excludeMask))
			return false;

		if (*(unsigned int *)m_excludeMask & 0x00000200)
		{
			if (obj->m_kindOf128 & 0x00000800)
				return false;
		}
	}

	int linkedId = m_linkedObjectId;
	if (linkedId != 0)
	{
		Object *found = TheGameLogic->findObjectByID(linkedId);

		if (!m_skipRelationship)
		{
			if (!found)
				return false;
			if (found->getRelationship(obj) != ALLIES)
				return false;
		}
	}

	unsigned int threshold = (unsigned int)m_frameThreshold;
	if (threshold > 0 && TheGameLogic->m_frame < threshold)
		return false;

	return true;
}
