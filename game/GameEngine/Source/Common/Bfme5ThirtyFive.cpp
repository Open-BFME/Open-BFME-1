// Four more: the counted handle taken from an indexed slot in two classes,
// and two presence tests over indexed arrays.

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

class Gen_00933540
{
public:
	BfmeHandleCX bfmeGet(int index) const;

private:
	int m_bfmeHead[2];					// +0x00
	BfmeHandleCX m_bfmeHandles[8];				// +0x08
};

// ?bfmeGet@Gen_00933540@@QBE?AVBfmeHandleCX@@H@Z
BfmeHandleCX Gen_00933540::bfmeGet(int index) const
{
	return m_bfmeHandles[index];
}

class Gen_00945490
{
public:
	BfmeHandleCX bfmeGet(int index) const;

private:
	int m_bfmeHead[3];					// +0x00
	BfmeHandleCX m_bfmeHandles[8];				// +0x0C
};

// ?bfmeGet@Gen_00945490@@QBE?AVBfmeHandleCX@@H@Z
BfmeHandleCX Gen_00945490::bfmeGet(int index) const
{
	return m_bfmeHandles[index];
}

class BfmeSlotDDa
{
public:
	int m_bfmeHead[7];					// +0x00
	int *m_bfmeThing;					// +0x1C
	int m_bfmeTail;						// +0x20
};

class Gen_009596D0
{
public:
	bool bfmeHasThing(int index) const;

private:
	int m_bfmeHead[19];					// +0x00
	BfmeSlotDDa *m_bfmeSlots;				// +0x4C
};

// ?bfmeHasThing@Gen_009596D0@@QBE_NH@Z
bool Gen_009596D0::bfmeHasThing(int index) const
{
	return m_bfmeSlots[index].m_bfmeThing != 0;
}

class BfmeSlotDDb
{
public:
	int m_bfmeHead[5];					// +0x00
	int *m_bfmeThing;					// +0x14
	int m_bfmeTail[1];					// +0x18
};

class Gen_0095B3F0
{
public:
	bool bfmeHasThing(int index) const;

private:
	int m_bfmeHead[20];					// +0x00
	BfmeSlotDDb *m_bfmeSlots;				// +0x50
};

// ?bfmeHasThing@Gen_0095B3F0@@QBE_NH@Z
bool Gen_0095B3F0::bfmeHasThing(int index) const
{
	return m_bfmeSlots[index].m_bfmeThing != 0;
}
