// ?invoke@Owner@@QAE_NPAVObject@@@Z
// partial score=0.77 date=2026-09-21
// cl: /DNDEBUG /MD

// Retail 0x0021AC30, 178 bytes. Anonymous containment/relationship gate:
// two prior blocked passes found no named caller, source owner, or vtable
// identity (reached only through a generated thunk), so the owner stays
// address-derived. The this+0x20 interior object mirrors the "this-0x20"
// adjusted-interface pattern already proven by the landed neighbour
// Rva21ABF0RingDispatch.cpp (retail 0x0021ABF0, immediately before this
// body) and needs a big dummy vtable to reach slots +0xc4/+0x100/+0x110/
// +0xcc. The embedded list at +0x38 (next/prev/value node layout) matches
// the BfmeObjectNode/BfmeObjectList shape used throughout this campaign
// (e.g. Code/GameEngine/Source/Common/BfmeOneHundredOne.cpp). The tail
// call at retail 0x00228050 is still a dump (thunks_002.cpp j_00005943);
// its return value is this function's own return value, so it is declared
// here with the exact ABI the call site proves and pinned fresh.

typedef bool Bool;

class Object;
class Player;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Relationship getRelationship(const Object *) const;
};

class Node
{
public:
	Node *next;
	Node *prev;
	Object *value;
};

class NodeList
{
public:
	Node *sentinel;
};

#define S(n) virtual void slot##n();

class Interior
{
public:
	S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
	S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
	S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29)
	S(30) S(31) S(32) S(33) S(34) S(35) S(36) S(37) S(38) S(39)
	S(40) S(41) S(42) S(43) S(44) S(45) S(46) S(47) S(48)
	virtual Bool slot49();				// +0xc4
	S(50)
	virtual Player *slot51();			// +0xcc
	S(52) S(53) S(54) S(55) S(56) S(57) S(58) S(59)
	S(60) S(61) S(62) S(63)
	virtual void *slot64(int arg);		// +0x100
	S(65) S(66) S(67)
	virtual void *slot68();			// +0x110
};

#undef S

class Owner
{
public:
	Bool invoke(Object *arg1);
	Bool tail(Object *arg1);

private:
	unsigned char m_pad00[0x08];
	Object *m_relationshipTarget;			// +0x08
	unsigned char m_pad0c[0x20 - 0x0c];
	Interior m_interior;				// +0x20
	unsigned char m_pad24[0x38 - 0x20 - sizeof(Interior)];
	NodeList m_members;				// +0x38
	unsigned char m_pad44[0x9bc - 0x38 - (int)sizeof(NodeList)];
	Node *m_otherList;				// +0x9bc
};

Bool Owner::invoke(Object *arg1)
{
	if (m_members.sentinel->next == m_members.sentinel)
		return true;

	Object *firstValue = m_members.sentinel->next->value;

	if (firstValue->getControllingPlayer() == arg1->getControllingPlayer())
		return true;

	if (!m_interior.slot49())
	{
		void *a = m_interior.slot64(0);
		void *b = m_interior.slot68();

		if (a == b)
			return tail(arg1);
	}

	if (arg1->getRelationship(m_relationshipTarget) != ENEMIES)
		return false;

	if (m_otherList->next == m_otherList)
		return true;

	return m_interior.slot51() == arg1->getControllingPlayer();
}
