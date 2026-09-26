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
// BFME mesh-load context constructor: 0x00970180, full 358 bytes.
// MeshModelClass::Load_W3D calls this at 0x00970341. It initializes the
// original typed vectors, alternate material descriptor and temporary UVs,
// then clears the W3D headers and pass state. The owning texture vector is
// at +0xF4, alternate descriptor +0x10C and temporary UV vector +0x200.
// RET at 0x009702E5 is followed by INT3 padding. The previous 61-byte
// claim ended inside the first container's initialization.
// Algorithm and member order: GeneralsMD WW3D2/meshmdlio.cpp.
#include "vector.h"
#include "simplevec.h"
#include "shader.h"
#include "w3d_file.h"
#include "vector2.h"

class TextureClass
{
public:
	void Add_Ref(void) { ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4); }
	void Release_Ref(void);
};

class BfmeHandleCX
{
public:
	BfmeHandleCX(void) : p(0) {}
	BfmeHandleCX(const BfmeHandleCX &other) : p(other.p) { if (p) p->Add_Ref(); }
	~BfmeHandleCX(void) { if (p) p->Release_Ref(); }
	BfmeHandleCX &operator=(const BfmeHandleCX &other)
	{
		if (other.p) other.p->Add_Ref();
		if (p) p->Release_Ref();
		p = other.p;
		return *this;
	}
	bool operator==(const BfmeHandleCX &other) const { return p == other.p; }
	bool operator!=(const BfmeHandleCX &other) const { return p != other.p; }
	TextureClass *operator->() const { return p; }
	TextureClass *p;
};

class VertexMaterialClass
{
public:
	virtual void Delete_This();
	VertexMaterialClass();
	void Release_Ref(void) { if (--RefCount == 0) Delete_This(); }
private:
	int RefCount;
	unsigned char fields[0x6c - 8];
};
class MeshMatDescClass
{
public:
	MeshMatDescClass();
	~MeshMatDescClass();
private:
	unsigned char Data[0xf4];
};



class MeshLoadContextClass
{
private:
	MeshLoadContextClass(void);
	~MeshLoadContextClass(void);
	W3dMeshHeader3Struct Header;
	W3dTexCoordStruct *TexCoords;
	W3dMaterialInfoStruct MatInfo;
	unsigned int PrelitChunkID;
	int CurPass;
	int CurTexStage;
	struct LegacyMaterialClass;
	DynamicVectorClass<LegacyMaterialClass *> LegacyMaterials;
	DynamicVectorClass<ShaderClass> Shaders;
	DynamicVectorClass<VertexMaterialClass *> VertexMaterials;
	DynamicVectorClass<unsigned long> VertexMaterialCrcs;
	DynamicVectorClass<BfmeHandleCX> Textures;
	MeshMatDescClass AlternateMatDesc;
	SimpleVecClass<Vector2> TempUVArray;
	bool LoadedDIG;
};

MeshLoadContextClass::MeshLoadContextClass(void)
{
	memset(&Header,0,sizeof(Header));
	memset(&MatInfo,0,sizeof(MatInfo));
	PrelitChunkID = 0xffffffff;
	CurPass = 0;
	CurTexStage = 0;
	TexCoords = NULL;
	LoadedDIG = false;
}

