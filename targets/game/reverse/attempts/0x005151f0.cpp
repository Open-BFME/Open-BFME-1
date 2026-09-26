// ?d_005151f0@@YAXXZ
// partial score=0.978 date=2026-09-18
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// The two in-game chat friend buttons, retail 0x00514DA0 (609 bytes) and
// 0x005151F0 (609 bytes). The constructor at 0x005160E0 pushes the selector
// string "AptInGameChat::OnBttnRemoveFriend" and "AptInGameChat::OnBttnAddFriend"
// and loads each body's ILT thunk a few bytes later, which is what names them.
//
// Both buttons run the same code. They read the selected rows out of the
// friends list at +0x264, fetch a confirmation title and message from
// GameText, and hand the pair to the dialog helper at 0x00522D20 with two
// callbacks. Only the three GameText labels and the second callback differ,
// and the two retail typos in the remove labels are real.

typedef bool Bool;
typedef int Int;
typedef unsigned short WideChar;


#include <vector>

extern "C" void _ReadWriteBarrier( void );
#pragma intrinsic( _ReadWriteBarrier )

class GameWindow;

extern const char g_bfmeEmptyUnicode[];

template <typename T>
class StringBase
{
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	~StringBase();

public:
	void set( const StringBase<T> &other );

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[ 1 ];
	};

	Header *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() {}

	void __cdecl format( UnicodeString fmt, ... );

	void set( const UnicodeString &other )
	{
		StringBase<unsigned short>::set( other );
	}

	const WideChar *str() const
	{
		return m_data ? &m_data->data[ 0 ]
		              : reinterpret_cast<const WideChar *>( g_bfmeEmptyUnicode );
	}
};

class GameTextInterface
{
public:
	virtual void bfmeSlot00GT();
	virtual void bfmeSlot01GT();
	virtual void bfmeSlot02GT();
	virtual void bfmeSlot03GT();
	virtual void bfmeSlot04GT();
	virtual void bfmeSlot05GT();
	virtual void bfmeSlot06GT();
	virtual void bfmeSlot07GT();
	virtual void bfmeSlot08GT();
	virtual void bfmeSlot09GT();
	virtual UnicodeString fetch( const char *label, bool *found );
};

extern GameTextInterface *TheGameText;

// Every source that names the in-game chat screen calls the class
// BfmeAptScreenInGameChat. The ledger spells the global pointer's type
// Rva005127A0InGameChat, so the pointee keeps that spelling and the two
// methods below take the screen under its real name.
class BfmeAptScreenInGameChat
{
public:
	void _bfme_onBttnRemoveFriend( const char *name );
	void _bfme_onBttnAddFriend( const char *name );

	// Retail 0x00513BF0, reached through ILT 0x00017373. It fills the
	// vector with the profile id of every selected row and returns how
	// many it wrote.
	Int rva00513BF0( GameWindow *list, void *selected, Int column, Bool refresh );

	// Retail 0x00512890, reached through ILT 0x0003DAF5. It turns one
	// GameSpy profile id into the buddy's display name.
	Int rva00512890( Int profileId, UnicodeString &name );

	unsigned char m_unmodelled000[ 0x264 ];
	// named by Code/GameEngine/Source/GameClient/GUI/BfmeAptScreenInGameChatInitGadgets.cpp
	GameWindow *m_friendsList;
};

// The ledger spells the global pointer's type Rva005127A0InGameChat, so the
// screen keeps that spelling where the pointer is declared.
class Rva005127A0InGameChat : public BfmeAptScreenInGameChat {};
extern Rva005127A0InGameChat *g_Rva005127A0InGameChat;

// The callback pair and the dialog call are the ones
// Code/GameEngine/Source/GameClient/GUI/OnlineShellHandleKey.cpp already
// byte-matches. 40584 routes to 0x005114F0, 2B878 to 0x00514D80, 28E25 to
// 0x00514D60, and 2E0B9 to the dialog body at 0x00522D20.
extern void j_00040584();
extern void j_0002b878();
extern void j_00028e25();
extern void j_0002e0b9();

struct FunctorSlot
{
	FunctorSlot( void ( *callback )() ) : m_callback( callback ) {}
	void ( *m_callback )();
};
class Open2Counted
{
public:
	Open2Counted() : m_refs( 0 ) {}
	virtual ~Open2Counted();
	int m_refs;
};
class Rva010FDFACFunctorSlotWrapper : public Open2Counted
{
public:
	Rva010FDFACFunctorSlotWrapper( const FunctorSlot &slot )
		: m_callback( slot.m_callback ) {}
	virtual ~Rva010FDFACFunctorSlotWrapper();
	virtual void invoke();
	void ( *m_callback )();
};

