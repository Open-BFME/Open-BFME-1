// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: the 18-byte constructor tail at 0x0051B690, address-derived name.
// Converted out of game/gen_asm/d_00512e40.asm.
//
// IDENTITY IS NOT ASSERTED. The class name is the address of the body and
// nothing more: the vtable it installs (0x01105FCC, .rdata RVA 0x00D05FCC)
// has no targets/game/reverse/vtables.tsv entry, and the base body it chains to at
// 0x00490420 is itself an unnamed gen_asm dump.
//
// What the bytes say: a constructor that runs a base constructor, overwrites
// the vfptr at this+0 with 0x01105FCC, and returns this -- the standard MSVC
// most-derived constructor tail. The base call is a `call rel32` through
// incremental-link thunk 0x0001F2DA; the resolver reaches it from the
// already-pinned `?b_00490420@@YAXXZ` candidate, so no new pin was needed.
// It is spelled as a plain __cdecl call because the base body needs `this`
// in ecx and ecx already holds it there -- writing a member call instead
// would make the compiler reload ecx that retail does not reload.

void b_00490420(void);

struct Gen_0051b690
{
	void *ctorTail(void);
};

void *Gen_0051b690::ctorTail(void)
{
	b_00490420();
	*(unsigned *)this = 0x1105FCCu;
	return this;
}
