// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep /Iinputs/toolchains/dx81/include
/*
** Copyright 2025 Electronic Arts Inc.
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
// BFME MeshModelClass::read_vertex_colors, RVA 0x0096D140, 373 bytes.
// read_chunks maps W3D_CHUNK_VERTEX_COLORS (0x0D) through selector byte
// 0x0097013F and table slot 0x0097011C to the arm at 0x0097001C;
// its call at 0x00970020 reaches this body. The dispatcher consumes AL
// and tests it against 1, matching the Boolean ABI of the sibling loaders.
// The final RET 8 at 0x0096D2B2 ends immediately before INT3 padding.
// read_dcg: RVA 0x0096D500, complete 773-byte body. Chunk 0x3B selects
// arm 0x0096FBB5; the call at 0x0096FBB9 reaches this body. It returns
// a Boolean in AL and ends with RET 8 at 0x0096D802, then INT3 padding.
// The matched MeshModel constructor establishes DefMatDesc at +0x94,
// AlternateMatDesc at +0x98, and CurMatDesc at +0x9C. Legacy vertex colors
// use CurMatDesc; the DCG reader starts with DefMatDesc.
// read_dig: RVA 0x0096D810, complete 809-byte body. Chunk 0x3C selects
// arm 0x0096FBC0, whose call at 0x0096FBC4 reaches this body. It ends
// with RET 8 at 0x0096DB36 and INT3 padding at 0x0096DB39.
// LoadedDIG at context+0x20C selects the alternate descriptor on repeat chunks.
// read_stage_texcoords: RVA 0x0096E690, complete 178-byte body. Texture-stage
// chunks 0x05 and 0x4A select the arm at 0x0096EDCB; its call at 0x0096EDCF
// reaches this loader. RET 8 at 0x0096E73F ends before INT3 at 0x0096E742.
// The original SimpleVecClass<Vector2> at context+0x200 provides the temporary
// array; its data pointer is at +0x204. The V conversion reads float 1.0f.
// read_texture_stage: RVA 0x0096ED60, full 247-byte compiler span. Material
// pass chunk 0x48 selects arm 0x0096FBCB, whose call at 0x0096FBCF reaches
// this body and checks AL against 1. RET 8 at +0x9A ends the executable code;
// the jump table (+0xA0..+0xAF) and selectors (+0xB0..+0xF6) belong to this
// function. INT3 padding starts at +0xF7. Per-face UV indices are skipped by
// the original inline length check and Seek; no separate body is claimed.
// Original semantic bodies: meshmdlio.cpp; BFME field views are local here.
#include "dx8wrapper.h"
#include "w3d_file.h"
#include "simplevec.h"
#include "vector2.h"
#include "vector3i.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class MeshMatDescClass
{
	int PassCount;
	int VertexCount;
	int PolyCount;
	void *UV[8];
	int UVSource[4][2];
	void *ColorArray[2];
	VertexMaterialClass::ColorSourceType DCGSource[4];
	VertexMaterialClass::ColorSourceType DIGSource[4];

public:
	bool Has_UV(int pass,int stage) { return UVSource[pass][stage] != -1; }
	void Install_UV_Array(int pass,int stage,Vector2 *uvs,int count);
	VertexMaterialClass::ColorSourceType Get_DCG_Source(int pass) { return DCGSource[pass]; }
	bool Has_Color_Array(int array) { return ColorArray[array] != 0; }
	unsigned *Get_Color_Array(int array,bool create = true);
	void Set_DCG_Source(int pass,VertexMaterialClass::ColorSourceType source)
	{
		DCGSource[pass] = source;
	}
};

class MeshLoadContextClass
{
	unsigned char prelit_padding[0x88];
public:
	unsigned long PrelitChunkID;
	int CurPass;
	int CurTexStage;
	unsigned char alternate_padding[0x10c - 0x94];
	MeshMatDescClass AlternateMatDesc;
	unsigned char temporary_uv_padding[0x200 - 0x10c - sizeof(MeshMatDescClass)];
	SimpleVecClass<Vector2> TempUVArray;
	bool LoadedDIG;

	Vector2 *Get_Temporary_UV_Array(int elementcount)
	{
		TempUVArray.Uninitialised_Grow(elementcount);
		return &TempUVArray[0];
	}

	bool Already_Loaded_DIG() { return LoadedDIG; }
	void Notify_Loaded_DIG_Chunk(bool loaded) { LoadedDIG = loaded; }
};

class MeshModelClass
{
	unsigned char geometry_padding[0x24];
	int PolyCount;
	int VertexCount;
	unsigned char material_padding[0x94 - 0x2c];
public:
	MeshMatDescClass *DefMatDesc;
	MeshMatDescClass *AlternateMatDesc;
	MeshMatDescClass *CurMatDesc;

	unsigned *Get_Color_Array(int array,bool create = true)
	{
		return CurMatDesc->Get_Color_Array(array,create);
	}

protected:
    bool read_texture_ids(ChunkLoadClass &cload,MeshLoadContextClass *context);
    bool read_per_face_texcoord_ids(ChunkLoadClass &cload,MeshLoadContextClass *context)
    {
        unsigned size = sizeof(Vector3i) * PolyCount;
        if (cload.Cur_Chunk_Length() == size) {
            cload.Seek(size);
            return true;
        }
        return false;
    }
    bool read_texture_stage(ChunkLoadClass &cload,MeshLoadContextClass *context);
	bool read_stage_texcoords(ChunkLoadClass &cload,MeshLoadContextClass *context);
	bool read_dig(ChunkLoadClass &cload,MeshLoadContextClass *context);
	bool read_dcg(ChunkLoadClass &cload,MeshLoadContextClass *context);
	bool read_vertex_colors(ChunkLoadClass &cload,MeshLoadContextClass *context);
};

bool MeshModelClass::read_vertex_colors(ChunkLoadClass &cload,MeshLoadContextClass *context)
{
	if (CurMatDesc->Has_Color_Array(0) == 0) {
		W3dRGBStruct color;
		unsigned *dcg = Get_Color_Array(0,true);
		for (int i=0; i<VertexCount; i++) {
			if (cload.Read(&color,sizeof(W3dRGBStruct)) != sizeof(W3dRGBStruct)) {
				return false;
			}

			Vector4 col;
			col.Set((float)color.R / 255.0f,(float)color.G / 255.0f,(float)color.B / 255.0f,1.0f);
			dcg[i] = DX8Wrapper::Convert_Color(col);
		}
	}
	CurMatDesc->Set_DCG_Source(context->CurPass,VertexMaterialClass::COLOR1);
	return true;
}

bool MeshModelClass::read_dcg(ChunkLoadClass &cload,MeshLoadContextClass *context)
{
	MeshMatDescClass *matdesc = DefMatDesc;
	if (DefMatDesc->Get_DCG_Source(context->CurPass) != VertexMaterialClass::MATERIAL) {
		matdesc = &context->AlternateMatDesc;
	}

	if (matdesc->Has_Color_Array(0) == 0) {
		W3dRGBAStruct color;
		unsigned *dcg = matdesc->Get_Color_Array(0);
		for (int i=0; i<VertexCount; i++) {
			cload.Read(&color,sizeof(color));
			Vector4 col;
			col.Set((float)color.R / 255.0f,(float)color.G / 255.0f,
				(float)color.B / 255.0f,(float)color.A / 255.0f);
			dcg[i] = DX8Wrapper::Convert_Color(col);
		}
	} else if (context->PrelitChunkID == W3D_CHUNK_PRELIT_VERTEX) {
		W3dRGBAStruct color;
		unsigned *dcg = matdesc->Get_Color_Array(0);
		for (int i=0; i<VertexCount; i++) {
			cload.Read(&color,sizeof(color));
			Vector4 col = DX8Wrapper::Convert_Color(dcg[i]);
			col.W = (float)color.A / 255.0f;
			dcg[i] = DX8Wrapper::Convert_Color(col);
		}
	}

	matdesc->Set_DCG_Source(context->CurPass,VertexMaterialClass::COLOR1);
	return true;
}

bool MeshModelClass::read_dig(ChunkLoadClass &cload,MeshLoadContextClass *context)
{
	MeshMatDescClass *matdesc = DefMatDesc;
	if (context->Already_Loaded_DIG()) {
		matdesc = &context->AlternateMatDesc;
	}
	context->Notify_Loaded_DIG_Chunk(true);

	W3dRGBAStruct color;
	if (matdesc->Has_Color_Array(0) == false) {
		unsigned *dcg = matdesc->Get_Color_Array(0);
		for (int i=0; i<VertexCount; i++) {
			cload.Read(&color,sizeof(color));
			Vector4 col;
			col.X = (float)color.R / 255.0f;
			col.Y = (float)color.G / 255.0f;
			col.Z = (float)color.B / 255.0f;
			col.W = 1.0f;
			dcg[i] = DX8Wrapper::Convert_Color(col);
		}
	} else {
		unsigned *dcg = matdesc->Get_Color_Array(0);
		for (int i=0; i<VertexCount; i++) {
			cload.Read(&color,sizeof(color));
			Vector4 col = DX8Wrapper::Convert_Color(dcg[i]);
			col.X *= (float)color.R / 255.0f;
			col.Y *= (float)color.G / 255.0f;
			col.Z *= (float)color.B / 255.0f;
			dcg[i] = DX8Wrapper::Convert_Color(col);
		}
	}

	matdesc->Set_DCG_Source(context->CurPass,VertexMaterialClass::COLOR1);
	return true;
}

bool MeshModelClass::read_stage_texcoords(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
    unsigned elementcount;
    Vector2 *uvs;
    W3dTexCoordStruct texcoord;
    MeshMatDescClass *matdesc = DefMatDesc;

    if (DefMatDesc->Has_UV(context->CurPass, context->CurTexStage)) {
        matdesc = &(context->AlternateMatDesc);
    }

    elementcount = cload.Cur_Chunk_Length() / sizeof(W3dTexCoordStruct);
    uvs = context->Get_Temporary_UV_Array(elementcount);

    if (uvs != NULL) {
        for (unsigned i = 0; i < elementcount; i++) {
            cload.Read(&texcoord, sizeof(texcoord));
            uvs[i].X = texcoord.U;
            uvs[i].Y = 1.0f - texcoord.V;
        }
    }

    matdesc->Install_UV_Array(context->CurPass, context->CurTexStage, uvs, elementcount);
    return true;
}

bool MeshModelClass::read_texture_stage(ChunkLoadClass &cload,MeshLoadContextClass *context)
{
	while (cload.Open_Chunk()) {
		bool error = true;
		switch (cload.Cur_Chunk_ID()) {
			case W3D_CHUNK_TEXTURE_IDS:
				error = read_texture_ids(cload,context);
				break;

			case W3D_CHUNK_STAGE_TEXCOORDS:
			case W3D_CHUNK_TEXCOORDS:
				error = read_stage_texcoords(cload,context);
				break;

			case W3D_CHUNK_PER_FACE_TEXCOORD_IDS:
				error = read_per_face_texcoord_ids(cload,context);
				break;
		}

		if (error != true) {
			return error;
		}
		cload.Close_Chunk();
	}

	context->CurTexStage++;
	// Reconstruction shaping: retain the direct memory increment at the tail.
	// The compiler barrier emits no instruction.
	_ReadWriteBarrier();
	return true;
}
