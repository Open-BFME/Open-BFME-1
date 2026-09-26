// Three two-byte-element reserves and range assignments.
//
// The reserve guards its count twice: once against the largest count the
// address space could hold for a two-byte element, which is why the immediate
// is 0x7FFFFFFF and MSVC does not fold it, and once against zero -- written as
// greater-than-zero, since a not-equal gives je where retail has jbe. Nothing
// is written when either guard fails, so the three pointers are only stored
// inside it.
//
// The two range assignments size themselves from the pointer difference plus
// one for the terminator, then copy the bytes through the imported copier --
// an indirect call through a function pointer, not a direct one -- and step
// the finish pointer past what was copied before writing the terminator. The
// copier's return value is what the step is applied to, so the destination is
// read once before the branch and used on both paths.

void *bfmeNewAlloc(unsigned int bytes);				// retail 0x00881F30
void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540

inline void *bfmeAllocate(unsigned int bytes)
{
	if (bytes > 0x80)
		return bfmeNewAlloc(bytes);

	return bfmeAllocNode(bytes);
}

extern void * (__cdecl *bfmeMemCopy)(void *destination, const void *source, unsigned int bytes);

class Gen_004F9C80
{
public:
	void bfmeReserve(unsigned int count);

private:
	short *m_bfmeStart;					// +0x00
	short *m_bfmeFinish;					// +0x04
	short *m_bfmeEnd;					// +0x08
};

class Gen_004FA770
{
public:
	void bfmeAssign(const short *first, const short *last, void *tag);

private:
	short *m_bfmeStart;					// +0x00
	short *m_bfmeFinish;					// +0x04
	short *m_bfmeEnd;					// +0x08
};

class Gen_006616A0
{
public:
	void bfmeAssign(const short *first, const short *last, void *tag);

private:
	short *m_bfmeStart;					// +0x00
	short *m_bfmeFinish;					// +0x04
	short *m_bfmeEnd;					// +0x08
};

// ?bfmeReserve@Gen_004F9C80@@QAEXI@Z
void Gen_004F9C80::bfmeReserve(unsigned int count)
{
	if (count <= (unsigned int)-1 / sizeof(short) && count > 0)
	{
		short *block = (short *)bfmeAllocate(count * sizeof(short));

		m_bfmeEnd = block + count;
		m_bfmeStart = block;
		m_bfmeFinish = block;
	}
}

// ?bfmeAssign@Gen_004FA770@@QAEXPBF0PAX@Z
void Gen_004FA770::bfmeAssign(const short *first, const short *last, void *tag)
{
	int bytes = (const char *)last - (const char *)first;
	unsigned int count = (unsigned int)(last - first) + 1;

	if (count <= (unsigned int)-1 / sizeof(short) && count > 0)
	{
		short *block = (short *)bfmeAllocate(count * sizeof(short));

		m_bfmeEnd = block + count;
		m_bfmeStart = block;
		m_bfmeFinish = block;
	}

	short *cursor = m_bfmeStart;

	if (last != first)
		cursor = (short *)((char *)bfmeMemCopy(cursor, first, bytes) + bytes);

	m_bfmeFinish = cursor;
	*cursor = 0;
}

// ?bfmeAssign@Gen_006616A0@@QAEXPBF0PAX@Z
void Gen_006616A0::bfmeAssign(const short *first, const short *last, void *tag)
{
	int bytes = (const char *)last - (const char *)first;
	unsigned int count = (unsigned int)(last - first) + 1;

	if (count <= (unsigned int)-1 / sizeof(short) && count > 0)
	{
		short *block = (short *)bfmeAllocate(count * sizeof(short));

		m_bfmeEnd = block + count;
		m_bfmeStart = block;
		m_bfmeFinish = block;
	}

	short *cursor = m_bfmeStart;

	if (last != first)
		cursor = (short *)((char *)bfmeMemCopy(cursor, first, bytes) + bytes);

	m_bfmeFinish = cursor;
	*cursor = 0;
}
