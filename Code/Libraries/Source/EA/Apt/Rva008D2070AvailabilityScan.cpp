// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

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

extern volatile BfmeSlot1220 g_bfmeSlots1220[ 15 ];
extern int g_bfmeValues1220[];

class BfmeNode1220
{
public:
	bool bfmeAllows1220();
	int bfmeTest1220( int *value, int zero );

private:
	unsigned int m_vptr;
	unsigned int m_kind;
	char m_gap08[ 0x50 - 8 ];
	BfmeOwner1220 * volatile m_owner;
};

bool BfmeNode1220::bfmeAllows1220()
{
	if ( (m_kind & 0x3f) == 0x0f && !((unsigned char)(~(m_kind >> 15)) & 1) )
		return false;

	BfmeEntryList1220 *list = m_owner->bfmeList1220();
	if ( list != 0 )
	{
		for ( int index = 0; index < list->m_count; ++index )
		{
			if ( (list->m_entries[ index ].m_flags & 0x7c00) != 0 )
				return true;
		}
	}

	for ( int index = 0; index < 15; ++index )
	{
		if ( (g_bfmeSlots1220[ index ].m_flags & 0x7c00) != 0 &&
			bfmeTest1220( g_bfmeValues1220 + g_bfmeSlots1220[ index ].m_index, 0 ) )
			return true;
	}

	return false;
}
