// Four free functions, 23 to 52 bytes, that append one string to a sink and
// hand the sink back.  Retail, the simplest of them (0x005C6350):
//
//     mov eax,[esp+8] / mov ecx,[eax] / push esi / mov esi,[esp+8]
//     push ecx / mov ecx,esi / call <REL32> / mov eax,esi / pop esi / ret
//
// WHAT THE BYTES SHOW.  A bare `ret` that pops nothing, with ecx dead on
// entry, is __cdecl with two dword parameters.  The FIRST parameter goes to
// esi, becomes the callee`s `this` (`mov ecx,esi`) and is returned in eax; the
// SECOND is dereferenced at offset 0 and that dword is the callee`s only
// argument.  A free function that calls a member on its first argument and
// returns that argument unchanged is the stream-inserter shape, the same one
// T1ReceiverSwappingThunks.cpp documents as its shape A -- this file is the
// arity where the argument comes out of the second parameter rather than being
// the second parameter.
//
// ALL FOUR CALL THE SAME MEMBER, 0x005C49D0, which is what forces its
// parameter type to be ONE type across all four rows: 0x005C6680 hands it a
// string literal, so the parameter is a `const char *` and 0x005C6350 is
// reading a `const char *` member, not an opaque dword.  A second sink method
// would be a second address; there is only one.
//
// 0x005C7A10, 25 bytes, IS THE FREE-CALLEE VARIANT: `push ecx / push esi /
// call <REL32> / add esp,8`.  The caller cleans up, so that callee is __cdecl
// and takes the sink as its FIRST argument instead of as `this`; everything
// else is identical.
//
// 0x005C6630, 52 bytes, CHOOSES BETWEEN A MEMBER AND THE EMPTY STRING:
//
//     mov eax,[esp+8] / mov eax,[eax] / test eax,eax / je empty
//     push esi / mov esi,[esp+8] / add eax,8 / push eax
//     mov ecx,esi / call <REL32> / mov eax,esi / pop esi / ret
//     empty: push esi / mov esi,[esp+8] / mov eax,<LITERAL> / push eax
//     mov ecx,esi / call <REL32> / mov eax,esi / pop esi / ret
//
// The second parameter holds a null-checked pointer at offset 0.  On the
// non-null path the pointer is advanced by a BARE `add eax,8` and the RESULT
// is what gets pushed -- an address inside the pointee, not a dword read out
// of it, so the member at offset 8 is an ARRAY that decays, not a pointer.  On
// the null path the pushed value is an absolute address that reads as a zero
// byte in .rdata: the empty string literal.  MSVC 7.1 duplicates the push,
// call, and epilogue into both arms rather than merging, because each arm
// materialises its pointer differently.
//
// 0x005C6680, 35 bytes, CHOOSES BETWEEN TWO LITERALS on a BYTE parameter:
//
//     mov al,[esp+8] / test al,al / mov eax,<"Yes"> / jne go
//     mov eax,<"No">
//     go: push esi / mov esi,[esp+8] / push eax / mov ecx,esi / call ...
//
// Only `al` is read, so the second parameter is a one-byte type, and the two
// absolute addresses spell "Yes" and "No" in retail .rdata.  The true value is
// loaded UNCONDITIONALLY and the false value overwrites it when the test
// fails, which is how MSVC 7.1 lays out a conditional expression whose arms
// are both immediates.
//
// THE ABSOLUTE ADDRESSES ARE DIR32 OPERANDS copied from retail and are not
// evidence for anything beyond the string contents the image already holds.
//
// IDENTITY IS NOT RECOVERED.  The sink type, the member and the two boxes are
// named nowhere; every name here comes from a row or callee address.

class U1Sink
{
public:
	void add( const char *text );
};

class U1Box
{
public:
	const char *m_value;
};

U1Sink *u1Insert_005C6350( U1Sink *sink, const U1Box *box )
{
	sink->add( box->m_value );
	return sink;
}

void u1Emit_005C7A10( U1Sink *sink, const char *text );

U1Sink *u1Insert_005C7A10( U1Sink *sink, const U1Box *box )
{
	u1Emit_005C7A10( sink, box->m_value );
	return sink;
}

class U1Named
{
public:
	char m_pad[ 8 ];
	const char m_name[ 4 ];
};

class U1NamedBox
{
public:
	const U1Named *m_named;
};

U1Sink *u1Insert_005C6630( U1Sink *sink, const U1NamedBox *box )
{
	const U1Named *named = box->m_named;
	sink->add( named ? named->m_name : "" );
	return sink;
}

U1Sink *u1Insert_005C6680( U1Sink *sink, bool flag )
{
	sink->add( flag ? "Yes" : "No" );
	return sink;
}
