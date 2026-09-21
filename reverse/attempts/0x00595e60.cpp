// ?rva00595e60@AptPalantirHeroSelector@@QAEXXZ
// partial score=0.24 date=2026-09-18
// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail RVA 0x00595E60, 1350 bytes.  The constructor at 0x00595AC0 and the
// direct call to 0x00595D40 establish AptPalantirHeroSelector as the owner.
// The method itself has no recovered semantic name, so the address remains in
// the method name.  The list, slot, object-table and UI fields below are only
// the layouts witnessed by this body and its constructor.

#include <math.h>

typedef unsigned char Byte;
typedef unsigned short WideChar;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

template <typename T> class Rva00595E60StringBase
{
protected:
	struct Header
	{
		int references;
		unsigned short length;
		unsigned short capacity;
		T text[ 1 ];
	};

	Rva00595E60StringBase() : m_data( 0 ) {}
	Rva00595E60StringBase( const T *text );
	void releaseBuffer();

	Header *m_data;
};

// These two one-word views deliberately preserve the separate retail
// spellings.  The object is constructed as BFMERetailAsciiString and the
// formatting entry point is the independently named AsciiString body.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data( 0 ) {}
	BFMERetailAsciiString( const char *text );
	~BFMERetailAsciiString() { releaseBuffer(); }

	void releaseBuffer();

	void *m_data;
};

class AsciiString
{
public:
	void __cdecl format( AsciiString format, ... );

	void *m_data;
};

class UnicodeString : private Rva00595E60StringBase<WideChar>
{
public:
	UnicodeString() : Rva00595E60StringBase<WideChar>() {}
	UnicodeString( const WideChar *text )
		: Rva00595E60StringBase<WideChar>( text ) {}
	~UnicodeString()
	{
		Rva00595E60StringBase<WideChar>::releaseBuffer();
	}

	void __cdecl format( UnicodeString format, ... );
};

class __single_inheritance FunctorTargetSingle
{
};

struct Rva00595E60HeroEntry
{
	UnsignedInt objectID;
	int rank;
	int remaining;
};

struct Rva00595E60HeroNode
{
	Rva00595E60HeroNode *next;
	Rva00595E60HeroNode *previous;
	Rva00595E60HeroEntry value;
};

struct Rva00595E60HeroSlot
{
	int words[ 5 ];
	Byte active;
	Byte ready;
	Byte padding[ 2 ];
};

struct Rva00595E60ObjectBucket
{
	Rva00595E60ObjectBucket *next;
	UnsignedInt objectID;
	void *object;
};

struct Rva00595E60ObjectTable
{
	Byte padding[ 0xb4 ];
	Rva00595E60ObjectBucket **buckets;
	Rva00595E60ObjectBucket **bucketEnd;
};

class AptPalantirHeroSelector : public FunctorTargetSingle
{
public:
	void rva00595e60();

private:
	Byte m_active;
	Byte m_padding_001[ 3 ];
	Rva00595E60HeroNode *m_heroes;
	Rva00595E60HeroSlot m_slots[ 17 ];
	Byte m_selectAll;
	Byte m_padding_1a1[ 3 ];
	void *m_window;
};

extern void j_00018dcc();
extern void j_0000b35c();
extern void j_0001f253();
extern void j_00020824();
extern void j_00013877();
extern void j_0001d85e();
extern void j_000022bb();
extern void j_00004246();
extern void j_0000c117();
extern void j_0001681a();
extern void j_0000bdca();
extern void j_00047b31();
extern void j_00028c45();
extern void j_0002ae8c();
extern void j_00038e5b();
extern void j_0002fb3a();
extern void j_0003de65();
extern void j_0002b38c();
extern void j_00010d39();
extern void j_00027895();
extern void j_0004a1fb();
extern void j_00027f2a();
extern void j_00032be6();
extern void d_0058b610();

extern "C" __declspec( dllimport ) double BfmeFloorER( double value );

extern Real g_bfmeScaleBC;
extern const Real g_bfmeK1253;

