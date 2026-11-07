#include "../../../Libraries/Source/WWVegas/WW3D2/texturefilter.h"
#include "../../../Libraries/Source/WWVegas/WW3D2/TextureFilterTable.h"

Rva00920AE0Slot g_bfmeOptionSlotsA[ 8 ] = {};  // retail 0x01346C50
Rva00920AE0Slot g_bfmeOptionSlotsB[ 8 ] = {};  // retail 0x01346CF0

void TextureFilterClass::_Set_Default_Mag_Filter(FilterType index)
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

void TextureFilterClass::_Set_Default_Mip_Filter(FilterType index)
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
