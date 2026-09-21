// ?handle@Gen0021CE60@@QAEXH@Z
// partial score=0.54 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// pins: ?handle@Gen0021CE60@@QAEXH@Z -- Gen0021CE60 is declared as an
// address-derived receiver in R1ForwardToStoredObject.cpp
// ("void handle(int value); target->handle(value);"); this file supplies the
// real body. Identity of the receiver is unproven, but every field and callee
// it touches is proven: this+8 is read exactly like GarrisonContain::m_object
// (GarrisonContainTrackTargets.cpp, retail 0x0021E260) and it makes a direct
// pinned thiscall to GarrisonContain::removeObjectFromGarrisonPoint(Object*,
// int) with index -1. `value` is a disguised Object*: Object::m_contain at
// +0x1FC and Object::unidentified_001BFE20 (both ObjectTeamAndPlayer.cpp) are
// the pinned bfmeFind1004 target (retail 0x0000D3B9 -> 0x001BFE20). Two
// virtual calls at ContainModuleInterface slot 63 (+0xFC, uncharted beyond
// the two named slots in that file) appear to register `this` as a listener
// on the object's contain module. A miss on Object+0x94 bit 0x20 (when no
// hold module, or via fallthrough otherwise) inserts into the already-landed
// _STL::_Rb_tree<unsigned int, pair<const unsigned int, 8-byte value>, ...>
// instantiation at this+0x9C4 (RvaTreeInsertUniqueUnsigned.cpp, retail
// 0x0000EE2B -> 0x0021BE20, Rva0021BE20Tree/Rva0021BE20Pair). The tail always
// runs: remove the object from every garrison point (index -1); set
// ObjectStatusMaskType bit 4 (ObjectStatusBits.cpp pattern,
// MAKE_OBJECT_STATUS_MASK); forward to the vision-spied-mask handle() shared
// body with player index 9 (retail 0x000348EC, still-dump alias pinned as
// actionA@BfmeObjE10, ICF-shared with Gen001C9A10::handle in
// BfmeVisionSpiedMaskHandlers.cpp -- routed here via alternatename since
// Object's real relationship to that body is unproven); then move the object
// to this receiver's own m_object's cached position (Thing::setPosition,
// retail 0x00132CE0).

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
#include <bitset>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	void setPosition( const Coord3D *position );

private:
	unsigned char m_pad00[ 0x38 ];
public:
	Coord3D m_cachedPos;
};

class HordeContainInterface;
struct Gen0021CE60;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
// Slot count and slot-26 signature match the proven declaration in
// ObjectTeamAndPlayer.cpp; only slot 63 (+0xFC), which this body reaches
// through an indirect vtable call with no REL32 evidence, is given real
// arguments here.
class ContainModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual HordeContainInterface *getHordeContainInterface();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37();
	virtual void slot38(); virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45();
	virtual void slot46(); virtual void slot47(); virtual void slot48(); virtual void slot49();
	virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57();
	virtual void slot58(); virtual void slot59(); virtual void slot60(); virtual void slot61();
	virtual void slot62();
	virtual void slot63( void ( *callback )( int, Gen0021CE60 * ), Gen0021CE60 *self, int mask );	// +0xFC
	virtual void slot64();
	virtual void slot65();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <int NUMBITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };
	BitFlags() { }
	BitFlags( _dummy_kInit, Int idx1 ) { m_bits.set( idx1 ); }
	void set( const BitFlags &other ) { m_bits |= other.m_bits; }
private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;
#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

class Object
{
public:
	void *unidentified_001BFE20( void ) const;
	void setStatus( const ObjectStatusMaskType &objectStatus, Bool set );
	void actionA( Int player );	// still-dump alias, routed via alternatename

	unsigned char m_unmodelled_000[ 0x94 ];
	unsigned char m_flags94;			// +0x94, bit 0x20 tested
	unsigned char m_unmodelled_095[ 0x1fc - 0x95 ];
	ContainModuleInterface *m_contain;		// +0x1FC
};

// GarrisonContain's proven layout (GarrisonContainTrackTargets.cpp): only the
// one member this body reaches is redeclared here.
class GarrisonContain
{
public:
	void removeObjectFromGarrisonPoint( Object *object, int index );
};

struct Rva0021BE20Value
{
	char m_body[ 8 ];
};

typedef _STL::pair<const unsigned int, Rva0021BE20Value> Rva0021BE20Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva0021BE20Pair,
	_STL::_Select1st<Rva0021BE20Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva0021BE20Pair> > Rva0021BE20Tree;

struct Gen0021CE60
{
	unsigned char m_pad00[ 8 ];
	Object *m_object;				// +8, matches GarrisonContain::m_object
	unsigned char m_pad0c[ 0x9c4 - 0xc ];
	Rva0021BE20Tree m_tree;			// +0x9C4

	void handle( int value );
};

// R1ForwardToStoredObject.cpp; already-landed forwarder this body registers
// as the hold module's callback (retail passes its address through the ILT
// thunk at 0x00033CA3).
void Rva0021A2D0( int value, Gen0021CE60 *target );

void Gen0021CE60::handle( int value )
{
	Object *obj = ( Object * )value;
	ContainModuleInterface *hold = obj->m_contain;
	bool doInsert = true;

	if ( hold != 0 )
	{
		void *x = obj->unidentified_001BFE20();
		if ( x != 0 )
		{
			hold->slot63( &Rva0021A2D0, this, 1 );
			hold->slot63( &Rva0021A2D0, this, 0x10 );
		}
	}
	else if ( obj->m_flags94 & 0x20 )
	{
		doInsert = false;
	}

	if ( doInsert )
	{
		Rva0021BE20Pair pairValue( ( unsigned int )obj, Rva0021BE20Value() );
		m_tree.insert_unique( pairValue );
	}

	( ( GarrisonContain * )this )->removeObjectFromGarrisonPoint( obj, -1 );
	obj->setStatus( MAKE_OBJECT_STATUS_MASK( 4 ), true );
	obj->actionA( 9 );
	( ( Thing * )obj )->setPosition( &( ( Thing * )m_object )->m_cachedPos );
}

#pragma comment( linker, "/alternatename:?actionA@Object@@QAEXH@Z=?j_000348ec@@YAXXZ" )
