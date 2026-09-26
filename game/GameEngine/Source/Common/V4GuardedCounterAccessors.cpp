// Two tiny __thiscall members that update one integer member behind a guard and
// return a value:
//
//     0x003BB8D0  mov eax,[ecx+4] / test eax,eax / jbe .out / dec eax
//                 mov [ecx+4],eax / .out: mov eax,[ecx+4] / ret
//     0x003BC9A0  mov al,[ecx+0x2C] / test al,al / jne .up / xor eax,eax / ret
//                 .up: mov eax,[ecx+0x18] / inc eax / mov [ecx+0x18],eax / ret
//
// WHAT THE BYTES SHOW.  `test eax,eax` followed by `jbe` is an UNSIGNED test:
// the only unsigned value that is `<=` zero is zero, so the guard is `> 0` on an
// unsigned member and the field is spelled unsigned here.  The trailing
// `mov eax,[ecx+4]` RE-READS the member after the store rather than reusing the
// decremented value already in eax, which is what returning the member itself
// compiles to -- returning the expression would have kept eax.
//
// The second row loads its guard with `mov al` -- a one-byte field at +0x2C --
// and then leaves the incremented value in eax without re-reading it, so that
// one returns the pre-increment expression's result, not the member.  Its
// zero return sits on the FALL-THROUGH path with the update out of line, which
// is what an early `return 0` produces.
//
// IDENTITY IS NOT RECOVERED.  Both names are derived from an address.

class Rva003BB8D0
{
public:
	unsigned decrement();
	char     m_pad00[ 0x4 ];
	unsigned m_at04;
};
unsigned Rva003BB8D0::decrement()
{
	if( m_at04 > 0 )
		--m_at04;
	return m_at04;
}

class Rva003BC9A0
{
public:
	int  advance();
	char m_pad00[ 0x18 ];
	int  m_at18;
	char m_pad1C[ 0x10 ];
	bool m_at2C;
};
int Rva003BC9A0::advance()
{
	if( !m_at2C )
		return 0;
	return ++m_at18;
}

// The carved boundary at 0x003BC990 contains only a return.
void Rva003BC990Noop()
{
}
