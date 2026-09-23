// ?read_v3_materials@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
// partial score=0.4640883977900553 date=2026-09-23
// ?read_v3_materials@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
// Resumed from reverse/attempts/0x0096f5b0.cpp; reconstruction, NOT a match.
// Copyright 2025 Electronic Arts Inc.; GPL-3.0-or-later, as in the source twin.
// Identity: MeshModelClass::read_chunks call at RVA 0x0096FFEA, the matching
// GeneralsMD meshmdlio.cpp algorithm, and the landed Add_Legacy_Material caller ABI.
// Decoded extent: 1448 bytes. RET 8 at +0x58B precedes the cold failure tail;
// the final JMP at +0x5A6 ends at +0x5A8, followed by eight INT3 bytes.
//
// Changes from the saved body: ordinary new (retail does not branch to Error
// on allocation failure), full-expression texture temporaries, the real
// chunk/texture/vertex-material headers, private context callee declarations,
// and the MeshModel forwarding setters from the source twin.
//
// Remaining wall: retail keeps the current texture in ESI across the chunk
// loop and early failures before assignment skip its null cleanup. This body
// reloads the texture on failure and has two additional cleanup entry paths.
// The stack frame is now the correct 0x57C and the local offsets agree.
// Instruction alignment (not acceptance) identifies a 13-byte deficit before
// the default-material setters and ten additional bytes in failure cleanup.
// Assignment visibility, base/derived handle destructors, destructor-local
// pointer copies, ChunkLoad throw annotations, /Ob1, /G6, /GX, /EHsc- do not
// fix the residue. /Oa, /Ow, /Og-, /G7 and /EHa diverge further.
// No assembly, byte emission or volatile shaping is used.

// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ibuild/toolchains/dx81/include
#include "w3d_file.h"
#include "vector.h"
#include "vector3.h"
#include "shader.h"
#include "wwstring.h"
#include "d3d8.h"
#include <new.h>

#include "chunkio.h"

#include "texture.h"

class BFMEWaterTrackTextureHandle
{
public:
	BFMEWaterTrackTextureHandle() : m_texture(0) {}
	BFMEWaterTrackTextureHandle(const BFMEWaterTrackTextureHandle &other) : m_texture(other.m_texture)
	{
		if (m_texture)
			++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(m_texture) + 4);
	}
	~BFMEWaterTrackTextureHandle()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}
	TextureClass *m_texture;
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char *, int, int);

class BfmeHandleCX
{
public:
	BfmeHandleCX() : p(0) {}
	~BfmeHandleCX()
	{
		if (p)
			p->Release_Ref();
	}
	bool operator==(const BfmeHandleCX &other) const { return p == other.p; }
	bool operator!=(const BfmeHandleCX &other) const { return p != other.p; }
	BfmeHandleCX &operator=(const BFMEWaterTrackTextureHandle &other);
	TextureClass *p;
};

#pragma comment(linker, "/alternatename:??4BfmeHandleCX@@QAEAAV0@ABVBFMEWaterTrackTextureHandle@@@Z=?j_0003652a@@YAXXZ")

class Rva006C07A0
{
public:
	void go();
	TextureClass *p;
};

#include "vertmaterial.h"

class MeshMatDescClass
{
public:
	void Set_Single_Material(VertexMaterialClass *, int);
	void Set_Single_Shader(ShaderClass, int);
	void Set_Single_Texture(const BfmeHandleCX &, int, int);
};

class MeshLoadContextClass
{
public:
	struct LegacyMaterialClass;
	W3dMeshHeader3Struct Header;
	W3dTexCoordStruct *TexCoords;
	W3dMaterialInfoStruct MatInfo;
	unsigned int PrelitChunkID;
	int CurPass;
	int CurTexStage;
	DynamicVectorClass<LegacyMaterialClass *> LegacyMaterials;
	DynamicVectorClass<ShaderClass> Shaders;
	DynamicVectorClass<VertexMaterialClass *> VertexMaterials;
	DynamicVectorClass<unsigned long> VertexMaterialCrcs;
	DynamicVectorClass<BfmeHandleCX> Textures;
private:
	friend class MeshModelClass;
	void Add_Legacy_Material(ShaderClass, VertexMaterialClass *, const BfmeHandleCX &);
	BfmeHandleCX Peek_Texture(int index);
	int Vertex_Material_Count() { return VertexMaterials.Count(); }
	int Texture_Count() { return Textures.Count(); }
	int Shader_Count() { return Shaders.Count(); }
	VertexMaterialClass *Peek_Vertex_Material(int index) { return VertexMaterials[index]; }
	ShaderClass Peek_Shader(int index) { return Shaders[index]; }
};

class MeshModelClass
{
	unsigned char _base[0x18];
	int Flags;
	unsigned char _before_descriptors[0x94 - 0x1c];
	MeshMatDescClass *DefMatDesc;
	MeshMatDescClass *AlternateMatDesc;
	MeshMatDescClass *CurMatDesc;
protected:
	bool read_v3_materials(ChunkLoadClass &, MeshLoadContextClass *);
	void Set_Single_Texture(const BfmeHandleCX &tex,int pass=0,int stage=0) { CurMatDesc->Set_Single_Texture(tex,pass,stage); }
	void Set_Single_Material(VertexMaterialClass *vmat,int pass=0) { CurMatDesc->Set_Single_Material(vmat,pass); }
	void Set_Single_Shader(ShaderClass shader,int pass=0) { CurMatDesc->Set_Single_Shader(shader,pass); }
	void Set_Flag(int flag, bool onoff) { if (onoff) Flags |= flag; else Flags &= ~flag; }
};

