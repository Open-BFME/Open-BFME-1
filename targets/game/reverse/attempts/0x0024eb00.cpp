// ?onDie@SlaughterHordeContain@@UAEXPBVDamageInfo@@@Z
// partial score=0.231 date=2026-11-03
// ?onDie@SlaughterHordeContain@@UAEXPBVDamageInfo@@@Z
// Retail: 329 bytes at 0x0024EB00, through RET 4 at +0x146.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// FILE: SlaughterHordeContainOnDie.cpp ///////////////////////////////////////
//
// SlaughterHordeContain::onDie.
//
// BFME 1 evidence: the SlaughterHordeContain constructor 0x0024E7A0 stores
// the die-interface table 0x010B0F1C at complete-object +0x28; its slot 0 is
// ILT 0x00041B82 to this body (identity_evidence/0x0024eb00-on-die-slot.md),
// and ilt_oracle CONFIRMS ?onDie@SlaughterHordeContain@@UAEXPBVDamageInfo@@@Z
// here (exact).
//
// Shape from the Open BFME 2 donor CitadelSlaughterHordeContain.cpp
// (revision 59e3f8f825, CitadelSlaughterHordeContain::onDie at BFME 2
// 0x00480821): walk a copy of the contained-object list; for every object
// whose template carries the horde-container kind, ask its contain
// interface for its own members and hand each one to this container's
// +0x20 interface. BFME 1 offsets come from this body: the contain list at
// complete +0x38 (this+0x10), the +0x20 interface slot 34, template kind
// word +0xD4 bit 0x1000, contain interface slot 60.
//
///////////////////////////////////////////////////////////////////////////////

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class DamageInfo;
class Object;

// The contained-object list is the generated four-byte list instantiation
// whose copy constructor is ledgered at 0x001CB160 (gen-tgrid); the payload
// name only spells that instantiation.
struct Gen_t_001cb160_p4cd { int a[1]; };
typedef _STL::list<Gen_t_001cb160_p4cd> SlaughterContainList;

// Declaration-only: retail calls the out-of-line copy constructor.
namespace _STL {
template <> list<Gen_t_001cb160_p4cd, allocator<Gen_t_001cb160_p4cd> >::list(
	const list<Gen_t_001cb160_p4cd, allocator<Gen_t_001cb160_p4cd> > &other );
}

// The members list a contained horde returns: built inline, destroyed through
// the pinned out-of-line ??1Rva000CEBD0IntListState@@QAE@XZ (0x000CEBD0).
class Rva000CEBD0IntListState : public _STL::list<int>
{
public:
	~Rva000CEBD0IntListState();
};

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
	unsigned char m_unmodelled_08[ 0xD4 - 0x08 ];
	UnsignedInt m_kindOfD4;					// +0xD4
};

#define BFME_SLOT( n ) virtual void unusedSlot##n();

class SlaughterContainedInterface
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
	virtual void getContainedMembers( Rva000CEBD0IntListState &members );						// slot 60
};

class Object
{
public:
	void *unidentified_001BFE20() const;
	const ThingTemplate *getTemplate() const
	{
		return !m_template ? 0 : (const ThingTemplate *)m_template->friend_getFinalOverride();
	}

	void *m_vptr;
	const Overridable *m_template;			// +0x04
};

class SlaughterHordeContainBase
{
public:
	virtual void s00();

private:
	unsigned char m_unmodelled_04[ 0x20 - 0x04 ];
};

class SlaughterHordeContainIface20
{
public:
	BFME_SLOT( 0 ) BFME_SLOT( 1 ) BFME_SLOT( 2 ) BFME_SLOT( 3 ) BFME_SLOT( 4 ) BFME_SLOT( 5 )
	BFME_SLOT( 6 ) BFME_SLOT( 7 ) BFME_SLOT( 8 ) BFME_SLOT( 9 ) BFME_SLOT( 10 ) BFME_SLOT( 11 )
	BFME_SLOT( 12 ) BFME_SLOT( 13 ) BFME_SLOT( 14 ) BFME_SLOT( 15 ) BFME_SLOT( 16 ) BFME_SLOT( 17 )
	BFME_SLOT( 18 ) BFME_SLOT( 19 ) BFME_SLOT( 20 ) BFME_SLOT( 21 ) BFME_SLOT( 22 ) BFME_SLOT( 23 )
	BFME_SLOT( 24 ) BFME_SLOT( 25 ) BFME_SLOT( 26 ) BFME_SLOT( 27 ) BFME_SLOT( 28 ) BFME_SLOT( 29 )
	BFME_SLOT( 30 ) BFME_SLOT( 31 ) BFME_SLOT( 32 ) BFME_SLOT( 33 )
	virtual void slot34( Int member );															// slot 34

private:
	unsigned char m_unmodelled_04[ 4 ];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleInterface
{
public:
	virtual void onDie( const DamageInfo *damageInfo ) = 0;
};

class SlaughterHordeContain : public SlaughterHordeContainBase,
	public SlaughterHordeContainIface20,
	public DieModuleInterface
{
public:
	virtual void onDie( const DamageInfo *damageInfo );

private:
	unsigned char m_unmodelled_2C[ 0x38 - 0x2C ];
	SlaughterContainList m_containList;		// +0x38
};

void SlaughterHordeContain::onDie( const DamageInfo * )
{
	SlaughterContainList objects( m_containList );
	for( SlaughterContainList::iterator it = objects.begin(); it != objects.end(); ++it )
	{
		Object *obj = *(Object **)&*it;
		if( obj && ( obj->getTemplate()->m_kindOfD4 & 0x1000 ) )
		{
			SlaughterContainedInterface *contain = (SlaughterContainedInterface *)obj->unidentified_001BFE20();
			if( contain )
			{
				Rva000CEBD0IntListState members;
				contain->getContainedMembers( members );
				for( _STL::list<int>::iterator m = members.begin(); m != members.end(); ++m )
				{
					if( *m )
						slot34( *m );
				}
			}
		}
	}
}
