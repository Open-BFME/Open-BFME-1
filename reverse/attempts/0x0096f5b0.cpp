// ?read_v3_materials@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
// partial score=0.43 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ibuild/toolchains/dx81/include
#include "w3d_file.h"
#include "vector.h"
#include "vector3.h"
#include "shader.h"
#include "wwstring.h"
#include "d3d8.h"
#include <new.h>

class ChunkLoadClass
{
public:
	unsigned long Cur_Chunk_ID();
	unsigned long Cur_Chunk_Length();
	unsigned long Read(void *, unsigned long);
	bool Open_Chunk();
	bool Close_Chunk();
};

class TextureClass
{
public:
	void Add_Ref() { ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4); }
	void Release_Ref();
};

class BFMEWaterTrackTexture
{
public:
	void Release_Ref();
};

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
			((BFMEWaterTrackTexture *)m_texture)->Release_Ref();
	}
	TextureClass *m_texture;
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char *, int, int);
extern const float BfmeZeroRange;

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

class VertexMaterialClass
{
	int RefCount;
	D3DMATERIAL8 *Material;
	unsigned int Flags;
	unsigned char _before_name[0x1c - 0x10];
	StringClass Name;
	unsigned char _before_dirty[0x68 - 0x20];
	bool CRCDirty;
public:
	virtual void Delete_This();
	VertexMaterialClass();
	void Init_From_Material3(const W3dMaterial3Struct &);
	void Set_Name(const char *name) { Name = name; }
	void Get_Diffuse(Vector3 *color) const;
	void Set_Ambient(const Vector3 &color)
	{
		CRCDirty = true;
		Material->Ambient.r = color.X;
		Material->Ambient.g = color.Y;
		Material->Ambient.b = color.Z;
	}
	void Set_Diffuse(const Vector3 &color)
	{
		CRCDirty = true;
		Material->Diffuse.r = color.X;
		Material->Diffuse.g = color.Y;
		Material->Diffuse.b = color.Z;
	}
	void Release_Ref() { if (--*reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 4) == 0) Delete_This(); }
};

class BfmeTexVGS
{
};

class BfmeMeshVGT
{
public:
	void bfmeSetVGT(BfmeTexVGS **source, int pass, int stage);
};

class MeshMatDescClass : public BfmeMeshVGT
{
public:
	void Set_Single_Material(VertexMaterialClass *, int);
	void Set_Single_Shader(ShaderClass, int);
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
public:
	void Add_Legacy_Material(ShaderClass, VertexMaterialClass *, const BfmeHandleCX &);
	BfmeHandleCX Peek_Texture(int index) const;
	int Vertex_Material_Count() const { return VertexMaterials.Count(); }
	int Texture_Count() const { return Textures.Count(); }
	int Shader_Count() const { return Shaders.Count(); }
	VertexMaterialClass *Peek_Vertex_Material(int index) const { return VertexMaterials[index]; }
	ShaderClass Peek_Shader(int index) const { return Shaders[index]; }
};

class Gen_0096D080
{
public:
	BfmeHandleCX bfmeGet(int index) const;
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
	void Set_Flag(int flag, bool onoff) { if (onoff) Flags |= flag; else Flags &= ~flag; }
};

bool MeshModelClass::read_v3_materials(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	for (unsigned int mi = 0; mi < context->Header.NumMaterials; ++mi) {
		if (!cload.Open_Chunk()) goto Error;
		if (cload.Cur_Chunk_ID() != W3D_CHUNK_MATERIAL3) goto Error;

		void *raw_vmat;
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
		raw_vmat = ::operator new(sizeof(VertexMaterialClass));
		if (!raw_vmat) goto Error;
		vmat = new(raw_vmat) VertexMaterialClass;
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
				BFMEWaterTrackTextureHandle loaded = BFMEGetWaterTrackTexture(filename, 0, 0);
				texture = loaded;
				shader.Set_Texturing(ShaderClass::TEXTURING_ENABLE);
			} else if (cload.Cur_Chunk_ID() == W3D_CHUNK_MATERIAL3_SI_MAP) {
				Vector3 diffuse;
				vmat->Get_Diffuse(&diffuse);
				if (diffuse == Vector3(BfmeZeroRange, BfmeZeroRange, BfmeZeroRange)) {
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
					BFMEWaterTrackTextureHandle loaded = BFMEGetWaterTrackTexture(filename, 0, 0);
					texture = loaded;
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
		CurMatDesc->Set_Single_Material(context->Peek_Vertex_Material(0), 0);
	if (context->Texture_Count() >= 1) {
		BfmeHandleCX texture = reinterpret_cast<const Gen_0096D080 *>(context)->bfmeGet(0);
		reinterpret_cast<BfmeMeshVGT *>(CurMatDesc)->bfmeSetVGT(
			reinterpret_cast<BfmeTexVGS **>(&texture.p), 0, 0);
	}
	if (context->Shader_Count() >= 1)
		CurMatDesc->Set_Single_Shader(context->Peek_Shader(0), 0);
	return true;

Error:
	return false;
}
