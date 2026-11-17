// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Identity and ABI: targets/game/reverse/identity_evidence/00365df0-state-transfer.md.

typedef int Int;
typedef float Real;
typedef bool Bool;

extern "C" __declspec(dllimport) double __cdecl floor( double value );

// ?bfmeFloatToLong@@YAJM@Z absent-from-retail
__forceinline long bfmeFloatToLong( Real value )
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

enum KindOfType
{
	RVA00365DF0_KIND_127 = 127
};

class Rva00365DF0Player;
class Player;
class BfmeLivingWorldPlayerArmyCollection;

class GameLogic
{
public:
	Bool _bfme_isInLivingWorldCampaign( void );
};

class Rva00365DF0PlayerList
{
private:
	char m_unmodelled00[ 0x0C ];

public:
	Player *m_firstPlayer;
};

extern GameLogic *TheGameLogic;
#define RVA00365DF0_GAME_LOGIC TheGameLogic
class PlayerList;
extern PlayerList *ThePlayerList;
#define RVA00365DF0_PLAYER_LIST (reinterpret_cast<Rva00365DF0PlayerList *>(ThePlayerList))

class Object
{
public:
	Player *getControllingPlayer( void ) const;

	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void bfmeBuildObjectInfo( struct BfmeObjectInfo *record ) const;
	// ?fill@Object@@QBEXPAX@Z absent-from-retail
	void fill(void *record) const { bfmeBuildObjectInfo(reinterpret_cast<BfmeObjectInfo *>(record)); }

	char m_unmodelled04[ 0x84 ];
	Object *m_next;
	char m_unmodelled8C[ 0x2B8 ];
	unsigned char m_flags;
	char m_unmodelled345[ 0x2B ];
	Int m_livingWorldIndex;
};

#define THING_TU_MEMBERS \
public: Bool isKindOf( KindOfType kind ) const;
#include "../../Common/Thing/thing.h"
#undef THING_TU_MEMBERS

class Rva00362670Owner
{
public:
    void reset();
};

class BfmeOwnVUM
{
public:
    BfmeOwnVUM();
    ~BfmeOwnVUM();
    virtual void bfmeSlot0VUM();
    virtual void bfmeSlot1VUM();
    virtual void bfmeSlot2VUM();
    virtual void bfmeSlot3VUM();
    virtual void bfmeSlot4VUM();

    // ?reset@BfmeOwnVUM@@QAEXXZ absent-from-retail
    void reset() { reinterpret_cast<Rva00362670Owner *>(this)->reset(); }

    char m_body00[0x30];
    Int m_field34;
    char m_body38[4];
    Int m_field3C;
    char m_body40[0x74];
};

typedef BfmeOwnVUM Rva00365DF0Record;
typedef char Rva00365DF0RecordSize[sizeof(Rva00365DF0Record) == 0xB4 ? 1 : -1];

class Rva00364B10Summary
{
};

class Rva00364B10LivingWorldPlayerArmyCollection
{
public:
	Int scanArmyGroups( Rva00364B10Summary *summary, Bool copySummary );
};

struct P6Elem00365520;
class Gen00365520
{
public:
	void bfmeAppend( const P6Elem00365520 *record );
};

class BfmeLivingWorldPlayerArmyCollection
{
public:
	void clearModeFourArmies();
	void rva00365df0(Object *firstObject);

	struct ArmySlot
	{
		char m_body[ 0x58 ];
	};
	struct ArmyVector
	{
		ArmySlot *m_begin;
		ArmySlot *m_end;
		ArmySlot *m_capacity;
		// ?size@ArmyVector@BfmeLivingWorldPlayerArmyCollection@@QBEIXZ absent-from-retail
	unsigned int size() const { return (unsigned int)(m_end - m_begin); }
		// ?begin@ArmyVector@BfmeLivingWorldPlayerArmyCollection@@QBEPAVArmySlot@2@XZ absent-from-retail
	ArmySlot *begin() const { return m_begin; }
	};

	char m_unmodelled00[ 0x18 ];
	ArmyVector m_playerArmies;
};

struct UpgradeMaskType
{
	unsigned int m_bits[ 6 ];
};

class Rva003C1050
{
public:
	void setMask( UpgradeMaskType mask );

	char m_unmodelled00[ 0xA8 ];
	UpgradeMaskType m_mask;
};

#include <vector>

enum ScienceType
{
	Rva003C2720ScienceTypeValue = 0
};

class Rva003C2720Owner
{
public:
	void copy( const _STL::vector<ScienceType> *source );
};

class Rva00365C20Visitor;
class Rva000F99C0RecordDispatch { public: void dispatch(Rva00365C20Visitor *visitor); };
class Rva000F99C0Owner
{
public:
	// ?update@Rva000F99C0Owner@@QAEXPAVBfmeLivingWorldPlayerArmyCollection@@@Z absent-from-retail
	void update( BfmeLivingWorldPlayerArmyCollection *owner ) { reinterpret_cast<Rva000F99C0RecordDispatch *>(this)->dispatch(reinterpret_cast<Rva00365C20Visitor *>(owner)); }

