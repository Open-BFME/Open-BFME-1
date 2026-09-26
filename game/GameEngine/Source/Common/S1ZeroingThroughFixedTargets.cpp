// Two more zero-the-members bodies of the same mnemonic shape as
// S1ZeroingConstructors.cpp (`xor` a register to zero, then store it repeatedly)
// which that file could not hold, because in these two the object being written
// is not simply `this`.
//
// 00339100 -- a constructor that ALSO parks a fixed address:
//
//     mov eax,ecx / xor ecx,ecx / mov dword ptr [eax],<DIR32> /
//     mov [eax+4],ecx / mov [eax+8],cl / ret
//
// The trailing `mov eax,ecx` return of `this` is the constructor tell.  The
// three stores ASCEND (0, 4, 8), so they are separate statements.  The first is
// a full-width immediate the linker fills, and build.py copies it from retail --
// NOT evidence.  The address it holds (RVA 0x00CE75C0, in .rdata) reads like a
// vftable, but a vftable store and `m_p = &SomeConstObject;` are the same four
// bytes, so the less assertive spelling is used.  The store widths of the other
// two are proven: dword at 4, single byte at 8.
//
// 006E1AC0 -- the same zeroing, through a pointer read from a global:
//
//     mov eax,[<DIR32>] / xor ecx,ecx / mov [eax+0x40],ecx /
//     mov [eax+0x3C],ecx / mov [eax+0x38],ecx / ret
//
// The base is loaded ONCE and reused for all three stores, which is what the
// compiler does when the pointer is copied to a local first.  No `mov eax,ecx`
// at the end, so this is void, not a constructor.
//
// THE STORES DESCEND HERE, and that is the one place this family's usual tell
// runs out.  Ascending stores prove separate statements, but descending stores
// do NOT prove a chain: `p->c = 0; p->b = 0; p->a = 0;` written as three
// statements in that order and `p->a = p->b = p->c = 0;` written as one chain
// compile to the SAME five instructions.  (What is excluded is the other chain:
// `p->c = p->b = p->a = 0` stores ascending, and does not match.)  Both matching
// spellings were compiled; the separate-statement form is used below because it
// asserts nothing about chaining.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived, including the .rdata
// datum and the global pointer slot.

extern const int Rdata00CE75C0;

class Rva00339100
{
public:
	Rva00339100();
	const int *m_target;
	int m_a;
	bool m_b;
};

Rva00339100::Rva00339100()
{
	m_target = &Rdata00CE75C0;
	m_a = 0;
	m_b = false;
}

class Gen006E1AC0
{
public:
	char m_lead[ 0x38 ];
	int m_a;
	int m_b;
	int m_c;
};

extern Gen006E1AC0 *Data00EF8048;

void Rva006E1AC0();
void Rva006E1AC0()
{
	Gen006E1AC0 *target = Data00EF8048;
	target->m_c = 0;
	target->m_b = 0;
	target->m_a = 0;
}
