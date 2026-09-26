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

extern unsigned int g_Va012F0FD8;
extern unsigned int g_Va012F1088;
extern unsigned int g_Va012F1090;
extern unsigned int g_Va012F13EC;
extern unsigned int g_Va012F13F4;
extern unsigned int g_Va012F1458;
extern unsigned int g_Va012F1460;
extern unsigned int g_Va012F149C;
extern unsigned int g_Va012F1530;
extern unsigned int g_Va012F1544;
extern unsigned int g_Va012F1550;
extern unsigned int g_Va012F1558;
extern unsigned int g_Va012F156C;
extern unsigned int g_Va012F15E4;
extern unsigned int g_Va012F1B2C;
extern unsigned int g_Va012F1BC0;
extern unsigned int g_Va012F341C;
extern unsigned int g_Va012F3444;
extern unsigned int g_Va012F3530;
extern unsigned int g_Va012F3538;
extern unsigned int g_Va012F3548;
extern unsigned int g_Va012F3620;
extern unsigned int g_Va012F3628;
extern unsigned int g_Va012F3634;
extern unsigned int g_Va012F367C;
extern unsigned int g_Va012F36AC;
extern unsigned int g_Va012F38EC;
extern unsigned int g_Va012F392C;
extern unsigned int g_Va012F3AA8;
extern unsigned int g_Va012F3E80;
extern unsigned int g_Va012F45B8;
extern unsigned int g_Va012F49CC;
extern unsigned int g_Va012F49E0;
extern unsigned int g_Va012F4AC8;
extern unsigned int g_Va012F4B0C;
extern unsigned int g_Va012F4B18;
extern unsigned int g_Va012F4B20;
extern unsigned int g_Va012F4B28;
extern unsigned int g_Va012F4B30;
extern unsigned int g_Va012F4B38;
extern unsigned int g_Va012F4B94;
extern unsigned int g_Va012F4BA8;
extern unsigned int g_Va012F4BB0;
extern unsigned int g_Va012F4BB8;

unsigned int Rva00C1C883ClearFlag( void )
{
	return g_Va012F0FD8 &= 0xFFFFFFEFu;
}

unsigned int Rva00C1C891ClearFlag( void )
{
	return g_Va012F0FD8 &= 0xFFFFFFDFu;
}

unsigned int Rva00C1C89FClearFlag( void )
{
	return g_Va012F0FD8 &= 0xFFFFFFBFu;
}

unsigned int Rva00C1C8ADClearFlag( void )
{
	return g_Va012F0FD8 &= 0xFFFFFEFFu;
}

unsigned int Rva00C1C8C8ClearFlag( void )
{
	return g_Va012F0FD8 &= 0xFFFFFBFFu;
}

unsigned int Rva00C1C8EBClearFlag( void )
{
	return g_Va012F0FD8 &= 0xFFFFFDFFu;
}

unsigned int Rva00C1C906ClearFlag( void )
{
	return g_Va012F0FD8 &= 0xFFFFF7FFu;
}

unsigned int Rva00C1C91EClearFlag( void )
{
	return g_Va012F0FD8 &= 0xFFFFEFFFu;
}

unsigned int Rva00C1FDC0ClearFlag( void )
{
	return g_Va012F1088 &= 0xFFFFFFFEu;
}

unsigned int Rva00C1FDE0ClearFlag( void )
{
	return g_Va012F1090 &= 0xFFFFFFFEu;
}

unsigned int Rva00C20A90ClearFlag( void )
{
	return g_Va012F13EC &= 0xFFFFFFFEu;
}

unsigned int Rva00C20A9EClearFlag( void )
{
	return g_Va012F13EC &= 0xFFFFFFFDu;
}

unsigned int Rva00C20CE0ClearFlag( void )
{
	return g_Va012F13F4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C21300ClearFlag( void )
{
	return g_Va012F1458 &= 0xFFFFFFFEu;
}

unsigned int Rva00C21320ClearFlag( void )
{
	return g_Va012F1460 &= 0xFFFFFFFEu;
}

unsigned int Rva00C228E0ClearFlag( void )
{
	return g_Va012F149C &= 0xFFFFFFFEu;
}

unsigned int Rva00C229A8ClearFlag( void )
{
	return g_Va012F1530 &= 0xFFFFFFFEu;
}

unsigned int Rva00C22B40ClearFlag( void )
{
	return g_Va012F1544 &= 0xFFFFFFFEu;
}

unsigned int Rva00C22B4EClearFlag( void )
{
	return g_Va012F1544 &= 0xFFFFFFFDu;
}

unsigned int Rva00C22EA0ClearFlag( void )
{
	return g_Va012F1550 &= 0xFFFFFFFEu;
}

unsigned int Rva00C22EE6ClearFlag( void )
{
	return g_Va012F1550 &= 0xFFFFFFFDu;
}

unsigned int Rva00C22F40ClearFlag( void )
{
	return g_Va012F1558 &= 0xFFFFFFFEu;
}

unsigned int Rva00C23010ClearFlag( void )
{
	return g_Va012F156C &= 0xFFFFFFFEu;
}

unsigned int Rva00C24007ClearFlag( void )
{
	return g_Va012F15E4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C25B90ClearFlag( void )
{
	return g_Va012F1B2C &= 0xFFFFFFFEu;
}

unsigned int Rva00C25BA6ClearFlag( void )
{
	return g_Va012F1B2C &= 0xFFFFFFFDu;
}

unsigned int Rva00C26700ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C2670EClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFFFFFFDu;
}

unsigned int Rva00C2671CClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFFFFFFBu;
}

