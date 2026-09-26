// ?Rva00515810@BfmeAptScreenInGameChat@@QAEXXZ
// partial score=0.95 date=2026-09-18
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
//
// BfmeAptScreenInGameChat::Rva00515810, retail 0x00515810, 1166 bytes.
// The InitGadgets caller and its ILT pin prove this member identity. The body
// preserves selected profile IDs, gathers buddy and request records, repaints
// the friends list, and restores the selected rows.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define __PLACEMENT_VEC_NEW_INLINE
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <algorithm>
#include <map>
#include <set>
#include <vector>

#include "StringInline.h"

typedef int Int;
typedef int GPProfile;
typedef int GPEnum;
typedef int Color;

class GameWindow
{
};

class BuddyInfo
{
public:
	~BuddyInfo();

	GPProfile m_id;
	AsciiString m_name;
	AsciiString m_email;
	AsciiString m_countryCode;
	GPEnum m_status;
	UnicodeString m_statusString;
	UnicodeString m_locationString;
};

class Gen_004E9FD0
{
public:
	Gen_004E9FD0( const Gen_004E9FD0 &other );
	~Gen_004E9FD0()
	{
		reinterpret_cast<BuddyInfo *>( this )->~BuddyInfo();
	}

	GPProfile m_id;
	AsciiString m_name;
	AsciiString m_email;
	AsciiString m_countryCode;
	GPEnum m_status;
	UnicodeString m_statusString;
	UnicodeString m_locationString;
};

typedef std::map<GPProfile, Gen_004E9FD0> BuddyInfoMap;

class GameSpyInfo
{
public:
#define GAMESPY_SLOT(n) virtual void slot##n() = 0
	GAMESPY_SLOT(00); GAMESPY_SLOT(01); GAMESPY_SLOT(02); GAMESPY_SLOT(03);
	GAMESPY_SLOT(04); GAMESPY_SLOT(05); GAMESPY_SLOT(06); GAMESPY_SLOT(07);
	GAMESPY_SLOT(08); GAMESPY_SLOT(09); GAMESPY_SLOT(10); GAMESPY_SLOT(11);
	GAMESPY_SLOT(12); GAMESPY_SLOT(13); GAMESPY_SLOT(14); GAMESPY_SLOT(15);
	GAMESPY_SLOT(16); GAMESPY_SLOT(17); GAMESPY_SLOT(18); GAMESPY_SLOT(19);
	GAMESPY_SLOT(20);
#undef GAMESPY_SLOT
	virtual BuddyInfoMap *getBuddyMap() = 0;
	virtual BuddyInfoMap *getBuddyRequestMap() = 0;
};

class GameWindowManager
{
public:
#define WINDOW_MANAGER_SLOT(n) virtual void slot##n() = 0
	WINDOW_MANAGER_SLOT(00); WINDOW_MANAGER_SLOT(01); WINDOW_MANAGER_SLOT(02);
	WINDOW_MANAGER_SLOT(03); WINDOW_MANAGER_SLOT(04); WINDOW_MANAGER_SLOT(05);
	WINDOW_MANAGER_SLOT(06); WINDOW_MANAGER_SLOT(07); WINDOW_MANAGER_SLOT(08);
	WINDOW_MANAGER_SLOT(09); WINDOW_MANAGER_SLOT(10); WINDOW_MANAGER_SLOT(11);
	WINDOW_MANAGER_SLOT(12); WINDOW_MANAGER_SLOT(13); WINDOW_MANAGER_SLOT(14);
	WINDOW_MANAGER_SLOT(15); WINDOW_MANAGER_SLOT(16); WINDOW_MANAGER_SLOT(17);
	WINDOW_MANAGER_SLOT(18); WINDOW_MANAGER_SLOT(19); WINDOW_MANAGER_SLOT(20);
	WINDOW_MANAGER_SLOT(21); WINDOW_MANAGER_SLOT(22); WINDOW_MANAGER_SLOT(23);
	WINDOW_MANAGER_SLOT(24); WINDOW_MANAGER_SLOT(25); WINDOW_MANAGER_SLOT(26);
	WINDOW_MANAGER_SLOT(27); WINDOW_MANAGER_SLOT(28); WINDOW_MANAGER_SLOT(29);
	WINDOW_MANAGER_SLOT(30); WINDOW_MANAGER_SLOT(31); WINDOW_MANAGER_SLOT(32);
	WINDOW_MANAGER_SLOT(33); WINDOW_MANAGER_SLOT(34); WINDOW_MANAGER_SLOT(35);
	WINDOW_MANAGER_SLOT(36); WINDOW_MANAGER_SLOT(37); WINDOW_MANAGER_SLOT(38);
	WINDOW_MANAGER_SLOT(39); WINDOW_MANAGER_SLOT(40); WINDOW_MANAGER_SLOT(41);
	WINDOW_MANAGER_SLOT(42); WINDOW_MANAGER_SLOT(43);
	virtual void winSetLoneWindow( GameWindow *window ) = 0;
#undef WINDOW_MANAGER_SLOT
};

