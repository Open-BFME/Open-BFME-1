// Four iterator makers.
//
// Each returns an eight-byte record through a hidden pointer -- the first
// stack argument, which is why the answer is stored through [esp+4] and the
// body cleans four bytes. Three pair a member with a fixed address; the fourth
// pairs this with the dword at +0x00.
//
// The record has to be built by a constructor in the return expression: with a
// named local the compiler copies it into the return slot instead of writing
// through the slot directly.

struct BfmeIterator
{
	BfmeIterator(void *node, void *owner)
	{
		m_bfmeNode = node;
		m_bfmeOwner = owner;
	}

	void *m_bfmeNode;					// +0x00
	void *m_bfmeOwner;					// +0x04
};


extern char TheBfmeOwner_000CBB80[];

class Gen_000CBB80
{
public:
	BfmeIterator bfmeMake(void);

private:
	char m_bfmeHead[0x274];
	void *m_bfmeNode;					// +0x274
};

extern char TheBfmeOwner_00161290[];

class Gen_00161290
{
public:
	BfmeIterator bfmeMake(void);

private:
	char m_bfmeHead[0x4];
	void *m_bfmeNode;					// +0x4
};

extern char TheBfmeOwner_001612B0[];

class Gen_001612B0
{
public:
	BfmeIterator bfmeMake(void);

private:
	char m_bfmeHead[0x8];
	void *m_bfmeNode;					// +0x8
};

class Gen_004C14F0
{
public:
	BfmeIterator bfmeMake(void);

private:
	void *m_bfmeFirst;					// +0x00
};

// ?bfmeMake@Gen_000CBB80@@QAE?AUBfmeIterator@@XZ
BfmeIterator Gen_000CBB80::bfmeMake(void)
{
	return BfmeIterator(m_bfmeNode, TheBfmeOwner_000CBB80);
}

// ?bfmeMake@Gen_00161290@@QAE?AUBfmeIterator@@XZ
BfmeIterator Gen_00161290::bfmeMake(void)
{
	return BfmeIterator(m_bfmeNode, TheBfmeOwner_00161290);
}

// ?bfmeMake@Gen_001612B0@@QAE?AUBfmeIterator@@XZ
BfmeIterator Gen_001612B0::bfmeMake(void)
{
	return BfmeIterator(m_bfmeNode, TheBfmeOwner_001612B0);
}

// ?bfmeMake@Gen_004C14F0@@QAE?AUBfmeIterator@@XZ
BfmeIterator Gen_004C14F0::bfmeMake(void)
{
	return BfmeIterator(this, m_bfmeFirst);
}
