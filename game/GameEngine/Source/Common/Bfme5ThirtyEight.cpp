// Four more: two gated accumulators, a planar difference returned by value,
// and a bounded attach.

class BfmeClockCJ
{
public:
	int m_bfmeHead[15];					// +0x00
	int m_bfmeNow;						// +0x3C
	char m_bfmeGap[0x50];					// +0x40
	unsigned char m_bfmeEnabled;				// +0x90
};

class GameLogic;

// retail 0x012F0898; the TU-local view below is BfmeClockCJ
extern GameLogic *TheGameLogic;

class Gen_000E8870
{
public:
	void bfmeAddA(int amount);
	void bfmeAddB(int amount);

private:
	int m_bfmeHead[71];					// +0x000
	int m_bfmeFirst;					// +0x11C
	int m_bfmeSecond;					// +0x120
};

// ?bfmeAddA@Gen_000E8870@@QAEXH@Z
void Gen_000E8870::bfmeAddA(int amount)
{
	unsigned char enabled = ((BfmeClockCJ *)TheGameLogic)->m_bfmeEnabled;

	if (enabled)
		m_bfmeFirst = m_bfmeFirst + amount;
}

// ?bfmeAddB@Gen_000E8870@@QAEXH@Z
void Gen_000E8870::bfmeAddB(int amount)
{
	unsigned char enabled = ((BfmeClockCJ *)TheGameLogic)->m_bfmeEnabled;

	if (enabled)
		m_bfmeSecond = m_bfmeSecond + amount;
}

// class-gate: allow Coord3D BFME's Coord3D copy constructor (coord3d.h) is load-bearing for 0x00148960's by-value return; the POD canonical header changes the stores (1/4 FAIL).
struct Coord3D
{
	Coord3D(void)
	{
	}

	Coord3D(const Coord3D &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	float x;						// +0x00
	float y;						// +0x04
	float z;						// +0x08
};

// The planar delta from this Object's position (+0x38/+0x3C) to `pos`, z = 0.
// Callers reach it through ILT 0x0000B00F with ECX = the Object: matched
// Object::rva001E2560 (0x001E2560) and Object::bfmeGo941G
// (0x001E3E20), which passes the other Object's position. The method name is
// not recovered; it keeps the ledger's established bfmeDelta.
class Object
{
public:
	Coord3D bfmeDelta(const Coord3D *pos) const;

private:
	int m_bfmeHead[14];					// +0x00
	float m_bfmeX;						// +0x38
	float m_bfmeY;						// +0x3C
};

// ?bfmeDelta@Object@@QBE?AUCoord3D@@PBU2@@Z
Coord3D Object::bfmeDelta(const Coord3D *pos) const
{
	Coord3D delta;

	delta.x = pos->x - m_bfmeX;
	delta.y = pos->y - m_bfmeY;
	delta.z = 0.0f;

	return delta;
}

class BfmeChildDG
{
public:
	int m_bfmeHead[16];					// +0x00
	void *m_bfmeParent;					// +0x40
};

class Gen_001A5D90
{
public:
	void bfmeAdd(BfmeChildDG *child);

private:
	int m_bfmeHead[8];					// +0x00
	BfmeChildDG *m_bfmeSlots[11];				// +0x20
	int m_bfmeCount;					// +0x4C
};

// ?bfmeAdd@Gen_001A5D90@@QAEXPAVBfmeChildDG@@@Z
void Gen_001A5D90::bfmeAdd(BfmeChildDG *child)
{
	int count = m_bfmeCount;

	if (count < 8)
	{
		m_bfmeSlots[count] = child;

		++m_bfmeCount;
	}

	child->m_bfmeParent = this;
}
