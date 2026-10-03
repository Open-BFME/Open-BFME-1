// RVA0035E710,56B. Preserve the banked bfmeUnlinkZN and bfmeDoZN names.
// Physical helper0035E5A0 (ILT0000CEC8) saves incoming ECX in EBX at+0x16
// and reads receiver+0C/+18: both caller/helper require member thiscall.
// The bank incorrectly declared a free stdcall helper and spent twenty
// verdicts on register allocation. Correct ABI plus walking the link slot
// directly reproduces all56B without register barriers or padding.
// Node next is at+0. The helper receives the address of the predecessor
// link plus the chosen/fallback pointer; semantic owner remains unknown.
extern void j_0000cec8();

struct BfmeNodeZN
{
	BfmeNodeZN *m_bfmeNextZN;
};

class Rva0035E710Owner {
public:
 void bfmeDoZN(void *a, BfmeNodeZN **link, void *what);
 void bfmeUnlinkZN(void *a, BfmeNodeZN **link, BfmeNodeZN *target, void *fallback, void *chosen);
};

void Rva0035E710Owner::bfmeUnlinkZN(void *a, BfmeNodeZN **link, BfmeNodeZN *target,
                            void *fallback, void *chosen)
{
    while (*link != target)
    {
        if (*link == 0) return;
        link = &(*link)->m_bfmeNextZN;
    }

	// Retail calls helper 0x0035E5A0 through its ILT thunk 0x0000CEC8.
	typedef void (Rva0035E710Owner::*DoZN)(void *, BfmeNodeZN **, void *);
	union { void (*fn)(); DoZN call; } doZN = { j_0000cec8 };
	(this->*doZN.call)(a, link, chosen != 0 ? chosen : fallback);
}
