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

extern unsigned int g_Va012F006C;
extern unsigned int g_Va012F0074;
extern unsigned int g_Va012F007C;
extern unsigned int g_Va012F0090;
extern unsigned int g_Va012F0098;
extern unsigned int g_Va012F01BC;
extern unsigned int g_Va012F01C4;
extern unsigned int g_Va012F01D4;
extern unsigned int g_Va012F01DC;
extern unsigned int g_Va012F01E4;
extern unsigned int g_Va012F01F4;
extern unsigned int g_Va012F020C;
extern unsigned int g_Va012F021C;
extern unsigned int g_Va012F0224;
extern unsigned int g_Va012F022C;
extern unsigned int g_Va012F0240;
extern unsigned int g_Va012F02A0;
extern unsigned int g_Va012F02B0;
extern unsigned int g_Va012F02C0;
extern unsigned int g_Va012F02C8;
extern unsigned int g_Va012F02D0;
extern unsigned int g_Va012F02F0;
extern unsigned int g_Va012F02F8;
extern unsigned int g_Va012F0300;
extern unsigned int g_Va012F0314;
extern unsigned int g_Va012F048C;
extern unsigned int g_Va012F04D0;
extern unsigned int g_Va012F0520;
extern unsigned int g_Va012F0528;
extern unsigned int g_Va012F0530;
extern unsigned int g_Va012F0538;
extern unsigned int g_Va012F0544;
extern unsigned int g_Va012F055C;
extern unsigned int g_Va012F056C;
extern unsigned int g_Va012F0574;
extern unsigned int g_Va012F057C;
extern unsigned int g_Va012F05A4;
extern unsigned int g_Va012F05AC;
extern unsigned int g_Va012F05B4;
extern unsigned int g_Va012F05DC;
extern unsigned int g_Va012F0600;
extern unsigned int g_Va012F0608;
extern unsigned int g_Va012F0628;
extern unsigned int g_Va012F0630;
extern unsigned int g_Va012F0638;
extern unsigned int g_Va012F0640;
extern unsigned int g_Va012F0648;
extern unsigned int g_Va012F0650;
extern unsigned int g_Va012F0658;
extern unsigned int g_Va012F0660;
extern unsigned int g_Va012F0668;
extern unsigned int g_Va012F0670;
extern unsigned int g_Va012F0678;
extern unsigned int g_Va012F0680;
extern unsigned int g_Va012F0688;
extern unsigned int g_Va012F0690;
extern unsigned int g_Va012F0698;
extern unsigned int g_Va012F06A0;
extern unsigned int g_Va012F06A8;
extern unsigned int g_Va012F06BC;
extern unsigned int g_Va012F06C4;
extern unsigned int g_Va012F06CC;
extern unsigned int g_Va012F06D4;
extern unsigned int g_Va012F06DC;
extern unsigned int g_Va012F06E4;
extern unsigned int g_Va012F06F0;
extern unsigned int g_Va012F06F8;
extern unsigned int g_Va012F0740;
extern unsigned int g_Va012F07DC;
extern unsigned int g_Va012F07F0;
extern unsigned int g_Va012F07F8;
extern unsigned int g_Va012F0800;
extern unsigned int g_Va012F0808;
extern unsigned int g_Va012F0810;
extern unsigned int g_Va012F0818;
extern unsigned int g_Va012F0820;
extern unsigned int g_Va012F0828;
extern unsigned int g_Va012F0834;
extern unsigned int g_Va012F083C;
extern unsigned int g_Va012F0844;
extern unsigned int g_Va012F084C;
extern unsigned int g_Va012F0854;
extern unsigned int g_Va012F085C;
extern unsigned int g_Va012F0868;
extern unsigned int g_Va012F0894;
extern unsigned int g_Va012F0A90;
extern unsigned int g_Va012F0CF8;
extern unsigned int g_Va012F0D88;
extern unsigned int g_Va012F0FD8;

unsigned int Rva00C128E0ClearFlag( void )
{
	return g_Va012F006C &= 0xFFFFFFFEu;
}

unsigned int Rva00C129A0ClearFlag( void )
{
	return g_Va012F0074 &= 0xFFFFFFFEu;
}

unsigned int Rva00C129F0ClearFlag( void )
{
	return g_Va012F007C &= 0xFFFFFFFEu;
}