#define RVA00595E60_GAME_LOGIC (*(void **)0x012F0898)
#define RVA00595E60_WINDOW_MANAGER (*(void **)0x012F19E8)
#define RVA00595E60_TRANSITION (*(void **)0x012F4C7C)

struct Rva00595E60SelectorCall
{
	typedef void (Rva00595E60SelectorCall::*Call)();
};

static void rva00595e60SelectorCall( AptPalantirHeroSelector *self,
	void (*address)() )
{
	union
	{
		void (*raw)();
		Rva00595E60SelectorCall::Call member;
	} route;
	route.raw = address;
	(reinterpret_cast<Rva00595E60SelectorCall *>( self )->*route.member)();
}

struct Rva00595E60FindObjectCall
{
	typedef void *(Rva00595E60FindObjectCall::*Call)( int );
};

static void *rva00595e60FindObject( void *gameLogic, UnsignedInt objectID )
{
	union
	{
		void (*raw)();
		Rva00595E60FindObjectCall::Call member;
	} route;
	route.raw = j_0001f253;
	return (reinterpret_cast<Rva00595E60FindObjectCall *>( gameLogic )
		->*route.member)( (int)objectID );
}

struct Rva00595E60ObjectNoArgCall
{
	typedef void *(Rva00595E60ObjectNoArgCall::*Call)();
};

static void *rva00595e60ControllingPlayer( void *object )
{
	union
	{
		void (*raw)();
		Rva00595E60ObjectNoArgCall::Call member;
	} route;
	route.raw = j_00020824;
	return (reinterpret_cast<Rva00595E60ObjectNoArgCall *>( object )
		->*route.member)();
}

struct Rva00595E60IsLocalCall
{
	typedef Bool (Rva00595E60IsLocalCall::*Call)();
};

static Bool rva00595e60IsLocal( void *player )
{
	union
	{
		void (*raw)();
		Rva00595E60IsLocalCall::Call member;
	} route;
	route.raw = j_00013877;
	return (reinterpret_cast<Rva00595E60IsLocalCall *>( player )
		->*route.member)();
}

struct Rva00595E60HeroNoArgCall
{
	typedef void *(Rva00595E60HeroNoArgCall::*Call)();
};

static void *rva00595e60HeroUI( void *header )
{
	union
	{
		void (*raw)();
		Rva00595E60HeroNoArgCall::Call member;
	} route;
	route.raw = j_000022bb;
	return (reinterpret_cast<Rva00595E60HeroNoArgCall *>( header )
		->*route.member)();
}

struct Rva00595E60WindowCall
{
	typedef void (Rva00595E60WindowCall::*BindCall)( const AsciiString &, void * );
	typedef void (Rva00595E60WindowCall::*SetCall)( UnicodeString &, AsciiString & );
	typedef void (Rva00595E60WindowCall::*AsciiCall)( AsciiString & );
	typedef void (Rva00595E60WindowCall::*IntCall)( int );
};

static void rva00595e60BindHeroUI( void *manager, AsciiString &name,
	void *value )
{
	union
	{
		void (*raw)();
		Rva00595E60WindowCall::BindCall member;
	} route;
	route.raw = j_0001681a;
	(reinterpret_cast<Rva00595E60WindowCall *>( manager )->*route.member)(
		name, value );
}

static void rva00595e60SetRank( void *manager, UnicodeString &value,
	AsciiString &name )
{
	union
	{
		void (*raw)();
		Rva00595E60WindowCall::SetCall member;
	} route;
	route.raw = j_0000bdca;
	(reinterpret_cast<Rva00595E60WindowCall *>( manager )->*route.member)(
		value, name );
}

static void rva00595e60ReleaseWindowText( void *manager, AsciiString &name )
{
	union
	{
		void (*raw)();
		Rva00595E60WindowCall::AsciiCall member;
	} route;
	route.raw = j_00047b31;
	(reinterpret_cast<Rva00595E60WindowCall *>( manager )->*route.member)(
		name );
}

static void rva00595e60WindowInt( void *window, int value, void (*address)() )
{
	union
	{
		void (*raw)();
		Rva00595E60WindowCall::IntCall member;
	} route;
	route.raw = address;
	(reinterpret_cast<Rva00595E60WindowCall *>( window )->*route.member)(
		value );
}

