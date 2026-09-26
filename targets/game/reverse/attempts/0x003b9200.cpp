// ?rva003B9200@Rva003B9200Owner@@QBE_NPBVRva003B9100@@@Z
// partial score=0.86 date=2026-09-22
// cl: /DNDEBUG /MD /EHs-c-
// Retail 0x003B9200, 79 bytes, a carved extent with one caller.  A __thiscall
// const predicate over a contiguous run of four-byte elements at +0x0C/+0x10:
// for each element it calls the matched
// ?contains@Rva003B9100@@QBE_NABVAsciiString@@@Z at 0x003B9100 through ILT
// 0x000202BB with the ELEMENT'S ADDRESS, returns true on the first hit and
// false when the run is exhausted.  The callee taking a const AsciiString& is
// what fixes the element type and the four-byte stride.
//
// Size is exact and the whole loop, the latch (which re-derives the count from
// memory every iteration), the loop-alignment nop and both epilogues are exact.
// Eleven bytes differ, all in the four-instruction prologue: retail gives ebx to
// the induction pointer and edi to the index, and VC7.1 hands them the other way
// round, which also moves the lazy `push edi`.
//
// The raw two-pointer model above is what took this from 67 differing bytes to
// eleven -- an _STL::vector member with size() in the condition compiles the
// begin load through a second register (`mov ebp,ebx`) and costs six more.
// Exhausted on the register pair: both local definition orders, a split
// `for (i = 0, name = m_begin; ...)`, the reversed increment `name++, i++`
// (16), the reversed comparison (12), the while form (16), non-const element
// pointers, and the index-only `m_begin[i]` body (62, which drops the induction
// pointer entirely).
//
// IDENTITY IS NOT RECOVERED; the name is address-derived.
class AsciiString
{
public:
	void *m_data;
};

class Rva003B9100
{
public:
	bool contains(const AsciiString &name) const;
};

class Rva003B9200Owner
{
public:
	bool rva003B9200(const Rva003B9100 *other) const;

private:
	char m_lead[0xc];
	const AsciiString *m_begin;
	const AsciiString *m_end;
};

// ?rva003B9200@Rva003B9200Owner@@QBE_NPBVRva003B9100@@@Z
bool Rva003B9200Owner::rva003B9200(const Rva003B9100 *other) const
{
	const AsciiString *name = m_begin;

	for (unsigned int i = 0; i < (unsigned int)(m_end - m_begin); i++, name++)
	{
		if (other->contains(*name))
			return true;
	}

	return false;
}