unsigned int Rva00C12A2EClearFlag( void )
{
	return g_Va012F0090 &= 0xFFFFFFF7u;
}

unsigned int Rva00C12A3CClearFlag( void )
{
	return g_Va012F0090 &= 0xFFFFFFFEu;
}

unsigned int Rva00C12A55ClearFlag( void )
{
	return g_Va012F0090 &= 0xFFFFFFFDu;
}

unsigned int Rva00C12A63ClearFlag( void )
{
	return g_Va012F0090 &= 0xFFFFFFFBu;
}

unsigned int Rva00C12B20ClearFlag( void )
{
	return g_Va012F0098 &= 0xFFFFFFFEu;
}

unsigned int Rva00C12BE9ClearFlag( void )
{
	return g_Va012F01BC &= 0xFFFFFFFEu;
}

unsigned int Rva00C12BF7ClearFlag( void )
{
	return g_Va012F01BC &= 0xFFFFFFFDu;
}

unsigned int Rva00C12C05ClearFlag( void )
{
	return g_Va012F01BC &= 0xFFFFFFFBu;
}

unsigned int Rva00C12C90ClearFlag( void )
{
	return g_Va012F01C4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C12D50ClearFlag( void )
{
	return g_Va012F01D4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C12D80ClearFlag( void )
{
	return g_Va012F01DC &= 0xFFFFFFFEu;
}

unsigned int Rva00C12DB0ClearFlag( void )
{
	return g_Va012F01E4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C12EB0ClearFlag( void )
{
	return g_Va012F01F4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C12F70ClearFlag( void )
{
	return g_Va012F020C &= 0xFFFFFFFEu;
}

unsigned int Rva00C13020ClearFlag( void )
{
	return g_Va012F021C &= 0xFFFFFFFEu;
}

unsigned int Rva00C13040ClearFlag( void )
{
	return g_Va012F0224 &= 0xFFFFFFFEu;
}

unsigned int Rva00C13080ClearFlag( void )
{
	return g_Va012F022C &= 0xFFFFFFFEu;
}

unsigned int Rva00C13190ClearFlag( void )
{
	return g_Va012F0240 &= 0xFFFFFFFEu;
}

unsigned int Rva00C13570ClearFlag( void )
{
	return g_Va012F02A0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C135E0ClearFlag( void )
{
	return g_Va012F02B0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C135EEClearFlag( void )
{
	return g_Va012F02B0 &= 0xFFFFFFFDu;
}

unsigned int Rva00C135FCClearFlag( void )
{
	return g_Va012F02B0 &= 0xFFFFFFFBu;
}

unsigned int Rva00C13650ClearFlag( void )
{
	return g_Va012F02C0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C1365EClearFlag( void )
{
	return g_Va012F02C0 &= 0xFFFFFFFDu;
}

unsigned int Rva00C1366CClearFlag( void )
{
	return g_Va012F02C0 &= 0xFFFFFFFBu;
}

unsigned int Rva00C137D8ClearFlag( void )
{
	return g_Va012F02C8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C13BD0ClearFlag( void )
{
	return g_Va012F02D0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C13D40ClearFlag( void )
{
	return g_Va012F02F0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C13D90ClearFlag( void )
{
	return g_Va012F02F8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C13E20ClearFlag( void )
{
	return g_Va012F0300 &= 0xFFFFFFFEu;
}

unsigned int Rva00C13EB0ClearFlag( void )
{
	return g_Va012F0314 &= 0xFFFFFFFEu;
}

unsigned int Rva00C13EBEClearFlag( void )
{
	return g_Va012F0314 &= 0xFFFFFFFDu;
}

unsigned int Rva00C140D0ClearFlag( void )
{
	return g_Va012F048C &= 0xFFFFFFFEu;
}

unsigned int Rva00C140DEClearFlag( void )
{
	return g_Va012F048C &= 0xFFFFFFFDu;
}

unsigned int Rva00C14290ClearFlag( void )
{
	return g_Va012F04D0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C14550ClearFlag( void )
{
	return g_Va012F0520 &= 0xFFFFFFFEu;
}

unsigned int Rva00C14590ClearFlag( void )
{
	return g_Va012F0528 &= 0xFFFFFFFEu;
}

unsigned int Rva00C14660ClearFlag( void )
{
	return g_Va012F0530 &= 0xFFFFFFFEu;
}

unsigned int Rva00C14720ClearFlag( void )
{
	return g_Va012F0538 &= 0xFFFFFFFEu;
}

unsigned int Rva00C14740ClearFlag( void )
{
	return g_Va012F0544 &= 0xFFFFFFFEu;
}

unsigned int Rva00C1474EClearFlag( void )
{
	return g_Va012F0544 &= 0xFFFFFFFDu;
}

unsigned int Rva00C14860ClearFlag( void )
{
	return g_Va012F055C &= 0xFFFFFFFEu;
}

unsigned int Rva00C148C0ClearFlag( void )
{
	return g_Va012F056C &= 0xFFFFFFFEu;
}

unsigned int Rva00C14910ClearFlag( void )
{
	return g_Va012F0574 &= 0xFFFFFFFEu;
}

unsigned int Rva00C14A20ClearFlag( void )
{
	return g_Va012F057C &= 0xFFFFFFFEu;
}

unsigned int Rva00C14B00ClearFlag( void )
{
	return g_Va012F05A4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C14B20ClearFlag( void )
{
	return g_Va012F05AC &= 0xFFFFFFFEu;
}

unsigned int Rva00C14B80ClearFlag( void )
{
	return g_Va012F05B4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C14D70ClearFlag( void )
{
	return g_Va012F05DC &= 0xFFFFFFFEu;
}

unsigned int Rva00C14E80ClearFlag( void )
{
	return g_Va012F0600 &= 0xFFFFFFFEu;
}

unsigned int Rva00C14E8EClearFlag( void )
{
	return g_Va012F0600 &= 0xFFFFFFFDu;
}

unsigned int Rva00C14ED0ClearFlag( void )
{
	return g_Va012F0608 &= 0xFFFFFFFEu;
}

unsigned int Rva00C15DB0ClearFlag( void )
{
	return g_Va012F0628 &= 0xFFFFFFFEu;
}

unsigned int Rva00C15DD0ClearFlag( void )
{
	return g_Va012F0630 &= 0xFFFFFFFEu;
}

unsigned int Rva00C15DF0ClearFlag( void )
{
	return g_Va012F0638 &= 0xFFFFFFFEu;
}

unsigned int Rva00C15E10ClearFlag( void )
{
	return g_Va012F0640 &= 0xFFFFFFFEu;
}

unsigned int Rva00C15E30ClearFlag( void )
{
	return g_Va012F0648 &= 0xFFFFFFFEu;
}

unsigned int Rva00C15E50ClearFlag( void )
{
	return g_Va012F0650 &= 0xFFFFFFFEu;
}

unsigned int Rva00C160C0ClearFlag( void )
{
	return g_Va012F0658 &= 0xFFFFFFFEu;
}

unsigned int Rva00C16180ClearFlag( void )
{
	return g_Va012F0660 &= 0xFFFFFFFEu;
}

unsigned int Rva00C161A0ClearFlag( void )
{
	return g_Va012F0668 &= 0xFFFFFFFEu;
}

unsigned int Rva00C161C0ClearFlag( void )
{
	return g_Va012F0670 &= 0xFFFFFFFEu;
}

unsigned int Rva00C161E0ClearFlag( void )
{
	return g_Va012F0678 &= 0xFFFFFFFEu;
}

unsigned int Rva00C16230ClearFlag( void )
{
	return g_Va012F0680 &= 0xFFFFFFFEu;
}

unsigned int Rva00C16940ClearFlag( void )
{
	return g_Va012F0688 &= 0xFFFFFFFEu;
}

unsigned int Rva00C169C0ClearFlag( void )
{
	return g_Va012F0690 &= 0xFFFFFFFEu;
}

unsigned int Rva00C16A0EClearFlag( void )
{
	return g_Va012F0698 &= 0xFFFFFFFEu;
}

unsigned int Rva00C16A53ClearFlag( void )
{
	return g_Va012F06A0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C16B00ClearFlag( void )
{
	return g_Va012F06A8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C16DB0ClearFlag( void )
{
	return g_Va012F06BC &= 0xFFFFFFFEu;
}

unsigned int Rva00C16DD0ClearFlag( void )
{
	return g_Va012F06C4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C16DF0ClearFlag( void )
{
	return g_Va012F06CC &= 0xFFFFFFFEu;
}

unsigned int Rva00C16E30ClearFlag( void )
{
	return g_Va012F06D4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C16E50ClearFlag( void )
{
	return g_Va012F06DC &= 0xFFFFFFFEu;
}

unsigned int Rva00C16E70ClearFlag( void )
{
	return g_Va012F06E4 &= 0xFFFFFFFEu;
}

unsigned int Rva00C17150ClearFlag( void )
{
	return g_Va012F06F0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C17190ClearFlag( void )
{
	return g_Va012F06F8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C173F0ClearFlag( void )
{
	return g_Va012F0740 &= 0xFFFFFFFEu;
}

unsigned int Rva00C173FEClearFlag( void )
{
	return g_Va012F0740 &= 0xFFFFFFFDu;
}

unsigned int Rva00C1A390ClearFlag( void )
{
	return g_Va012F07DC &= 0xFFFFFFFEu;
}

unsigned int Rva00C1A4D0ClearFlag( void )
{
	return g_Va012F07F0 &= 0xFFFFFFFEu;
}

unsigned int Rva00C1A510ClearFlag( void )
{
	return g_Va012F07F8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C1A590ClearFlag( void )
{
	return g_Va012F0800 &= 0xFFFFFFFEu;
}

unsigned int Rva00C1A6E0ClearFlag( void )
{
	return g_Va012F0808 &= 0xFFFFFFFEu;
}

unsigned int Rva00C1A740ClearFlag( void )
{
	return g_Va012F0810 &= 0xFFFFFFFEu;
}

unsigned int Rva00C1A780ClearFlag( void )
{
	return g_Va012F0818 &= 0xFFFFFFFEu;
}

unsigned int Rva00C1A7F0ClearFlag( void )
{
	return g_Va012F0820 &= 0xFFFFFFFEu;
}

unsigned int Rva00C1A910ClearFlag( void )
{
	return g_Va012F0828 &= 0xFFFFFFFEu;
}

unsigned int Rva00C1A930ClearFlag( void )
{
	return g_Va012F0834 &= 0xFFFFFFFEu;
}

unsigned int Rva00C1A93EClearFlag( void )
{
	return g_Va012F0834 &= 0xFFFFFFFDu;
}

unsigned int Rva00C1A960ClearFlag( void )
{
	return g_Va012F083C &= 0xFFFFFFFEu;
}

unsigned int Rva00C1A980ClearFlag( void )
{
	return g_Va012F0844 &= 0xFFFFFFFEu;
}

unsigned int Rva00C1AA40ClearFlag( void )
{
	return g_Va012F084C &= 0xFFFFFFFEu;
}

unsigned int Rva00C1AA68ClearFlag( void )
{
	return g_Va012F0854 &= 0xFFFFFFFEu;
}

unsigned int Rva00C1AA90ClearFlag( void )
{
	return g_Va012F085C &= 0xFFFFFFFEu;
}

unsigned int Rva00C1ACC0ClearFlag( void )
{
	return g_Va012F0868 &= 0xFFFFFFFEu;
}

unsigned int Rva00C1ACCEClearFlag( void )
{
	return g_Va012F0868 &= 0xFFFFFFFDu;
}

unsigned int Rva00C1B350ClearFlag( void )
{
	return g_Va012F0894 &= 0xFFFFFFFEu;
}

unsigned int Rva00C1BAB0ClearFlag( void )
{
	return g_Va012F0A90 &= 0xFFFFFFFEu;
}

unsigned int Rva00C1C788ClearFlag( void )
{
	return g_Va012F0CF8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C1C7AEClearFlag( void )
{
	return g_Va012F0CF8 &= 0xFFFFFFFDu;
}

unsigned int Rva00C1C7F8ClearFlag( void )
{
	return g_Va012F0D88 &= 0xFFFFFFFEu;
}

unsigned int Rva00C1C830ClearFlag( void )
{
	return g_Va012F0FD8 &= 0xFFFFFF7Fu;
}

unsigned int Rva00C1C84BClearFlag( void )
{
	return g_Va012F0FD8 &= 0xFFFFFFFEu;
}

unsigned int Rva00C1C859ClearFlag( void )
{
	return g_Va012F0FD8 &= 0xFFFFFFFDu;
}

unsigned int Rva00C1C867ClearFlag( void )
{
	return g_Va012F0FD8 &= 0xFFFFFFFBu;
}

unsigned int Rva00C1C875ClearFlag( void )
{
	return g_Va012F0FD8 &= 0xFFFFFFF7u;
}

