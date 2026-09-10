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

// BFME DX8FVFCategoryContainer::Find_Matching_Texture_Category texture
// overload at 0x00946C00.  The retail category stores two texture handles at
// +0x0c/+0x10, a ShaderClass at +0x14 and material at +0x18.  Its owning
// getter at 0x00945490 and the matched category constructor establish this
// TU-local ABI view without changing the shared WW3D2 header.
// Full431B ends at 0x00946DAF CC after both ret16 epilogues. Argument one
// is a const handle reference; the candidate and reference getters return
// owning handles released through the existing 0x009EB7A0 routine. The
// canonical overload and retail argument/field layout establish this shape;
// no matched direct caller has been established for this body.

#include "../WWLib/multilist.h"

class TextureClass
{
public:
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

inline bool operator==(TextureClass *left, const BfmeHandleCX &right)
{
	return left == right.p;
}

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
};

class DX8PolygonRendererClass;
class DX8TextureCategoryClass : public MultiListObjectClass
{
public:
	const VertexMaterialClass *Peek_Material() const { return material; }
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
		const BfmeHandleCX &texture,
		unsigned pass,
		unsigned stage,
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
	const BfmeHandleCX &texture,
	unsigned pass,
	unsigned stage,
	DX8TextureCategoryClass *ref_category)
{
	DX8TextureCategoryClass *dest_tex_category = NULL;
	TextureCategoryListIterator dest_it(&texture_category_list[pass]);
	while (!dest_it.Is_Done()) {
		if (reinterpret_cast<const Gen_00945490 *>(dest_it.Peek_Obj())->bfmeGet(stage) == texture) {
			dest_tex_category = dest_it.Peek_Obj();
			bool all_textures_same = true;
			for (unsigned int s = 0; s < 2; ++s) {
				if (stage != s) {
					all_textures_same = all_textures_same &&
						(reinterpret_cast<const Gen_00945490 *>(dest_tex_category)->bfmeGet(s) ==
						 reinterpret_cast<const Gen_00945490 *>(ref_category)->bfmeGet(s));
				}
			}
			if (all_textures_same &&
				Equal_Material(dest_tex_category->Peek_Material(), ref_category->Peek_Material()) &&
				dest_tex_category->Get_Shader_Bits() == ref_category->Get_Shader_Bits())
				return dest_tex_category;
		}
		dest_it.Next();
	}
	return NULL;
}
