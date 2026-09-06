// ?bfmeCtorHelper_00844460@@YGXPAVGen_008443A0@@PAX1@Z
// partial score=0.55 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: fuzzy-twin of Gen_0049A330's constructor
// (Bfme5SehStarters.cpp, retail 0x0049A330, 85 bytes): same
// BfmeSehPair/BfmeSehSlot zero-and-start shape (two zeroed words, a member
// with a destructor zeroed third, then bfmeStart(first, second, &X)), but
// this body takes its "self" pointer through an explicit stack argument
// (offset +0x18) instead of an implicit ecx this -- so it is not a real
// C++ constructor but a __stdcall placement helper, and the "third" pointer
// it hands to bfmeStart is &self (the helper's own stack-resident first
// parameter) rather than &second, since the twin's usual &second trick
// needs the address of a genuine local. The EH frame's this-copy slot is
// left 0 here (the twin writes the real this there) -- consistent with
// there being no true 'this' for the unwind machinery to track.
// The callee (0x00042BB8) is Gen_008443A0::bfmeStart, i.e. this constructs
// a Gen_008443A0 object through a raw pointer rather than through its own
// named constructor.

class BfmeSehPair
{
public:
	BfmeSehPair(void) : m_bfmeA(0), m_bfmeB(0) {}

	int m_bfmeA;						// +0x00
	int m_bfmeB;						// +0x04
};

class BfmeSehSlot
{
public:
	BfmeSehSlot(void) : m_bfmeC(0) {}
	~BfmeSehSlot(void);

	int m_bfmeC;						// +0x00
};

class Gen_008443A0 : public BfmeSehPair
{
public:
	Gen_008443A0(void *first, void *second, void *third);
	void bfmeStart(void *first, void *second, void **slot);	// retail 0x00042BB8

	BfmeSehSlot m_bfmeSlot;					// +0x08
};

void *operator new(unsigned int, void *place) { return place; }

// __stdcall placement helper: builds a Gen_008443A0 in place at *self.
// Address-derived name pending the real symbol (identity unknown).
static void __stdcall bfmeCtorHelper_00844460(Gen_008443A0 *self, void *first, void *second)
{
	self->m_bfmeA = 0;
	self->m_bfmeB = 0;
	new (&self->m_bfmeSlot) BfmeSehSlot();
	self->bfmeStart(first, second, (void **)&self);
}

// absent from retail: gives the static helper an external caller so it is
// emitted and reachable by RVA.
void Rva00844460CallCtorHelper(Gen_008443A0 *self, void *first, void *second)
{
	bfmeCtorHelper_00844460(self, first, second);
}
