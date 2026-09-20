// ?rvaReleaseEntry@Rva0033B1D0Owner@@QAEPAPAVRva0033B1D0Node@@PAPAV2@_N1@Z
// partial score=0.45 date=2026-09-21
// cl: /O2 /Ob1 /EHs-c- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Retail 0x0033B1D0, 127 bytes, __thiscall (ret 0xc, 3 stack args): an
// element pointer P1 into a vector<ScienceInfo*>-shaped array embedded at
// this+0xc (begin/finish at +0xc/+0x10, matching the sibling
// Rva003BF4C0OwnedVectorErase.cpp idiom), plus two bools. *P1 is walked as a
// singly linked "override chain" (matching Overridable::m_nextOverride, the
// same shape at +0x28 -- not independently offset-witnessed for this
// specific retail layout, so the node stays address-derived rather than
// claiming Overridable/ScienceInfo by name) and each node is destroyed via
// its own scalar deleting destructor (`delete`).
//
// When *P1 is already null and the caller asked for chain release, the
// element is dropped from the array with a plain BfmeMemMove tail-shift and
// finish--, exactly like the sibling file. When *P1 is non-null, either the
// whole chain is destroyed (single flag) or just the head is (advancing to
// the next override) and, if the array slot is now null and the caller also
// asked for it, the position is erased from the vector proper through the
// SAME already-matched STLport instantiation Science.cpp's
// scienceStoreRetainVectorErase uses (dup_339d10 at 0x00339D10) -- pinned
// again here under this function's own name since the call site needs the
// return value (the erase call's own iterator result), which that void
// wrapper does not expose.

extern "C" __declspec(dllimport) void *__cdecl BfmeMemMove(
	void *destination, const void *source, unsigned int bytes);

typedef bool Bool;

class Rva0033B1D0Node
{
public:
	virtual ~Rva0033B1D0Node();

private:
	unsigned char m_prefix[0x28];

public:
	Rva0033B1D0Node *m_next;   // +0x28
};

class Rva0033B1D0Vector
{
public:
	Rva0033B1D0Node **erase(Rva0033B1D0Node **it);

	Rva0033B1D0Node **m_begin;   // +0x0
	Rva0033B1D0Node **m_finish;  // +0x4
};

class Rva0033B1D0Owner
{
public:
	Rva0033B1D0Node **rvaReleaseEntry(Rva0033B1D0Node **it, Bool releaseChain, Bool eraseIfEmpty);

private:
	unsigned char m_prefix[0xc];
	Rva0033B1D0Vector m_vec;   // +0xc
};

// ?rvaReleaseEntry@Rva0033B1D0Owner@@QAEPAPAVRva0033B1D0Node@@PAPAV2@_N1@Z
Rva0033B1D0Node **Rva0033B1D0Owner::rvaReleaseEntry(Rva0033B1D0Node **it, Bool releaseChain, Bool eraseIfEmpty)
{
	Rva0033B1D0Node *head = *it;
	if (head == 0)
	{
		if (releaseChain)
		{
			Rva0033B1D0Node **next = it + 1;
			if (m_vec.m_finish != next)
				BfmeMemMove(it, next, (unsigned int)((char *)m_vec.m_finish - (char *)next));

			--m_vec.m_finish;
		}

		return it;
	}

	if (releaseChain)
	{
		do
		{
			Rva0033B1D0Node *next = head->m_next;
			delete head;
			head = next;
		}
		while (head != 0);

		*it = 0;
	}
	else
	{
		*it = head->m_next;
		delete head;
		if (*it != 0)
			return it;
	}

	if (eraseIfEmpty)
		return m_vec.erase(it);

	return it;
}
