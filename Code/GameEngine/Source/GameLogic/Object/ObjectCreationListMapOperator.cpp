// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// This is the retail ObjectCreationList map's explicit STLport instantiation.
// The complete header cannot be included here: its normal PreRTS path selects
// the default-constructor compatibility switch before <map> is parsed. The
// named parser caller proves that the mapped value is ObjectCreationList, whose
// sole vector member is 12 bytes. Retail's selected COMDAT is the neighboring
// address-derived tree_int_p12cd family, so this TU-local ABI slice keeps the
// proven 4-byte key/12-byte value shape without inventing a second callee pin.
// A canonical NameKeyType/ObjectCreationList probe was byte-identical except
// for the +0x81 insert_unique call: retail reaches 0x001DA900 through ILT
// 0x0001F389, while the typed spelling resolves to the distinct 0x00768710
// specialization. Keep this neutral view until that helper identity is proven.
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>
#include <vector>

struct Gen_t_001da900_p12cd
{
	// ObjectCreationList's only data member is this three-word vector.
	std::vector<void *> m_nuggets;
};

typedef std::map<int, Gen_t_001da900_p12cd, std::less<int> > BfmeObjectCreationListMap;

// ??A?$map@W4NameKeyType@@VObjectCreationList@@U?$less@W4NameKeyType@@@_STL@@V?$allocator@U?$pair@$$CBW4NameKeyType@@VObjectCreationList@@@_STL@@@4@@_STL@@QAEAAVObjectCreationList@@ABW4NameKeyType@@@Z
template Gen_t_001da900_p12cd &BfmeObjectCreationListMap::operator[](
	const int &key);