unsigned int Rva00C2672AClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFFFFFF7u;
}

unsigned int Rva00C26738ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFFFFFEFu;
}

unsigned int Rva00C26746ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFFFFFDFu;
}

unsigned int Rva00C26754ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFFFFFBFu;
}

unsigned int Rva00C26762ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFFFFF7Fu;
}

unsigned int Rva00C26772ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFFFFEFFu;
}

unsigned int Rva00C26782ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFFFFDFFu;
}

unsigned int Rva00C26792ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFFFFBFFu;
}

unsigned int Rva00C267A2ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFFFF7FFu;
}

unsigned int Rva00C267B2ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFFFEFFFu;
}

unsigned int Rva00C267C2ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFFFDFFFu;
}

unsigned int Rva00C267D2ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFFFBFFFu;
}

unsigned int Rva00C267E2ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFFF7FFFu;
}

unsigned int Rva00C267F2ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFFEFFFFu;
}

unsigned int Rva00C26802ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFFDFFFFu;
}

unsigned int Rva00C26812ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFFBFFFFu;
}

unsigned int Rva00C26822ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFF7FFFFu;
}

unsigned int Rva00C26832ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFEFFFFFu;
}

unsigned int Rva00C26842ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFDFFFFFu;
}

unsigned int Rva00C26852ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xFFBFFFFFu;
}

unsigned int Rva00C26862ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xDFFFFFFFu;
}

unsigned int Rva00C26872ClearFlag( void )
{
	return g_Va012F1BC0 &= 0xBFFFFFFFu;
}

unsigned int Rva00C27F90ClearFlag( void )
{
	return g_Va012F341C &= 0xFFFFFFFEu;
}

unsigned int Rva00C27F9EClearFlag( void )
{
	return g_Va012F341C &= 0xFFFFFFFDu;
}

unsigned int Rva00C27FACClearFlag( void )
{
	return g_Va012F341C &= 0xFFFFFFFBu;
}

unsigned int Rva00C28300ClearFlag( void )
{
	return g_Va012F3444 &= 0xFFFFFFFEu;
}

unsigned int Rva00C2830EClearFlag( void )
{
	return g_Va012F3444 &= 0xFFFFFFFDu;
}

unsigned int Rva00C2831CClearFlag( void )
{
	return g_Va012F3444 &= 0xFFFFFFFBu;
}

unsigned int Rva00C28350ClearFlag( void )
{
	return g_Va012F3530 &= 0xFFFFFFFEu;
}

unsigned int Rva00C2835EClearFlag( void )
{
	return g_Va012F3530 &= 0xFFFFFFFDu;
}

unsigned int Rva00C2836CClearFlag( void )
{
	return g_Va012F3530 &= 0xFFFFFFFBu;
}

unsigned int Rva00C2837AClearFlag( void )
{
	return g_Va012F3530 &= 0xFFFFFFF7u;
}

unsigned int Rva00C28388ClearFlag( void )
{
	return g_Va012F3530 &= 0xFFFFFFEFu;
}

unsigned int Rva00C2839EClearFlag( void )
{
	return g_Va012F3530 &= 0xFFFFFFDFu;
}

unsigned int Rva00C283ACClearFlag( void )
{
	return g_Va012F3530 &= 0xFFFFFFBFu;
}

unsigned int Rva00C283BAClearFlag( void )
{
	return g_Va012F3530 &= 0xFFFFFF7Fu;
}

unsigned int Rva00C283CAClearFlag( void )
{
	return g_Va012F3530 &= 0xFFFFFEFFu;
}

unsigned int Rva00C28410ClearFlag( void )
{
	return g_Va012F3538 &= 0xFFFFFFFEu;
}

unsigned int Rva00C28470ClearFlag( void )
{
	return g_Va012F3548 &= 0xFFFFFFFEu;
}

unsigned int Rva00C2847EClearFlag( void )
{
	return g_Va012F3548 &= 0xFFFFFFFDu;
}

unsigned int Rva00C2848CClearFlag( void )
{
	return g_Va012F3548 &= 0xFFFFFFFBu;
}

unsigned int Rva00C28568ClearFlag( void )
{
	return g_Va012F3620 &= 0xFFFFFFFEu;
}

