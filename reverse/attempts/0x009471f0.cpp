// ?Add_Mesh@DX8TextureCategoryClass@@QAEIAAVVertex_Split_Table@@IIPAVIndexBufferClass@@I@Z
// partial score=0.62 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ibuild/toolchains/dx81/include
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

// BFME DX8TextureCategoryClass::Add_Mesh at retail RVA 0x009471F0.
// The body counts polygons matching this category, creates a renderer for
// the matching indices, and appends the index range.  BFME's split-table
// texture accessor returns an owning BfmeHandleCX; the TU-local view below
// preserves that ABI while the shared WW3D2 headers retain their pointer
// shaped Zero Hour declaration.

#include "dx8renderer.h"
#include "dx8polygonrenderer.h"
#include "dx8indexbuffer.h"

class BfmeHandleCX
{
public:
	BfmeHandleCX(void) : p(0) {}
	BfmeHandleCX(const BfmeHandleCX &other) : p(other.p)
	{
		if (p)
			p->Add_Ref();
	}
	~BfmeHandleCX(void)
	{
		if (p)
			p->Release_Ref();
	}
	BfmeHandleCX &operator=(const BfmeHandleCX &other)
	{
		if (other.p)
			other.p->Add_Ref();
		if (p)
			p->Release_Ref();
		p = other.p;
		return *this;
	}
	bool operator==(TextureClass *other) const { return p == other; }
	TextureClass *p;
};

class Gen_00945B20
{
public:
	BfmeHandleCX bfmeGet(int pidx, int pass, int stage) const;
};

// This is the BFME member order used by the established Vertex_Split_Table
// helper methods.  Only Add_Mesh's existing method calls are exposed here;
// the class itself is not constructed by this TU.
class Vertex_Split_Table
{
	MeshModelClass *mmc;
	bool npatch_enable;
	unsigned polygon_count;
	TriIndex *polygon_array;
	bool allocated_polygon_array;

public:
	unsigned Get_Polygon_Count(void) const { return polygon_count; }

	__forceinline BfmeHandleCX Peek_Texture(unsigned index, unsigned pass, unsigned stage)
	{
		return reinterpret_cast<const Gen_00945B20 *>(this)->bfmeGet(index, pass, stage);
	}

	__forceinline VertexMaterialClass *Peek_Material(unsigned index, unsigned pass)
	{
		if (mmc->Has_Material_Array(pass)) {
			return mmc->Peek_Material(
				(*reinterpret_cast<ShareBufferClass<TriIndex> **>(
					reinterpret_cast<char *>(mmc) + 0x2c))->Get_Array()[index][0], pass);
		}
		return mmc->Peek_Single_Material(pass);
	}

	ShaderClass Peek_Shader(unsigned index, unsigned pass);
	__forceinline MeshModelClass *Get_Mesh_Model_Class(void) { return mmc; }
	__forceinline unsigned short *Get_Polygon_Array(unsigned pass)
	{
		(void)pass;
		return reinterpret_cast<unsigned short *>(polygon_array);
	}
};

inline static bool Equal_Material(const VertexMaterialClass *mat1,
	const VertexMaterialClass *mat2)
{
	int crc0 = mat1 ? mat1->Get_CRC() : 0;
	int crc1 = mat2 ? mat2->Get_CRC() : 0;
	return crc0 == crc1;
}

// ?Add_Mesh@DX8TextureCategoryClass@@QAEIAAVVertex_Split_Table@@IIPAVIndexBufferClass@@I@Z
unsigned DX8TextureCategoryClass::Add_Mesh(
	Vertex_Split_Table &split_table,
	unsigned vertex_offset,
	unsigned index_offset,
	IndexBufferClass *index_buffer,
	unsigned pass)
{
	int poly_count = split_table.Get_Polygon_Count();
	unsigned index_count = 0;
	unsigned polygons = 0;
	int i;

	for (i = 0; i < poly_count; ++i) {
		bool all_textures_same = true;
		for (unsigned int stage = 0; stage < MeshMatDescClass::MAX_TEX_STAGES; ++stage) {
			all_textures_same = all_textures_same &&
				(reinterpret_cast<const Gen_00945B20 *>(&split_table)->bfmeGet(i, pass, stage) == textures[stage]);
		}
		VertexMaterialClass *mat = split_table.Peek_Material(i, pass);
		ShaderClass shd = split_table.Peek_Shader(i, pass);

		if (all_textures_same && Equal_Material(mat, material) && shd == shader) {
			++polygons;
		}
	}

	if (polygons) {
		index_count = polygons * 3;
		bool stripify = false;
		const TriIndex *src_indices =
			(const TriIndex *)split_table.Get_Polygon_Array(pass);

		DX8PolygonRendererClass *p_renderer = W3DNEW DX8PolygonRendererClass(
			index_count,
			split_table.Get_Mesh_Model_Class(),
			this,
			vertex_offset,
			index_offset,
			stripify,
			pass);
		PolygonRendererList.Add_Tail(p_renderer);

		IndexBufferClass::AppendLockClass l(index_buffer, index_offset, index_count);
		unsigned short *dst_indices = l.Get_Index_Array();
		unsigned short vmin = 0xffff;
		unsigned short vmax = 0;
		unsigned short first_polygon = 0xffff;
		unsigned short last_polygon = 0;

		for (i = 0; i < poly_count; ++i) {
			bool all_textures_same = true;
			for (unsigned int stage = 0; stage < MeshMatDescClass::MAX_TEX_STAGES; ++stage) {
				all_textures_same = all_textures_same &&
					(reinterpret_cast<const Gen_00945B20 *>(&split_table)->bfmeGet(i, pass, stage) == textures[stage]);
			}
			VertexMaterialClass *mat = split_table.Peek_Material(i, pass);
			ShaderClass shd = split_table.Peek_Shader(i, pass);

			if (all_textures_same && Equal_Material(mat, material) && shd == shader) {
				unsigned short idx;
				if (first_polygon == 0xffff)
					first_polygon = (unsigned short)i;
				idx = (unsigned short)(src_indices[i][0] + vertex_offset);
				vmin = MIN(vmin, idx);
				last_polygon = (unsigned short)i;
				vmax = MAX(vmax, idx);
				*dst_indices++ = idx;
				idx = (unsigned short)(src_indices[i][1] + vertex_offset);
				vmin = MIN(vmin, idx);
				vmax = MAX(vmax, idx);
				*dst_indices++ = idx;
				idx = (unsigned short)(src_indices[i][2] + vertex_offset);
				vmin = MIN(vmin, idx);
				vmax = MAX(vmax, idx);
				*dst_indices++ = idx;
			}
		}

		// BFME keeps the split-table polygon span in the renderer's second
		// range pair.  The fields were added to the established renderer layout
		// at +0x24/+0x28 and retail writes them after the vertex range.
		p_renderer->Set_Vertex_Index_Range(vmin, vmax - vmin + 1);
		*reinterpret_cast<unsigned *>(reinterpret_cast<char *>(p_renderer) + 0x24) = first_polygon;
		*reinterpret_cast<unsigned *>(reinterpret_cast<char *>(p_renderer) + 0x28) =
			last_polygon - first_polygon + 1;
		WWASSERT(index_count <= unsigned(split_table.Get_Polygon_Count() * 3));
	}

	return index_count;
}
