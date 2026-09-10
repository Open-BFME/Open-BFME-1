// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
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

// Retail 0x00933590, complete 0x118-byte body.  MaterialPassClass's
// constructor at 0x009333A0 installs vtable 0x0113C884; zero-based slot 2 is this
// Install_Materials body, between the named deleting destructor at 0x00933570
// and the empty UnInstall_Materials slot at 0x00933410.  The upstream
// matpass.h declaration supplies the public identity.  BFME stores the eight
// texture stages as one-word owning handles and uses the already matched
// by-value helper at 0x00933540, so those ABI details stay local to this TU.

#include "matpass.h"
#include "vertmaterial.h"
#include "texture.h"
#include "dx8wrapper.h"

class BFMETextureRelease
{
public:
	void Release_Ref(void);
};

class BfmeHandleCX
{
public:
	~BfmeHandleCX(void)
	{
		if (m_bfmeThing)
			m_bfmeThing->Release_Ref();
	}

	operator TextureBaseClass *&(void)
	{
		return *(TextureBaseClass **)&m_bfmeThing;
	}

private:
	BFMETextureRelease *m_bfmeThing;
};

// This is the existing BFME by-value texture-stage helper at 0x00933540.
// The declaration is intentionally local: its name and address are already
// represented by the matched Bfme5ThirtyFive.cpp row, while this method only
// needs the helper's return ABI and the shared `this` pointer.
class Gen_00933540
{
public:
	BfmeHandleCX bfmeGet(int index) const;
};

// BFME's caps object has additional fields before MaxTexturesPerPass.  The
// shared WW3D2 header is the upstream layout, so only this field uses the
// retail offset observed in the candidate body.
struct MaterialPassCapsView
{
	char m_unmodeled[0x278];
	int max_textures;
};

extern void BoxSetTexture(unsigned int index, TextureBaseClass *&texture);

void MaterialPassClass::Install_Materials(void) const
{
	DX8Wrapper::Set_Material(Peek_Material());
	DX8Wrapper::Set_Shader(Peek_Shader());
	for (int i = 0; i < reinterpret_cast<const MaterialPassCapsView *>(DX8Wrapper::Get_Current_Caps())->max_textures; ++i)
	{
		BoxSetTexture(i, (TextureBaseClass *&)
			reinterpret_cast<const Gen_00933540 *>(this)->bfmeGet(i));
	}
}
