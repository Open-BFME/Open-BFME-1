// ?d_00365df0@@YAXXZ
// partial score=0.82 date=2026-09-17
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00365DF0 (498 B).  The owning class is not named by the retail
// symbols; this TU keeps the proven Living World layouts and uses an
// address-qualified owner/method name.

typedef int Int;
typedef float Real;
typedef bool Bool;

extern "C" __declspec(dllimport) double __cdecl floor( double value );

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
typedef Rva00365DF0Player Player;
class BfmeLivingWorldPlayerArmyCollection;

class GameLogic
{
public:
	Bool _bfme_isInLivingWorldCampaign( void );
};

#pragma comment( linker, "/alternatename:?_bfme_isInLivingWorldCampaign@GameLogic@@QAE_NXZ=?j_0001d1c9@@YAXXZ" )

class Rva00365DF0PlayerList
{
private:
	char m_unmodelled00[ 0x0C ];

public:
	Player *m_firstPlayer;
};

#define RVA00365DF0_GAME_LOGIC (*(GameLogic **)0x012F0898)
#define RVA00365DF0_PLAYER_LIST (*(Rva00365DF0PlayerList **)0x012ED748)

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
	virtual void fill( void *record );

	char m_unmodelled04[ 0x84 ];
	Object *m_next;
	char m_unmodelled8C[ 0x2B8 ];
	unsigned char m_flags;
	char m_unmodelled345[ 0x2B ];
	Int m_livingWorldIndex;
};

#pragma comment( linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ" )

class Thing
{
public:
	Bool isKindOf( KindOfType kind ) const;
};

#pragma comment( linker, "/alternatename:?isKindOf@Thing@@QBE_NW4KindOfType@@@Z=?j_0003251f@@YAXXZ" )

class Rva00365DF0Record
{
public:
	Rva00365DF0Record();
	~Rva00365DF0Record();
	void reset();

	char m_body00[ 0x34 ];
	Int m_field34;
	char m_body38[ 0x04 ];
	Int m_field3C;
	char m_body40[ 0x74 ];
};

#pragma comment( linker, "/alternatename:??0Rva00365DF0Record@@QAE@XZ=?j_0000b30c@@YAXXZ" )
#pragma comment( linker, "/alternatename:??1Rva00365DF0Record@@QAE@XZ=?j_000257ed@@YAXXZ" )
#pragma comment( linker, "/alternatename:?reset@Rva00365DF0Record@@QAEXXZ=?j_00022e99@@YAXXZ" )

class Rva00364B10Summary
{
};

class Rva00364B10LivingWorldPlayerArmyCollection
{
public:
	Int scanArmyGroups( Rva00364B10Summary *summary, Bool copySummary );
};

#pragma comment( linker, "/alternatename:?scanArmyGroups@Rva00364B10LivingWorldPlayerArmyCollection@@QAEHPAVRva00364B10Summary@@_N@Z=?j_0002fdc4@@YAXXZ" )

class Gen00365520
{
public:
	void bfmeAppend( const Rva00365DF0Record *record );
};

#pragma comment( linker, "/alternatename:?bfmeAppend@Gen00365520@@QAEXPBVRva00365DF0Record@@@Z=?j_0000c405@@YAXXZ" )

class BfmeLivingWorldPlayerArmyCollection
{
public:
	void clearModeFourArmies();
	static void __fastcall rva00365df0(
		BfmeLivingWorldPlayerArmyCollection *self, void *unused,
		Object *firstObject );

	struct ArmySlot
	{
		char m_body[ 0x58 ];
	};
	struct ArmyVector
	{
		ArmySlot *m_begin;
		ArmySlot *m_end;
		ArmySlot *m_capacity;
	};

	char m_unmodelled00[ 0x18 ];
	ArmyVector m_playerArmies;
};

#pragma comment( linker, "/alternatename:?clearModeFourArmies@BfmeLivingWorldPlayerArmyCollection@@QAEXXZ=?j_00002dba@@YAXXZ" )

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

#pragma comment( linker, "/alternatename:?setMask@Rva003C1050@@QAEXUUpgradeMaskType@@@Z=?j_000275a7@@YAXXZ" )

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type, class Allocator = allocator<Type> >
class vector
{
public:
	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};
}

enum ScienceType
{
	Rva003C2720ScienceTypeValue = 0
};

class Rva003C2720Owner
{
public:
	void copy( const _STL::vector<ScienceType> *source );
};

#pragma comment( linker, "/alternatename:?copy@Rva003C2720Owner@@QAEXPBV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@Z=?j_0001c440@@YAXXZ" )

class Rva000F99C0Owner
{
public:
	void update( BfmeLivingWorldPlayerArmyCollection *owner );

	void *m_begin;
	void *m_end;
	void *m_capacity;
};

#pragma comment( linker, "/alternatename:?update@Rva000F99C0Owner@@QAEXPAVBfmeLivingWorldPlayerArmyCollection@@@Z=?j_00020fef@@YAXXZ" )

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
};

#define RVA00365DF0_LIVING_WORLD_LOGIC (*(Rva00365DF0Logic **)0x012F1028)

void __fastcall BfmeLivingWorldPlayerArmyCollection::rva00365df0(
	BfmeLivingWorldPlayerArmyCollection *self, void *unused,
	Object *firstObject )
{
	Rva00365DF0Player *player;
	(void)unused;

	if( !RVA00365DF0_GAME_LOGIC->_bfme_isInLivingWorldCampaign() )
		return;
	if( firstObject == 0 )
		return;

	self->clearModeFourArmies();
	player = RVA00365DF0_PLAYER_LIST->m_firstPlayer;
	if( player == 0 )
		return;

	Rva00365DF0Record record;
	for( Object *object = firstObject; object != 0; object = object->m_next )
	{
		if( object->getControllingPlayer() != player )
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

		BfmeLivingWorldPlayerArmyCollection::ArmySlot *begin = self->m_playerArmies.m_begin;
		BfmeLivingWorldPlayerArmyCollection::ArmySlot *end = self->m_playerArmies.m_end;
		if( (unsigned int)index > (unsigned int)(end - begin) - 1 )
			continue;

		object->fill( &record );
		Gen00365520 *army = reinterpret_cast<Gen00365520 *>(
			reinterpret_cast<char *>( begin ) + index * 0x58 );
		++record.m_field3C;
		record.m_field34 = 1;
		army->bfmeAppend( &record );
		record.reset();
	}

	player->m_field684.update( self );
	Real floored = (Real)floor( (double)player->m_field25C );
	Int whole = bfmeFloatToLong( floored );
	RVA00365DF0_LIVING_WORLD_LOGIC->m_field74 = whole;
	RVA00365DF0_LIVING_WORLD_LOGIC->m_fieldA0 = player->m_field264;
	RVA00365DF0_LIVING_WORLD_LOGIC->m_fieldA4 = player->m_field260;
	reinterpret_cast<Rva003C2720Owner *>( RVA00365DF0_LIVING_WORLD_LOGIC )->copy(
		&player->m_sciences );
	UpgradeMaskType mask = player->m_upgradesCompleted;
	reinterpret_cast<Rva003C1050 *>( RVA00365DF0_LIVING_WORLD_LOGIC )->setMask( mask );
}
