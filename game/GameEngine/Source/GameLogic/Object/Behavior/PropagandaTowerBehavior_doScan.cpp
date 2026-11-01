// ?doScan@PropagandaTowerBehavior@@MAEXXZ
// Retail: 764 bytes at 0x00203800, through RET at +0x2FB.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Include
// stlport

// FILE: PropagandaTowerBehavior_doScan.cpp ///////////////////////////////////
//
// PropagandaTowerBehavior::doScan. Identity: the matched update entry at
// 0x00203660 (PropagandaTowerBehavior_update_BFME.cpp) calls primary vtable
// slot 12 when the scan delay elapses, and the installed PropagandaTowerBehavior
// vtable holds this body there; slot 13 is effectLogic.
//
// Shape from the Open BFME 2 donor PropagandaTowerBehavior::doScan
// (Code/GameEngine/Source/GameLogic/Object/Behavior/PropagandaTowerBehavior.cpp,
// donor revision 45afcff3): pulse FX by upgrade state, a wide partition query
// through a relationship / root / self / kind-of filter chain, a fresh
// ObjectTracker list, effectLogic(false) for objects that left, then the old
// list is freed. BFME 1 offsets and callees are read from this body: module
// data at +0x04, owner at +0x08, tracker list at +0x28, required upgrade at
// +0x2C; module data radius +0x08, pulse FX +0x14, upgraded pulse FX +0x20.
// The partition result and filter views follow the matched sibling
// Rva00257DB0PartitionScan.cpp.
//
///////////////////////////////////////////////////////////////////////////////

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <bitset>
#include <hash_map>

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

enum ObjectID { INVALID_ID = 0, FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff };

#include "Lib/Coord3D.h"

class Player;
class UpgradeTemplate;

class Object
{
public:
	Player *getControllingPlayer() const;
	Bool hasUpgrade( const UpgradeTemplate *upgrade ) const;
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_id; }

private:
	unsigned char m_00_to_38[ 0x38 ];
	Coord3D m_pos;
	unsigned char m_44_to_74[ 0x74 - 0x44 ];
	ObjectID m_id;
};

class Player
{
public:
	Bool hasUpgradeComplete( const UpgradeTemplate *upgrade );
};

class UpgradeTemplate
{
public:
	Int getUpgradeType() const { return m_type; }

private:
	void *m_unmodelled_00;
	Int m_type;
};

class FXList
{
public:
	Bool bfmeIsBlocked();
	void doFXObj( const Object *primary, const Object *secondary ) const;

	static void doFXObj( const FXList *fx, const Object *primary, const Object *secondary = 0 )
	{
		if( fx && !const_cast<FXList *>( fx )->bfmeIsBlocked() )
			fx->doFXObj( primary, secondary );
	}
};

