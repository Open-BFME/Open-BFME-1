// cl: /EHs-c-
// Four 21-byte __thiscall accessors returning a float from behind a nullable
// pointer.  Retail:
//
//     mov eax,[ecx+<PTR>]     ; 0x1CC in three rows, 0x20C in the fourth
//     test eax,eax
//     je L
//     fld dword ptr [eax+<FIELD>]     ; 0x30, 0x24, 0x2C and 0x2C
//     ret
//   L:
//     fld dword ptr [<CONSTANT>]      ; 0.0f in three rows, 1.0f in the fourth
//     ret
//
// WHAT THE BYTES SHOW.  `ret` with no operand and no argument slot read, `ecx`
// as the base, and an x87 value left on the stack: a const member function of no
// arguments returning `Real`.  The whole body is
// `return m_ptr ? m_ptr->m_field : <constant>;` -- one conditional expression,
// not an `if` with two returns, which would duplicate the epilogue.
//
// THE CONSTANT IS LOADED FROM MEMORY EVEN WHEN IT IS ZERO.  Three of the four
// rows return 0.0f and none of them uses `fldz`; MSVC 7.1 spells every
// floating-point literal in this position as an `fld` from a `__real@` datum, so
// the site is a four-byte DIR32 the gate takes from the target and the literal's
// value is not evidence.  It is read here only to describe the rows.
//
// FOUR ROWS, FOUR ACCESSORS.  Three read one pointer at 0x1CC at three different
// field offsets, so they belong to one class; the fourth reads a different
// pointer at 0x20C and a different constant, so it belongs to another.
//
// IDENTITY IS NOT RECOVERED.  Names come from addresses and field names carry
// their offsets.  Seventeen of each row's 21 bytes are concrete.

typedef float Real;
typedef int Int;

class Rva005C3510Data
{
public:
	Int m_unreconstructed_00[ 9 ];	// +0x00 .. +0x20
	Real m_field24;
	Real m_field28;
	Real m_field2C;
	Real m_field30;
};

class Rva005C3510Owner
{
public:
	Int m_unreconstructed_000[ 115 ];	// +0x000 .. +0x1C8
	Rva005C3510Data *m_data1CC;

	Real field30(void) const;
	Real field24(void) const;
	Real field2C(void) const;
};

Real Rva005C3510Owner::field30(void) const
{
	return m_data1CC ? m_data1CC->m_field30 : 0.0f;
}

Real Rva005C3510Owner::field24(void) const
{
	return m_data1CC ? m_data1CC->m_field24 : 0.0f;
}

Real Rva005C3510Owner::field2C(void) const
{
	return m_data1CC ? m_data1CC->m_field2C : 0.0f;
}

class Rva00988F00Owner
{
public:
	Int m_unreconstructed_000[ 131 ];	// +0x000 .. +0x208
	Rva005C3510Data *m_data20C;

	Real field2C(void) const;
};

Real Rva00988F00Owner::field2C(void) const
{
	return m_data20C ? m_data20C->m_field2C : 1.0f;
}
