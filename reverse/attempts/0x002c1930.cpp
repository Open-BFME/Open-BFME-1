// ?method@Rva002C1930Owner@@QAEXPAX00@Z
// partial score=0.92 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc
//
// Retail RVA 0x002C1930 (205 bytes), thiscall taking (void *arg1, void*, void*)
// and returning void.  Lives in the GiantBird AI-state cluster (landed
// neighbours: 0x002C1740 Gen_002C1740::bfmeSeed, 0x002C1A60 the deleting
// destructor for GiantBirdNormalFlightState).  callers_of finds no direct
// caller and no vtable slot names the owning method, so this lands under an
// opaque address-derived name per docs/naming_evidence.md; every field below
// is proven from the disassembly and every callee is the pinned/matched
// contract callees.py resolves for this body.
//
// this-0x1c reads an Object-shaped pointer (range float at +0xbc, a further
// status word at +0x120) -- a negative offset off `this`, so `this` is a
// secondary sub-object whose primary base sits behind it (docs/shape_levers.md
// "secondary vtable slot" note).  this-0x24 is a second sub-object that both
// answers getCurrentVictim() and receives the final steering delta.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct Coord3D
{
	float x, y, z;
	void normalize();
};

class Object;

// pinned callee: ?getCurrentVictim@AIUpdateInterface@@QBEPAVObject@@XZ
class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
};

// pinned callee: ?bfmeGetHM@BfmeHolderHM@@QAEPAVBfmeItemHM@@XZ
class BfmeItemHM;
class BfmeHolderHM
{
public:
	BfmeItemHM *bfmeGetHM();
};

// pinned callee: ?bfmeAskAIA@BfmeThingAIA@@QAE_NH@Z
class BfmeThingAIA
{
public:
	Bool bfmeAskAIA( Int kindOf );
};

// pinned callee: ?bfmeCalcBT@BfmeSrcBT@@QAEMPAX@Z
class BfmeSrcBT
{
public:
	float bfmeCalcBT( void *other );
};

// pinned callee: ?bfmeDeltaTo@BfmeDeltaOwner@@QAEXPAXPAD@Z
class BfmeDeltaOwner
{
public:
	void bfmeDeltaTo( void *outDelta, char *from );
};

// matched callee: ?bfmeAdd2BB990@BfmeThing2BB990@@QAEXPBUBfmeVec2BB990@@@Z @ BfmeAddVec2BB990.cpp
struct BfmeVec2BB990;
class BfmeThing2BB990
{
public:
	void bfmeAdd2BB990( const BfmeVec2BB990 *delta );
};

// Shared shape for the owner object (this-0x1c) and the candidate argument:
// a range float at +0xbc and a status word at +0x120.
struct Rva002C1930RangeObj
{
	unsigned char m_unreconstructed_00[0xbc];
	float m_range0xbc;
	unsigned char m_unreconstructed_c0[0x120 - 0xc0];
	UnsignedInt m_flags120;
};

class Rva002C1930Owner
{
public:
	void method( void *arg1, void *arg2, void *arg3 );

	unsigned char m_unreconstructed_00[0xc];
	BfmeHolderHM *m_fallbackMachine0c;          // +0xc
	unsigned char m_unreconstructed_10[0x3cc - 0x10];
	UnsignedInt m_flags3cc;                     // +0x3cc
};

void Rva002C1930Owner::method( void *arg1, void * /*arg2*/, void * /*arg3*/ )
{
	Rva002C1930RangeObj *obj = *(Rva002C1930RangeObj **)( (char *)this - 0x1c );
	if ( !obj )
		return;

	Rva002C1930RangeObj *target = (Rva002C1930RangeObj *)arg1;
	if ( !target )
		return;

	if ( obj->m_flags120 & 0x20000 )
		return;

	void *steer = (char *)this - 0x24;
	Object *victim = ( (AIUpdateInterface *)steer )->getCurrentVictim();

	if ( !victim )
	{
		BfmeHolderHM *fallback = m_fallbackMachine0c;
		if ( !fallback )
			return;
		victim = (Object *)fallback->bfmeGetHM();
		if ( !victim )
			return;
		if ( victim == (Object *)target )
			return;
	}

	if ( !( (BfmeThingAIA *)target )->bfmeAskAIA( 2 ) )
		return;

	unsigned char shiftedByte = (unsigned char)( m_flags3cc >> 6 );
	if ( ( shiftedByte & 1 ) == 0 && victim )
	{
		float sumRange = obj->m_range0xbc + target->m_range0xbc;
		float gapSq = ( (BfmeSrcBT *)victim )->bfmeCalcBT( target );
		if ( sumRange * sumRange >= gapSq )
			return;
	}

	Coord3D delta;
	( (BfmeDeltaOwner *)target )->bfmeDeltaTo( &delta, (char *)obj );
	delta.normalize();
	( (BfmeThing2BB990 *)steer )->bfmeAdd2BB990( (const BfmeVec2BB990 *)&delta );
}