template <int NUMBITS> class BitFlags
{
public:
	enum BogusInitType { kInit = 0 };
	BitFlags( BogusInitType, Int bit ) { m_bits.set( bit ); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<192> KindOfMaskType;
extern const KindOfMaskType KINDOFMASK_NONE;

class PartitionFilter
{
public:
	PartitionFilter() : m_next( 0 ) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow( Object * ) = 0;
	virtual int getPlayerMask();

	PartitionFilter *link( PartitionFilter *next );

	PartitionFilter *m_next;
};

class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	explicit Rva0025ED50ObjectFilter( Object *object )
		: m_object( object ) {}
	virtual ~Rva0025ED50ObjectFilter() {}
	virtual Bool allow( Object * );

	Object *m_object;
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship( Object *object, Int mode, Bool match )
		: m_obj( object ), m_flags( mode ), m_match( match ) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow( Object * );
	virtual int getPlayerMask();

	Object *m_obj;
	Int m_flags;
	Bool m_match;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow( Object * );
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	// The 102-byte body at 0x000C3DD0, kept visible (as in
	// Rva002622D0Collect.cpp) so the mask temporary is known not to escape
	// and its storage is reused for the relationship filter.
	__declspec( noinline ) PartitionFilterAcceptByKindOf( const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear )
		: m_mustBeSet( mustBeSet ), m_mustBeClear( mustBeClear ) {}
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow( Object * );

	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

struct Rva0025ED50Entry
{
	Object *object;
	UnsignedInt unknown04;
};

struct Rva0025ED50ResultData
{
	std::vector<Rva0025ED50Entry> entries;
	Rva0025ED50Entry *current;
	Int references;
};

struct BfmeWideResult
{
	Rva0025ED50ResultData *value;

	BfmeWideResult();
	BfmeWideResult( const BfmeWideResult & );
	~BfmeWideResult()
	{
		if( --value->references == 0 )
			delete value;
	}

	Object *next()
	{
		if( value->current == value->entries.end() )
			return 0;
		return ( value->current++ )->object;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC( int, int, int, int, int );
};

extern BfmeWideForwardC *ThePartitionManager;

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<int>, _STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	Object *findObjectByID( ObjectID id )
	{
		if( id == INVALID_ID )
			return 0;
		ObjectPtrHash::iterator it = m_objHash.find( id );
		if( it == m_objHash.end() )
			return 0;
		return ( *it ).second;
	}

private:
	unsigned char m_00_to_b0[ 0xB0 ];
	ObjectPtrHash m_objHash;
};

extern GameLogic *TheGameLogic;

class ObjectTracker
{
public:
	ObjectTracker() : objectID( INVALID_ID ), next( 0 ) {}
	virtual ~ObjectTracker();

	ObjectID objectID;
	ObjectTracker *next;
};

class PropagandaTowerBehaviorModuleData
{
public:
	unsigned char m_00_to_08[ 0x08 ];
	Real m_scanRadius;
	unsigned char m_0c_to_14[ 0x14 - 0x0C ];
	const FXList *m_pulseFX;
	unsigned char m_18_to_20[ 0x20 - 0x18 ];
	const FXList *m_upgradedPulseFX;
};

class PropagandaTowerBehavior
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void removeAllInfluence();

protected:
	virtual void doScan();
	virtual void effectLogic( Object *obj, Bool giving, const PropagandaTowerBehaviorModuleData *modData );

	const PropagandaTowerBehaviorModuleData *getPropagandaTowerBehaviorModuleData() const { return m_moduleData; }

private:
	const PropagandaTowerBehaviorModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_0c_to_28[ 0x28 - 0x0C ];
	ObjectTracker *m_insideList;
	const UpgradeTemplate *m_upgradeRequired;
};

void PropagandaTowerBehavior::doScan()
{
	const PropagandaTowerBehaviorModuleData *modData = getPropagandaTowerBehaviorModuleData();
	Object *us = m_object;
	ObjectTracker *newInsideList = 0;

	Bool upgradePresent = false;
	if( m_upgradeRequired )
	{
		switch( m_upgradeRequired->getUpgradeType() )
		{
			case 0:
			{
				Player *player = us->getControllingPlayer();
				upgradePresent = player->hasUpgradeComplete( m_upgradeRequired );
				break;
			}
			case 1:
				upgradePresent = us->hasUpgrade( m_upgradeRequired );
				break;
		}
	}

	if( upgradePresent == true )
		FXList::doFXObj( modData->m_upgradedPulseFX, us );
	else
		FXList::doFXObj( modData->m_pulseFX, us );

	BfmeWideResult hits = ThePartitionManager->bfmeForwardWideC(
		(int)us->getPosition(), *(const int *)&modData->m_scanRadius, 0,
		(int)PartitionFilterRelationship( us, 4, false ).link(
			Rva0025ED50RootFilter().link(
				Rva0025ED50ObjectFilter( us ).link(
					&PartitionFilterAcceptByKindOf( KINDOFMASK_NONE,
						KindOfMaskType( KindOfMaskType::kInit, 7 ) ) ) ) ), 0 );

	Object *obj;
	while( ( obj = hits.next() ) != 0 )
	{
		if( obj == us )
			continue;

		ObjectTracker *newEntry = new ObjectTracker;
		newEntry->objectID = obj->getID();
		newEntry->next = newInsideList;
		newInsideList = newEntry;
	}

	for( ObjectTracker *curr = m_insideList; curr; curr = curr->next )
	{
		ObjectTracker *objectTracker;
		for( objectTracker = newInsideList; objectTracker; objectTracker = objectTracker->next )
			if( objectTracker->objectID == curr->objectID )
				break;

		if( objectTracker == 0 )
		{
			obj = TheGameLogic->findObjectByID( curr->objectID );
			if( obj )
				effectLogic( obj, false, modData );
		}
	}

	while( m_insideList )
	{
		ObjectTracker *next = m_insideList->next;
		delete m_insideList;
		m_insideList = next;
	}
	m_insideList = newInsideList;
}
