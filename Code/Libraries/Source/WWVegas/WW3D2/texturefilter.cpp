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

// TextureFilterClass default-filter setters from WW3D2/texturefilter.cpp,
// verbatim from the Zero Hour reference. The real texturefilter.h reaches
// dx8wrapper.h and the DirectX 8 SDK, which the fleet toolchains do not have,
// so the class is cut down to the enum and the filter table these bodies touch;
// the table is file-scope in Zero Hour too, so its address comes from retail.

const unsigned MAX_TEXTURE_STAGES=8;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texturefilter.h
class TextureFilterClass
{
public:
	enum FilterType
	{
		FILTER_TYPE_NONE,
		FILTER_TYPE_FAST,
		FILTER_TYPE_BEST,
		FILTER_TYPE_DEFAULT,
		FILTER_TYPE_COUNT
	};

	static void _Set_Default_Min_Filter(FilterType filter);
};

unsigned _MinTextureFilters[MAX_TEXTURE_STAGES][TextureFilterClass::FILTER_TYPE_COUNT];

void TextureFilterClass::_Set_Default_Min_Filter(FilterType filter)
{
	for (int i=0;i<MAX_TEXTURE_STAGES;++i)
	{
		_MinTextureFilters[i][FILTER_TYPE_DEFAULT]=_MinTextureFilters[i][filter];
	}
}
