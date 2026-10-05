// Four more tiny ones: a byte count through a pointer, a slot count with a
// signed division, a table copied into an object, and a detach that writes
// back before dropping its pointer.

class BfmeThingBZ
{
public:
	char m_bfmeHead[0x10];					// +0x00
	int m_bfmeCount;					// +0x10
};

class Gen_009715E0
{
public:
	int bfmeBytes(void) const;

private:
	int m_bfmeHead[5];					// +0x00
	BfmeThingBZ *m_bfmeThing;				// +0x14
};

// ?bfmeBytes@Gen_009715E0@@QBEHXZ
int Gen_009715E0::bfmeBytes(void) const
{
	BfmeThingBZ *thing = m_bfmeThing;

	if (thing)
		return thing->m_bfmeCount * 0xB4 + 0x1C;

	return 0;
}

class Gen_009779A0
{
public:
	int bfmeSlots(void) const;

private:
	int m_bfmeHead[3];					// +0x00
	int m_bfmeStart;					// +0x0C
	int m_bfmeEnd;						// +0x10
};

// ?bfmeSlots@Gen_009779A0@@QBEHXZ
int Gen_009779A0::bfmeSlots(void) const
{
	return (m_bfmeEnd - m_bfmeStart + 8) / 8 + 0x18;
}

extern "C" void * __cdecl memcpy(void *destination, const void *source, unsigned int bytes);

#pragma intrinsic(memcpy)

extern const unsigned g_bfmeTableBZ[64] = {
	94, 92, 90, 88, 86, 82, 78, 74,
	70, 66, 62, 58, 54, 53, 52, 51,
	50, 49, 48, 47, 46, 45, 44, 43,
	42, 40, 39, 37, 36, 35, 34, 33,
	32, 31, 30, 29, 28, 27, 26, 25,
	24, 23, 22, 21, 20, 19, 18, 17,
	16, 15, 14, 13, 12, 11, 10, 9,
	8, 7, 6, 5, 4, 3, 2, 1
};					// retail 0x01141708

// ?bfmeLoadTable@@YAXPAE@Z
void __cdecl bfmeLoadTable(unsigned char *out)
{
	memcpy(out + 0x3C, g_bfmeTableBZ, sizeof(g_bfmeTableBZ));
}

class BfmeOwnerBZ
{
public:
	char m_bfmeHead[0x1DC];					// +0x000
	int m_bfmeBack;						// +0x1DC
};

class Gen_00479250
{
public:
	void bfmeDetach(void);

private:
	int m_bfmeTag;						// +0x00
	int m_bfmeValue;					// +0x04
	BfmeOwnerBZ *m_bfmeOwner;				// +0x08
};

// ?bfmeDetach@Gen_00479250@@QAEXXZ
void Gen_00479250::bfmeDetach(void)
{
	BfmeOwnerBZ *owner = m_bfmeOwner;

	if (owner)
	{
		owner->m_bfmeBack = m_bfmeValue;

		m_bfmeOwner = 0;
	}
}
