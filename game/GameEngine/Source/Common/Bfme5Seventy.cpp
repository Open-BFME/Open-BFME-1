// Three more: a three-value setter, a mode field written two ways, and an
// unlink through the owner.

class Gen_0042E7C0
{
public:
	void bfmeSet(int first, int second, int third);

private:
	char m_bfmeHead[0xC5];					// +0x000
	bool m_bfmeFlagA;					// +0x0C5
	bool m_bfmeFlagB;					// +0x0C6
	char m_bfmePad;						// +0x0C7
	int m_bfmeFirst;					// +0x0C8
	int m_bfmeSecond;					// +0x0CC
	int m_bfmeThird;					// +0x0D0
};

// ?bfmeSet@Gen_0042E7C0@@QAEXHHH@Z
void Gen_0042E7C0::bfmeSet(int first, int second, int third)
{
	m_bfmeFlagA = true;
	m_bfmeFlagB = true;

	m_bfmeFirst = first;
	m_bfmeSecond = second;
	m_bfmeThird = third;
}

class BfmeOwnerEH
{
public:
	int m_bfmeHead[8];					// +0x00
	int *m_bfmeThing;					// +0x20
};

class Gen_003F68B0
{
public:
	void bfmeSetMode(unsigned int mode);

private:
	BfmeOwnerEH *m_bfmeOwner;				// +0x00
	int m_bfmeGap[2];					// +0x04
	unsigned int m_bfmeMode : 3;				// +0x0C
	unsigned int m_bfmeRest : 29;				// +0x0C
};

// A constant into the field comes out as and/or; a variable needs the
// xor-and-xor form.
// ?bfmeSetMode@Gen_003F68B0@@QAEXI@Z
void Gen_003F68B0::bfmeSetMode(unsigned int mode)
{
	BfmeOwnerEH *owner = m_bfmeOwner;

	if (owner != 0 && owner->m_bfmeThing != 0)
	{
		m_bfmeMode = 4;

		return;
	}

	m_bfmeMode = mode;
}

class BfmeOwnerEI
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeHead[8];					// +0x04
	unsigned int m_bfmeFlags;				// +0x24
	int m_bfmeGap;						// +0x28
	BfmeOwnerEI *m_bfmePrev;				// +0x2C
	BfmeOwnerEI *m_bfmeNext;				// +0x30
};

class Gen_003F69E0
{
public:
	void bfmeDetach(void);

private:
	BfmeOwnerEI *m_bfmeOwner;				// +0x00
};

// ?bfmeDetach@Gen_003F69E0@@QAEXXZ
void Gen_003F69E0::bfmeDetach(void)
{
	BfmeOwnerEI *owner = m_bfmeOwner;

	BfmeOwnerEI *next = owner->m_bfmeNext;

	if (next != 0)
	{
		next->m_bfmeFirst = (int)owner->m_bfmePrev;

		BfmeOwnerEI *previous = owner->m_bfmePrev;

		if (previous != 0)
			previous->m_bfmeNext = owner->m_bfmeNext;

		owner->m_bfmeNext = 0;
		owner->m_bfmePrev = 0;
	}

	m_bfmeOwner->m_bfmeFlags = m_bfmeOwner->m_bfmeFlags & ~8;
}
