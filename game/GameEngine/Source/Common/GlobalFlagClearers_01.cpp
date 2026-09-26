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

extern unsigned int g_Va012ED544;
extern unsigned int g_Va012ED558;
extern unsigned int g_Va012ED56C;
extern unsigned int g_Va012ED580;
extern unsigned int g_Va012ED71C;
extern unsigned int g_Va012ED724;
extern unsigned int g_Va012ED72C;
extern unsigned int g_Va012ED738;
extern unsigned int g_Va012ED79C;
extern unsigned int g_Va012ED7A4;
extern unsigned int g_Va012ED818;
extern unsigned int g_Va012ED820;
extern unsigned int g_Va012ED830;
extern unsigned int g_Va012ED838;
extern unsigned int g_Va012EF170;
extern unsigned int g_Va012EF178;
extern unsigned int g_Va012EF184;
extern unsigned int g_Va012EF1B8;
extern unsigned int g_Va012EF1CC;
extern unsigned int g_Va012EF1D4;
extern unsigned int g_Va012EF1E8;
extern unsigned int g_Va012EF1F4;
extern unsigned int g_Va012EF21C;
extern unsigned int g_Va012EF224;
extern unsigned int g_Va012EF24C;
extern unsigned int g_Va012EF254;
extern unsigned int g_Va012EF25C;
extern unsigned int g_Va012EF284;
extern unsigned int g_Va012EF2B4;
extern unsigned int g_Va012EF2BC;
extern unsigned int g_Va012EF2F4;
extern unsigned int g_Va012EF2FC;
extern unsigned int g_Va012EF304;
extern unsigned int g_Va012EF4E0;
extern unsigned int g_Va012EF528;
extern unsigned int g_Va012EF530;
extern unsigned int g_Va012EF538;
extern unsigned int g_Va012EF540;
extern unsigned int g_Va012EF548;
extern unsigned int g_Va012EF550;
extern unsigned int g_Va012EF558;
extern unsigned int g_Va012EF560;
extern unsigned int g_Va012EF568;
extern unsigned int g_Va012EF570;
extern unsigned int g_Va012EF578;
extern unsigned int g_Va012EF580;
extern unsigned int g_Va012EF588;
extern unsigned int g_Va012EF594;
extern unsigned int g_Va012EF59C;
extern unsigned int g_Va012EF5A4;
extern unsigned int g_Va012EF5AC;
extern unsigned int g_Va012EF5C0;
extern unsigned int g_Va012EF640;
extern unsigned int g_Va012EF718;
extern unsigned int g_Va012EF720;
extern unsigned int g_Va012EF730;
extern unsigned int g_Va012EF740;
extern unsigned int g_Va012EF748;
extern unsigned int g_Va012EF750;
extern unsigned int g_Va012EF758;
extern unsigned int g_Va012EF760;
extern unsigned int g_Va012EF770;
extern unsigned int g_Va012EF790;
extern unsigned int g_Va012EF798;
extern unsigned int g_Va012EF7A0;
extern unsigned int g_Va012EF7A8;
extern unsigned int g_Va012EF7B0;
extern unsigned int g_Va012EF7B8;
extern unsigned int g_Va012EF7C0;
extern unsigned int g_Va012EF7D8;
extern unsigned int g_Va012EF7E0;
extern unsigned int g_Va012EF7E8;
extern unsigned int g_Va012EF7F0;
extern unsigned int g_Va012EF810;
extern unsigned int g_Va012EF820;
extern unsigned int g_Va012EF828;
extern unsigned int g_Va012EF840;
extern unsigned int g_Va012EF848;
extern unsigned int g_Va012EF850;
extern unsigned int g_Va012EF858;
extern unsigned int g_Va012EF860;
extern unsigned int g_Va012EF868;
extern unsigned int g_Va012EF870;
extern unsigned int g_Va012EF878;
extern unsigned int g_Va012EF90C;
extern unsigned int g_Va012EF914;
extern unsigned int g_Va012EF924;
extern unsigned int g_Va012EF954;
extern unsigned int g_Va012EF95C;
extern unsigned int g_Va012EF964;
extern unsigned int g_Va012EF96C;
extern unsigned int g_Va012EF974;
extern unsigned int g_Va012EF994;
extern unsigned int g_Va012EF99C;

