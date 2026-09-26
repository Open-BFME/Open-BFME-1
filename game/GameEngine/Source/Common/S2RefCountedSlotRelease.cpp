// Six __thiscall void members that release a reference-counted object held in
// one slot of the owner and clear the slot:
//
//     push esi / mov esi,ecx / mov ecx,[esi+<OFFSET>] / test ecx,ecx / je end
//     dec dword ptr [ecx+4] / jne clear / mov eax,[ecx] / call dword ptr [eax]
//     clear: mov dword ptr [esi+<OFFSET>],0 / end: pop esi / ret
//
// WHAT THE BYTES SHOW.  The counter lives at +4 of the pointee and is
// PRE-decremented (`dec` then a flag test), and the release runs only when it
// reaches zero, through the FIRST vtable slot of the pointee with no arguments.
// The clear of the slot is INSIDE the null test but OUTSIDE the zero-count
// test: the `je` at the top skips past it, the `jne` in the middle lands on it.
// That is `if (p) { if (--p->count == 0) p->slot0(); p = 0; }` and not
// `if (p) { ... } p = 0;`, which would leave the clear unconditional.
//
// SIX OWNERS, FOUR OFFSETS: 0x14 twice, 0x68 twice, 0x70 and 0xC8.  The two
// pairs are byte-identical; retail kept all six at distinct addresses.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived.  The bytes do not say
// whether the counter is signed, nor what the first vtable slot is called; a
// destroy-on-zero slot 0 is the only thing they establish.

class GenRefCounted
{
public:
	virtual void releaseSelf();
	int m_refCount;
};

#define BFME_REF_SLOT_RELEASE( NAME, OFFSET )                             \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void releaseSlot();                                               \
		char m_lead[ OFFSET ];                                            \
		GenRefCounted *m_held;                                            \
	};                                                                    \
	void NAME::releaseSlot()                                              \
	{                                                                     \
		GenRefCounted *held = m_held;                                     \
		if( held )                                                        \
		{                                                                 \
			if( --held->m_refCount == 0 )                                 \
				held->releaseSelf();                                      \
			m_held = 0;                                                   \
		}                                                                 \
	}

// @?releaseSlot@Rva0090BCD0@@QAEXXZ 0x0090BCD0
BFME_REF_SLOT_RELEASE( Rva0090BCD0, 0x14 )
// @?releaseSlot@Rva00970E20@@QAEXXZ 0x00970E20
BFME_REF_SLOT_RELEASE( Rva00970E20, 0x14 )
// @?releaseSlot@Rva007AEC90@@QAEXXZ 0x007AEC90
BFME_REF_SLOT_RELEASE( Rva007AEC90, 0x68 )
// @?releaseSlot@Rva007B0470@@QAEXXZ 0x007B0470
BFME_REF_SLOT_RELEASE( Rva007B0470, 0x68 )
// @?releaseSlot@Rva008FEC30@@QAEXXZ 0x008FEC30
BFME_REF_SLOT_RELEASE( Rva008FEC30, 0x70 )
// @?releaseSlot@Rva0092CEC0@@QAEXXZ 0x0092CEC0
BFME_REF_SLOT_RELEASE( Rva0092CEC0, 0xC8 )
