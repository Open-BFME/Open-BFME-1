// Four more: another counted handle, a four-word copy out, an xor swap and a
// global flag setter.

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

class Gen_00929290
{
public:
	BfmeHandleCX bfmeGet(int index) const;

private:
	int m_bfmeHead[2];					// +0x00
	BfmeHandleCX *m_bfmeSlots;				// +0x08
};

// ?bfmeGet@Gen_00929290@@QBE?AVBfmeHandleCX@@H@Z
BfmeHandleCX Gen_00929290::bfmeGet(int index) const
{
	return m_bfmeSlots[index];
}

class BfmeQuadEC
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	int m_bfmeThird;					// +0x08
	int m_bfmeFourth;					// +0x0C
};

class Gen_006D2390
{
public:
	void bfmeGetQuad(BfmeQuadEC *out) const;

private:
	char m_bfmeHead[0x30E8];				// +0x0000
	BfmeQuadEC m_bfmeQuad;					// +0x30E8
};

// ?bfmeGetQuad@Gen_006D2390@@QBEXPAVBfmeQuadEC@@@Z
void Gen_006D2390::bfmeGetQuad(BfmeQuadEC *out) const
{
	*out = m_bfmeQuad;
}

class Gen_0073A2E0
{
public:
	void bfmeSwapBits(void);

private:
	int m_bfmeHead[16];					// +0x00
	unsigned int m_bfmeFirst;				// +0x40
	unsigned int m_bfmeSecond;				// +0x44
	bool m_bfmeDirty;					// +0x48
};

// ?bfmeSwapBits@Gen_0073A2E0@@QAEXXZ
void Gen_0073A2E0::bfmeSwapBits(void)
{
	if (m_bfmeDirty)
	{
		m_bfmeFirst = m_bfmeFirst ^ m_bfmeSecond;
		m_bfmeSecond = m_bfmeSecond ^ m_bfmeFirst;
		m_bfmeFirst = m_bfmeFirst ^ m_bfmeSecond;

		m_bfmeDirty = false;
	}
}

extern bool g_bfmeFlagEC;					// retail 0x012F9DB8

// ?bfmeSet@@YGX_N@Z
void __stdcall bfmeSet(bool value)
{
	if (value)
	{
		g_bfmeFlagEC = true;

		return;
	}

	if (g_bfmeFlagEC)
		g_bfmeFlagEC = false;
}
