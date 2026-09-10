// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
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
// BFME DX8FVFCategoryContainer::Find_Matching_Texture_Category material
// overload at 0x00946DB0. Actual retail material-migration call at 0x00948300
// passes new material, pass and reference category; that caller is not yet
// a matched C++ body.  The retail category stores two raw texture
// pointers at +0x0c/+0x10, but its accessor returns an owning BfmeHandleCX;
// the 0x00945490 callee and the matched category constructor establish this
// TU-local ABI view without changing the shared WW3D2 header.

#include "../WWLib/multilist.h"

class TextureClass
{
public:
	void Add_Ref();
	void Release_Ref();
};

class BfmeHandleCX
{
public:
	TextureClass *p;

	~BfmeHandleCX(void)
	{
		if (p)
			p->Release_Ref();
	}
	bool operator==(const BfmeHandleCX &other) const { return p == other.p; }
};

class Gen_00945490
{
public:
	BfmeHandleCX bfmeGet(int stage) const throw();
};

class VertexMaterialClass
{
	unsigned char pad[0x64];
	mutable unsigned long CRC;
	mutable bool CRCDirty;
	unsigned long Compute_CRC() const;

public:
	unsigned long Get_CRC() const
	{
		if (CRCDirty) {
			CRC = Compute_CRC();
			CRCDirty = false;
		}
		return CRC;
	}
};

class ShaderClass
{
public:
	unsigned int ShaderBits;
	bool operator==(const ShaderClass &other) const { return ShaderBits == other.ShaderBits; }
};

class DX8PolygonRendererClass;
class DX8FVFCategoryContainer;

class DX8TextureCategoryClass : public MultiListObjectClass
{
public:
	__forceinline BfmeHandleCX Get_Texture(int stage) const
	{
		return reinterpret_cast<const Gen_00945490 *>(this)->bfmeGet(stage);
	}

	const VertexMaterialClass *Peek_Material() const { return material; }
	ShaderClass Get_Shader() const { return shader; }
	unsigned int Get_Shader_Bits() const { return shader.ShaderBits; }

private:
	int pass;
	TextureClass *textures[2];
	ShaderClass shader;
	VertexMaterialClass *material;
	MultiListClass<DX8PolygonRendererClass> polygon_renderer_list;
};

typedef MultiListClass<DX8TextureCategoryClass> TextureCategoryList;
typedef MultiListIterator<DX8TextureCategoryClass> TextureCategoryListIterator;

class DX8FVFCategoryContainer : public MultiListObjectClass
{
	protected:
	DX8TextureCategoryClass *Find_Matching_Texture_Category(
		VertexMaterialClass *vmat,
		unsigned pass,
		DX8TextureCategoryClass *ref_category);

private:
	TextureCategoryList texture_category_list[4];
};

inline static bool Equal_Material(const VertexMaterialClass *mat1,
	const VertexMaterialClass *mat2)
{
	unsigned int crc0 = mat1 ? mat1->Get_CRC() : 0;
	unsigned int crc1 = mat2 ? mat2->Get_CRC() : 0;
	return crc0 == crc1;
}

DX8TextureCategoryClass *DX8FVFCategoryContainer::Find_Matching_Texture_Category(
	VertexMaterialClass *vmat,
	unsigned pass,
	DX8TextureCategoryClass *ref_category)
{
	DX8TextureCategoryClass *dest_tex_category = NULL;
	TextureCategoryListIterator dest_it(&texture_category_list[pass]);
	while (!dest_it.Is_Done()) {
		if (Equal_Material(dest_it.Peek_Obj()->Peek_Material(), vmat)) {
			dest_tex_category = dest_it.Peek_Obj();
			bool all_textures_same = true;
			for (unsigned int stage = 0; stage < 2; ++stage) {
				all_textures_same = all_textures_same &&
					(reinterpret_cast<const Gen_00945490 *>(dest_tex_category)->bfmeGet(stage) ==
					 reinterpret_cast<const Gen_00945490 *>(ref_category)->bfmeGet(stage));
			}
			if (all_textures_same &&
				dest_tex_category->Get_Shader_Bits() == ref_category->Get_Shader_Bits())
				return dest_tex_category;
		}
		dest_it.Next();
	}
	return NULL;
}
