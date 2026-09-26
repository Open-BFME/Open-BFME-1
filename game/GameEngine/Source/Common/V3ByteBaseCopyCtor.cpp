// cl: /EHs-c-
// One 50-byte __thiscall copy constructor, one level below
// V3InlineTwoBaseCopyCtors.cpp.  Retail:
//
//     push esi ; push edi ; mov edi,[esp+0xC] ; push edi ; mov esi,ecx
//     call 0x005EB090                       ; first base's copy ctor, arg at 0
//     test edi,edi ; je L ; lea eax,[edi+0xC] ; jmp M ; L: xor eax,eax ; M:
//     mov al,[eax] ; mov [esi+0xC],al       ; one byte, from the base at 0xC
//     pop edi
//     mov [esi],  <DERIVED VFTABLE 0>
//     mov [esi+8],<DERIVED VFTABLE 8>
//     mov eax,esi ; pop esi ; ret 4
//
// WHAT THE BYTES SHOW.  One out-of-line call taking the argument unchanged, one
// round of two vptr stores at 0 and 8, and between them a single byte copied
// through the null-propagating test/je/lea/jmp/xor conversion -- so the thing at
// 0xC is a BASE (a member subobject's address is never null and gets a bare
// displacement) and it is not polymorphic (nothing stamps a vptr at 0xC).  One
// round of vptr stores means one class and no intermediate level.
//
// THE CALLEE IS ALREADY A LEDGER ROW: 0x005EB090 is the two-base class
// V3InlineTwoBaseCopyCtors.cpp landed, whose own body re-stamps exactly the
// slots at 0 and 8.
//
// AND THIS BODY FIXES ITS WIDTH AT 0xC.  That file could not: all six of its
// 41-byte rows stamp two vptrs and copy the first base's int, and none of them
// reads or writes anything past 8, so the second base's width is invisible
// there -- it was taken from Q2MultipleBaseVtableSetters.cpp, which reads
// 0x0107375C as carrying an extra dword.  Here the byte base sits at 0xC and is
// reached by a conversion, not a displacement, so 0x005EB090 ends at 0xC and its
// second base is four bytes wide.  Spelling that base with the extra dword puts
// the byte base at 0x10 and the body stops matching.
//
// IDENTITY IS NOT RECOVERED.  Names come from addresses; the two vftable dwords
// are DIR32 sites the gate takes from the target, leaving 38 of the 50 bytes
// concrete.

typedef int Int;

// ---- the first base, landed in V3InlineTwoBaseCopyCtors.cpp; declared only --

class V3Vt01111D90
{
public:
	virtual void s0();
	virtual ~V3Vt01111D90() {}
	Int m_unreconstructed_04;
};

class V3Vt0107375C
{
public:
	virtual void s0();
	virtual ~V3Vt0107375C() {}
};

class Rva005EB090 : public V3Vt01111D90, public V3Vt0107375C
{
public:
	Rva005EB090( const Rva005EB090 & );
};

// ---- the base at 0xC: one byte, no vptr ------------------------------------

class V3Byte0C
{
public:
	char m_field00;
};

// --------------------------------------------------------------- the row ----

class Rva005EB050 : public Rva005EB090, public V3Byte0C
{
public:
	Rva005EB050( const Rva005EB050 & );
};

Rva005EB050::Rva005EB050( const Rva005EB050 &o )
	: Rva005EB090( o ), V3Byte0C( o )
{
}
