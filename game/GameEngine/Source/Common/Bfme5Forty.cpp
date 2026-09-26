// Six more: a reset, two walks over a circular list, a two-flag veto reached
// by a back-step, a float read behind two guards, and a fill.

class Gen_001A3030
{
public:
	void bfmeReset(void);

private:
	int m_bfmeA;						// +0x00
	int m_bfmeB;						// +0x04
	int m_bfmeC;						// +0x08
	int m_bfmeD;						// +0x0C
	int m_bfmeE;						// +0x10
	int m_bfmeF;						// +0x14
	bool m_bfmeQuiet;					// +0x18
	char m_bfmeGap[0x0F];					// +0x19
	int m_bfmeCount;					// +0x28
	bool m_bfmeOpen;					// +0x2C
	bool m_bfmeArmed;					// +0x2D
};

// ?bfmeReset@Gen_001A3030@@QAEXXZ
void Gen_001A3030::bfmeReset(void)
{
	m_bfmeA = 0;
	m_bfmeB = 0;
	m_bfmeC = 0;
	m_bfmeD = 0;
	m_bfmeE = 0;
	m_bfmeF = 0;
	m_bfmeQuiet = false;

	m_bfmeCount = 1;
	m_bfmeOpen = true;
	m_bfmeArmed = true;
}

class BfmeNodeDI
{
public:
	BfmeNodeDI *m_bfmeNext;					// +0x00
	int m_bfmeGap;						// +0x04
	void *m_bfmeKey;					// +0x08
};

class BfmeThingDI
{
public:
	int m_bfmeHead[29];					// +0x00
	void *m_bfmeKey;					// +0x74
};

class Gen_001EFD20
{
public:
	bool bfmeIsNew(const BfmeThingDI *thing) const;

private:
	int m_bfmeHead[31];					// +0x00
	BfmeNodeDI *m_bfmeList;					// +0x7C
};

// ?bfmeIsNew@Gen_001EFD20@@QBE_NPBVBfmeThingDI@@@Z
bool Gen_001EFD20::bfmeIsNew(const BfmeThingDI *thing) const
{
	BfmeNodeDI *head = m_bfmeList;

	void *key = thing->m_bfmeKey;

	for (BfmeNodeDI *node = head->m_bfmeNext; node != head; node = node->m_bfmeNext)
	{
		if (key == node->m_bfmeKey)
			return false;
	}

	return true;
}

class Gen_002227A0
{
public:
	bool bfmeContains(void *key) const;

private:
	int m_bfmeHead[6];					// +0x00
	BfmeNodeDI *m_bfmeList;					// +0x18
};

// ?bfmeContains@Gen_002227A0@@QBE_NPAX@Z
bool Gen_002227A0::bfmeContains(void *key) const
{
	BfmeNodeDI *head = m_bfmeList;

	for (BfmeNodeDI *node = head->m_bfmeNext; node != head; node = node->m_bfmeNext)
	{
		if (node->m_bfmeKey == key)
			return true;
	}

	return false;
}

class BfmeHolderDI
{
public:
	char m_bfmeHead[0x258];					// +0x258
	unsigned char m_bfmeReady : 1;				// +0x258
	unsigned char m_bfmeRest : 7;				// +0x258
};

class BfmeStateDI
{
public:
	char m_bfmeHead[0x128];					// +0x000
	unsigned int m_bfmeFlags;				// +0x128
};

class Gen_0026E1C0
{
public:
	bool bfmeBlocked(int unused) const;
};

// ?bfmeBlocked@Gen_0026E1C0@@QBE_NH@Z
bool Gen_0026E1C0::bfmeBlocked(int unused) const
{
	BfmeHolderDI *holder = *(BfmeHolderDI **)((const char *)this - 0x1C);

	// The answer starts as true in the register both tests then share.
	bool blocked = true;

	if (holder->m_bfmeReady)
	{
		BfmeStateDI *state = *(BfmeStateDI **)((const char *)this - 0x18);

		if (state->m_bfmeFlags & 0x800)
			blocked = false;
	}

	return blocked;
}

class BfmeSlotDI
{
public:
	int m_bfmeHead[2];					// +0x00
	float *m_bfmeValue;					// +0x08
};

extern float g_bfmeZeroCY;					// retail 0x01075350

class Gen_0026EB40
{
public:
	float bfmeValue(int index) const;

private:
	int m_bfmeHead[122];					// +0x000
	BfmeSlotDI *m_bfmeSlots[8];				// +0x1E8
};

// ?bfmeValue@Gen_0026EB40@@QBEMH@Z
float Gen_0026EB40::bfmeValue(int index) const
{
	if (index != -1)
	{
		BfmeSlotDI *slot = m_bfmeSlots[index];

		if (slot != 0)
			return *slot->m_bfmeValue;
	}

	return g_bfmeZeroCY;
}

class BfmeItemDI
{
public:
	int m_bfmeData[7];					// 28 bytes
};

// ?bfmeFill@@YAXPAVBfmeItemDI@@0PBV1@@Z
void __cdecl bfmeFill(BfmeItemDI *first, BfmeItemDI *last, const BfmeItemDI *value)
{
	while (first != last)
	{
		*first = *value;

		++first;
	}
}
