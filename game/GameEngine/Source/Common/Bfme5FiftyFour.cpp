// Six more: an intrusive push and remove whose links sit ahead of the item, a
// walk that looks for a blocked node, a length check against a limit, and the
// same saturating twelve-bit counter in two classes.

class BfmeItemDX;

class BfmeLinksDX
{
public:
	BfmeItemDX *m_bfmePrev;					// -0x08
	BfmeItemDX *m_bfmeNext;					// -0x04
};

class BfmeItemDX
{
public:
	int m_bfmeBody[4];					// +0x00
};

// The links live in the header just ahead of the item.
inline BfmeLinksDX *bfmeLinksDX(BfmeItemDX *item)
{
	return (BfmeLinksDX *)item - 1;
}

extern BfmeItemDX *g_bfmeHeadDX;				// retail 0x013379A0

// ?bfmePush@@YAXPAVBfmeItemDX@@@Z
void __cdecl bfmePush(BfmeItemDX *item)
{
	BfmeItemDX *head = g_bfmeHeadDX;

	if (head != 0)
		bfmeLinksDX(head)->m_bfmePrev = item;

	bfmeLinksDX(item)->m_bfmeNext = g_bfmeHeadDX;
	bfmeLinksDX(item)->m_bfmePrev = 0;

	g_bfmeHeadDX = item;
}

// ?bfmeRemove@@YAXPAVBfmeItemDX@@@Z
void __cdecl bfmeRemove(BfmeItemDX *item)
{
	BfmeItemDX *previous = bfmeLinksDX(item)->m_bfmePrev;
	BfmeItemDX *next = bfmeLinksDX(item)->m_bfmeNext;

	if (previous != 0)
		bfmeLinksDX(previous)->m_bfmeNext = next;

	if (next != 0)
		bfmeLinksDX(next)->m_bfmePrev = previous;

	if (g_bfmeHeadDX == item)
		g_bfmeHeadDX = next;
}

class BfmeNodeDX
{
public:
	int m_bfmeHead[19];					// +0x00
	BfmeNodeDX *m_bfmeNext;					// +0x4C
};

class Gen_008A0C30
{
public:
	bool bfmeAllows(BfmeNodeDX *node) const;

private:
	char m_bfmeHead[0x129C];				// +0x0000
	BfmeNodeDX *m_bfmeBlocked;				// +0x129C
};

// ?bfmeAllows@Gen_008A0C30@@QBE_NPAVBfmeNodeDX@@@Z
bool Gen_008A0C30::bfmeAllows(BfmeNodeDX *node) const
{
	BfmeNodeDX *blocked = m_bfmeBlocked;

	if (blocked == 0)
		return false;

	while (node != 0)
	{
		if (node == blocked)
			return false;

		node = node->m_bfmeNext;
	}

	return true;
}

extern "C" unsigned int __cdecl strlen(const char *text);

#pragma intrinsic(strlen)

class BfmeThingDX
{
public:
	int m_bfmeHead[4];					// +0x00
	const char *m_bfmeText;					// +0x10
};

// ?bfmeTooLong@@YGHPBVBfmeThingDX@@@Z
int __stdcall bfmeTooLong(const BfmeThingDX *thing)
{
	return strlen(thing->m_bfmeText) > 0x800;
}

class Gen_008991B0
{
public:
	void bfmeBump(void);

private:
	int m_bfmeHead;						// +0x00
	unsigned int m_bfmeBits;				// +0x04
};

// ?bfmeBump@Gen_008991B0@@QAEXXZ
void Gen_008991B0::bfmeBump(void)
{
	// The field is masked by hand, not declared as a bitfield: a bitfield
	// store comes out as xor-and-xor instead of and-shift-or.
	unsigned int bits = m_bfmeBits;

	unsigned int count = ((bits >> 16) & 0xFFF) + 1;

	if (count > 0xFFF)
		count = 0xFFF;

	m_bfmeBits = (bits & 0xF000FFFF) | (count << 16);
}

class Gen_00899DA0
{
public:
	void bfmeBump(void);

private:
	int m_bfmeHead;						// +0x00
	unsigned int m_bfmeBits;				// +0x04
};

// ?bfmeBump@Gen_00899DA0@@QAEXXZ
void Gen_00899DA0::bfmeBump(void)
{
	// The field is masked by hand, not declared as a bitfield: a bitfield
	// store comes out as xor-and-xor instead of and-shift-or.
	unsigned int bits = m_bfmeBits;

	unsigned int count = ((bits >> 16) & 0xFFF) + 1;

	if (count > 0xFFF)
		count = 0xFFF;

	m_bfmeBits = (bits & 0xF000FFFF) | (count << 16);
}
