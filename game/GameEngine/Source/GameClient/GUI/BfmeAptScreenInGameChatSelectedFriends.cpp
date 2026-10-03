// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Include
// stlport
// Keep the selection helper visible to its friend-button caller: VC7.1 then
// retains the vector start through cleanup, as retail does.
#include "GameClient/BfmeAptScreenBaseLayout.h"
typedef bool Bool;
typedef int Int;
typedef unsigned short WideChar;

#include <vector>

class GameWindow;

#include "unicode_string.h"
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::UnicodeString(const UnicodeString &other)
{
 ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&other);
}
inline UnicodeString::~UnicodeString()
{
 ((StringBase<unsigned short> *)this)->releaseBuffer();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &other)
{
 ((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&other);
 return *this;
}

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

// Retain the owner layout already verified by the selection helper and
// the matched constructor at RVA 0x005160E0.
class BfmeAptScreenBase
{
public:
	virtual ~BfmeAptScreenBase();
	virtual int aptSlot1(unsigned int, unsigned int, unsigned int);
	virtual int aptSlot2(unsigned int, unsigned int, unsigned int);
	virtual int aptSlot3(unsigned int);
	virtual int aptSlot4(unsigned int, unsigned int);
	virtual int aptSlot5();
	virtual int aptSlot6();
	virtual void *aptSlot7();
	virtual int aptSlot8();
	virtual int aptSlot9();
	virtual bool aptSlot10();
	virtual bool aptSlot11();
	virtual void aptSlot12();
	virtual void aptSlot13();
private:
	BfmeAptScreenBaseLayout<> m_primaryStorage;
};

class S4Owner
{
public:
	virtual ~S4Owner();
private:
	unsigned char m_unmodelled[0x30];
};

class _bfme_AptGameWindow : public BfmeAptScreenBase, public S4Owner
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();
private:
	unsigned char m_tail[0xc];
};

class __multiple_inheritance BfmeAptScreenInGameChat
	: public _bfme_AptGameWindow
{
public:
	void OnBttnAddFriend(const char *name);
	void _bfme_onBttnRemoveFriend(const char *name);
	Int rva00513BF0( GameWindow *list, void *selected, Int buddyMask, Bool skipStatusFilter );
	Int _bfme_getInternetPlayerStatus( const UnicodeString &name );
	Int rva00512890( Int profileID, UnicodeString &result );

private:
	int m_field258;
	unsigned char m_padding25c[ 4 ];
	int m_field260;
	GameWindow *m_friendsList;
	int m_field268;
	unsigned char m_padding26c[ 4 ];
	unsigned char m_tail[ 0x34 ];
};

Int GadgetListBoxGetNumEntries( GameWindow *listbox );
void GadgetListBoxGetSelected( GameWindow *listbox, Int *selectList );
UnicodeString GadgetListBoxGetText( GameWindow *listbox, Int row, Int column );
void *GadgetListBoxGetItemData( GameWindow *listbox, Int row, Int column );

class Player
{
public:
	UnicodeString getPlayerDisplayName();
};

struct Rva002EE330PlayerList
{
	unsigned char m_unmodelled000[ 0xc ];
	Player *m_local;
};

class PlayerList;
extern PlayerList *ThePlayerList;	// retail [0x012ED748]

// The same object as ThePlayerList; this body reads it through this view.
static inline Rva002EE330PlayerList *rva002EE330ThePlayers( void )
{
	return (Rva002EE330PlayerList *)ThePlayerList;
}

// List-box text column read from .rdata at VA 0x01106F04 (value 2).
extern const Int Rva01106F04;

// ?rva00513BF0@BfmeAptScreenInGameChat@@QAEHPAVGameWindow@@PAXH_N@Z
Int BfmeAptScreenInGameChat::rva00513BF0( GameWindow *list, void *selected, Int buddyMask, Bool skipStatusFilter )
{
	std::vector<Int> *profileIDs = (std::vector<Int> *)selected;
	Int entries = GadgetListBoxGetNumEntries( list );
	profileIDs->erase( profileIDs->begin(), profileIDs->end() );

	Int index = 0;
	Int localStatus = 0;
	if ( !skipStatusFilter )
	{
		Player *localPlayer = rva002EE330ThePlayers()->m_local;
		if ( localPlayer != 0 )
			localStatus = _bfme_getInternetPlayerStatus( localPlayer->getPlayerDisplayName() );
	}
	if ( entries != 0 )
	{
		Int *selectedRows = 0;
		GadgetListBoxGetSelected( list, (Int *)&selectedRows );

		for ( index = 0; index < entries; ++index )
		{
			if ( selectedRows[ index ] < 0 )
				break;

			Bool keep = true;
			if ( localStatus != 0 )
			{
				UnicodeString rowName = GadgetListBoxGetText( m_friendsList, selectedRows[ index ], Rva01106F04 );
				Int rowStatus = _bfme_getInternetPlayerStatus( rowName );
				if ( ( rowStatus == 2 ) ^ ( localStatus == 2 ) )
					keep = false;
			}

			if ( keep )
			{
				Int profileID = (Int)GadgetListBoxGetItemData( m_friendsList, selectedRows[ index ], 0 );
				UnicodeString buddyName;
				if ( buddyMask == 0 || ( buddyMask & rva00512890( profileID, buddyName ) ) )
					profileIDs->push_back( profileID );
			}
		}
	}

	return (Int)profileIDs->size();
}

// The ledger spells the global pointer's type Rva005127A0InGameChat, so the
// screen keeps that spelling where the pointer is declared.
class Rva005127A0InGameChat : public BfmeAptScreenInGameChat {};
extern Rva005127A0InGameChat *g_Rva005127A0InGameChat;

// The callback pair and the dialog call are the ones
// GameEngine/Source/GameClient/GUI/OnlineShellHandleKey.cpp already
// byte-matches. 40584 routes to 0x005114F0, 28E25 to 0x00514D60,
// and 2E0B9 to the dialog body at 0x00522D20.
extern void j_00040584();
extern void j_00028e25();
extern void j_0002b878();
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

// The constructor pairs AptInGameChat::OnBttnAddFriend with ILT 0x0001CE63.
// Retail RET4 at RVA 0x0051544E ends this 609-byte callback.
// @?OnBttnAddFriend@BfmeAptScreenInGameChat@@QAEXPBD@Z 0x005151F0
void BfmeAptScreenInGameChat::OnBttnAddFriend( const char *name )
{
	(void)name;

	if( g_Rva005127A0InGameChat == 0 )
		return;

	std::vector<Int> selected;
	Int count = g_Rva005127A0InGameChat->rva00513BF0(
		g_Rva005127A0InGameChat->m_friendsList, &selected, 7, true );
	Int *ids = selected.begin();
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
			message = TheGameText->fetch( "APT:AcceptRequestMessageMulti", 0 );
		}

		( (void( __cdecl * )( int, const UnicodeString &, const UnicodeString &,
			Rva004C6370 ))j_0002e0b9 )(
			2, title, message, Rva004C5C30(
				FunctorSlot( j_00028e25 ),
				FunctorSlot( j_00040584 ) ) );
	}
}

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
			message = ( TheGameText->fetch( "APT:RemovieFriendMessageMulti", 0 ) );
		}

		( (void( __cdecl * )( int, const UnicodeString &, const UnicodeString &,
			Rva004C6370 ))j_0002e0b9 )(
			2, title, message, Rva004C5C30(
				FunctorSlot( j_0002b878 ),
				FunctorSlot( j_00040584 ) ) );
	}
}
