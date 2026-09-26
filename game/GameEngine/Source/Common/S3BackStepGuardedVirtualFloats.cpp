// Five 38-to-41-byte __thiscall float accessors that ask a predicate sixteen
// bytes BEHIND `this`, then tail-jump into a virtual on a stored pointer:
//
//     push esi / mov esi,ecx / lea ecx,[esi-0x10] / call <REL32> /
//     test al,al / je .1 /
//     mov eax,[esi+0xD0] / lea ecx,[eax+0x10] / mov eax,[ecx] /
//     pop esi / jmp [eax+SLOT]
//  .1 fld [<float>] / pop esi / ret
//
// WHAT THE BYTES SHOW.  The -0x10 adjust is BARE.  A base-to-derived
// static_cast at a non-zero offset is null-guarded by MSVC -- probing that
// spelling produced `test esi,esi / je / lea / jmp / xor ecx,ecx`, five bytes
// longer, in both the pointer and the reference form.  Retail has no guard, so
// whatever sits at `this - 0x10` is NOT reached by a derived-class conversion;
// the address is simply computed and known non-null.  That is written here as
// pointer arithmetic to an unrelated type, which is the spelling that asserts
// LEAST: it claims a fixed 16-byte back-step and nothing about inheritance.
//
// The target pointer at [this+0xD0] is adjusted by +0x10 BEFORE its vptr is
// read, so the interface being called is a SECOND base of the pointee, sitting
// at offset 0x10 behind a first base that is itself polymorphic (a non-
// polymorphic first base would have been reordered to the back by MSVC and the
// interface would have landed at offset 0 with no `lea`).
//
// Control leaves through `jmp`, so the virtual's return value IS this
// function's: st0, a float.  The other arm loads a float from a fixed address
// with `fld dword ptr [imm32]`, not `fldz` -- the literal 0.0f compiles to
// `fldz`, so this is a named object, and it is the SAME address in all five.
//
// ONE AXIS: the vtable slot -- 0x18, 0x1C, 0x6C, 0x78 and 0x8C, i.e. indices 6,
// 7, 27, 30 and 35.  Predicate, member offset, base adjust and float are shared
// by all five, which is why they are written as five members of ONE class:
// splitting them would assert five layouts that the bytes say are identical.
// The 0x8C row is three bytes longer only because that slot needs a disp32.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address, the 36
// declared virtuals exist only to place five slots, and the bytes say nothing
// about what any of them compute.

extern const float GenFloat00C75350;

struct GenPair002153D0
{
	unsigned int first;
	unsigned int second;
};

class GenTargetFace
{
public:
	virtual float v00();
	virtual float v01();
	virtual float v02( int value );
	virtual float v03();
	virtual float v04();
	virtual float v05();
	virtual float v06();
	virtual float v07();
	virtual float v08();
	virtual float v09();
	virtual float v10();
	virtual float v11();
	virtual float v12();
	virtual float v13();
	virtual float v14();
	virtual float v15();
	virtual float v16();
	virtual float v17();
	virtual float v18();
	virtual float v19();
	virtual float v20();
	virtual float v21();
	virtual float v22();
	virtual float v23();
	virtual float v24();
	virtual float v25();
	virtual float v26();
	virtual float v27();
	virtual float v28();
	virtual float v29();
	virtual float v30();
	virtual GenPair002153D0 *v31( GenPair002153D0 *result );
	virtual float v32();
	virtual float v33();
	virtual float v34();
	virtual float v35();
};

class GenTargetHead
{
public:
	virtual void h();
	char m_pad[ 12 ];
};

class GenTarget : public GenTargetHead, public GenTargetFace {};

class GenOwner
{
public:
	bool ready();
	float sample002150E0();
	char m_pad[ 0xe0 ];
	GenTarget *m_cached;
};

class BfmeOwnFCB
{
public:
	void bfmeAfterFCB();
};

class GenPart
{
public:
	float sample00215040();
	GenPair002153D0 sample002153D0();
	float sample00215470( int value );
	float sample00215150();
	float sample002154B0();
	float sample002154E0();
	float sample00215510();
	float sample00215550();
	char m_pad[ 0xd0 ];
	GenTarget *m_target;
};

#define S3_SAMPLE( NAME, SLOT )                                            	float GenPart::NAME()                                                   	{                                                                       		GenOwner *owner = (GenOwner *)( (char *)this - 0x10 );               		if( owner->ready() )                                                 			return m_target->v##SLOT();                                        		return GenFloat00C75350;                                             	}

S3_SAMPLE( sample00215150, 27 )
S3_SAMPLE( sample002154B0, 06 )
S3_SAMPLE( sample002154E0, 07 )
S3_SAMPLE( sample00215510, 35 )
S3_SAMPLE( sample00215550, 30 )

float GenPart::sample00215470( int value )
{
	GenOwner *owner = (GenOwner *)( (char *)this - 0x10 );
	if( owner->ready() )
		return m_target->v02( value );
	return GenFloat00C75350;
}

float GenOwner::sample002150E0()
{
	((BfmeOwnFCB *)this)->bfmeAfterFCB();
	if( ready() )
		return m_cached->v04();
	return GenFloat00C75350;
}

float GenPart::sample00215040()
{
	GenOwner *owner = (GenOwner *)( (char *)this - 0x10 );
	((BfmeOwnFCB *)owner)->bfmeAfterFCB();
	if( owner->ready() )
		return m_target->v05();
	return GenFloat00C75350;
}

GenPair002153D0 GenPart::sample002153D0()
{
	GenPair002153D0 fallback;
	GenPair002153D0 temporary;
	GenPair002153D0 *result;
	fallback.first = 0;
	GenOwner *owner = (GenOwner *)( (char *)this - 0x10 );
	if( owner->ready() )
		result = m_target->v31( &temporary );
	else
	{
		fallback.first = 0;
		fallback.second = 0;
		result = &fallback;
	}
	return *result;
}
