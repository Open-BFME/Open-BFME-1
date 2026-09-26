// 110 of the image's 530 bodies with one shape:
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

extern unsigned int g_Va012EF9A4;
extern unsigned int g_Va012EF9AC;
extern unsigned int g_Va012EF9BC;
extern unsigned int g_Va012EF9C4;
extern unsigned int g_Va012EF9D4;
extern unsigned int g_Va012EF9E4;
extern unsigned int g_Va012EFA04;
extern unsigned int g_Va012EFA44;
extern unsigned int g_Va012EFA4C;
extern unsigned int g_Va012EFA6C;
extern unsigned int g_Va012EFA74;
extern unsigned int g_Va012EFA7C;
extern unsigned int g_Va012EFA90;
extern unsigned int g_Va012EFA98;
extern unsigned int g_Va012EFAA0;
extern unsigned int g_Va012EFAB8;
extern unsigned int g_Va012EFAC0;
extern unsigned int g_Va012EFAC8;
extern unsigned int g_Va012EFAD0;
extern unsigned int g_Va012EFAD8;
extern unsigned int g_Va012EFB14;
extern unsigned int g_Va012EFB58;
extern unsigned int g_Va012EFB60;
extern unsigned int g_Va012EFB68;
extern unsigned int g_Va012EFB70;
extern unsigned int g_Va012EFB78;
extern unsigned int g_Va012EFB80;
extern unsigned int g_Va012EFB88;
extern unsigned int g_Va012EFBD8;
extern unsigned int g_Va012EFBE0;
extern unsigned int g_Va012EFBE8;
extern unsigned int g_Va012EFC20;
extern unsigned int g_Va012EFC30;
extern unsigned int g_Va012EFC48;
extern unsigned int g_Va012EFC50;
extern unsigned int g_Va012EFC60;
extern unsigned int g_Va012EFC68;
extern unsigned int g_Va012EFC70;
extern unsigned int g_Va012EFC80;
extern unsigned int g_Va012EFC88;
extern unsigned int g_Va012EFC90;
extern unsigned int g_Va012EFC98;
extern unsigned int g_Va012EFCA0;
extern unsigned int g_Va012EFCA8;
extern unsigned int g_Va012EFCB0;
extern unsigned int g_Va012EFCB8;
extern unsigned int g_Va012EFCC0;
extern unsigned int g_Va012EFCC8;
extern unsigned int g_Va012EFCD0;
extern unsigned int g_Va012EFCD8;
extern unsigned int g_Va012EFCE0;
extern unsigned int g_Va012EFCF0;
extern unsigned int g_Va012EFCF8;
extern unsigned int g_Va012EFD00;
extern unsigned int g_Va012EFD08;
extern unsigned int g_Va012EFD10;
extern unsigned int g_Va012EFD18;
extern unsigned int g_Va012EFD20;
extern unsigned int g_Va012EFD28;
extern unsigned int g_Va012EFD30;
extern unsigned int g_Va012EFD38;
extern unsigned int g_Va012EFD40;
extern unsigned int g_Va012EFD48;
extern unsigned int g_Va012EFD64;
extern unsigned int g_Va012EFD6C;
extern unsigned int g_Va012EFD74;
extern unsigned int g_Va012EFD7C;
extern unsigned int g_Va012EFD84;
extern unsigned int g_Va012EFD8C;
extern unsigned int g_Va012EFD94;
extern unsigned int g_Va012EFD9C;
extern unsigned int g_Va012EFDA4;
extern unsigned int g_Va012EFDE0;
extern unsigned int g_Va012EFDE8;
extern unsigned int g_Va012EFDF0;
extern unsigned int g_Va012EFDF8;
extern unsigned int g_Va012EFE44;
extern unsigned int g_Va012EFE4C;
extern unsigned int g_Va012EFE64;
extern unsigned int g_Va012EFE6C;
extern unsigned int g_Va012EFEB4;
extern unsigned int g_Va012EFEBC;
extern unsigned int g_Va012EFEC4;
extern unsigned int g_Va012EFED4;
extern unsigned int g_Va012EFEDC;
extern unsigned int g_Va012EFEEC;
extern unsigned int g_Va012EFEF4;
extern unsigned int g_Va012EFEFC;
extern unsigned int g_Va012EFF14;
extern unsigned int g_Va012EFF1C;
extern unsigned int g_Va012EFF2C;
extern unsigned int g_Va012EFF34;
extern unsigned int g_Va012EFF3C;
extern unsigned int g_Va012EFF74;
extern unsigned int g_Va012EFF7C;
extern unsigned int g_Va012EFF9C;
extern unsigned int g_Va012EFFB4;
extern unsigned int g_Va012EFFC4;
extern unsigned int g_Va012EFFD4;
extern unsigned int g_Va012EFFDC;
extern unsigned int g_Va012EFFE4;
extern unsigned int g_Va012EFFEC;
extern unsigned int g_Va012F0004;
extern unsigned int g_Va012F000C;
extern unsigned int g_Va012F002C;
extern unsigned int g_Va012F0034;
extern unsigned int g_Va012F003C;
extern unsigned int g_Va012F005C;
extern unsigned int g_Va012F0064;

