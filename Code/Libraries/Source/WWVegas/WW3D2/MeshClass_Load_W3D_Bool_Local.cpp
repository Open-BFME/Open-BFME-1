// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /Ireference/shims/sweep
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
// BFME MeshClass::Load_W3D at retail 0x0092D0D0, complete 594-byte body.
//
// The named prototype-loader caller at 0x00970CD0 declares this member as a
// bool and tests AL after the call.  The retail body also returns AL
// and ends with RET 4.  The shared ZH mesh.h declaration uses WW3DErrorType,
// so this TU keeps the BFME bool ABI local.  MeshModelClass::Load_W3D is the
// already-matched BFME bool ABI at 0x009702F0; the local model view preserves
// its primary vtable slot (+8), W3dAttributes (+0x20), PolyCount (+0x24), and
// CurMatDesc (+0x9c).  MeshClass::Model is proven at +0xc8 by its matched
// constructor/destructor and the same prototype-loader caller.

#define Set_Alpha bfmeSlot108
#define Set_Additive bfmeSlot110
#define _bfme_ro_flag116 bfmeSlot118
#include "rendobj.h"
#include "meshmatdesc.h"
#include "w3d_file.h"
#include "w3derr.h"
#include "wwdebug.h"
#undef Set_Alpha
#undef Set_Additive
#undef _bfme_ro_flag116

class ChunkLoadClass;
class MeshClass;

// ABI slice of the already-matched BFME MeshModelClass.  RefCountClass and
// MultiListObjectClass are retained so Release_Ref and the virtual Load_W3D
// slot have the retail arrangement; unused members remain opaque padding.
class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
public:
	virtual ~MeshGeometryClass(void);
	virtual bool Load_W3D(ChunkLoadClass &cload);

	int Get_Flag(int flag) { return Flags & flag; }

protected:
	char _base[8];				// through this+0x17
	int Flags;					// this+0x18
	char SortLevel;
	unsigned char _sort_padding[3];
	unsigned int W3dAttributes;		// this+0x20
	int PolyCount;					// this+0x24
	int VertexCount;
	char _tail[0x94 - 0x2c];			// MeshGeometryClass ends at +0x94

	friend class MeshClass;
};

typedef char VerifyMeshGeometryClassSize[
	(sizeof(MeshGeometryClass) == 0x94) ? 1 : -1];

class MeshModelClass : public MeshGeometryClass
{
public:
	enum { SORT = 0x10 };

	MeshModelClass(void);
	virtual ~MeshModelClass(void);
	virtual bool Load_W3D(ChunkLoadClass &cload);

	bool Has_Shader_Array(int pass) const
	{
		return CurMatDesc->Has_Shader_Array(pass);
	}

	int Get_Polygon_Count(void) const { return PolyCount; }
	ShaderClass Get_Shader(int pidx, int pass = 0) const
	{
		return CurMatDesc->Get_Shader(pidx, pass);
	}
	ShaderClass Get_Single_Shader(int pass = 0) const
	{
		return CurMatDesc->Get_Single_Shader(pass);
	}

protected:
	MeshMatDescClass *DefMatDesc;		// this+0x94
	MeshMatDescClass *AlternateMatDesc;	// this+0x98
	MeshMatDescClass *CurMatDesc;		// this+0x9c
	char _tail[0xc8 - 0xa0];			// MeshModelClass ends at +0xc8
};

typedef char VerifyMeshModelClassSize[
	(sizeof(MeshModelClass) == 0xc8) ? 1 : -1];

// Only Model is used by this body.  The inline Free is intentionally limited
// to the BFME field proven by the retail entry; the ZH DecalMesh member is not
// part of this ABI slice and would add the extra release seen in the prior
// enum-ABI probe.
class MeshClass : public W3DMPO, public RenderObjClass
{
public:
	bool Load_W3D(ChunkLoadClass &cload);

protected:
	void Free(void)
	{
		if (Model) {
			Model->Release_Ref();
			Model = NULL;
		}
	}

private:
	MeshModelClass *Model;				// this+0xc8
	char _tail[0x318 - 0xcc];
};

typedef char VerifyMeshClassSize[(sizeof(MeshClass) == 0x318) ? 1 : -1];

// ?Load_W3D@MeshClass@@QAE_NAAVChunkLoadClass@@@Z
bool MeshClass::Load_W3D(ChunkLoadClass &cload)
{
	Free();

	Model = NEW_REF(MeshModelClass,());
	if (Model == NULL) {
		WWDEBUG_SAY(("MeshClass::Load - Failed to allocate model\r\n"));
		return false;
	}

	if (!Model->Load_W3D(cload)) {
		Free();
		return false;
	}

	int col_bits = (Model->W3dAttributes & W3D_MESH_FLAG_COLLISION_TYPE_MASK) >> W3D_MESH_FLAG_COLLISION_TYPE_SHIFT;
	Set_Collision_Type(col_bits << 1);
	Set_Hidden(Model->W3dAttributes & W3D_MESH_FLAG_HIDDEN);

	int is_translucent = Model->Get_Flag(0x10);
	int is_alpha = 0;
	int is_additive = 0;
	if (Model->Has_Shader_Array(0)) {
		for (int i = 0; i < Model->Get_Polygon_Count(); i++) {
			ShaderClass shader = Model->Get_Shader(i, 0);
			is_translucent |= (shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_ENABLE);
			is_alpha |= (shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO ||
							 shader.Get_Src_Blend_Func() != ShaderClass::SRCBLEND_ONE) &&
							(shader.Get_Alpha_Test() != ShaderClass::ALPHATEST_ENABLE);
			is_additive |= (shader.Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_ONE &&
							shader.Get_Src_Blend_Func() == ShaderClass::SRCBLEND_ONE);
		}
	} else {
		ShaderClass shader = Model->Get_Single_Shader(0);
		is_translucent |= (shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_ENABLE);
		is_alpha |= (shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO ||
						 shader.Get_Src_Blend_Func() != ShaderClass::SRCBLEND_ONE) &&
						(shader.Get_Alpha_Test() != ShaderClass::ALPHATEST_ENABLE);
		is_additive |= (shader.Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_ONE &&
						 shader.Get_Src_Blend_Func() == ShaderClass::SRCBLEND_ONE);
	}
	// Raw calls use vtable byte offsets 0x1b0, 0x1b8 and 0x1d8.
	// TU-local names describe those slots without borrowing the shared
	// header's differing semantic names. Each takes one 32-bit flag.
	bfmeSlot108(is_translucent);
	bfmeSlot110(is_alpha);
	bfmeSlot118(is_additive);

	return true;
}
