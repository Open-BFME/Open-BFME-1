// Five more: a counted handle returned by value, a dot product, a triple of
// mixed types, a rate that a flag overrides, and five flags raised together.

class BfmeThingCX
{
public:
	int m_bfmeHead;						// +0x00
	unsigned short m_bfmeRefs;				// +0x04
};

class BfmeHandleCX
{
public:
	BfmeHandleCX(void)
	{
		m_bfmeThing = 0;
	}

	BfmeHandleCX(const BfmeHandleCX &other)
	{
		BfmeThingCX *thing = other.m_bfmeThing;

		m_bfmeThing = thing;

		if (thing)
			++thing->m_bfmeRefs;
	}

	~BfmeHandleCX(void)
	{
		if (m_bfmeThing)
			--m_bfmeThing->m_bfmeRefs;
	}

	BfmeThingCX *m_bfmeThing;				// +0x00
};

class Gen_006C5690
{
public:
	BfmeHandleCX bfmeGet(void) const;

private:
	char m_bfmeHead[0xBC];					// +0x00
	BfmeHandleCX m_bfmeHandle;				// +0xBC
};

// The four zeroed bytes on the stack are an empty temporary the compiler has
// to keep because the destructor reads the pointer; with no destructor it
// disappears and the body is nine bytes shorter.
// ?bfmeGet@Gen_006C5690@@QBE?AVBfmeHandleCX@@XZ
BfmeHandleCX Gen_006C5690::bfmeGet(void) const
{
	return m_bfmeHandle;
}

class BfmeVec3CX
{
public:
	float m_bfmeX;						// +0x00
	float m_bfmeY;						// +0x04
	float m_bfmeZ;						// +0x08
};

class BfmePlaneCX
{
public:
	float m_bfmeX;						// +0x00
	float m_bfmeY;						// +0x04
	float m_bfmeZ;						// +0x08
	float m_bfmeW;						// +0x0C
};

// ?bfmeDot@@YAMPBVBfmePlaneCX@@PBVBfmeVec3CX@@@Z
float __cdecl bfmeDot(const BfmePlaneCX *plane, const BfmeVec3CX *point)
{
	return plane->m_bfmeX * point->m_bfmeX + plane->m_bfmeY * point->m_bfmeY + plane->m_bfmeZ * point->m_bfmeZ + plane->m_bfmeW;
}

class BfmeTripleCX
{
public:
	BfmeTripleCX(void)
	{
	}

	BfmeTripleCX(const BfmeTripleCX &other)
	{
		m_bfmeId = other.m_bfmeId;
		m_bfmeY = other.m_bfmeY;
		m_bfmeZ = other.m_bfmeZ;
	}

	int m_bfmeId;						// +0x00
	float m_bfmeY;						// +0x04
	float m_bfmeZ;						// +0x08
};

class Gen_006FCF10
{
public:
	BfmeTripleCX bfmeGetTriple(void) const;

private:
	char m_bfmeHead[0xC0];					// +0x000
	int m_bfmeId;						// +0x0C0
	float m_bfmeY;						// +0x0C4
	float m_bfmeZ;						// +0x0C8
};

// ?bfmeGetTriple@Gen_006FCF10@@QBE?AVBfmeTripleCX@@XZ
BfmeTripleCX Gen_006FCF10::bfmeGetTriple(void) const
{
	BfmeTripleCX triple;

	triple.m_bfmeZ = m_bfmeZ;
	triple.m_bfmeY = m_bfmeY;
	triple.m_bfmeId = m_bfmeId;

	return triple;
}

extern float g_bfmeDefaultRateCX;				// retail 0x012F8234

class Gen_006FD060
{
public:
	void bfmeSetRate(bool fast);

private:
	char m_bfmeHead[0xE8];					// +0x000
	float m_bfmeRate;					// +0x0E8
};

// ?bfmeSetRate@Gen_006FD060@@QAEX_N@Z
void Gen_006FD060::bfmeSetRate(bool fast)
{
	m_bfmeRate = g_bfmeDefaultRateCX;

	if (fast)
		m_bfmeRate = 1.0f;
}

class Gen_00733E00
{
public:
	void bfmeMarkAll(void);

private:
	char m_bfmeHead[0x2A7CB4];				// +0x000000
	bool m_bfmeA;						// +0x2A7CB4
	bool m_bfmeB;						// +0x2A7CB5
	char m_bfmeGapA[3];					// +0x2A7CB6
	bool m_bfmeC;						// +0x2A7CB9
	char m_bfmeGapB[0x1C42];				// +0x2A7CBA
	bool m_bfmeD;						// +0x2A98FC
	char m_bfmeGapC[0xF];					// +0x2A98FD
	bool m_bfmeE;						// +0x2A990C
};

// ?bfmeMarkAll@Gen_00733E00@@QAEXXZ
void Gen_00733E00::bfmeMarkAll(void)
{
	m_bfmeC = true;
	m_bfmeD = true;
	m_bfmeA = true;
	m_bfmeE = true;
	m_bfmeB = true;
}