extern GameSpyInfo *TheGameSpyInfo;
extern GameWindowManager *TheWindowManager;
extern Color GameSpyColor[];

struct Q4Sort005156D0
{
	bool m_state;
	bool operator()( Int first, Int second ) const;
};

extern void Rva00515780( Int *first, Int *last, Q4Sort005156D0 comparator );

struct Gen_t_00513940_m4pod
{
	Int value;
};

extern Int GadgetListBoxGetNumEntries( GameWindow *listbox );
extern void GadgetListBoxGetSelected( GameWindow *listbox, Int *selectList );
extern void *GadgetListBoxGetItemData( GameWindow *listbox, Int row, Int column );
extern Int GadgetListBoxGetTopVisibleEntry( GameWindow *listbox );
extern void GadgetListBoxReset( GameWindow *listbox );
extern void GadgetListBoxSetSelected( GameWindow *listbox, const Int *selectList,
	Int count );
extern void GadgetListBoxSetTopVisibleEntry( GameWindow *listbox, Int topEntry );

// The list renderer is an existing ILT body. Its address is proven by the
// friends-list call site, while its generated declaration carries no ABI.
extern Int Rva00515810AddEntry( GameWindow *listbox, Int profileID,
	void *record, Color color );
#pragma comment(linker, "/alternatename:?Rva00515810AddEntry@@YAHPAVGameWindow@@HPAXH@Z=?j_000208d3@@YAXXZ")

class BfmeAptScreenInGameChat
{
public:
	void Rva00515810();
	void updateButtons();

private:
	unsigned char m_unmodelled000[0x260];
	GameWindow *m_chatEntry;
	GameWindow *m_friendsList;
};

#pragma comment(linker, "/alternatename:?updateButtons@BfmeAptScreenInGameChat@@QAEXXZ=?j_00006f4b@@YAXXZ")

// ?Rva00512890@@YGHHAAVUnicodeString@@@Z
extern "C" int __stdcall Rva00512890( Int profileID, UnicodeString &result );

void BfmeAptScreenInGameChat::Rva00515810()
{
	if ( m_friendsList == 0 || TheGameSpyInfo == 0 )
		return;

	Int maxSelectedItems = GadgetListBoxGetNumEntries( m_friendsList );
	Int *selectedIndices;
	GadgetListBoxGetSelected( m_friendsList, (Int *)&selectedIndices );
	std::set<Int> selectedProfiles;
	Int numSelected = 0;
	for ( Int i = 0; i < maxSelectedItems; ++i )
	{
		if ( selectedIndices[i] < 0 )
			break;
		++numSelected;
		selectedProfiles.insert(
			(Int)GadgetListBoxGetItemData( m_friendsList, selectedIndices[i], 0 ) );
	}

	Int previousTopIndex;
	previousTopIndex = GadgetListBoxGetTopVisibleEntry( m_friendsList );
	GadgetListBoxReset( m_friendsList );
	std::vector<Gen_t_00513940_m4pod> records;
	BuddyInfoMap *buddies = TheGameSpyInfo->getBuddyMap();
	for ( BuddyInfoMap::iterator it = buddies->begin(); it != buddies->end(); ++it )
	{
		Gen_t_00513940_m4pod record = { (Int)&it->second };
		records.push_back( record );
	}

	BuddyInfoMap *requests = TheGameSpyInfo->getBuddyRequestMap();
	for ( BuddyInfoMap::iterator it = requests->begin(); it != requests->end(); ++it )
	{
		Gen_t_00513940_m4pod record = { (Int)&it->second };
		records.push_back( record );
	}

	Q4Sort005156D0 comparator = { false };
	Rva00515780( (Int *)records.begin(), (Int *)records.end(), comparator );
	std::vector<Int> indicesToSelect;

	for ( std::vector<Gen_t_00513940_m4pod>::iterator it = records.begin();
		it != records.end(); ++it )
	{
		unsigned char *record = (unsigned char *)it->value;
		Int profileID = *(Int *)record;
		UnicodeString displayName;
		Int state = Rva00512890( profileID, displayName );
		Int color = 0;
		if ( state == 1 )
			color = 9;
		else if ( state == 2 )
			color = 8;
		Int index = Rva00515810AddEntry( m_friendsList, profileID,
			record + 4, GameSpyColor[color] );
		if ( selectedProfiles.find( profileID ) != selectedProfiles.end() )
			indicesToSelect.push_back( index );
	}
	std::sort( indicesToSelect.begin(), indicesToSelect.end() );
	if ( indicesToSelect.size() != 0 )
	{
		Int *newIndices = new Int[indicesToSelect.size()];
		for ( Int i = 0; i < (Int)indicesToSelect.size(); ++i )
			newIndices[i] = indicesToSelect[i];
		GadgetListBoxSetSelected( m_friendsList, newIndices,
			(Int)indicesToSelect.size() );
		delete[] newIndices;
	}

	if ( (Int)indicesToSelect.size() != numSelected )
		TheWindowManager->winSetLoneWindow( 0 );

	updateButtons();
	GadgetListBoxSetTopVisibleEntry( m_friendsList, previousTopIndex );
}
