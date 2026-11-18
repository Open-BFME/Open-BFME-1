// ?Rva00515810@AptInGameChat@@QAEXXZ
// matched 1166/1166 bytes (exact modulo relocations) 2026-10-13
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline
// stlport
//
// AptInGameChat::Rva00515810, retail 0x00515810, 1166 bytes.
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

#include "../../../../../Include/Common/ScalarTypes.h"
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
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual BuddyInfoMap *getBuddyMap() = 0;
	virtual BuddyInfoMap *getBuddyRequestMap() = 0;
};

class GameWindowManager
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void winSetLoneWindow( GameWindow *window ) = 0;
};

// Retail 0x012F7194: use the existing data owner; retain the local pointee view.
extern class GameSpyInfoInterface *TheGameSpyInfo;
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

// The row-adder is an already matched body (0x0052DC00, 147 bytes, matched in
// BfmeAptScreenOnlineChatAddFriend.cpp); this call site targets its
// incremental-link thunk, so the matched ledger row resolves the displacement.
extern Int Rva0052DC00AddFriend( GameWindow *listbox, Int profileID,
	const AsciiString *name, Color color );

class AptInGameChat
{
public:
	void Rva00515810();
	void Rva00006F4BUpdateButtons();
	Int rva00512890( Int profileID, UnicodeString &result );

private:
	unsigned char m_unmodelled000[0x260];
	GameWindow *m_chatEntry;
	GameWindow *m_friendsList;
};

void AptInGameChat::Rva00515810()
{
	if ( m_friendsList == 0 || reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo) == 0 )
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
	BuddyInfoMap *buddyMap = reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->getBuddyMap();
	for ( BuddyInfoMap::iterator it = buddyMap->begin(); it != buddyMap->end(); ++it )
	{
		Gen_t_00513940_m4pod record = { (Int)&it->second };
		records.push_back( record );
	}

	buddyMap = reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->getBuddyRequestMap();
	for ( BuddyInfoMap::iterator it = buddyMap->begin(); it != buddyMap->end(); ++it )
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
		UnicodeString displayName;
		Int state = rva00512890( *(Int *)record, displayName );
		Int color = 0;
		switch ( state )
		{
		case 1:
			color = 8;
			break;
		case 2:
			color = 9;
			break;
		case 4:
			color = 0;
			break;
		}
		Int index = Rva0052DC00AddFriend( m_friendsList, *(Int *)record,
			(const AsciiString *)(record + 4), GameSpyColor[color] );
		if ( selectedProfiles.find( *(Int *)record ) != selectedProfiles.end() )
			indicesToSelect.push_back( index );
	}
	Int selectedCount = (Int)indicesToSelect.size();
	if ( selectedCount != 0 )
	{
		std::sort( indicesToSelect.begin(), indicesToSelect.end() );
		Int *newIndices = new Int[selectedCount];
		std::vector<Int>::iterator indexIt;
		Int i;
		for ( i = 0, indexIt = indicesToSelect.begin(); indexIt != indicesToSelect.end(); ++i, ++indexIt )
			newIndices[i] = *indexIt;
		GadgetListBoxSetSelected( m_friendsList, newIndices, selectedCount );
		delete[] newIndices;
	}

	if ( selectedCount != numSelected )
		TheWindowManager->winSetLoneWindow( 0 );

	GadgetListBoxSetTopVisibleEntry( m_friendsList, previousTopIndex );
	Rva00006F4BUpdateButtons();
}
