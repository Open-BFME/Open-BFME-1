// ?maxOverrideField43C@Rva0015A560List@@QBEHXZ
// partial score=0.88 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Retail 0x0015A560, 63 bytes. Same-dump leftover as lookForInnerTarget.
// Walks a counted inline Object* list, takes each object's template at +4,
// follows the override chain via the 0x000022BB ILT, then returns the max
// of the dword at template+0x43C.
//
// Closest MSVC 7.1 shape: 61 vs 63. Prologue through +0x10 is exact. Wall is
// `add eax,4; mov eax,[eax]` folding to `mov eax,[eax+4]`.

typedef int Int;

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride();

	unsigned char m_pad00[4];
	BfmeOverridable *m_nextOverride;				// +0x04
	unsigned char m_pad08[0x43C - 0x08];
	Int m_value43C;									// +0x43C
};

struct Rva0015A560Object
{
	void *m_vptr;
	BfmeOverridable *m_template;					// +0x04
};

class Rva0015A560List
{
public:
	Int maxOverrideField43C() const;

	Int m_count;									// +0x00
	Rva0015A560Object *m_items[1];					// +0x04
};

Int Rva0015A560List::maxOverrideField43C() const
{
	Int count = m_count;
	Int best = 0;
	if (count > 0)
	{
		Rva0015A560Object *const *it = m_items;
		Int remaining = count;
		do
		{
			int *slot = (int *)*it;
			++slot;
			BfmeOverridable *tmpl = *(BfmeOverridable **)slot;
			if (tmpl && tmpl->m_nextOverride)
				tmpl = tmpl->m_nextOverride->friend_getFinalOverride();
			Int v = tmpl->m_value43C;
			if (v > best)
				best = v;
			it++;
			--remaining;
		} while (remaining);
	}
	return best;
}