bool MeshModelClass::read_v3_materials(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	for (unsigned int mi = 0; mi < context->Header.NumMaterials; ++mi) {
		if (!cload.Open_Chunk()) goto Error;
		if (cload.Cur_Chunk_ID() != W3D_CHUNK_MATERIAL3) goto Error;

		VertexMaterialClass *vmat = 0;
		ShaderClass shader(0x0010441b);
		BfmeHandleCX texture;
		char name[256];

		if (!cload.Open_Chunk()) goto Error;
		if (cload.Cur_Chunk_ID() != W3D_CHUNK_MATERIAL3_NAME) goto Error;
		cload.Read(name, cload.Cur_Chunk_Length());
		if (!cload.Close_Chunk()) goto Error;

		if (!cload.Open_Chunk()) goto Error;
		W3dMaterial3Struct material;
		if (cload.Cur_Chunk_ID() != W3D_CHUNK_MATERIAL3_INFO) goto Error;
		if (cload.Read(&material, sizeof(material)) != sizeof(material)) goto Error;
		vmat = new VertexMaterialClass;
		vmat->Init_From_Material3(material);
		vmat->Set_Name(name);
		shader.Init_From_Material3(material);
		if (shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO)
			Set_Flag(0x10, true);
		if (!cload.Close_Chunk()) goto Error;

		while (cload.Open_Chunk()) {
			if (cload.Cur_Chunk_ID() == W3D_CHUNK_MATERIAL3_DC_MAP) {
				char filename[0x200];
				if (!cload.Open_Chunk()) goto Error;
				if (cload.Cur_Chunk_ID() != W3D_CHUNK_MAP3_FILENAME) goto Error;
				if (cload.Cur_Chunk_Length() >= sizeof(filename)) goto Error;
				cload.Read(filename, cload.Cur_Chunk_Length());
				if (!cload.Close_Chunk()) goto Error;
				W3dMap3Struct mapinfo;
				if (!cload.Open_Chunk()) goto Error;
				if (cload.Cur_Chunk_ID() != W3D_CHUNK_MAP3_INFO) goto Error;
				if (cload.Read(&mapinfo, sizeof(mapinfo)) != sizeof(mapinfo)) goto Error;
				if (!cload.Close_Chunk()) goto Error;
				texture = BFMEGetWaterTrackTexture(filename, 0, 0);
				shader.Set_Texturing(ShaderClass::TEXTURING_ENABLE);
			} else if (cload.Cur_Chunk_ID() == W3D_CHUNK_MATERIAL3_SI_MAP) {
				Vector3 diffuse;
				vmat->Get_Diffuse(&diffuse);
				if (diffuse == Vector3(0, 0, 0)) {
					char filename[0x200];
					if (!cload.Open_Chunk()) goto Error;
					if (cload.Cur_Chunk_ID() != W3D_CHUNK_MAP3_FILENAME) goto Error;
					if (cload.Cur_Chunk_Length() >= sizeof(filename)) goto Error;
					cload.Read(filename, cload.Cur_Chunk_Length());
					if (!cload.Close_Chunk()) goto Error;
					W3dMap3Struct mapinfo;
					if (!cload.Open_Chunk()) goto Error;
					if (cload.Cur_Chunk_ID() != W3D_CHUNK_MAP3_INFO) goto Error;
					if (cload.Read(&mapinfo, sizeof(mapinfo)) != sizeof(mapinfo)) goto Error;
					if (!cload.Close_Chunk()) goto Error;
					texture = BFMEGetWaterTrackTexture(filename, 0, 0);
					shader.Set_Texturing(ShaderClass::TEXTURING_ENABLE);
					shader.Set_Dst_Blend_Func(ShaderClass::DSTBLEND_ONE);
					shader.Set_Src_Blend_Func(ShaderClass::SRCBLEND_ONE);
					shader.Set_Primary_Gradient(ShaderClass::GRADIENT_DISABLE);
				}
			}
			cload.Close_Chunk();
		}

		if (shader.Get_Texturing() == ShaderClass::TEXTURING_DISABLE) {
			Vector3 color;
			vmat->Get_Diffuse(&color);
			vmat->Set_Ambient(color);
			vmat->Set_Diffuse(Vector3(0, 0, 0));
		}
		context->Add_Legacy_Material(shader, vmat, texture);
		vmat->Release_Ref();
		reinterpret_cast<Rva006C07A0 *>(&texture)->go();
		cload.Close_Chunk();
	}

	if (context->Vertex_Material_Count() >= 1)
		Set_Single_Material(context->Peek_Vertex_Material(0), 0);
	if (context->Texture_Count() >= 1) {
		Set_Single_Texture(context->Peek_Texture(0), 0, 0);
	}
	if (context->Shader_Count() >= 1)
		Set_Single_Shader(context->Peek_Shader(0), 0);
	return true;

Error:
	return false;
}
