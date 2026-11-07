// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// BfmeNode1220 mask test, retail 0x008D1F10 (107 bytes, ret 4). It sits beside
// BfmeNode1220_bfmeAllows.cpp but needs a non-volatile m_owner view, which that
// TU's bfmeAllows1220 body cannot use, so it has its own unit.
// Handoff: targets/game/reverse/attempt_support/20261107-008d1f10-nonvolatile-owner.md

struct BfmeEntry1220
{
	unsigned int m_flags;
	int m_a;
	int m_b;
};

struct BfmeEntryList1220
{
	int m_count;
	BfmeEntry1220 *m_entries;
};

struct BfmeOwner1220
{
	BfmeEntryList1220 *bfmeList1220() const { return m_list; }

	char m_gap[ 0x20 ];
	BfmeEntryList1220 *m_list;
};

struct BfmeSlot1220
{
	unsigned int m_flags;
	int m_index;
};

// Retail walks fourteen 8-byte slots at 0x012D5D50 ({flags, value index});
// the exclusive end is 0x012D5DC0. Declared volatile because the defining TU
// (BfmeNode1220_bfmeAllows.cpp) defines ?g_bfmeSlots1220@@3RCUBfmeSlot1220@@C,
// the recorded data row.
extern volatile BfmeSlot1220 g_bfmeSlots1220[ 14 ];
// Retail 0x01338480 is defined once, as bfmeObjDAE (Rva00C6DC90ArrayInit.cpp).
#define g_bfmeValues1220 __identifier("bfmeObjDAE")
extern "C" int g_bfmeValues1220[];

class BfmeNode1220
{
public:
	bool rva008D1F10( unsigned int mask );
	int bfmeTest1220( int *value, int zero );

private:
	unsigned int m_vptr;
	unsigned int m_kind;
	char m_gap08[ 0x50 - 8 ];
	BfmeOwner1220 *m_owner;
};

// Retail 0x008D1F10 (107 bytes, ret 4): true when an owner entry carries any
// bit of `mask`; otherwise the slot whose flags equal `mask` selects the
// value tested with bfmeTest1220 (no match leaves the index at -1, as retail
// does). The method's real name is not proven, so it keeps the address.
bool BfmeNode1220::rva008D1F10( unsigned int mask )
{
	BfmeEntryList1220 *list = m_owner->bfmeList1220();
	if ( list != 0 )
	{
		for ( int index = 0; index < list->m_count; ++index )
		{
			if ( list->m_entries[ index ].m_flags & mask )
				return true;
		}
	}

	int slot = -1;
	for ( int index = 0; index < 14; ++index )
	{
		if ( g_bfmeSlots1220[ index ].m_flags == mask )
		{
			slot = index;
			break;
		}
	}

	return (bool)bfmeTest1220( g_bfmeValues1220 + g_bfmeSlots1220[ slot ].m_index, 0 );
}
