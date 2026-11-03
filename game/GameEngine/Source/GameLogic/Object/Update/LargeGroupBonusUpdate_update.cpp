// ?update@LargeGroupBonusUpdate@@UAE?AW4UpdateSleepTime@@XZ
// Retail: 818 bytes at 0x00297930, through RET at +0x331.
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// FILE: LargeGroupBonusUpdate_update.cpp /////////////////////////////////////
//
// LargeGroupBonusUpdate::update.
//
// BFME 1 evidence: the LargeGroupBonusUpdate constructor installs the update
// interface table 0x010BFC5C at +0x10; its slot 0 reaches this body through
// ILT 0x0001CEF9, and ilt_oracle CONFIRMS the decorated name here (exact).
// The interface sits at owner+0x10, so the module data and object are
// this-0x0C and this-0x08 (as in BannerCarrierUpdate_update.cpp).
//
// Shape from the Open BFME 2 donor LargeGroupBonusUpdate.cpp (donor revision
// 59e3f8f825, BFME 2 0x00490225, 589 B): every-frame kind test or the update
// delay; a member / player / alive / not-self partition scan counting the
// members each hit's interface accepts; enough members turns the bonus on,
// otherwise a second pass looks for an active bonus holder within the
// rub-off radius; a changed state applies or removes the attribute
// modifier; the tail touches the same interface and picks the sleep time.
// BFME 1 offsets and callees come from this body: module data update rate
// +0x08, member filter +0x0C, count +0x10, radius +0x14, rub-off radius
// +0x1C, attribute modifier +0x2C; owner frame +0x24, state bytes +0x28 and
// +0x29; template kind word +0xC8 bit 8 and Thing::isKindOf(9); behavior
// modules at Object+0x1F0 (the inlined rva00297480 scan, slot +0x70 of the
// +0x0C interface); Object+0x344 bit 0. The partition result and filter
// views follow PropagandaTowerBehavior_doScan.cpp.
//
///////////////////////////////////////////////////////////////////////////////

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum KindOfType
{
	KINDOF_RVA_9 = 9
};

#include "Lib/Coord3D.h"
#include "ascii_string.h"

class Player;

// Retail ?getFinalOverride@Overridable@@QBEPBV1@XZ (ILT 0x000022BB).
class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	const Overridable *friend_getFinalOverride() const
	{
		if( m_nextOverride )
			return m_nextOverride->getFinalOverride();
		return this;
	}

	unsigned char m_unmodelled_00[ 4 ];
	Overridable *m_nextOverride;			// +0x04
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled_08[ 0xC8 - 0x08 ];
	UnsignedInt m_kindOfBits;				// +0xC8
};

class Thing
{
public:
	Bool isKindOf( KindOfType t ) const;
	const ThingTemplate *getTemplate() const
	{
		return !m_template ? 0 : (const ThingTemplate *)m_template->friend_getFinalOverride();
	}

protected:
	void *m_vptr;
	const ThingTemplate *m_template;		// +0x04
};

// What a behavior module's +0x0C interface slot 28 hands back: slot 2 says
// whether it holds the bonus (the inlined rva00297480 scan).
class LargeGroupBonusMember
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Bool isActive();
};

#define BFME_SLOT( n ) virtual void unusedSlot##n();

class LargeGroupBonusBehaviorIface
{
public:
	BFME_SLOT( 0 ) BFME_SLOT( 1 ) BFME_SLOT( 2 ) BFME_SLOT( 3 ) BFME_SLOT( 4 ) BFME_SLOT( 5 )
	BFME_SLOT( 6 ) BFME_SLOT( 7 ) BFME_SLOT( 8 ) BFME_SLOT( 9 ) BFME_SLOT( 10 ) BFME_SLOT( 11 )
	BFME_SLOT( 12 ) BFME_SLOT( 13 ) BFME_SLOT( 14 ) BFME_SLOT( 15 ) BFME_SLOT( 16 ) BFME_SLOT( 17 )
	BFME_SLOT( 18 ) BFME_SLOT( 19 ) BFME_SLOT( 20 ) BFME_SLOT( 21 ) BFME_SLOT( 22 ) BFME_SLOT( 23 )
	BFME_SLOT( 24 ) BFME_SLOT( 25 ) BFME_SLOT( 26 ) BFME_SLOT( 27 )
	virtual LargeGroupBonusMember *getMember();									// slot 28 (+0x70)
};

struct LargeGroupBonusBehaviorModule
{
	unsigned char m_unmodelled_00[ 0x0C ];
	LargeGroupBonusBehaviorIface m_iface;	// +0x0C
};