unsigned int Rva00BF3C60ClearFlag( void )
{
	return g_Va012ED544 &= 0xFFFFFFFEu;
}

unsigned int Rva00BF3C80ClearFlag( void )
{
	return g_Va012ED558 &= 0xFFFFFFFEu;
}

unsigned int Rva00BF3CA0ClearFlag( void )
{
	return g_Va012ED56C &= 0xFFFFFFFEu;
}

unsigned int Rva00BF3CC0ClearFlag( void )
{
	return g_Va012ED580 &= 0xFFFFFFFEu;
}

unsigned int Rva00BF9470ClearFlag( void )
{
	return g_Va012ED71C &= 0xFFFFFFFEu;
}

unsigned int Rva00BF9730ClearFlag( void )
{
	return g_Va012ED724 &= 0xFFFFFFFEu;
}

unsigned int Rva00BF9AA0ClearFlag( void )
{
	return g_Va012ED72C &= 0xFFFFFFFEu;
}

unsigned int Rva00BF9B48ClearFlag( void )
{
	return g_Va012ED738 &= 0xFFFFFFFEu;
}

unsigned int Rva00BF9B56ClearFlag( void )
{
	return g_Va012ED738 &= 0xFFFFFFFDu;
}

unsigned int Rva00BFB1F0ClearFlag( void )
{
	return g_Va012ED79C &= 0xFFFFFFFEu;
}

unsigned int Rva00BFB210ClearFlag( void )
{
	return g_Va012ED7A4 &= 0xFFFFFFFEu;
}

unsigned int Rva00BFBA30ClearFlag( void )
{
	return g_Va012ED818 &= 0xFFFFFFFEu;
}

unsigned int Rva00BFC1C3ClearFlag( void )
{
	return g_Va012ED820 &= 0xFFFFFFFEu;
}

unsigned int Rva00BFC260ClearFlag( void )
{
	return g_Va012ED830 &= 0xFFFFFFFEu;
}

unsigned int Rva00BFC26EClearFlag( void )
{
	return g_Va012ED830 &= 0xFFFFFFFDu;
}

unsigned int Rva00BFC2D0ClearFlag( void )
{
	return g_Va012ED838 &= 0xFFFFFFFEu;
}

unsigned int Rva00BFCF60ClearFlag( void )
{
	return g_Va012EF170 &= 0xFFFFFFFEu;
}

unsigned int Rva00BFCF80ClearFlag( void )
{
	return g_Va012EF178 &= 0xFFFFFFFEu;
}

unsigned int Rva00BFD140ClearFlag( void )
{
	return g_Va012EF184 &= 0xFFFFFFFEu;
}

