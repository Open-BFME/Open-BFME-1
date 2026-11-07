// cl: /DNDEBUG
/*
**	Command & Conquer Generals(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "texturefilter.h"

const unsigned MAX_TEXTURE_STAGES=8;

struct Rva00920AE0Slot
{
	int m_options[4];
	int m_selected;
};

Rva00920AE0Slot g_bfmeOptionSlots0[MAX_TEXTURE_STAGES] = {};

void TextureFilterClass::_Set_Default_Min_Filter(FilterType filter)
{
	for (int i=0;i<MAX_TEXTURE_STAGES;++i)
	{
		g_bfmeOptionSlots0[i].m_selected=g_bfmeOptionSlots0[i].m_options[filter];
	}
}

void TextureFilterClass::Set_Mip_Mapping(FilterType mipmap)
{
	MipMapFilter=mipmap;
}