unsigned int Rva00C0C880ClearFlag( void )
{
	return g_Va012EF9A4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0C8A0ClearFlag( void )
{
	return g_Va012EF9AC &= 0xFFFFFFFEu;
}

unsigned int Rva00C0C910ClearFlag( void )
{
	return g_Va012EF9BC &= 0xFFFFFFFEu;
}

unsigned int Rva00C0C9E0ClearFlag( void )
{
	return g_Va012EF9C4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0CA80ClearFlag( void )
{
	return g_Va012EF9D4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0CAC0ClearFlag( void )
{
	return g_Va012EF9E4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0CB10ClearFlag( void )
{
	return g_Va012EFA04 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0CDC0ClearFlag( void )
{
	return g_Va012EFA44 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0CE70ClearFlag( void )
{
	return g_Va012EFA4C &= 0xFFFFFFFEu;
}

unsigned int Rva00C0D1F0ClearFlag( void )
{
	return g_Va012EFA6C &= 0xFFFFFFFEu;
}

unsigned int Rva00C0D230ClearFlag( void )
{
	return g_Va012EFA74 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0D3A0ClearFlag( void )
{
	return g_Va012EFA7C &= 0xFFFFFFFEu;
}

unsigned int Rva00C0D518ClearFlag( void )
{
	return g_Va012EFA90 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0D630ClearFlag( void )
{
	return g_Va012EFA98 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0D6B0ClearFlag( void )
{
	return g_Va012EFAA0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0D8C0ClearFlag( void )
{
	return g_Va012EFAB8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0D930ClearFlag( void )
{
	return g_Va012EFAC0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0DA10ClearFlag( void )
{
	return g_Va012EFAC8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0DAD8ClearFlag( void )
{
	return g_Va012EFAD0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0DB70ClearFlag( void )
{
	return g_Va012EFAD8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0DCD0ClearFlag( void )
{
	return g_Va012EFB14 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0E0F0ClearFlag( void )
{
	return g_Va012EFB58 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0E1F0ClearFlag( void )
{
	return g_Va012EFB60 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0E280ClearFlag( void )
{
	return g_Va012EFB68 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0E320ClearFlag( void )
{
	return g_Va012EFB70 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0E490ClearFlag( void )
{
	return g_Va012EFB78 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0E4B0ClearFlag( void )
{
	return g_Va012EFB80 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0E530ClearFlag( void )
{
	return g_Va012EFB88 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0E740ClearFlag( void )
{
	return g_Va012EFBD8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0E7A0ClearFlag( void )
{
	return g_Va012EFBE0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0E810ClearFlag( void )
{
	return g_Va012EFBE8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0EC40ClearFlag( void )
{
	return g_Va012EFC20 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0EC80ClearFlag( void )
{
	return g_Va012EFC30 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0ED80ClearFlag( void )
{
	return g_Va012EFC48 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0EE40ClearFlag( void )
{
	return g_Va012EFC50 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0EF90ClearFlag( void )
{
	return g_Va012EFC60 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0EFD0ClearFlag( void )
{
	return g_Va012EFC68 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0F030ClearFlag( void )
{
	return g_Va012EFC70 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0F070ClearFlag( void )
{
	return g_Va012EFC80 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0F0E0ClearFlag( void )
{
	return g_Va012EFC88 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0F100ClearFlag( void )
{
	return g_Va012EFC90 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0F120ClearFlag( void )
{
	return g_Va012EFC98 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0F170ClearFlag( void )
{
	return g_Va012EFCA0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0F2C0ClearFlag( void )
{
	return g_Va012EFCA8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0F340ClearFlag( void )
{
	return g_Va012EFCB0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0F360ClearFlag( void )
{
	return g_Va012EFCB8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0F410ClearFlag( void )
{
	return g_Va012EFCC0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0F4C0ClearFlag( void )
{
	return g_Va012EFCC8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0F520ClearFlag( void )
{
	return g_Va012EFCD0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0F5B0ClearFlag( void )
{
	return g_Va012EFCD8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0F6D0ClearFlag( void )
{
	return g_Va012EFCE0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0F8B0ClearFlag( void )
{
	return g_Va012EFCF0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0F8F0ClearFlag( void )
{
	return g_Va012EFCF8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0F9B0ClearFlag( void )
{
	return g_Va012EFD00 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0FA20ClearFlag( void )
{
	return g_Va012EFD08 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0FA70ClearFlag( void )
{
	return g_Va012EFD10 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0FB90ClearFlag( void )
{
	return g_Va012EFD18 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0FBB0ClearFlag( void )
{
	return g_Va012EFD20 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0FBE0ClearFlag( void )
{
	return g_Va012EFD28 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0FC10ClearFlag( void )
{
	return g_Va012EFD30 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0FC50ClearFlag( void )
{
	return g_Va012EFD38 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0FC90ClearFlag( void )
{
	return g_Va012EFD40 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0FCD0ClearFlag( void )
{
	return g_Va012EFD48 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0FEC0ClearFlag( void )
{
	return g_Va012EFD64 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0FFF0ClearFlag( void )
{
	return g_Va012EFD6C &= 0xFFFFFFFEu;
}

unsigned int Rva00C10030ClearFlag( void )
{
	return g_Va012EFD74 &= 0xFFFFFFFEu;
}

unsigned int Rva00C10050ClearFlag( void )
{
	return g_Va012EFD7C &= 0xFFFFFFFEu;
}

unsigned int Rva00C100E0ClearFlag( void )
{
	return g_Va012EFD84 &= 0xFFFFFFFEu;
}

unsigned int Rva00C10100ClearFlag( void )
{
	return g_Va012EFD8C &= 0xFFFFFFFEu;
}

unsigned int Rva00C10120ClearFlag( void )
{
	return g_Va012EFD94 &= 0xFFFFFFFEu;
}

unsigned int Rva00C10140ClearFlag( void )
{
	return g_Va012EFD9C &= 0xFFFFFFFEu;
}

unsigned int Rva00C10160ClearFlag( void )
{
	return g_Va012EFDA4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C10210ClearFlag( void )
{
	return g_Va012EFDE0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C10270ClearFlag( void )
{
	return g_Va012EFDE8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C10290ClearFlag( void )
{
	return g_Va012EFDF0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C102F0ClearFlag( void )
{
	return g_Va012EFDF8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C10830ClearFlag( void )
{
	return g_Va012EFE44 &= 0xFFFFFFFEu;
}

unsigned int Rva00C10870ClearFlag( void )
{
	return g_Va012EFE4C &= 0xFFFFFFFEu;
}

unsigned int Rva00C10A60ClearFlag( void )
{
	return g_Va012EFE64 &= 0xFFFFFFFEu;
}

unsigned int Rva00C10BD0ClearFlag( void )
{
	return g_Va012EFE6C &= 0xFFFFFFFEu;
}

unsigned int Rva00C10D50ClearFlag( void )
{
	return g_Va012EFEB4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C10D5EClearFlag( void )
{
	return g_Va012EFEB4 &= 0xFFFFFFFDu;
}

unsigned int Rva00C10EF0ClearFlag( void )
{
	return g_Va012EFEBC &= 0xFFFFFFFEu;
}

unsigned int Rva00C10F70ClearFlag( void )
{
	return g_Va012EFEC4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C11190ClearFlag( void )
{
	return g_Va012EFED4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C11250ClearFlag( void )
{
	return g_Va012EFEDC &= 0xFFFFFFFEu;
}

unsigned int Rva00C113D0ClearFlag( void )
{
	return g_Va012EFEEC &= 0xFFFFFFFEu;
}

unsigned int Rva00C11440ClearFlag( void )
{
	return g_Va012EFEF4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C114D0ClearFlag( void )
{
	return g_Va012EFEFC &= 0xFFFFFFFEu;
}

unsigned int Rva00C11570ClearFlag( void )
{
	return g_Va012EFF14 &= 0xFFFFFFFEu;
}

unsigned int Rva00C115F0ClearFlag( void )
{
	return g_Va012EFF1C &= 0xFFFFFFFEu;
}

unsigned int Rva00C11830ClearFlag( void )
{
	return g_Va012EFF2C &= 0xFFFFFFFEu;
}

unsigned int Rva00C11930ClearFlag( void )
{
	return g_Va012EFF34 &= 0xFFFFFFFEu;
}

unsigned int Rva00C119E0ClearFlag( void )
{
	return g_Va012EFF3C &= 0xFFFFFFFEu;
}

unsigned int Rva00C11BE0ClearFlag( void )
{
	return g_Va012EFF74 &= 0xFFFFFFFEu;
}

unsigned int Rva00C11C40ClearFlag( void )
{
	return g_Va012EFF7C &= 0xFFFFFFFEu;
}

unsigned int Rva00C11DD0ClearFlag( void )
{
	return g_Va012EFF9C &= 0xFFFFFFFEu;
}

unsigned int Rva00C11EA0ClearFlag( void )
{
	return g_Va012EFFB4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C11FA0ClearFlag( void )
{
	return g_Va012EFFC4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C12060ClearFlag( void )
{
	return g_Va012EFFD4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C12080ClearFlag( void )
{
	return g_Va012EFFDC &= 0xFFFFFFFEu;
}

unsigned int Rva00C120B0ClearFlag( void )
{
	return g_Va012EFFE4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C120F0ClearFlag( void )
{
	return g_Va012EFFEC &= 0xFFFFFFFEu;
}

unsigned int Rva00C122B0ClearFlag( void )
{
	return g_Va012F0004 &= 0xFFFFFFFEu;
}

unsigned int Rva00C12380ClearFlag( void )
{
	return g_Va012F000C &= 0xFFFFFFFEu;
}

unsigned int Rva00C12560ClearFlag( void )
{
	return g_Va012F002C &= 0xFFFFFFFEu;
}

unsigned int Rva00C125C0ClearFlag( void )
{
	return g_Va012F0034 &= 0xFFFFFFFEu;
}

unsigned int Rva00C126C0ClearFlag( void )
{
	return g_Va012F003C &= 0xFFFFFFFEu;
}

unsigned int Rva00C128A0ClearFlag( void )
{
	return g_Va012F005C &= 0xFFFFFFFEu;
}

unsigned int Rva00C128C0ClearFlag( void )
{
	return g_Va012F0064 &= 0xFFFFFFFEu;
}

