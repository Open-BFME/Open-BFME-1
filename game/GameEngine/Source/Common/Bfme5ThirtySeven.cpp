// Six more: a complement that hands itself back, a clamped difference, a size
// test, a band search, a flag test, and a counter that reports when it fills a
// mask.

// The trim takes the word by address, which is what keeps the complement's own
// store alive ahead of the masked one.
inline void bfmeTrimDF(unsigned int *word)
{
	*word = *word & 0x3FFFFF;
}

class Gen_001C3D40
{
public:
	Gen_001C3D40 &bfmeInvert(void);

private:
	unsigned int m_bfmeFirst;				// +0x00
	unsigned int m_bfmeSecond;				// +0x04
	unsigned int m_bfmeThird;				// +0x08
};

// Handing the object back is what keeps this in eax across the whole body.
// ?bfmeInvert@Gen_001C3D40@@QAEAAV1@XZ
Gen_001C3D40 &Gen_001C3D40::bfmeInvert(void)
{
	m_bfmeFirst = ~m_bfmeFirst;
	m_bfmeSecond = ~m_bfmeSecond;
	m_bfmeThird = ~m_bfmeThird;

	bfmeTrimDF(&m_bfmeThird);

	return *this;
}

class BfmeThingDF
{
public:
	int m_bfmeHead[6];					// +0x00
	float m_bfmeValue;					// +0x18
};

// retail 0x01098AD4 is MSVC's own literal pool entry __real@40200000: the
// image holds 0x40200000 (2.5f) there and the only recorded spelling of that
// address is the compiler literal, so the constant is spelled as the literal
// (game/GameEngine/Source/Common/BfmeConv2032.cpp already does this).
extern const float g_rva01075350;					// retail 0x01075350

class Gen_001E1950
{
public:
	float bfmeValue(void) const;

private:
	int m_bfmeHead;						// +0x00
	BfmeThingDF *m_bfmeThing;				// +0x04
};

// ?bfmeValue@Gen_001E1950@@QBEMXZ
float Gen_001E1950::bfmeValue(void) const
{
	float value = m_bfmeThing->m_bfmeValue - 2.5f;

	if (value < g_rva01075350)
		value = g_rva01075350;

	return value;
}

class BfmeTripleDF
{
public:
	int m_bfmeData[3];					// 12 bytes
};

class Gen_001EFA70
{
public:
	bool bfmeHasAny(void) const;

private:
	unsigned int bfmeSize(void) const
	{
		return m_bfmeFinish - m_bfmeStart;
	}

	int m_bfmeHead[17];					// +0x00
	BfmeTripleDF *m_bfmeStart;				// +0x44
	BfmeTripleDF *m_bfmeFinish;				// +0x48
};

// ?bfmeHasAny@Gen_001EFA70@@QBE_NXZ
bool Gen_001EFA70::bfmeHasAny(void) const
{
	return bfmeSize() > 0;
}

// The rank thresholds are the first member of the shared rank-point table,
// retail 0x012F401C (TheRankPointValues).
struct RankPoints
{
	int m_ranks[11];
};

extern RankPoints *TheRankPointValues;				// retail 0x012F401C

// ?bfmeBand@@YAHH@Z
int __cdecl bfmeBand(int value)
{
	int index = 1;

	while (index < 10 && value >= TheRankPointValues->m_ranks[index])
		++index;

	return index;
}

class BfmeStateDF
{
public:
	int m_bfmeHead[2];					// +0x00
	bool m_bfmeBusy;					// +0x08
};

// Retail global at 0x012F7048 is Rva006092D0State *, defined once in
// game/GameEngine/Source/GameClient/LivingWorld.cpp as
// ?g_rva012F7048LivingWorld@@3PAVRva006092D0State@@A.  This TU only reads the
// +0x08 busy flag, so it keeps its local BfmeStateDF view and reaches the
// canonical spelling through a forward declaration, exactly as
// game/GameEngine/Source/Common/BfmeConv1734.cpp does.
class Rva006092D0State;
extern Rva006092D0State *g_rva012F7048LivingWorld;		// retail 0x012F7048

static inline BfmeStateDF *localGlo012F7048(void)
{
	return reinterpret_cast<BfmeStateDF *>(g_rva012F7048LivingWorld);
}

class Gen_005896B0
{
public:
	int bfmeReady(void) const;

private:
	char m_bfmeHead[0x4B];					// +0x00
	bool m_bfmeArmed;					// +0x4B
};

// ?bfmeReady@Gen_005896B0@@QBEHXZ
int Gen_005896B0::bfmeReady(void) const
{
	if (!localGlo012F7048()->m_bfmeBusy && m_bfmeArmed)
		return 1;

	return 0;
}

class Gen_005BD290
{
public:
	int bfmeTick(void);

private:
	int m_bfmeHead[1460];					// +0x0000
	int m_bfmeCount;					// +0x16D0
	int m_bfmeMask;						// +0x16D4
};

// ?bfmeTick@Gen_005BD290@@QAEHXZ
int Gen_005BD290::bfmeTick(void)
{
	int count = m_bfmeCount + 1;

	m_bfmeCount = count;

	int mask = m_bfmeMask;

	return (mask & count) != mask;
}
