// ?Rva0042F0D0StoreLabel@@YG_NVAsciiStringXK@@@Z
// partial score=0.85 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Fuzzy twin (ratio 0.893) of Gen_00602DB0::bfmeStoreXK (0x00602DB0, 127B,
// BfmeLabelStoreXK.cpp). Same buffer/length guard shape and the same
// double-release-on-both-arms epilogue duplication, but this target: (1) has
// no second "unused" parameter (ret 4, not ret 8 -- a single by-value string
// argument passed by hidden pointer); (2) never calls set()/bfmeSetXK on the
// true arm, it just releases the buffer and returns true; and (3) has no
// "mov [esp+8], 0" EH-state pre-store because with no throwing set() call on
// the true arm the destructor cleanup state is unambiguous.

struct BfmeBufferXK
{
	int m_bfmeRef;						// +0x00
	short m_bfmeLength;					// +0x04
};

class AsciiStringXK
{
public:
	AsciiStringXK(const AsciiStringXK &other);
	~AsciiStringXK(void);

protected:
	BfmeBufferXK *m_bfmeData;				// +0x00
};

class BfmeStrXK0042F0D0 : private AsciiStringXK
{
public:
	const BfmeBufferXK *bfmeBufferXK(void) const
	{
		return m_bfmeData;
	}
};

// address-derived name (real owner/name unproven)
bool __stdcall Rva0042F0D0StoreLabel(AsciiStringXK value)
{
	const BfmeBufferXK *buffer = ((BfmeStrXK0042F0D0 *)&value)->bfmeBufferXK();

	if (buffer && buffer->m_bfmeLength)
		return true;

	return false;
}
