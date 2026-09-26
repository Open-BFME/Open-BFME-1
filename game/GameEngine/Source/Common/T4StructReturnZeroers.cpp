// cl: /EHs-c-
//
// Two __stdcall leaves from the 0x005E97B0..0x0060D680 slice that zero a small
// block the caller owns.  Both take the block by pointer as their first stack
// argument, load it once into eax and store zeros through it; neither reads
// ecx, so neither is __thiscall, and both pop their own arguments, so neither
// is __cdecl.  The argument counts come straight from the `ret` immediate --
// 0x0C over a three-dword frame and 0x14 over a five-dword frame -- and the
// extra arguments are never touched.
//
// The block is an OUT PARAMETER and not a returned struct.  A twelve-byte
// return value would also arrive as a hidden leading pointer, but MSVC 7.1
// builds one through a named local and shuffles registers doing it; retail
// writes straight through the incoming pointer with no local at all.
//
// THE TWO SPELLINGS OF ZERO ARE THE SAME SOURCE.  0x0060D5B0 stores two
// immediate zeros; 0x005FA4C0 stores three through a zeroed ecx.  That is
// MSVC's own threshold for materialising a shared constant, not a difference in
// the source, which is why both are written the same way.
//
// IDENTITY IS NOT RECOVERED.  Both names are derived from addresses, and the
// unread arguments are spelled `int` because only their count is visible.

typedef int Int;

struct T4Pair
{
	Int m_a;
	Int m_b;
};

struct T4Triple3
{
	Int m_x;
	Int m_y;
	Int m_z;
};

void __stdcall t4Zero0060D5B0( T4Pair *out, Int a, Int b )
{
	out->m_a = 0;
	out->m_b = 0;
}

void __stdcall t4Zero005FA4C0( T4Triple3 *out, Int a, Int b, Int c, Int d )
{
	out->m_x = 0;
	out->m_y = 0;
	out->m_z = 0;
}