static void rva00595e60TwoInts( int first, int second, void (*address)() )
{
	typedef void (*Call)( int, int );
	((Call)address)( first, second );
}

static void rva00595e60HeroAndObject( void *first, void *second )
{
	typedef void (*Call)( void *, void * );
	((Call)j_0000c117)( first, second );
}

static void rva00595e60HeroIndex( int index, void (*address)() )
{
	typedef void (*Call)( int );
	((Call)address)( index );
}

static void rva00595e60Window( void *window, void (*address)() )
{
	typedef void (*Call)( void * );
	((Call)address)( window );
}

static void *rva00595e60FindBucket( UnsignedInt objectID )
{
	Rva00595E60ObjectTable *table =
		(Rva00595E60ObjectTable *)RVA00595E60_GAME_LOGIC;
	Rva00595E60ObjectBucket **begin = table->buckets;
	Rva00595E60ObjectBucket **end = table->bucketEnd;
	UnsignedInt bucketCount = (UnsignedInt)( end - begin );
	Rva00595E60ObjectBucket *bucket = begin[ objectID % bucketCount ];
	while( bucket != 0 && bucket->objectID != objectID )
		bucket = bucket->next;
	return bucket == 0 ? 0 : bucket->object;
}

static Real rva00595e60VirtualReal( void *object )
{
	// VC7.1 reserves __thiscall in a free-function pointer typedef.  This
	// one-receiver virtual slot has the same ECX/no-stack ABI as __fastcall.
	typedef Real (__fastcall *Call)( void * );
	void **vtable = *(void ***)object;
	return ((Call)vtable[ 5 ])( object );
}

static void *rva00595e60VirtualRecord( void *object )
{
	typedef void *(__fastcall *Call)( void * );
	void **vtable = *(void ***)object;
	return ((Call)vtable[ 10 ])( object );
}

