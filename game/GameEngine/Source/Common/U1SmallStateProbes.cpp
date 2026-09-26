// Four small bodies from the 0x005BFEE0-0x005E9780 drawer that read state and
// answer a question about it.  None of them contains a relocation site, so
// every byte compared here is concrete evidence.
//
// 0x005C0DE0, 19 bytes -- a CONSTRUCTOR:
//
//     mov eax,ecx / mov ecx,[esp+4] / test ecx,ecx
//     mov [eax],ecx / setne cl / mov [eax+4],cl / ret 4
//
// `this` in ecx, `ret 4`, and the leading `mov eax,ecx` returning `this` is a
// __thiscall constructor with one dword parameter.  The parameter is stored
// whole at offset 0 -- a pointer member -- and the SIGN of the same test is
// stored as a byte at offset 4.  `setne` after a `test` of the parameter is
// `p != 0` materialised as 0 or 1, which is what a bool member initialised
// from a pointer compiles to.  The test is emitted BEFORE the pointer store,
// so both members are initialised from the one parameter in a member-init
// list, in declaration order 0 then 4.
//
// 0x005C0E00, 11 bytes -- reads that same byte back:
//
//     mov dl,[ecx+4] / xor eax,eax / test dl,dl / sete al / ret
//
// __thiscall, no parameters, a bare `ret`: a const member function of no
// arguments.  It reads ONE byte, at offset 4, and returns its logical
// negation; `xor eax,eax` before the compare rather than a `movzx` is how
// MSVC 7.1 widens a `sete` result to a bool return.  It is the same
// displacement 0x005C0DE0 writes and the two bodies are adjacent COMDATs, but
// nothing in either body says they are members of one type, so each keeps its
// own class -- the layout is padded to the displacement instead of asserted.
//
// 0x005C0F90, 14 bytes -- the free-function form of the same question:
//
//     mov ecx,[esp+4] / mov dl,[ecx] / xor eax,eax / test dl,dl / sete al / ret
//
// A bare `ret` that pops nothing with ecx dead on entry is __cdecl, and the
// single parameter is dereferenced for a byte at offset 0.  Same negation,
// same widening.
//
// 0x005C1C20, 26 bytes -- a two-level emptiness test:
//
//     mov eax,[esp+4] / mov eax,[eax] / test eax,eax / je yes
//     cmp word ptr [eax+4],0 / je yes
//     xor eax,eax / ret
//     yes: mov eax,1 / ret
//
// __cdecl, one parameter.  A pointer is read at offset 0 of it and
// null-checked; when it survives, a SIXTEEN-BIT field at offset 4 of the
// pointee is compared against zero.  `cmp word ptr` is the operand size the
// source type dictates and cannot come from a dword member.
//
// THE RETURN TYPE IS `int`, NOT `bool`, and the bytes say so: the true arm is
// `mov eax,1`, a full dword, where the three bool-returning bodies above all
// widen through `xor eax,eax` and write only `al`.  Spelling this one `bool`
// emits `mov al,1` and a `sete`, and misses.  Both zero-tests fall through to
// a SHARED `mov eax,1`, so they are one `&&` guarding a `return 0` with a
// trailing `return 1`, not two early returns -- two early returns would put
// the constant 1 in the first arm and leave the second `je` pointing
// elsewhere.
//
// IDENTITY IS NOT RECOVERED.  Nothing names any of these four; every name is
// derived from the row address.

class U1Probe_005C0DE0
{
public:
	U1Probe_005C0DE0( void *p );

	void *m_pointer;
	bool m_present;
};

U1Probe_005C0DE0::U1Probe_005C0DE0( void *p )
	: m_pointer( p ), m_present( p != 0 )
{
}

class U1Probe_005C0E00
{
public:
	bool isAbsent( void ) const;

	void *m_pad;
	bool m_present;
};

bool U1Probe_005C0E00::isAbsent( void ) const
{
	return !m_present;
}

class U1Flagged_005C0F90
{
public:
	bool m_present;
};

bool u1IsAbsent_005C0F90( const U1Flagged_005C0F90 *f )
{
	return !f->m_present;
}

class U1PtrFlagged_005C0FB0
{
public:
	const void *m_ptr;
};

bool u1IsAbsent_005C0FB0( const U1PtrFlagged_005C0FB0 *f )
{
	return !f->m_ptr;
}

class U1Counted_005C1C20
{
public:
	void *m_pad;
	unsigned short m_count;
};

class U1Holder_005C1C20
{
public:
	U1Counted_005C1C20 *m_item;
};

int u1IsEmpty_005C1C20( const U1Holder_005C1C20 *h )
{
	const U1Counted_005C1C20 *item = h->m_item;
	if ( item != 0 && item->m_count != 0 )
	{
		return 0;
	}
	return 1;
}
