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

class Gen_00929260
{
public:
	__declspec(noinline) BfmeHandleCX bfmeGet(int index) const;

private:
	int m_bfmeHead[2];					// +0x00
	BfmeHandleCX *m_bfmeSlots;				// +0x08
};

class Gen_00929290
{
public:
	__declspec(noinline) BfmeHandleCX bfmeGet(int index) const;

private:
	int m_bfmeHead[2];					// +0x00
	BfmeHandleCX *m_bfmeSlots;				// +0x08
};

// Same-TU getters so the compiler can see edx is preserved across the call.
// Bodies already matched at 0x00929260 / 0x00929290; these copies are for
// intra-TU register allocation only.
BfmeHandleCX Gen_00929260::bfmeGet(int index) const
{
	return m_bfmeSlots[index];
}

BfmeHandleCX Gen_00929290::bfmeGet(int index) const
{
	return m_bfmeSlots[index];
}

class Gen_009299D0
{
public:
	__declspec(noinline) BfmeHandleCX bfmeGet(int pidx, int pass, int stage) const;

private:
	int m_bfmeHead[29];					// +0x00
	BfmeHandleCX m_bfmeSlots[8];				// +0x74
	int m_bfmeMid[8];					// +0x94
	Gen_00929260 *m_bfmeArrays[8];				// +0xB4
};

class Gen_00929A20
{
public:
	__declspec(noinline) BfmeHandleCX bfmeGet(int pidx, int pass, int stage) const;

private:
	int m_bfmeHead[29];					// +0x00
	BfmeHandleCX m_bfmeSlots[8];				// +0x74
	int m_bfmeMid[8];					// +0x94
	Gen_00929290 *m_bfmeArrays[8];				// +0xB4
};

class Gen_0092F070
{
public:
	BfmeHandleCX bfmeGet(int pidx, int pass, int stage) const;

private:
	int m_bfmeHead[39];					// +0x00
	Gen_00929A20 *m_cur;					// +0x9C
};

// ?bfmeGet@Gen_009299D0@@QBE?AVBfmeHandleCX@@HHH@Z
BfmeHandleCX Gen_009299D0::bfmeGet(int pidx, int pass, int stage) const
{
	Gen_00929260 *array = m_bfmeArrays[stage + pass * 2];

	if (array)
		return array->bfmeGet(pidx);

	return m_bfmeSlots[stage + pass * 2];
}

// ?bfmeGet@Gen_00929A20@@QBE?AVBfmeHandleCX@@HHH@Z
BfmeHandleCX Gen_00929A20::bfmeGet(int pidx, int pass, int stage) const
{
	Gen_00929290 *array = m_bfmeArrays[stage + pass * 2];

	if (array)
		return array->bfmeGet(pidx);

	return m_bfmeSlots[stage + pass * 2];
}

// ?bfmeGet@Gen_0092F070@@QBE?AVBfmeHandleCX@@HHH@Z
BfmeHandleCX Gen_0092F070::bfmeGet(int pidx, int pass, int stage) const
{
	return m_cur->bfmeGet(pidx, pass, stage);
}