// The interface Object's unidentified_001BFE20 returns: slot 84 counts the
// members the given filter accepts.
class LargeGroupBonusContain
{
public:
	BFME_SLOT( 0 ) BFME_SLOT( 1 ) BFME_SLOT( 2 ) BFME_SLOT( 3 ) BFME_SLOT( 4 ) BFME_SLOT( 5 )
	BFME_SLOT( 6 ) BFME_SLOT( 7 ) BFME_SLOT( 8 ) BFME_SLOT( 9 ) BFME_SLOT( 10 ) BFME_SLOT( 11 )
	BFME_SLOT( 12 ) BFME_SLOT( 13 ) BFME_SLOT( 14 ) BFME_SLOT( 15 ) BFME_SLOT( 16 ) BFME_SLOT( 17 )
	BFME_SLOT( 18 ) BFME_SLOT( 19 ) BFME_SLOT( 20 ) BFME_SLOT( 21 ) BFME_SLOT( 22 ) BFME_SLOT( 23 )
	BFME_SLOT( 24 ) BFME_SLOT( 25 ) BFME_SLOT( 26 ) BFME_SLOT( 27 ) BFME_SLOT( 28 ) BFME_SLOT( 29 )
	BFME_SLOT( 30 ) BFME_SLOT( 31 ) BFME_SLOT( 32 ) BFME_SLOT( 33 ) BFME_SLOT( 34 ) BFME_SLOT( 35 )
	BFME_SLOT( 36 ) BFME_SLOT( 37 ) BFME_SLOT( 38 ) BFME_SLOT( 39 ) BFME_SLOT( 40 ) BFME_SLOT( 41 )
	BFME_SLOT( 42 ) BFME_SLOT( 43 ) BFME_SLOT( 44 ) BFME_SLOT( 45 ) BFME_SLOT( 46 ) BFME_SLOT( 47 )
	BFME_SLOT( 48 ) BFME_SLOT( 49 ) BFME_SLOT( 50 ) BFME_SLOT( 51 ) BFME_SLOT( 52 ) BFME_SLOT( 53 )
	BFME_SLOT( 54 ) BFME_SLOT( 55 ) BFME_SLOT( 56 ) BFME_SLOT( 57 ) BFME_SLOT( 58 ) BFME_SLOT( 59 )
	BFME_SLOT( 60 ) BFME_SLOT( 61 ) BFME_SLOT( 62 ) BFME_SLOT( 63 ) BFME_SLOT( 64 ) BFME_SLOT( 65 )
	BFME_SLOT( 66 ) BFME_SLOT( 67 ) BFME_SLOT( 68 ) BFME_SLOT( 69 ) BFME_SLOT( 70 ) BFME_SLOT( 71 )
	BFME_SLOT( 72 ) BFME_SLOT( 73 ) BFME_SLOT( 74 ) BFME_SLOT( 75 ) BFME_SLOT( 76 ) BFME_SLOT( 77 )
	BFME_SLOT( 78 ) BFME_SLOT( 79 ) BFME_SLOT( 80 ) BFME_SLOT( 81 ) BFME_SLOT( 82 ) BFME_SLOT( 83 )
	virtual UnsignedInt countMembers( const void *filter );							// slot 84 (+0x150)
};

// Retail ?bfmeSendXI@BfmeOwnerXI@@QAEXPAVBfmeMsgXI@@@Z (0x001C1E30): with the
// attribute-modifier name, the removal partner of applyAttributeModifier.
class BfmeMsgXI;
class BfmeOwnerXI
{
public:
	void bfmeSendXI( BfmeMsgXI *msg );
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	void *unidentified_001BFE20() const;
	Bool applyAttributeModifier( const AsciiString &name, Int duration );
	void removeAttributeModifier( const AsciiString &name )
	{
		( (BfmeOwnerXI *)this )->bfmeSendXI( (BfmeMsgXI *)&name );
	}

	const Coord3D *getPosition() const { return &m_pos; }
	Real getDistanceSquared2D( const Coord3D *pos ) const
	{
		Real dx = m_pos.x - pos->x;
		Real dy = m_pos.y - pos->y;
		return dx * dx + dy * dy;
	}

	__forceinline LargeGroupBonusMember *findMember() const
	{
		for( LargeGroupBonusBehaviorModule **m = m_behaviors; *m; ++m )
		{
			LargeGroupBonusMember *member = ( *m )->m_iface.getMember();
			if( member )
				return member;
		}
		return 0;
	}

	unsigned char m_unmodelled_008[ 0x38 - 0x08 ];
	Coord3D m_pos;							// +0x38
	unsigned char m_unmodelled_044[ 0x1F0 - 0x44 ];
	LargeGroupBonusBehaviorModule **m_behaviors;	// +0x1F0
	unsigned char m_unmodelled_1F4[ 0x344 - 0x1F4 ];
	unsigned char m_344;					// +0x344
};

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

// vtable 0x010BFAB8 (out-of-line ctor 0x00297440): the member filter and
// whether a counted hit allows. The class keeps the address-derived name the
// DIR32 ledger records for that vtable (dir32_addresses.csv).
class Rva00297440VptrZeroObject : public PartitionFilter
{
public:
	Rva00297440VptrZeroObject( const void *filter, Bool match )
		: m_filter( filter ), m_match( match ) {}
	virtual ~Rva00297440VptrZeroObject() {}
	virtual Bool allow( Object * );

	const void *m_filter;
	Bool m_match;
};

