// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: two more bodies out of d_0005b6c0.asm.
//
// 0x0005FA90 is a __thiscall forwarder, not a __stdcall one: it never touches
// ecx and its callee at 0x0005ECD0 opens `mov ebx,ecx`, so the this pointer is
// passed through untouched and both are members of the same class. What the
// wrapper adds is two zero arguments in the middle of the list -- the pushes
// read out as (a0 a1 a2 0 0 a3) -- and the return value is simply left in eax.
//
// 0x00065F30 is a float table lookup over 0x40-byte entries based at this+0.
// The first test is against the 0.0f constant at 0x01075350 with `test ah,0x44`
// (C3 and C2) and a jp: even parity covers less greater and unordered and only
// equality is odd, so the guard is `value == 0.0f` and it returns null. The
// second compare is `test ah,1` on C0 alone, which is the NaN-careless form MSVC
// emits for `>=` and not the `test ah,5` + jp it emits for `<`: the source tests
// value >= entry->threshold and returns the pointer at +4, falling through to
// the one at +8 below it.
//
// Identity is address-derived for both.

typedef int Int;
typedef float Real;

class Rva0005FA90Factory
{
public:
	void *create(void *a0, void *a1, void *a2, void *a3);

private:
	void *createEx(void *a0, void *a1, void *a2, void *a3, void *a4, void *a5);
};

// ?create@Rva0005FA90Factory@@QAEPAXPAX000@Z
void *Rva0005FA90Factory::create(void *a0, void *a1, void *a2, void *a3)
{
	return createEx(a0, a1, a2, 0, 0, a3);
}

// ---------------------------------------------------------------------------

struct Rva00065F30Entry
{
	Real m_threshold;									///< entry+0x00
	void *m_atOrAbove;									///< entry+0x04
	void *m_below;										///< entry+0x08
	unsigned char m_unreconstructed_0C[0x34];
};

class Rva00065F30Table
{
public:
	void *lookup(Int index, Real value, Int unused);

private:
	Rva00065F30Entry m_entries[1];						///< retail this+0x00
};

// ?lookup@Rva00065F30Table@@QAEPAXHMH@Z
void *Rva00065F30Table::lookup(Int index, Real value, Int unused)
{
	if (value == 0.0f)
	{
		return 0;
	}

	Rva00065F30Entry *entry = &m_entries[index];

	if (value >= entry->m_threshold)
	{
		return entry->m_atOrAbove;
	}

	return entry->m_below;
}
