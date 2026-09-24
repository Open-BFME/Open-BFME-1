extern "C" void _ReadWriteBarrier(void);

// Answers given by a part that has to look back at the whole it sits in,
// reaching behind itself to find the record that owns it.

class BfmeOwnerYH
{
public:
	__forceinline int hasMaskedFlags() const
	{
		// Keep the one retail memory test and the two distinct return arms.
		if (!(((const volatile BfmeOwnerYH *)this)->m_bfmeFlags & 0x70000000)) {
			_ReadWriteBarrier();
			return 0;
		}
		return 1;
	}

	unsigned char m_bfmeHead[0x28];		// 0x000
	unsigned int m_bfmeLimit;		// 0x028
	unsigned char m_bfmeBody[0x100];	// 0x02c
	unsigned int m_bfmeFlags;		// 0x12c
};

class BfmeStateYH
{
public:
	unsigned char m_bfmeHead[0x94];		// 0x00
	unsigned int m_bfmeFlags;		// 0x94
};

class BfmePartYH
{
public:
	int bfmeStepYH(void) const;
	int bfmeStageYH(int spare) const;
	int rva002B2470HasMaskedFlags(void) const;

	unsigned char m_bfmeHead[0x14];		// 0x00
	unsigned int m_bfmeMark;		// 0x14
};

class BfmeHostYH
{
public:
	BfmeOwnerYH *m_bfmeOwner;		// 0x00
	BfmeStateYH *m_bfmeState;		// 0x04
	unsigned char m_bfmeGap[0x14];		// 0x08
	BfmePartYH m_bfmePart;			// 0x1c
};

int BfmePartYH::bfmeStepYH(void) const
{
	const BfmeHostYH *host = (const BfmeHostYH *)((const char *)this - 0x1c);

	return (m_bfmeMark < host->m_bfmeOwner->m_bfmeLimit) ? 0 : 4;
}

int BfmePartYH::bfmeStageYH(int spare) const
{
	const BfmeHostYH *host = (const BfmeHostYH *)((const char *)this - 0x1c);

	if (m_bfmeMark >= host->m_bfmeOwner->m_bfmeLimit)
		return 4;

	return (host->m_bfmeState->m_bfmeFlags & 0x20000000) != 0 ? 3 : 0;
}

int BfmePartYH::rva002B2470HasMaskedFlags(void) const
{
	const BfmeHostYH *host = (const BfmeHostYH *)((const char *)this - 0x1c);
	return host->m_bfmeOwner->hasMaskedFlags();
}
