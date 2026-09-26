// ?Rva00920AE0SelectOption@@YAXH@Z
struct Rva00920AE0Slot
{
	int m_options[ 4 ];
	int m_selected;
};

extern Rva00920AE0Slot g_bfmeOptionSlotsA[ 8 ];  // retail 0x01346C50
extern Rva00920AE0Slot g_bfmeOptionSlotsB[ 8 ];  // retail 0x01346CF0

void __cdecl Rva00920AE0SelectOption( int index )
{
	g_bfmeOptionSlotsA[ 0 ].m_selected = g_bfmeOptionSlotsA[ 0 ].m_options[ index ];
	g_bfmeOptionSlotsA[ 1 ].m_selected = g_bfmeOptionSlotsA[ 1 ].m_options[ index ];
	g_bfmeOptionSlotsA[ 2 ].m_selected = g_bfmeOptionSlotsA[ 2 ].m_options[ index ];
	g_bfmeOptionSlotsA[ 3 ].m_selected = g_bfmeOptionSlotsA[ 3 ].m_options[ index ];
	g_bfmeOptionSlotsA[ 4 ].m_selected = g_bfmeOptionSlotsA[ 4 ].m_options[ index ];
	g_bfmeOptionSlotsA[ 5 ].m_selected = g_bfmeOptionSlotsA[ 5 ].m_options[ index ];
	g_bfmeOptionSlotsA[ 6 ].m_selected = g_bfmeOptionSlotsA[ 6 ].m_options[ index ];
	g_bfmeOptionSlotsA[ 7 ].m_selected = g_bfmeOptionSlotsA[ 7 ].m_options[ index ];
}

// ?Rva00920B50SelectOption@@YAXH@Z
void __cdecl Rva00920B50SelectOption( int index )
{
	g_bfmeOptionSlotsB[ 0 ].m_selected = g_bfmeOptionSlotsB[ 0 ].m_options[ index ];
	g_bfmeOptionSlotsB[ 1 ].m_selected = g_bfmeOptionSlotsB[ 1 ].m_options[ index ];
	g_bfmeOptionSlotsB[ 2 ].m_selected = g_bfmeOptionSlotsB[ 2 ].m_options[ index ];
	g_bfmeOptionSlotsB[ 3 ].m_selected = g_bfmeOptionSlotsB[ 3 ].m_options[ index ];
	g_bfmeOptionSlotsB[ 4 ].m_selected = g_bfmeOptionSlotsB[ 4 ].m_options[ index ];
	g_bfmeOptionSlotsB[ 5 ].m_selected = g_bfmeOptionSlotsB[ 5 ].m_options[ index ];
	g_bfmeOptionSlotsB[ 6 ].m_selected = g_bfmeOptionSlotsB[ 6 ].m_options[ index ];
	g_bfmeOptionSlotsB[ 7 ].m_selected = g_bfmeOptionSlotsB[ 7 ].m_options[ index ];
}