unsigned int Rva00BFF5A0ClearFlag( void )
{
	return g_Va012EF1B8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C01640ClearFlag( void )
{
	return g_Va012EF1CC &= 0xFFFFFFFEu;
}

unsigned int Rva00C01C50ClearFlag( void )
{
	return g_Va012EF1D4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C03B30ClearFlag( void )
{
	return g_Va012EF1E8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C03B60ClearFlag( void )
{
	return g_Va012EF1F4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C04720ClearFlag( void )
{
	return g_Va012EF21C &= 0xFFFFFFFEu;
}

unsigned int Rva00C0483DClearFlag( void )
{
	return g_Va012EF224 &= 0xFFFFFFFEu;
}

unsigned int Rva00C04F30ClearFlag( void )
{
	return g_Va012EF24C &= 0xFFFFFFFEu;
}

unsigned int Rva00C04F90ClearFlag( void )
{
	return g_Va012EF254 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0505BClearFlag( void )
{
	return g_Va012EF25C &= 0xFFFFFFFEu;
}

unsigned int Rva00C05230ClearFlag( void )
{
	return g_Va012EF284 &= 0xFFFFFFFEu;
}

unsigned int Rva00C05630ClearFlag( void )
{
	return g_Va012EF2B4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0572EClearFlag( void )
{
	return g_Va012EF2BC &= 0xFFFFFFFEu;
}

unsigned int Rva00C05B90ClearFlag( void )
{
	return g_Va012EF2F4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C05BB0ClearFlag( void )
{
	return g_Va012EF2FC &= 0xFFFFFFFEu;
}

unsigned int Rva00C05BD0ClearFlag( void )
{
	return g_Va012EF304 &= 0xFFFFFFFEu;
}

unsigned int Rva00C080E3ClearFlag( void )
{
	return g_Va012EF4E0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C08CD0ClearFlag( void )
{
	return g_Va012EF528 &= 0xFFFFFFFEu;
}

unsigned int Rva00C08CF0ClearFlag( void )
{
	return g_Va012EF530 &= 0xFFFFFFFEu;
}

unsigned int Rva00C08D30ClearFlag( void )
{
	return g_Va012EF538 &= 0xFFFFFFFEu;
}

unsigned int Rva00C08D70ClearFlag( void )
{
	return g_Va012EF540 &= 0xFFFFFFFEu;
}

unsigned int Rva00C08D90ClearFlag( void )
{
	return g_Va012EF548 &= 0xFFFFFFFEu;
}

unsigned int Rva00C08DD0ClearFlag( void )
{
	return g_Va012EF550 &= 0xFFFFFFFEu;
}

unsigned int Rva00C08DF0ClearFlag( void )
{
	return g_Va012EF558 &= 0xFFFFFFFEu;
}

unsigned int Rva00C08E10ClearFlag( void )
{
	return g_Va012EF560 &= 0xFFFFFFFEu;
}

unsigned int Rva00C08E50ClearFlag( void )
{
	return g_Va012EF568 &= 0xFFFFFFFEu;
}

unsigned int Rva00C08FC0ClearFlag( void )
{
	return g_Va012EF570 &= 0xFFFFFFFEu;
}

unsigned int Rva00C08FE0ClearFlag( void )
{
	return g_Va012EF578 &= 0xFFFFFFFEu;
}

unsigned int Rva00C09000ClearFlag( void )
{
	return g_Va012EF580 &= 0xFFFFFFFEu;
}

unsigned int Rva00C09020ClearFlag( void )
{
	return g_Va012EF588 &= 0xFFFFFFFEu;
}

unsigned int Rva00C090C0ClearFlag( void )
{
	return g_Va012EF594 &= 0xFFFFFFFEu;
}

unsigned int Rva00C090E0ClearFlag( void )
{
	return g_Va012EF59C &= 0xFFFFFFFEu;
}

unsigned int Rva00C09180ClearFlag( void )
{
	return g_Va012EF5A4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C093E0ClearFlag( void )
{
	return g_Va012EF5AC &= 0xFFFFFFFEu;
}

unsigned int Rva00C09498ClearFlag( void )
{
	return g_Va012EF5C0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C094A6ClearFlag( void )
{
	return g_Va012EF5C0 &= 0xFFFFFFFDu;
}

unsigned int Rva00C094B4ClearFlag( void )
{
	return g_Va012EF5C0 &= 0xFFFFFFFBu;
}

unsigned int Rva00C094C2ClearFlag( void )
{
	return g_Va012EF5C0 &= 0xFFFFFFF7u;
}

unsigned int Rva00C09607ClearFlag( void )
{
	return g_Va012EF640 &= 0xFFFFFFFEu;
}

unsigned int Rva00C09628ClearFlag( void )
{
	return g_Va012EF640 &= 0xFFFFFFFBu;
}

unsigned int Rva00C09649ClearFlag( void )
{
	return g_Va012EF640 &= 0xFFFFFFEFu;
}

unsigned int Rva00C09662ClearFlag( void )
{
	return g_Va012EF640 &= 0xFFFFFFBFu;
}

unsigned int Rva00C0967BClearFlag( void )
{
	return g_Va012EF640 &= 0xFFFFFEFFu;
}

unsigned int Rva00C09696ClearFlag( void )
{
	return g_Va012EF640 &= 0xFFFFFBFFu;
}

unsigned int Rva00C096B9ClearFlag( void )
{
	return g_Va012EF640 &= 0xFFFFEFFFu;
}

unsigned int Rva00C096DCClearFlag( void )
{
	return g_Va012EF640 &= 0xFFFFBFFFu;
}

unsigned int Rva00C096ECClearFlag( void )
{
	return g_Va012EF640 &= 0xFFFF7FFFu;
}

unsigned int Rva00C096FCClearFlag( void )
{
	return g_Va012EF640 &= 0xFFFEFFFFu;
}

unsigned int Rva00C09AFBClearFlag( void )
{
	return g_Va012EF718 &= 0xFFFFFFFEu;
}

unsigned int Rva00C09C60ClearFlag( void )
{
	return g_Va012EF720 &= 0xFFFFFFFEu;
}

unsigned int Rva00C09D00ClearFlag( void )
{
	return g_Va012EF730 &= 0xFFFFFFFEu;
}

unsigned int Rva00C09D3AClearFlag( void )
{
	return g_Va012EF730 &= 0xFFFFFFFDu;
}

unsigned int Rva00C09D48ClearFlag( void )
{
	return g_Va012EF730 &= 0xFFFFFFFBu;
}

unsigned int Rva00C0A160ClearFlag( void )
{
	return g_Va012EF740 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0A398ClearFlag( void )
{
	return g_Va012EF748 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0A6B0ClearFlag( void )
{
	return g_Va012EF750 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0A6F0ClearFlag( void )
{
	return g_Va012EF758 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0A730ClearFlag( void )
{
	return g_Va012EF760 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0A8F0ClearFlag( void )
{
	return g_Va012EF770 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0ADC0ClearFlag( void )
{
	return g_Va012EF790 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0AEB0ClearFlag( void )
{
	return g_Va012EF798 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0AF70ClearFlag( void )
{
	return g_Va012EF7A0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0AFB0ClearFlag( void )
{
	return g_Va012EF7A8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0AFF0ClearFlag( void )
{
	return g_Va012EF7B0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0B010ClearFlag( void )
{
	return g_Va012EF7B8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0B290ClearFlag( void )
{
	return g_Va012EF7C0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0B350ClearFlag( void )
{
	return g_Va012EF7D8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0B5B8ClearFlag( void )
{
	return g_Va012EF7E0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0B6B0ClearFlag( void )
{
	return g_Va012EF7E8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0B750ClearFlag( void )
{
	return g_Va012EF7F0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0B7D0ClearFlag( void )
{
	return g_Va012EF810 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0B8D0ClearFlag( void )
{
	return g_Va012EF820 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0B920ClearFlag( void )
{
	return g_Va012EF828 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0BB10ClearFlag( void )
{
	return g_Va012EF840 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0BBA0ClearFlag( void )
{
	return g_Va012EF848 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0BBC0ClearFlag( void )
{
	return g_Va012EF850 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0BCF0ClearFlag( void )
{
	return g_Va012EF858 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0BD90ClearFlag( void )
{
	return g_Va012EF860 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0BE50ClearFlag( void )
{
	return g_Va012EF868 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0BE70ClearFlag( void )
{
	return g_Va012EF870 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0BF20ClearFlag( void )
{
	return g_Va012EF878 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0C2E0ClearFlag( void )
{
	return g_Va012EF90C &= 0xFFFFFFFEu;
}

unsigned int Rva00C0C320ClearFlag( void )
{
	return g_Va012EF914 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0C380ClearFlag( void )
{
	return g_Va012EF924 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0C661ClearFlag( void )
{
	return g_Va012EF954 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0C6A0ClearFlag( void )
{
	return g_Va012EF95C &= 0xFFFFFFFEu;
}

unsigned int Rva00C0C700ClearFlag( void )
{
	return g_Va012EF964 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0C740ClearFlag( void )
{
	return g_Va012EF96C &= 0xFFFFFFFEu;
}

unsigned int Rva00C0C780ClearFlag( void )
{
	return g_Va012EF974 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0C840ClearFlag( void )
{
	return g_Va012EF994 &= 0xFFFFFFFEu;
}

unsigned int Rva00C0C860ClearFlag( void )
{
	return g_Va012EF99C &= 0xFFFFFFFEu;
}