// vtable 0x01097144: Player* at +8; the class keeps the address-derived name
// the DIR32 ledger records for that vtable (dir32_addresses.csv).
class Rva0016A9F0FunctorValueWrapper : public PartitionFilter
{
public:
	Rva0016A9F0FunctorValueWrapper( Player *p ) : m_player( p ) {}
	virtual ~Rva0016A9F0FunctorValueWrapper() {}
	virtual Bool allow( Object * );
	virtual int getPlayerMask();

	Player *m_player;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow( Object * );
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

struct WidePair
{
	Object *object;
	UnsignedInt unknown04;
};

struct WidePayload
{
	std::vector<WidePair> entries;
	WidePair *current;
	Int references;
};

struct BfmeWideResult
{
	WidePayload *value;

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

	void reset() { value->current = value->entries.begin(); }
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC( int, int, int, int, int );
};

extern BfmeWideForwardC *ThePartitionManager;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	unsigned char m_unmodelled_00[ 0x3C ];
	UnsignedInt m_frame;					// +0x3C
};

extern GameLogic *TheGameLogic;

class LargeGroupBonusUpdateModuleData
{
public:
	unsigned char m_unmodelled_00[ 0x08 ];
	UnsignedInt m_updateRate;				// +0x08
	unsigned char m_hordeMemberFilter[ 4 ];	// +0x0C
	UnsignedInt m_count;					// +0x10
	Real m_radius;							// +0x14
	unsigned char m_unmodelled_18[ 0x1C - 0x18 ];
	Real m_rubOffRadius;					// +0x1C
	unsigned char m_unmodelled_20[ 0x2C - 0x20 ];
	AsciiString m_attributeModifier;		// +0x2C
};

class LargeGroupBonusModuleBase
{
public:
	virtual void s00();

protected:
	const LargeGroupBonusUpdateModuleData *m_moduleData;	// +0x04
	Object *m_object;										// +0x08
};

class LargeGroupBonusBehaviorInterface
{
public:
	virtual void s00();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class LargeGroupBonusUpdate : public LargeGroupBonusModuleBase,
	public LargeGroupBonusBehaviorInterface,
	public UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();

private:
	unsigned char m_unmodelled_14[ 0x24 - 0x14 ];
	UnsignedInt m_lastFrame;				// +0x24
	Bool m_active;							// +0x28
	Bool m_fullGroup;						// +0x29
};

static inline Real sqr( Real x ) { return x * x; }

UpdateSleepTime LargeGroupBonusUpdate::update()
{
	Object *obj = m_object;
	if( !obj )
		return UPDATE_SLEEP_FOREVER;
	{
		const LargeGroupBonusUpdateModuleData *data = m_moduleData;
		Bool wasActive = m_active;
		UnsignedInt kindOfBits = obj->getTemplate()->m_kindOfBits;
		GameLogic *gameLogic = TheGameLogic;
		Bool everyFrame = ( kindOfBits & 0x100 ) || obj->isKindOf( KINDOF_RVA_9 );
		if( everyFrame || gameLogic->getFrame() > m_lastFrame + data->m_updateRate )
		{
			m_lastFrame = gameLogic->getFrame();
			const void *memberFilter = data->m_hordeMemberFilter;
			Rva00297440VptrZeroObject filterMember( memberFilter, true );
			Rva0016A9F0FunctorValueWrapper filterPlayer( obj->getControllingPlayer() );
			Rva0025ED50RootFilter filterAlive;
			Rva0025ED50ObjectFilter filterNotThis( obj );
			BfmeWideResult hits = ThePartitionManager->bfmeForwardWideC(
				(int)obj->getPosition(), *(const int *)&data->m_radius, 3,
				(int)filterMember.link( filterPlayer.link( filterAlive.link( &filterNotThis ) ) ), 0 );

			UnsignedInt count = 0;
			Object *other;
			while( ( other = hits.next() ) != 0 )
			{
				LargeGroupBonusContain *contain = (LargeGroupBonusContain *)other->unidentified_001BFE20();
				if( contain )
					count += contain->countMembers( memberFilter );
			}
			hits.reset();

			if( count >= data->m_count - 1 )
			{
				m_fullGroup = true;
				m_active = true;
			}
			else
			{
				m_active = false;
				m_fullGroup = false;
				Real nearSqr = sqr( data->m_rubOffRadius );
				while( ( other = hits.next() ) != 0 )
				{
					LargeGroupBonusMember *member = other->findMember();
					if( member && member->isActive() )
					{
						Real distSqr = m_object->getDistanceSquared2D( other->getPosition() );
						if( distSqr <= nearSqr )
						{
							m_active = true;
							break;
						}
					}
				}
			}

			if( wasActive != m_active )
			{
				if( m_active )
					obj->applyAttributeModifier( data->m_attributeModifier, 0 );
				else
					obj->removeAttributeModifier( data->m_attributeModifier );
			}
		}

		if( obj->m_344 & 1 )
			return UPDATE_SLEEP_FOREVER;
		obj->unidentified_001BFE20();
		return everyFrame ? (UpdateSleepTime)data->m_updateRate : UPDATE_SLEEP_NONE;
	}
}
