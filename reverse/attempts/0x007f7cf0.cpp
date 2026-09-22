// ?rva007F7CF0@Rva007F7CF0Owner@@QAEXPAVBfmeThingVFD@@PAX@Z
// partial score=0.18 date=2026-09-22
// STRONG IDENTITY EVIDENCE (new this session, not in prior blocked rows):
// `python3 tools/vtable_lookup.py 0x0112B7F0 --slots 20` proves this RVA is
// SLOT 0 of the BfmeThingDGD vtable -- the SAME vtable the already-landed
// constructor (0x007F7FA0, BfmeThingDGDConstructor.cpp) and destructor
// (0x007F8090, BfmeThingDGDDestructor.cpp) install. Slot 0 is neither of
// those (they are plain, non-virtually-dispatched calls), so this is some
// OTHER BfmeThingDGD virtual method with no caller and no source name --
// stays address-derived under the proven class per AGENTS.md.
//
// SIGNATURE: thiscall(this=BfmeThingDGD*), 2 explicit args, ret 8. Second
// arg (esi) is proven `BfmeThingVFD*` by the tail call `bfmeGoVFD(BfmeThingVFD*)`
// (0x007F7760, already matched, see Code/GameEngine/Source/Common/BfmeConv1351.cpp)
// -- esi is passed there unmodified. BfmeThingVFD::m_bfme08 (already a plain
// field in that landed struct) is read here as a state tag (must be 4 to
// proceed, gets set to 0 on the full path / 5 on the deferred path) -- NEW
// evidence that vendor's m_bfmePad[8] (bytes 0-7) hides a vtable-shaped
// pointer this function dispatches through (the existing sibling body never
// touches those bytes, so there is no contradiction, just no prior evidence).
//
// THIS-8 SIBLING: retail computes edi=(char*)this-8 and calls a 24-slot
// vtable's slot 0x17 (index 23) on it with 2 int args. No identity for that
// object; BfmeThingDGD's own ctor/dtor prove ONLY the primary vtable
// (0112B7F0) installed AT `this`, so the -8 object is a distinct instance
// this class is embedded/paired with (possibly the wrapping "sibling"
// mentioned in the destructor's multi-level-inheritance comment) -- unproven.
//
// GLOBAL CALL 0x007EB810 (Rva007EB810Get, already matched/pinned, returns a
// `long` that is really a pointer): the returned object's OWN first field is
// ALSO a vtable-shaped pointer (double indirection, `mov ecx,[eax]` then
// `call [ecx+8]`), and the call passes (self=eax, 0, 0x0112b7e0, this-arg2)
// as four PLAIN STACK ARGS -- NOT a thiscall (ecx only holds the fetched
// function-table pointer, never becomes the callee's `this`). Modelled here
// as a raw function-pointer table (Rva007F7CF0Registry) rather than a C++
// virtual class for that reason. 0x0112b7e0 is a fixed literal (16 less than
// this vtable's own install VA 0x0112b7f0); no proven meaning.
//
// RESULT: compiles and links (all six callees resolve: Rva007EB810Get,
// BfmeThingVFD's two getters modelled as hidden-pointer-returning by-value
// methods to match retail's out-param+eax-mirror ABI, the -8 sibling's
// slot 0x17, this->m_14's slot 0x2c [an 11-dummy-slot vtable, index 11 =
// offset 0x2c], and bfmeGoVFD). ours=149B retail=167B, 137/167 non-reloc
// bytes differ -- the SHAPE (branch structure, which calls happen on which
// path, argument counts) is largely right but codegen diverges early
// (retail's very first instruction is a bare `push ecx` stack-filler before
// any register is given a role; a diff of the compiled listing shows the
// args reaching the sibling's slot 0x17 call collapse to a single pushed
// value in our build instead of two, so the Handle-by-value ABI for
// getA()/getB() is not fully reproducing retail's two-temporary shape) --
// NOT exact, do not trust the field offsets/vtable slot counts as final,
// verify independently before reusing.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

long Rva007EB810Get( void );

struct Rva007F7CF0Registry
{
	void **m_vtable;
};
typedef void ( __cdecl *Rva007F7CF0RegFn2 )( void *, int, unsigned, void * );

class Rva007F7CF0Handle
{
public:
	Rva007F7CF0Handle( const Rva007F7CF0Handle & );
	int m_id;
};

class BfmeThingVFD
{
public:
	virtual void slot00();
	virtual Rva007F7CF0Handle getA();
	virtual Rva007F7CF0Handle getB();
	void *m_04;
	int m_state;
};

void __stdcall bfmeGoVFD( BfmeThingVFD * );

class Rva007F7CF0Sibling
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
	virtual void s0c(); virtual void s0d(); virtual void s0e(); virtual void s0f();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
	virtual void s14(); virtual void s15(); virtual void s16();
	virtual void s17( int, int );
};

class Rva007F7CF0M14
{
public:
	virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03();
	virtual void t04(); virtual void t05(); virtual void t06(); virtual void t07();
	virtual void t08(); virtual void t09(); virtual void t0a();
	virtual void t0b( BfmeThingVFD *, void * );
};

class Rva007F7CF0Owner
{
public:
	void rva007F7CF0( BfmeThingVFD *task, void *resource );

	void *m_00; // vtable install (not stored/used here)
	void *m_04;
	void *m_08;
	void *m_0c;
	void *m_10;
	Rva007F7CF0M14 *m_14;
};

void Rva007F7CF0Owner::rva007F7CF0( BfmeThingVFD *task, void *resource )
{
	if( !task || task->m_state != 4 )
		return;

	if( resource )
	{
		Rva007F7CF0Registry *reg = (Rva007F7CF0Registry *)Rva007EB810Get();
		Rva007F7CF0RegFn2 fn2 = (Rva007F7CF0RegFn2)reg->m_vtable[ 2 ];
		fn2( reg, 0, 0x0112b7e0, resource );
		Rva007F7CF0Handle a = task->getA();
		Rva007F7CF0Handle b = task->getB();
		Rva007F7CF0Sibling *sibling = (Rva007F7CF0Sibling *)( (char *)this - 8 );
		sibling->s17( b.m_id, a.m_id );
		task->m_state = 0;
		m_14->t0b( task, resource );
		bfmeGoVFD( task );
	}
	else
	{
		task->m_state = 5;
		m_14->t0b( task, 0 );
	}
}