// ?rva00595e60@AptPalantirHeroSelector@@QAEXXZ
void AptPalantirHeroSelector::rva00595e60()
{
	if( m_window == 0 )
	{
		rva00595e60SelectorCall( this, j_00018dcc );
		rva00595e60SelectorCall( this, j_0000b35c );
	}

	if( m_active == 0 )
	{
		Rva00595E60HeroNode *sentinel = m_heroes;
		Rva00595E60HeroNode *node = sentinel->next;
		while( node != sentinel )
		{
			void *object = rva00595e60FindObject( RVA00595E60_GAME_LOGIC,
				node->value.objectID );
			if( object != 0 && rva00595e60IsLocal(
				rva00595e60ControllingPlayer( object )) )
			{
				j_0001d85e();
				m_active = 1;
				break;
			}
			node = node->next;
		}
	}

	if( m_active != 0 )
	{
		Rva00595E60HeroNode *sentinel = m_heroes;
		Rva00595E60HeroNode *node = sentinel->next;
		int heroIndex = 0;
		Bool processed = false;

		while( node != sentinel )
		{
			void *object = rva00595e60FindBucket( node->value.objectID );
			if( object != 0 )
			{
				int current = 0;
				d_0058b610();
				if( node->value.rank > 0 )
				{
					current = node->value.rank;
					if( current > node->value.rank )
						current = node->value.rank;
				}
				node->value.rank = current;

				void *player = rva00595e60ControllingPlayer( object );
				if( player != 0 && rva00595e60IsLocal( player )
					&& heroIndex < 17 )
				{
					Rva00595E60HeroSlot *slot = &m_slots[ heroIndex ];
					if( slot->words[ 0 ] != (int)node )
					{
						rva00595e60HeroIndex( heroIndex, j_00028c45 );
						slot->words[ 0 ] = (int)node;
					}

					void *header = *(void **)((Byte *)object + 4);
					void *headerData = header == 0 ? 0
						: *(void **)((Byte *)header + 4);
					void *ui = headerData == 0 ? 0
						: rva00595e60HeroUI( headerData );
					void *newUI = ui == 0 ? 0 : rva00595e60HeroUI( ui );
					if( newUI != (void *)slot->words[ 1 ] )
					{
						if( slot->words[ 1 ] != 0 )
							rva00595e60TwoInts( heroIndex, 1, j_0002ae8c );
						if( newUI == 0 )
							rva00595e60TwoInts( heroIndex, 1, j_0002ae8c );
						else
						{
							BFMERetailAsciiString uiName;
							BFMERetailAsciiString uiFormat( "HeroSelectUI/Hero%d" );
							((AsciiString *)&uiName)->format(
								*(AsciiString *)&uiFormat, heroIndex + 1 );
							rva00595e60BindHeroUI( RVA00595E60_WINDOW_MANAGER,
								*(AsciiString *)&uiName, newUI );
						}
						slot->words[ 1 ] = (int)newUI;
					}

					BFMERetailAsciiString rankName;
					BFMERetailAsciiString rankFormat( "APT:PalantirHero%dRank" );
					((AsciiString *)&rankName)->format(
						*(AsciiString *)&rankFormat, heroIndex + 1 );
					UnicodeString rankValue;
					UnicodeString rankFormatWide( L"%d" );
					((UnicodeString *)&rankValue)->format( rankFormatWide,
						slot->words[ 2 ] );
					rva00595e60SetRank( RVA00595E60_WINDOW_MANAGER,
						rankValue, *(AsciiString *)&rankName );

					Real progress = *(Real *)((Byte *)object + 0x1f8);
					if( progress > 0.0f )
					{
						int percent = (int)BfmeFloorER( (double)(
							progress * g_bfmeScaleBC + g_bfmeK1253 ) );
						if( percent > 100 ) percent = 100;
						if( percent < 0 ) percent = 0;
						if( percent != slot->words[ 3 ] )
						{
							rva00595e60TwoInts( heroIndex, percent,
								j_0002fb3a );
							slot->words[ 3 ] = percent;
						}
					}

					void *record = rva00595e60VirtualRecord( object );
					if( record != 0 )
					{
						Byte selected = *(Byte *)((Byte *)record + 0x3ac);
						if( selected != slot->active )
						{
							rva00595e60TwoInts( heroIndex, selected,
								j_0003de65 );
							slot->active = selected;
						}
						Byte ready = *(int *)((Byte *)record + 0x10) > 0;
						if( ready != slot->ready )
						{
							rva00595e60TwoInts( heroIndex, ready,
								j_0002b38c );
							slot->ready = ready;
						}
					}

					if( rva00595e60IsLocal( player ) )
						rva00595e60HeroIndex( heroIndex, j_00004246 );
					++heroIndex;
					processed = true;
				}
			}

			if( node->value.remaining > 0 )
				--node->value.remaining;
			node = node->next;
		}

		for( int index = 0; index < 17; ++index )
		{
			Rva00595E60HeroSlot *slot = &m_slots[ index ];
			if( slot->words[ 0 ] != (int)sentinel )
			{
				rva00595e60HeroIndex( index, j_00028c45 );
				slot->words[ 0 ] = (int)sentinel;
			}
			if( slot->words[ 1 ] != 0 )
			{
				rva00595e60TwoInts( index, 0, j_0002ae8c );
				slot->words[ 1 ] = 0;
			}
			slot->words[ 2 ] = -1;
			slot->words[ 3 ] = -1;
			slot->words[ 4 ] = -1;
			if( slot->active )
				rva00595e60TwoInts( index, 0, j_0002b38c );
			slot->active = 0;
			slot->ready = 0;
		}

		if( processed )
			rva00595e60SelectorCall( this, j_00032be6 );
		return;
	}

	if( m_selectAll != 0 && m_window != 0 )
	{
		if( RVA00595E60_TRANSITION != 0 )
			rva00595e60Window( m_window, j_00027895 );
		rva00595e60WindowInt( m_window, 0, j_0004a1fb );
		rva00595e60WindowInt( m_window, 1, j_00027f2a );
		j_00010d39();
		m_selectAll = 0;
	}
}
