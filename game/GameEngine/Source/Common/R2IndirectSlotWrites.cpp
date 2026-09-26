// The last two members of the mnemonic-only family anchored at 0x00061580.
// Retail:
//
//     mov eax,[ecx-<BACK>] / mov edx,[eax+4]
//     mov dword ptr [edx+ecx-<BACK>],<ADDRESS> / ret
//
// WHAT THE BYTES SHOW.  `this` in ecx, bare `ret`: __thiscall, no stack
// arguments.  A pointer is read a fixed distance BACK from `this`; the dword at
// +4 of what it points at is used as a DISPLACEMENT, not as data; and an
// absolute address is stored that many bytes past the same back-reference
// point.  Eleven of the fifteen bytes are concrete -- only the stored address
// is a relocation, and the patcher fills that from retail.
//
// THIS IS THE SHAPE MSVC EMITS FOR A VIRTUAL-BASE VFTABLE FIXUP: a vbptr at
// offset 0 of the object, entry 1 of the vbtable giving the base's
// displacement, and a vftable written at that displacement.  IT IS NOT WRITTEN
// THAT WAY HERE, because a virtual-inheritance spelling that produces these
// exact bytes was not found, and asserting a base hierarchy the bytes only
// suggest would claim more than they show.  What is written is the pointer
// arithmetic the instructions perform, and nothing else: the layout, the
// hierarchy and what lives at the stored address are NOT RECOVERED.
//
// THE BACK-REFERENCE IS COMPUTED TWICE ON PURPOSE.  Naming `(char *)this - 8`
// once and reusing it makes MSVC 7.1 fold the base into the register it already
// has and encode the store as `mov [ecx+edx-8]` (SIB 0x11); recomputing it
// leaves ecx as the INDEX and edx as the base, which is `mov [edx+ecx-8]`
// (SIB 0x0A) and is what retail contains.  Same address, same length, different
// byte -- a size comparison cannot see it, and the gate can.
//
// IDENTITY IS NOT RECOVERED.  Both names are address-derived.

#define R2_INDIRECT_SLOT_WRITE( NAME, BACK, ADDRESS )                     \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void run();                                                       \
	};                                                                    \
	void NAME::run()                                                      \
	{                                                                     \
		char *held = *(char **)( (char *)this - BACK );                   \
		*(void **)( (char *)this - BACK + *(int *)( held + 4 ) ) =         \
			&ADDRESS;                                                     \
	}

extern int R2Data0112F2F4;
extern int R2Data0112F304;

R2_INDIRECT_SLOT_WRITE( Rva005381F0, 8, R2Data0112F2F4 )
R2_INDIRECT_SLOT_WRITE( Rva005BFA20, 4, R2Data0112F304 )
