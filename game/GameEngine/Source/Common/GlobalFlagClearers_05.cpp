// 90 of the image's 530 bodies with one shape:
//
//     mov eax,[<address>] / and eax,<mask> / mov [<address>],eax / ret
//
// WHAT THE BYTES SHOW.  A dword is read from a fixed .data address, one or more
// bits are cleared, and the result is written back to the same address and left
// in eax.  No argument is touched and nothing is pushed.  Fourteen bytes when
// the mask fits a sign-extended imm8, sixteen when it needs a full imm32; the
// masks are what a bit-clear looks like -- 0xFFFFFFFE, 0xFFFFFEFF and the like
// -- so these are one setter per flag over a bank of flag words.  530 bodies
// share 398 distinct globals, up to 25 flags in the busiest word.
//
// WHY IT LOADS AND STORES THROUGH eax.  Written as a plain `g &= MASK`, MSVC
// 7.1 emits `and dword ptr [g],<mask>` in eight bytes -- a read-modify-write in
// one instruction, which is measurably not this.  What emits retail's separate
// load, mask and store is the value being wanted afterwards: `return g &= MASK`
// leaves it in eax, which the `ret` here does too.  Declaring the global
// `volatile` produces the identical bytes, so the bytes do not settle which the
// source said; the returning form is written because it asserts only that the
// result is live in eax, which is what the instruction stream shows.
//
// IDENTITY IS NOT RECOVERED, for the globals any more than for the functions;
// every name is derived from an address.

extern unsigned int g_Va012F4BC4;
extern unsigned int g_Va012F4BD0;
extern unsigned int g_Va012F4BDC;
extern unsigned int g_Va012F4BE8;
extern unsigned int g_Va012F4BFC;
extern unsigned int g_Va012F4C08;
extern unsigned int g_Va012F4C14;
extern unsigned int g_Va012F4C2C;
extern unsigned int g_Va012F4C34;
extern unsigned int g_Va012F4C4C;
extern unsigned int g_Va012F4C70;
extern unsigned int g_Va012F684C;
extern unsigned int g_Va012F6930;
extern unsigned int g_Va012F6938;
extern unsigned int g_Va012F6940;
extern unsigned int g_Va012F6948;
extern unsigned int g_Va012F6950;
extern unsigned int g_Va012F6958;
extern unsigned int g_Va012F6970;
extern unsigned int g_Va012F6A18;
extern unsigned int g_Va012F6A48;
extern unsigned int g_Va012F6A78;
extern unsigned int g_Va012F6AA8;
extern unsigned int g_Va012F6AD8;
extern unsigned int g_Va012F6DDC;
extern unsigned int g_Va012F7000;
extern unsigned int g_Va012F703C;
extern unsigned int g_Va012F7044;
extern unsigned int g_Va012F7760;
extern unsigned int g_Va012F7778;
extern unsigned int g_Va012F7780;
extern unsigned int g_Va012F7794;
extern unsigned int g_Va012F779C;
extern unsigned int g_Va012F7FD8;
extern unsigned int g_Va012F8528;
extern unsigned int g_Va01304B40;
extern unsigned int g_Va01304B58;
extern unsigned int g_Va01304B70;
extern unsigned int g_Va01304BA4;
extern unsigned int g_Va01304BAC;
extern unsigned int g_Va01304BBC;
extern unsigned int g_Va01304BC4;
extern unsigned int g_Va01304BCC;
extern unsigned int g_Va01304BD4;
extern unsigned int g_Va01305A48;
extern unsigned int g_Va01305A54;
extern unsigned int g_Va01305A78;
extern unsigned int g_Va013068E8;
extern unsigned int g_Va013068F0;
extern unsigned int g_Va01306C68;
extern unsigned int g_Va01306CE4;
extern unsigned int g_Va01306CFC;
extern unsigned int g_Va01306D4C;
extern unsigned int g_Va01306D60;
extern unsigned int g_Va01306D74;
extern unsigned int g_Va013073B4;
extern unsigned int g_Va01341210;
extern unsigned int g_Va0134B0E0;
extern unsigned int g_Va0134B124;
extern unsigned int g_Va0134B278;
extern unsigned int g_Va0134C66C;
extern unsigned int g_Va0134C6B8;
extern unsigned int g_Va0134FB14;

