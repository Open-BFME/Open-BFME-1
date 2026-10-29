// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Include
// stlport
// Visible helper bodies preserve the call setup and vector lifetime.
#include "GameClient/BfmeAptScreenBaseLayout.h"
typedef bool Bool;
typedef int Int;
typedef unsigned short WideChar;

#include <vector>

#include "ascii_string.h"

extern char g_bfmeBufferAN[];

void bfmeAssembleAN(int a, char *buffer, const char *text, int p3, int p4, int p5,
		int p6, int p7, int p8);

class BfmeLevelAN
{
public:
	char *bfmeBuildAN(unsigned int level, int p2, int p3, int p4, int p5, int p6,
			int p7, int p8);

	char m_bfmePadAN[0x1c4];
	char m_bfmeBuiltAN;
};

// ?bfmeBuildAN@BfmeLevelAN@@QAEPADIHHHHHHH@Z
inline __declspec(noinline) char *BfmeLevelAN::bfmeBuildAN(unsigned int level, int p2, int p3, int p4, int p5,
		int p6, int p7, int p8)
{
	g_bfmeBufferAN[0] = 0;

	if (level < 12)
	{
		AsciiString suffix;

		suffix.format(AsciiString("/_level%d"), level);

		bfmeAssembleAN(p2, g_bfmeBufferAN, suffix.str(), p3, p4, p5, p6, p7, p8);

		m_bfmeBuiltAN = 1;
	}

	return g_bfmeBufferAN;
}


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

class __multiple_inheritance AptInGameChat
	: public _bfme_AptGameWindow
{
public:
	void OnBttnAddFriend(const char *name);
	void OnBttnRemoveFriend(const char *name);
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

// ?rva00513BF0@AptInGameChat@@QAEHPAVGameWindow@@PAXH_N@Z
inline __declspec(noinline) Int AptInGameChat::rva00513BF0( GameWindow *list, void *selected, Int buddyMask, Bool skipStatusFilter )
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


class GameWindow;
typedef AptInGameChat BfmeAptScreenInGameChat;
void __cdecl operator delete(void *);


typedef std::vector<int> Rva00514560IntVector;

struct Rva00579160Manager
{
    // ?fire@Rva00579160Manager@@QAEPAXIPBDHHHHHH@Z absent-from-retail
    void *fire(unsigned target, const char *name, int a, int b, int c, int d, int e, int f)
    {
        return ((BfmeLevelAN *)this)->bfmeBuildAN(target, (int)name, a, b, c, d, e, f);
    }
};
// Retail 0x012F19E8 is ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A (data_rows.csv,
// GUI/WindowManager.cpp); Rva00579160TheManager was only a pin.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;
#define Rva00579160TheManager ( *(Rva00579160Manager **)&g_rva012F19E8WindowManager )

class GameSpyInfo
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
    virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
    virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
    virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
    virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
    virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
    virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
    virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
    virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
    virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
    virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
    virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
    virtual void bfmeSlot72(int value);
};
extern GameSpyInfo *TheGameSpyInfo;

// Complete 285-byte acceptance helper at 0x004EF980 (ILT 0x0001E73B).
void Rva004EF980AcceptBuddyRequest(Int profileID);

class Glo00EF4988
{
public:
    void h00514560();
    void h005143D0();

private:
    unsigned char m_unmodelled000[0x250];
    unsigned m_target;
    unsigned char m_unmodelled254[0x264 - 0x254];
    GameWindow *m_window;
    unsigned char m_unmodelled268[0x292 - 0x268];
    bool m_addDirty;
    bool m_addEnabled;
    bool m_removeDirty;
    bool m_removeEnabled;
};

// ?h00514560@Glo00EF4988@@QAEXXZ
void Glo00EF4988::h00514560()
{
    int *begin;
    Rva00514560IntVector values;

    if (m_addDirty || m_addEnabled) {
        m_addDirty = false;
        m_addEnabled = false;
        Rva00579160TheManager->fire(m_target, "DisableAddButton", 0, 0, 0, 0, 0, 0);
    }

    if (m_removeDirty || m_removeEnabled) {
        m_removeDirty = false;
        m_removeEnabled = false;
        Rva00579160TheManager->fire(m_target, "DisableRemoveButton", 0, 0, 0, 0, 0, 0);
    }

    if (((BfmeAptScreenInGameChat *)this)->rva00513BF0(m_window, &values, 7, true) > 0) {
        begin = values.begin();
        int *end = values.end();
        int *it = begin;
        if (it != end) {
            do {
                TheGameSpyInfo->bfmeSlot72(*it);
                ++it;
            } while (it != end);
        }
    }
}

// Sibling of h00514560: same flag/button reset and selected-friend walk, but
// each selected profile goes to the buddy-request acceptance helper. Reached
// from the guarded tail-jump at 0x00514D60 (OnBttnAddFriend's accept callback,
// ILT 0x00028E25). Passing m_window straight into the helper call (no local
// copy) gives retail's ECX/EAX roles for the list and the vector address.
// ?h005143D0@Glo00EF4988@@QAEXXZ
void Glo00EF4988::h005143D0()
{
    Rva00514560IntVector values;

    if (m_addDirty || m_addEnabled) {
        m_addDirty = false;
        m_addEnabled = false;
        Rva00579160TheManager->fire(m_target, "DisableAddButton", 0, 0, 0, 0, 0, 0);
    }

    if (m_removeDirty || m_removeEnabled) {
        m_removeDirty = false;
        m_removeEnabled = false;
        Rva00579160TheManager->fire(m_target, "DisableRemoveButton", 0, 0, 0, 0, 0, 0);
    }

    if (((BfmeAptScreenInGameChat *)this)->rva00513BF0(m_window, &values, 7, true) > 0) {
        int *it = values.begin();
        int *end = values.end();
        if (it != end) {
            do {
                Rva004EF980AcceptBuddyRequest(*it);
                ++it;
            } while (it != end);
        }
    }
}
