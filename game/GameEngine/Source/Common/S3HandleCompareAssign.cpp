// Eight bodies in two shapes.
//
// 0x0054ECB0, 0x0054ECE0, 0x0054F200 and 0x0054F230 compare the dword at +0x04
// of two objects through a __cdecl helper and test the answer against
// 0xAA37ACC2, a sentinel rather than zero, so the helper hands back a hash and
// not an ordering. The result is materialised as xor ecx,ecx / setne cl /
// mov al,cl, a byte, so it is Bool. The two pushes put this's member first,
// which fixes the argument order.
//
// 0x005D1E50, 0x005D2040, 0x00749D90 and 0x00749DD0 are the reference-counted
// assignment operator, and they are written in the order that makes it safe
// against self-assignment: bump the source's count first, release the old
// block second, store third. The old block is passed as a this in ecx, so the
// release is a member of the block and not a free function, and the source
// pointer is re-read after the call because the call could have touched it.

struct BfmeHandleBlock
{
	char m_bfmeHead[4];
	unsigned short m_bfmeRefCount;				// +0x04
};

struct BfmeSharedBlock
{
	void bfmeRelease(void);					// retail 0x009EB7A0
};

unsigned int bfmeHashCompareA(unsigned int left, unsigned int right);	// ILT 0x00027BFB
unsigned int bfmeHashCompareB(unsigned int left, unsigned int right);	// ILT 0x00020AA4

enum { BFME_HASH_EQUAL = 0xAA37ACC2 };


class Gen_0054ECB0
{
public:
	bool bfmeDiffers(const Gen_0054ECB0 &other) const;

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_0054ECE0
{
public:
	bool bfmeDiffers(const Gen_0054ECE0 &other) const;

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_0054F200
{
public:
	bool bfmeDiffers(const Gen_0054F200 &other) const;

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_0054F230
{
public:
	bool bfmeDiffers(const Gen_0054F230 &other) const;

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_005D1E50
{
public:
	Gen_005D1E50 &operator=(const Gen_005D1E50 &other);

private:
	BfmeSharedBlock *m_bfmeData;
};

class Gen_005D2040
{
public:
	Gen_005D2040 &operator=(const Gen_005D2040 &other);

private:
	BfmeSharedBlock *m_bfmeData;
};

class Gen_00749D90
{
public:
	Gen_00749D90 &operator=(const Gen_00749D90 &other);

private:
	BfmeSharedBlock *m_bfmeData;
};

class Gen_00749DD0
{
public:
	Gen_00749DD0 &operator=(const Gen_00749DD0 &other);

private:
	BfmeSharedBlock *m_bfmeData;
};

// ?bfmeDiffers@Gen_0054ECB0@@QBE_NABV1@@Z
bool Gen_0054ECB0::bfmeDiffers(const Gen_0054ECB0 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return bfmeHashCompareA(mine, theirs) != BFME_HASH_EQUAL;
}

// ?bfmeDiffers@Gen_0054ECE0@@QBE_NABV1@@Z
bool Gen_0054ECE0::bfmeDiffers(const Gen_0054ECE0 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return bfmeHashCompareB(mine, theirs) != BFME_HASH_EQUAL;
}

// ?bfmeDiffers@Gen_0054F200@@QBE_NABV1@@Z
bool Gen_0054F200::bfmeDiffers(const Gen_0054F200 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return bfmeHashCompareA(mine, theirs) != BFME_HASH_EQUAL;
}

// ?bfmeDiffers@Gen_0054F230@@QBE_NABV1@@Z
bool Gen_0054F230::bfmeDiffers(const Gen_0054F230 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return bfmeHashCompareB(mine, theirs) != BFME_HASH_EQUAL;
}

// ??4Gen_005D1E50@@QAEAAV0@ABV0@@Z
Gen_005D1E50 &Gen_005D1E50::operator=(const Gen_005D1E50 &other)
{
	if (other.m_bfmeData)
		++((BfmeHandleBlock *)other.m_bfmeData)->m_bfmeRefCount;

	if (m_bfmeData)
		m_bfmeData->bfmeRelease();

	m_bfmeData = other.m_bfmeData;

	return *this;
}

// ??4Gen_005D2040@@QAEAAV0@ABV0@@Z
Gen_005D2040 &Gen_005D2040::operator=(const Gen_005D2040 &other)
{
	if (other.m_bfmeData)
		++((BfmeHandleBlock *)other.m_bfmeData)->m_bfmeRefCount;

	if (m_bfmeData)
		m_bfmeData->bfmeRelease();

	m_bfmeData = other.m_bfmeData;

	return *this;
}

// ??4Gen_00749D90@@QAEAAV0@ABV0@@Z
Gen_00749D90 &Gen_00749D90::operator=(const Gen_00749D90 &other)
{
	if (other.m_bfmeData)
		++((BfmeHandleBlock *)other.m_bfmeData)->m_bfmeRefCount;

	if (m_bfmeData)
		m_bfmeData->bfmeRelease();

	m_bfmeData = other.m_bfmeData;

	return *this;
}

// ??4Gen_00749DD0@@QAEAAV0@ABV0@@Z
Gen_00749DD0 &Gen_00749DD0::operator=(const Gen_00749DD0 &other)
{
	if (other.m_bfmeData)
		++((BfmeHandleBlock *)other.m_bfmeData)->m_bfmeRefCount;

	if (m_bfmeData)
		m_bfmeData->bfmeRelease();

	m_bfmeData = other.m_bfmeData;

	return *this;
}