unsigned int Rva00C374E0ClearFlag( void )
{
	return g_Va012F4BC4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C374EEClearFlag( void )
{
	return g_Va012F4BC4 &= 0xFFFFFFFDu;
}

unsigned int Rva00C37510ClearFlag( void )
{
	return g_Va012F4BD0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C3751EClearFlag( void )
{
	return g_Va012F4BD0 &= 0xFFFFFFFDu;
}

unsigned int Rva00C37540ClearFlag( void )
{
	return g_Va012F4BDC &= 0xFFFFFFFEu;
}

unsigned int Rva00C3754EClearFlag( void )
{
	return g_Va012F4BDC &= 0xFFFFFFFDu;
}

unsigned int Rva00C378F0ClearFlag( void )
{
	return g_Va012F4BE8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C378FEClearFlag( void )
{
	return g_Va012F4BE8 &= 0xFFFFFFFDu;
}

unsigned int Rva00C37998ClearFlag( void )
{
	return g_Va012F4BFC &= 0xFFFFFFFEu;
}

unsigned int Rva00C379A6ClearFlag( void )
{
	return g_Va012F4BFC &= 0xFFFFFFFDu;
}

unsigned int Rva00C379B4ClearFlag( void )
{
	return g_Va012F4BFC &= 0xFFFFFFFBu;
}

unsigned int Rva00C379C2ClearFlag( void )
{
	return g_Va012F4BFC &= 0xFFFFFFF7u;
}

unsigned int Rva00C37A60ClearFlag( void )
{
	return g_Va012F4C08 &= 0xFFFFFFFEu;
}

unsigned int Rva00C37A6EClearFlag( void )
{
	return g_Va012F4C08 &= 0xFFFFFFFDu;
}

unsigned int Rva00C37AA0ClearFlag( void )
{
	return g_Va012F4C14 &= 0xFFFFFFFEu;
}

unsigned int Rva00C37ABEClearFlag( void )
{
	return g_Va012F4C14 &= 0xFFFFFFFDu;
}

unsigned int Rva00C37D80ClearFlag( void )
{
	return g_Va012F4C2C &= 0xFFFFFFFEu;
}

unsigned int Rva00C37D8EClearFlag( void )
{
	return g_Va012F4C2C &= 0xFFFFFFFDu;
}

unsigned int Rva00C37DF0ClearFlag( void )
{
	return g_Va012F4C34 &= 0xFFFFFFFEu;
}

unsigned int Rva00C38040ClearFlag( void )
{
	return g_Va012F4C4C &= 0xFFFFFFFEu;
}

unsigned int Rva00C38056ClearFlag( void )
{
	return g_Va012F4C4C &= 0xFFFFFFFDu;
}

unsigned int Rva00C38064ClearFlag( void )
{
	return g_Va012F4C4C &= 0xFFFFFFFBu;
}

unsigned int Rva00C38082ClearFlag( void )
{
	return g_Va012F4C4C &= 0xFFFFFFF7u;
}

unsigned int Rva00C388A0ClearFlag( void )
{
	return g_Va012F4C70 &= 0xFFFFFFFEu;
}

unsigned int Rva00C3A6F0ClearFlag( void )
{
	return g_Va012F684C &= 0xFFFFFFFEu;
}

unsigned int Rva00C3A706ClearFlag( void )
{
	return g_Va012F684C &= 0xFFFFFFFDu;
}

unsigned int Rva00C3AC30ClearFlag( void )
{
	return g_Va012F6930 &= 0xFFFFFFFEu;
}

unsigned int Rva00C3AC50ClearFlag( void )
{
	return g_Va012F6938 &= 0xFFFFFFFEu;
}

unsigned int Rva00C3AC70ClearFlag( void )
{
	return g_Va012F6940 &= 0xFFFFFFFEu;
}

unsigned int Rva00C3AC90ClearFlag( void )
{
	return g_Va012F6948 &= 0xFFFFFFFEu;
}

unsigned int Rva00C3ACB0ClearFlag( void )
{
	return g_Va012F6950 &= 0xFFFFFFFEu;
}

unsigned int Rva00C3ACD0ClearFlag( void )
{
	return g_Va012F6958 &= 0xFFFFFFFEu;
}

unsigned int Rva00C3AFD0ClearFlag( void )
{
	return g_Va012F6970 &= 0xFFFFFFFEu;
}

unsigned int Rva00C3B170ClearFlag( void )
{
	return g_Va012F6A18 &= 0xFFFFFFFEu;
}

unsigned int Rva00C3B1B0ClearFlag( void )
{
	return g_Va012F6A48 &= 0xFFFFFFFEu;
}

unsigned int Rva00C3B1F0ClearFlag( void )
{
	return g_Va012F6A78 &= 0xFFFFFFFEu;
}

unsigned int Rva00C3B230ClearFlag( void )
{
	return g_Va012F6AA8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C3B270ClearFlag( void )
{
	return g_Va012F6AD8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C3C460ClearFlag( void )
{
	return g_Va012F6DDC &= 0xFFFFFFFEu;
}

unsigned int Rva00C3C870ClearFlag( void )
{
	return g_Va012F7000 &= 0xFFFFFFFEu;
}

unsigned int Rva00C3D580ClearFlag( void )
{
	return g_Va012F703C &= 0xFFFFFFFEu;
}

unsigned int Rva00C3D890ClearFlag( void )
{
	return g_Va012F7044 &= 0xFFFFFFFEu;
}

unsigned int Rva00C48D40ClearFlag( void )
{
	return g_Va012F7760 &= 0xFFFFFFFEu;
}

unsigned int Rva00C4917BClearFlag( void )
{
	return g_Va012F7778 &= 0xFFFFFFFEu;
}

unsigned int Rva00C49248ClearFlag( void )
{
	return g_Va012F7780 &= 0xFFFFFFFEu;
}

unsigned int Rva00C49288ClearFlag( void )
{
	return g_Va012F7794 &= 0xFFFFFFFEu;
}

unsigned int Rva00C49340ClearFlag( void )
{
	return g_Va012F779C &= 0xFFFFFFFEu;
}

unsigned int Rva00C49FC8ClearFlag( void )
{
	return g_Va012F7FD8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C4C0E0ClearFlag( void )
{
	return g_Va012F8528 &= 0xFFFFFFFEu;
}

unsigned int Rva00C4E4D0ClearFlag( void )
{
	return g_Va01304B40 &= 0xFFFFFFFEu;
}

unsigned int Rva00C4E660ClearFlag( void )
{
	return g_Va01304B58 &= 0xFFFFFFFEu;
}

unsigned int Rva00C4E6A0ClearFlag( void )
{
	return g_Va01304B70 &= 0xFFFFFFFEu;
}

unsigned int Rva00C4E880ClearFlag( void )
{
	return g_Va01304BA4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C4E9B0ClearFlag( void )
{
	return g_Va01304BAC &= 0xFFFFFFFEu;
}

unsigned int Rva00C4EAF0ClearFlag( void )
{
	return g_Va01304BBC &= 0xFFFFFFFEu;
}

unsigned int Rva00C4EB50ClearFlag( void )
{
	return g_Va01304BC4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C4EB90ClearFlag( void )
{
	return g_Va01304BCC &= 0xFFFFFFFEu;
}

unsigned int Rva00C4EBF0ClearFlag( void )
{
	return g_Va01304BD4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C4EC90ClearFlag( void )
{
	return g_Va01305A48 &= 0xFFFFFFFEu;
}

unsigned int Rva00C4FB00ClearFlag( void )
{
	return g_Va01305A54 &= 0xFFFFFFFEu;
}

unsigned int Rva00C4FB38ClearFlag( void )
{
	return g_Va01305A78 &= 0xFFFFFFFEu;
}

unsigned int Rva00C4FD00ClearFlag( void )
{
	return g_Va013068E8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C507D0ClearFlag( void )
{
	return g_Va013068F0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C510C0ClearFlag( void )
{
	return g_Va01306C68 &= 0xFFFFFFFEu;
}

unsigned int Rva00C51730ClearFlag( void )
{
	return g_Va01306CE4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C51746ClearFlag( void )
{
	return g_Va01306CE4 &= 0xFFFFFFFDu;
}

unsigned int Rva00C5175CClearFlag( void )
{
	return g_Va01306CE4 &= 0xFFFFFFFBu;
}

unsigned int Rva00C51772ClearFlag( void )
{
	return g_Va01306CE4 &= 0xFFFFFFF7u;
}

unsigned int Rva00C51788ClearFlag( void )
{
	return g_Va01306CE4 &= 0xFFFFFFEFu;
}

unsigned int Rva00C5179EClearFlag( void )
{
	return g_Va01306CE4 &= 0xFFFFFFDFu;
}

unsigned int Rva00C517B4ClearFlag( void )
{
	return g_Va01306CE4 &= 0xFFFFFFBFu;
}

unsigned int Rva00C51820ClearFlag( void )
{
	return g_Va01306CFC &= 0xFFFFFFFEu;
}

unsigned int Rva00C51836ClearFlag( void )
{
	return g_Va01306CFC &= 0xFFFFFFFDu;
}

unsigned int Rva00C5184CClearFlag( void )
{
	return g_Va01306CFC &= 0xFFFFFFFBu;
}

unsigned int Rva00C51862ClearFlag( void )
{
	return g_Va01306CFC &= 0xFFFFFFF7u;
}

unsigned int Rva00C51AA6ClearFlag( void )
{
	return g_Va01306D4C &= 0xFFFFFFFDu;
}

unsigned int Rva00C51ABCClearFlag( void )
{
	return g_Va01306D4C &= 0xFFFFFFFBu;
}

unsigned int Rva00C51AF0ClearFlag( void )
{
	return g_Va01306D60 &= 0xFFFFFFFEu;
}

unsigned int Rva00C51B20ClearFlag( void )
{
	return g_Va01306D74 &= 0xFFFFFFFEu;
}

unsigned int Rva00C53D30ClearFlag( void )
{
	return g_Va013073B4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C5B9B0ClearFlag( void )
{
	return g_Va01341210 &= 0xFFFFFFFEu;
}

unsigned int Rva00C5D9B0ClearFlag( void )
{
	return g_Va0134B0E0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C5DFA0ClearFlag( void )
{
	return g_Va0134B124 &= 0xFFFFFFFEu;
}

unsigned int Rva00C5DFAEClearFlag( void )
{
	return g_Va0134B124 &= 0xFFFFFFFDu;
}

unsigned int Rva00C5E4E0ClearFlag( void )
{
	return g_Va0134B278 &= 0xFFFFFFFEu;
}

unsigned int Rva00C5FEF0ClearFlag( void )
{
	return g_Va0134C66C &= 0xFFFFFFFEu;
}

unsigned int Rva00C5FEFEClearFlag( void )
{
	return g_Va0134C66C &= 0xFFFFFFFDu;
}

unsigned int Rva00C5FF0CClearFlag( void )
{
	return g_Va0134C66C &= 0xFFFFFFFBu;
}

unsigned int Rva00C60010ClearFlag( void )
{
	return g_Va0134C6B8 &= 0xFFFFFFF7u;
}

unsigned int Rva00C61F50ClearFlag( void )
{
	return g_Va0134FB14 &= 0xFFFFFFFEu;
}

