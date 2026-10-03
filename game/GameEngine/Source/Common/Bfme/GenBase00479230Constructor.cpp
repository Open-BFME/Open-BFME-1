// cl: /DNDEBUG /MD /EHsc
// Open-BFME: GenBase00479230::GenBase00479230, retail 0x00479230, 17 bytes.
//
// A vftable store and two zeroed words -- no base to run, so `this' goes
// straight into eax and the zero is materialised once for both stores.
//
// The destructor is defined in-class so the vftable slot 0 this constructor
// stores (retail 0x010F77AC) resolves inside this TU; declaring the virtual
// with no body left ??1GenBase00479230@@UAE@XZ unresolved at link.  It carries
// no retail body claim: slot 0 of that vftable is retail 0x0040B8FC, a `j'
// gap thunk owned by game/gen_small/gthunks_012.cpp whose target
// ?bfmeDestroy@Bfme5Detachable@@QAEPAXH@Z (0x00479C80) is the real identity,
// so the destructor body belongs to another ledger row.
//
// Slot 1 of that vftable (0x00403DF0 -> ?invokeFallback@Rva00479270Delegate@@QAEEXZ
// at 0x00479270) has no counterpart in this declaration; nothing references it
// from here, so the ctor's 17 bytes are unaffected.

class GenBase00479230
{
public:
	GenBase00479230();

	virtual ~GenBase00479230() {}

private:
	void *m_a;						// +0x04
	void *m_b;						// +0x08
};

GenBase00479230::GenBase00479230()
{
	m_a = 0;
	m_b = 0;
}