class Open2Handle
{
public:
	Open2Handle( const FunctorSlot &slot )
		: m_held( new Rva010FDFACFunctorSlotWrapper( slot ) )
	{
		if( m_held != 0 )
			++m_held->m_refs;
	}

	Open2Handle( const Open2Handle &other ) : m_held( other.m_held )
	{
		if( m_held != 0 )
			++m_held->m_refs;
	}

	~Open2Handle()
	{
		if( m_held != 0 && --m_held->m_refs <= 0 )
			delete m_held;
	}

	Open2Counted *m_held;
};

class Bfme5RefCounted
{
public:
	virtual ~Bfme5RefCounted();
	int m_refs;
};
class Bfme5RefPtr
{
public:
	Bfme5RefPtr( const Bfme5RefPtr &other ) : m_ptr( other.m_ptr )
	{
		if( m_ptr ) ++m_ptr->m_refs;
	}
	Bfme5RefCounted *m_ptr;
};
struct Bfme5RefPairVal
{
	Bfme5RefPtr m_a;
	Bfme5RefPtr m_b;
	~Bfme5RefPairVal();
};
class Rva004C5C30 : public Bfme5RefPairVal
{
public:
	Rva004C5C30( Open2Handle first, Open2Handle second );
};
class Rva004C6370
{
public:
	Rva004C6370( Bfme5RefPairVal s );
	Rva004C6370( const Rva004C6370 &other ) throw() : m_bfmeNode( other.m_bfmeNode )
	{
		if( m_bfmeNode ) ++( (Open2Counted *)m_bfmeNode )->m_refs;
	}
	~Rva004C6370();
	void *m_bfmeNode;
};

// @?_bfme_onBttnRemoveFriend@BfmeAptScreenInGameChat@@QAEXPBD@Z 0x00514DA0
void BfmeAptScreenInGameChat::_bfme_onBttnRemoveFriend( const char *name )
{
	(void)name;

	if( g_Rva005127A0InGameChat == 0 )
		return;

	std::vector<Int> selected;
	Int count = g_Rva005127A0InGameChat->rva00513BF0(
		g_Rva005127A0InGameChat->m_friendsList, &selected, 7, true );
	Int *ids = selected.begin();
	_ReadWriteBarrier();
	if( count > 0 )
	{
		UnicodeString title = TheGameText->fetch( "APT:RemoveFirendTitle", 0 );
		UnicodeString message;

		if( count == 1 )
		{
			UnicodeString fmt =
				TheGameText->fetch( "APT:RemovieFriendMessage", 0 );
			Int id = ids[ 0 ];
			UnicodeString buddy;
			g_Rva005127A0InGameChat->rva00512890( id, buddy );
			message.format( fmt, buddy.str() );
		}
		else
		{
			message.set( TheGameText->fetch( "APT:RemovieFriendMessageMulti", 0 ) );
		}

		( (void( __cdecl * )( int, const UnicodeString &, const UnicodeString &,
			Rva004C6370 ))j_0002e0b9 )(
			2, title, message, Rva004C5C30(
				FunctorSlot( j_0002b878 ),
				FunctorSlot( j_00040584 ) ) );
	}
}

// @?_bfme_onBttnAddFriend@BfmeAptScreenInGameChat@@QAEXPBD@Z 0x005151F0
void BfmeAptScreenInGameChat::_bfme_onBttnAddFriend( const char *name )
{
	(void)name;

	if( g_Rva005127A0InGameChat == 0 )
		return;

	std::vector<Int> selected;
	Int count = g_Rva005127A0InGameChat->rva00513BF0(
		g_Rva005127A0InGameChat->m_friendsList, &selected, 7, true );
	Int *ids = selected.begin();
	_ReadWriteBarrier();
	if( count > 0 )
	{
		UnicodeString title = TheGameText->fetch( "APT:AcceptRequestTitle", 0 );
		UnicodeString message;

		if( count == 1 )
		{
			UnicodeString fmt =
				TheGameText->fetch( "APT:AcceptRequestMessage", 0 );
			Int id = ids[ 0 ];
			UnicodeString buddy;
			g_Rva005127A0InGameChat->rva00512890( id, buddy );
			message.format( fmt, buddy.str() );
		}
		else
		{
			message.set( TheGameText->fetch( "APT:AcceptRequestMessageMulti", 0 ) );
		}

		( (void( __cdecl * )( int, const UnicodeString &, const UnicodeString &,
			Rva004C6370 ))j_0002e0b9 )(
			2, title, message, Rva004C5C30(
				FunctorSlot( j_00028e25 ),
				FunctorSlot( j_00040584 ) ) );
	}
}
