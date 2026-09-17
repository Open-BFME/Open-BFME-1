// cl: /O2 /Ob1

// The body has no matched caller, vtable slot, string literal, or witnessed
// class layout.  Keep the owner and member names address-derived until one of
// those sources identifies them.

class Rva008F7B00
{
	char m_pad[0xA4];
	char m_slots[16];

public:
	char get(int index);
};

class Team;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Player
{
public:
	Relationship getRelationship(const Team *) const;
};

class PlayerList
{
public:
	Player *getNthPlayer(int);
};

extern PlayerList *ThePlayerList;

enum KindOfType
{
	KINDOF_2 = 2,
	KINDOF_B2 = 0xB2
};

class Thing
{
public:
	bool isKindOf(KindOfType) const;
};

struct Rva001CA9C0
{
	char _0[0x1D8];
	Team *m_ptr01D8;
	char _1[0x34C - 0x1D8 - 4];
	Rva008F7B00 *m_ptr034C;

	bool rva001CA9C0(int);
};

bool Rva001CA9C0::rva001CA9C0(int n)
{
	if (m_ptr034C == 0)
		return false;

	int playerIndex = n;
	Player *p = ThePlayerList->getNthPlayer(playerIndex);
	Relationship r = p->getRelationship(m_ptr01D8);
	register Thing *o;
	const KindOfType hostKind = KINDOF_2;

	if (r == NEUTRAL)
	{
		o = (Thing *)((char *)this - 0x64);
		if (o->isKindOf(hostKind) && !o->isKindOf(KINDOF_B2))
			goto deny;
	}
	else
	{
		o = (Thing *)((char *)this - 0x64);
		if (o->isKindOf(hostKind) && m_ptr034C->get(playerIndex) &&
			!o->isKindOf(KINDOF_B2))
			goto deny;
	}

	return true;

deny:
	return false;
}
