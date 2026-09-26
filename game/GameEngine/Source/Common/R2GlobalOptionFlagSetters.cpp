// Eight bodies in one drawer of the retail image (0x00061180..0x00061470, on a
// 0x20 stride with one gap) that each set one bit of a shared 32-bit global,
// set one BYTE global to 1, and return 1:
//
//     or dword ptr [0x012A6FA0],<BIT> / mov eax,1
//     mov byte ptr [<BYTE>],al / ret
//
// WHAT THE BYTES SHOW.  No `this`, no stack arguments, a bare `ret`: __cdecl
// with no parameters.  `mov eax,1` COSTS FIVE BYTES where `mov byte ptr
// [<BYTE>],1` would have written the flag in seven and needed no register at
// all -- the compiler paid for eax because eax is the RESULT, and then reused
// al for the store.  A bool result would have been `mov al,1`, two bytes, so
// the result is four bytes wide: these return int, not bool.
//
// THE BITS ARE 0x20, 0x40, 0x80, 0x100, 0x200, 0x400, 0x800 and 0x1000 -- one
// per body, ascending with address, and the two smallest use the sign-extended
// imm8 encoding (`83 0D ... 20`) while the rest need imm32 (`81 0D ...`).  That
// is purely an encoding consequence of the value and is why the family splits
// 18/21 bytes.  The byte globals ascend with them: 0xDC, 0xDD, 0xDE, 0xDF,
// 0xE0, then 0xE2, 0xE3, 0xE4 -- 0xE1 IS SKIPPED, and 0x00061260..0x00061460
// is a gap in the drawer, so at least one sibling of this family is somewhere
// else or was never emitted.  Nothing here recovers what the bit means.
//
// All three operand addresses are DIR32 sites the patcher fills from retail;
// the extern names are address-derived.  Ten bytes of every body are concrete.
//
// IDENTITY IS NOT RECOVERED.

extern unsigned int R2Mask012A6FA0;
extern bool R2Flag012ED4DC;
extern bool R2Flag012ED4DD;
extern bool R2Flag012ED4DE;
extern bool R2Flag012ED4DF;
extern bool R2Flag012ED4E0;
extern bool R2Flag012ED4E2;
extern bool R2Flag012ED4E3;
extern bool R2Flag012ED4E4;

#define R2_SET_OPTION_BIT( NAME, BIT, FLAG )                              \
	int NAME()                                                            \
	{                                                                     \
		R2Mask012A6FA0 |= BIT;                                              \
		FLAG = true;                                                        \
		return 1;                                                           \
	}

R2_SET_OPTION_BIT( Rva00061180, 0x20, R2Flag012ED4DC )
R2_SET_OPTION_BIT( Rva000611A0, 0x40, R2Flag012ED4DD )
R2_SET_OPTION_BIT( Rva000611C0, 0x80, R2Flag012ED4DE )
R2_SET_OPTION_BIT( Rva000611E0, 0x100, R2Flag012ED4DF )
R2_SET_OPTION_BIT( Rva00061200, 0x200, R2Flag012ED4E0 )
R2_SET_OPTION_BIT( Rva00061220, 0x400, R2Flag012ED4E2 )
R2_SET_OPTION_BIT( Rva00061240, 0x800, R2Flag012ED4E3 )
R2_SET_OPTION_BIT( Rva00061470, 0x1000, R2Flag012ED4E4 )
