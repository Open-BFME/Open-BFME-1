// cl: /DNDEBUG /MD /EHsc
// stlport
//
// BfmeAptScreenInGameChat::rva00513BF0, retail 0x00513BF0, 511 bytes: collects the profile ids of the
// selected friends-list rows, filtered by internet player status and by the buddy-lookup result mask.
// The friend-button callers at 0x00514DA0 and 0x005151F0 reach it through the pinned ILT 0x00017373.

#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned short WideChar;

class GameWindow;

template <typename T>
class StringBase
{
	friend class UnicodeString;

	public:
	StringBase() : m_data( 0 ) {}
	~StringBase() { releaseBuffer(); }

	private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[ 1 ];
	};

	Header *m_data;
	void releaseBuffer();
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
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

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

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
	unsigned char m_unmodelled[0x214];
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
		Player *localPlayer = Rva002EE330ThePlayers->m_local;
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