	void *m_begin;
	void *m_end;
	void *m_capacity;
};

class Rva00365DF0Player
{
public:
	char m_unmodelled00[ 0x54 ];
	void *m_upgradeList;
	char m_betweenListAndMasks[ 0x1C ];
	UpgradeMaskType m_upgradesInProgress;
	UpgradeMaskType m_upgradesCompleted;
	char m_unmodelledA4[ 0x190 ];
	_STL::vector<ScienceType> m_sciences;
	_STL::vector<ScienceType> m_sciencesDisabled;
	_STL::vector<ScienceType> m_sciencesHidden;
	Int m_rankLevel;
	Real m_field25C;
	Real m_field260;
	Int m_field264;
	char m_unmodelled268[ 0x41C ];
	Rva000F99C0Owner m_field684;
};

class Rva00365DF0Logic
{
public:
	char m_unmodelled00[ 0x74 ];
	Int m_field74;
	char m_unmodelled78[ 0x28 ];
	Int m_fieldA0;
	Real m_fieldA4;
	Rva003C1050 m_setMaskView;
	// ?assign74@Rva00365DF0Logic@@QAEXH@Z absent-from-retail
	void assign74( Int value ) { m_field74 = value; }
	// ?assignA0@Rva00365DF0Logic@@QAEXH@Z absent-from-retail
	void assignA0( Int value ) { m_fieldA0 = value; }
	// ?assignA4@Rva00365DF0Logic@@QAEXM@Z absent-from-retail
	void assignA4( Real value ) { m_fieldA4 = value; }

};

// Retail 0x012F1028 is EA's TheLivingWorldLogic (data_rows.csv owns
// ?TheLivingWorldLogic@@3PAVLivingWorldLogic@@A there, defined in
// game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldLogic.cpp).  The
// Glo012F1028 spelling was the address-derived pin, which nothing defines, so
// the reference moves to the defining name.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#define RVA00365DF0_LIVING_WORLD_LOGIC (reinterpret_cast<Rva00365DF0Logic *>(TheLivingWorldLogic))

// ?rva00365df0@BfmeLivingWorldPlayerArmyCollection@@QAEXPAVObject@@@Z
void BfmeLivingWorldPlayerArmyCollection::rva00365df0(Object *firstObject)
{
	Rva00365DF0Player *player;
	BfmeLivingWorldPlayerArmyCollection *self = this;

	if( !RVA00365DF0_GAME_LOGIC->_bfme_isInLivingWorldCampaign() )
		return;
	if( firstObject == 0 )
		return;

	self->clearModeFourArmies();
	player = reinterpret_cast<Rva00365DF0Player *>(RVA00365DF0_PLAYER_LIST->m_firstPlayer);
	if( player == 0 )
		return;

	Rva00365DF0Record record;
	for( Object *object = firstObject; object != 0; object = object->m_next )
	{
		if( object == 0 )
			continue;
		if( reinterpret_cast<Player *>(player) != object->getControllingPlayer() )
			continue;
		if( !reinterpret_cast<Thing *>( object )->isKindOf( RVA00365DF0_KIND_127 ) )
			continue;
		if( (object->m_flags & 1) != 0 )
			continue;

		Int index = object->m_livingWorldIndex;
		if( index == -1 )
			index = reinterpret_cast<Rva00364B10LivingWorldPlayerArmyCollection *>( self )
				->scanArmyGroups( reinterpret_cast<Rva00364B10Summary *>( object ), false );
		if( index < 0 )
			continue;

		if( (unsigned int)index > self->m_playerArmies.size() - 1 )
			continue;

		object->fill( &record );
		++record.m_field3C;
		record.m_field34 = 1;
		BfmeLivingWorldPlayerArmyCollection::ArmySlot *begin = self->m_playerArmies.begin();
		Gen00365520 *army = reinterpret_cast<Gen00365520 *>(
			reinterpret_cast<char *>( begin ) + index * 0x58 );
		army->bfmeAppend( reinterpret_cast<const P6Elem00365520 *>(&record) );
		record.reset();
	}

	player->m_field684.update( self );
	Real floored = (Real)floor( (double)player->m_field25C );
	Int whole = bfmeFloatToLong( floored );
	RVA00365DF0_LIVING_WORLD_LOGIC->assign74( whole );
	RVA00365DF0_LIVING_WORLD_LOGIC->assignA0( player->m_field264 );
	reinterpret_cast<Rva003C2720Owner *>(RVA00365DF0_LIVING_WORLD_LOGIC)->copy( (RVA00365DF0_LIVING_WORLD_LOGIC->assignA4(player->m_field260), &player->m_sciences) );
	UpgradeMaskType mask = player->m_upgradesCompleted;
	reinterpret_cast<Rva003C1050 *>( RVA00365DF0_LIVING_WORLD_LOGIC )->setMask( mask );
}
