// ?equal@Rva001C0470@@QBE_NABU1@@Z
// The carved boundary proves a three-dword equality loop with a const-reference
// argument. No caller proves a semantic owner, so the class name preserves the
// retail address.
// cl: /O2 /Oy /DNDEBUG /MD

struct Rva001C0470
{
	unsigned m_word0;
	unsigned m_word1;
	unsigned m_word2;

	bool equal(const Rva001C0470 &source) const;
};

bool Rva001C0470::equal(const Rva001C0470 &source) const
{
	const unsigned *thisWords = &m_word0;
	const unsigned *sourceWords = &source.m_word0;
	for (unsigned i = 0; i < 3; ++i)
	{
		if (thisWords[i] != sourceWords[i])
			return false;
	}
	return true;
}