unsigned int Rva00C28576ClearFlag( void )
{
	return g_Va012F3620 &= 0xFFFFFFFDu;
}

unsigned int Rva00C285A0ClearFlag( void )
{
	return g_Va012F3628 &= 0xFFFFFFFEu;
}

unsigned int Rva00C28928ClearFlag( void )
{
	return g_Va012F3634 &= 0xFFFFFFFEu;
}

unsigned int Rva00C28F18ClearFlag( void )
{
	return g_Va012F367C &= 0xFFFFFEFFu;
}

unsigned int Rva00C28F30ClearFlag( void )
{
	return g_Va012F367C &= 0xFFFFFFFEu;
}

unsigned int Rva00C28F3EClearFlag( void )
{
	return g_Va012F367C &= 0xFFFFFFFDu;
}

unsigned int Rva00C28F4CClearFlag( void )
{
	return g_Va012F367C &= 0xFFFFFFFBu;
}

unsigned int Rva00C28F5AClearFlag( void )
{
	return g_Va012F367C &= 0xFFFFFFF7u;
}

unsigned int Rva00C28F68ClearFlag( void )
{
	return g_Va012F367C &= 0xFFFFFFEFu;
}

unsigned int Rva00C28F76ClearFlag( void )
{
	return g_Va012F367C &= 0xFFFFFFDFu;
}

unsigned int Rva00C28F84ClearFlag( void )
{
	return g_Va012F367C &= 0xFFFFFFBFu;
}

unsigned int Rva00C28F9AClearFlag( void )
{
	return g_Va012F367C &= 0xFFFFFF7Fu;
}

unsigned int Rva00C291B0ClearFlag( void )
{
	return g_Va012F36AC &= 0xFFFFFFFEu;
}

unsigned int Rva00C292A0ClearFlag( void )
{
	return g_Va012F38EC &= 0xFFFFFFFEu;
}

unsigned int Rva00C293C0ClearFlag( void )
{
	return g_Va012F392C &= 0xFFFFFFFEu;
}

unsigned int Rva00C293D6ClearFlag( void )
{
	return g_Va012F392C &= 0xFFFFFFFDu;
}

unsigned int Rva00C293ECClearFlag( void )
{
	return g_Va012F392C &= 0xFFFFFFFBu;
}

unsigned int Rva00C29402ClearFlag( void )
{
	return g_Va012F392C &= 0xFFFFFFF7u;
}

unsigned int Rva00C29858ClearFlag( void )
{
	return g_Va012F3AA8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C2986EClearFlag( void )
{
	return g_Va012F3AA8 &= 0xFFFFFFFDu;
}

unsigned int Rva00C2A118ClearFlag( void )
{
	return g_Va012F3E80 &= 0xFFFFFFFEu;
}

unsigned int Rva00C2A126ClearFlag( void )
{
	return g_Va012F3E80 &= 0xFFFFFFFDu;
}

unsigned int Rva00C2CAC8ClearFlag( void )
{
	return g_Va012F45B8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C30010ClearFlag( void )
{
	return g_Va012F49CC &= 0xFFFFFFFEu;
}

unsigned int Rva00C30047ClearFlag( void )
{
	return g_Va012F49CC &= 0xFFFFFFFDu;
}

unsigned int Rva00C30530ClearFlag( void )
{
	return g_Va012F49E0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C30546ClearFlag( void )
{
	return g_Va012F49E0 &= 0xFFFFFFFDu;
}

unsigned int Rva00C33C90ClearFlag( void )
{
	return g_Va012F4AC8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C34BB0ClearFlag( void )
{
	return g_Va012F4B0C &= 0xFFFFFFFEu;
}

unsigned int Rva00C34BE0ClearFlag( void )
{
	return g_Va012F4B18 &= 0xFFFFFFFEu;
}

unsigned int Rva00C34BEEClearFlag( void )
{
	return g_Va012F4B18 &= 0xFFFFFFFDu;
}

unsigned int Rva00C34C20ClearFlag( void )
{
	return g_Va012F4B20 &= 0xFFFFFFFEu;
}

unsigned int Rva00C34C50ClearFlag( void )
{
	return g_Va012F4B28 &= 0xFFFFFFFEu;
}

unsigned int Rva00C34C80ClearFlag( void )
{
	return g_Va012F4B30 &= 0xFFFFFFFEu;
}

unsigned int Rva00C34CB0ClearFlag( void )
{
	return g_Va012F4B38 &= 0xFFFFFFFEu;
}

unsigned int Rva00C37100ClearFlag( void )
{
	return g_Va012F4B94 &= 0xFFFFFFFEu;
}

unsigned int Rva00C37130ClearFlag( void )
{
	return g_Va012F4BA8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C373D0ClearFlag( void )
{
	return g_Va012F4BB0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C373F0ClearFlag( void )
{
	return g_Va012F4BB8 &= 0xFFFFFFFEu;
}

