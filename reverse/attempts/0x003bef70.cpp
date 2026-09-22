// ?bfmeRecentDelta@Rva003BEF70Owner@@QAEXPAURva003BEF70Range@@PAURva003BEF70Coord2D@@@Z
// partial score=0.76 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc
// ?d_003bef70@@YAXXZ @ 0x003BEF70, 120 bytes.
//
// Reads the last two (clamped) elements of a 4-byte-element range [begin,end)
// through the MATCHED Rva003C9470Owner::fallback(Rva003C9470Key*,
// Rva003C9470Output*) thiscall (Rva003C9470StatusFallback.cpp, callee ILT
// 0x00033EBA -> 0x003C9470) and writes their componentwise difference
// (second-to-last minus last) to the caller-supplied 2-float output. Both
// indices clamp to 0 so a 0- or 1-element range never underflows. No named
// caller, vtable, or source declaration proves the owning class or method,
// so both are address-derived; the receiver's own "owner" pointer at +0x28
// is the thiscall target for fallback().

class Rva003C9470Key;

struct Rva003C9470Output
{
	union
	{
		float m_x;
		unsigned int m_rawX;
	};
	union
	{
		float m_y;
		unsigned int m_rawY;
	};
};

class Rva003C9470Owner
{
public:
	bool fallback(Rva003C9470Key *key, Rva003C9470Output *output);
};

struct Rva003BEF70Range
{
	Rva003C9470Key **m_begin;
	Rva003C9470Key **m_end;
};

struct Rva003BEF70Coord2D
{
	union
	{
		float x;
		unsigned int m_rawX;
	};
	union
	{
		float y;
		unsigned int m_rawY;
	};
};

class Rva003BEF70Owner
{
public:
	void bfmeRecentDelta(Rva003BEF70Range *range, Rva003BEF70Coord2D *out);

private:
	char m_pad00[0x28];
	Rva003C9470Owner *m_owner;			// +0x28
};

// ?d_003bef70@@YAXXZ
void Rva003BEF70Owner::bfmeRecentDelta(Rva003BEF70Range *range, Rva003BEF70Coord2D *out)
{
	Rva003BEF70Owner *self = this;
	int count = (int)(range->m_end - range->m_begin);

	int last = count - 1;
	if (last < 0)
		last = 0;

	int secondLast = count - 2;
	if (secondLast < 0)
		secondLast = 0;

	Rva003C9470Output lastFill;
	self->m_owner->fallback(range->m_begin[last], &lastFill);

	Rva003C9470Output secondLastFill;
	self->m_owner->fallback(range->m_begin[secondLast], &secondLastFill);

	out->m_rawX = secondLastFill.m_rawX;
	out->x -= lastFill.m_x;
	out->m_rawY = secondLastFill.m_rawY;
	out->y -= lastFill.m_y;
}
