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
// BFME MeshLoadContextClass::Add_Legacy_Material: RVA 0x0096F210,
// complete 922 bytes. The version-3 material reader calls this at 0x0096FA3C
// with a shader, a vertex material and a borrowed owning-texture handle.
// The original GeneralsMD algorithm deduplicates shaders by value, vertex
// materials by CRC, and textures by identity or case-insensitive name.
// BFME texture names are returned as StringClass values; both temporaries
// are destroyed after comparison. The handle getter at 0x008FF5B0 calls
// the texture's name slot and the named StringClass copy constructor.
// Actual DynamicVectorClass layout is used at offsets 94/AC/C4/DC/F4.
// Vertex material refs/CRC/dirty are +4/+64/+68; texture refs are 16-bit +4.
// RET 12 at RVA 0x0096F5A7 ends before six INT3 bytes at 0x0096F5AA.
//
// BFME MeshModelClass::read_v3_materials: RVA 0x0096F5B0, complete 1448
// bytes, directly after Add_Legacy_Material as in the original meshmdlio.cpp.
// MeshModelClass::read_chunks dispatches W3D chunk 0x15 to it at 0x0096FFEA.
// RET 8 at +0x58B; the cold failure tail's JMP ends at +0x5A8.
// The two bodies share this TU on purpose: retail keeps the texture handle's
// pointer in ESI across the chunk loop, and skips its cleanup on early
// failures, only because VC7.1 can see that Add_Legacy_Material (and the
// handle name getter at 0x008FF5B0 it calls), the handle assignment
// (0x005D2040) and the guarded release (0x006C07A0) never retain the
// handle's address. With any of them opaque the body reloads the pointer on
// every failure path and grows two extra cleanup entries. All of them stay
// out of line, as in retail; the assignment and release are named after
// their ledger rows because neither identity is recovered, so the reader
// reaches them through those address-named views of the handle's pointer
// (the getter's result is bound as a full-expression temporary, as retail
// passes it straight from EAX). Retail allocates the vertex material with
// the global operator new (0x00881F30), 0x6C bytes, so the view below has no
// memory-pool glue; its name is the StringClass at +0x1C.
#include "w3d_file.h"
#include "wwstring.h"
#include "shader.h"
#include "vector.h"
#include "vector3.h"
#include "chunkio.h"

class VertexMaterialClass {
public:
    VertexMaterialClass();
    virtual void Delete_This();
    void Add_Ref() { ++RefCount; }
    void Release_Ref() { RefCount--; if (RefCount == 0) Delete_This(); }
    void Init_From_Material3(const W3dMaterial3Struct &mat3);
    void Set_Name(const char *name) { Name = name; }
    void Set_Ambient(const Vector3 &color);
    void Get_Diffuse(Vector3 *set_color) const;
    void Set_Diffuse(const Vector3 &color);
    unsigned long Get_CRC() const {
        if (CRCDirty) {
            CRC = Compute_CRC();
            CRCDirty = false;
        }
        return CRC;
    }
private:
    int RefCount;
    unsigned char beforeName[0x1c - 8];
    StringClass Name;
    unsigned char beforeCRC[0x64 - 0x20];
    mutable unsigned long CRC;
    mutable bool CRCDirty;
    unsigned long Compute_CRC() const;
};

class TextureClass {
public:
    virtual const char *Get_Name() const;
    void Add_Ref() {
        ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
    }
    void Release_Ref();
};

class BFMEWaterTrackTextureHandle;

class BfmeHandleCX {
public:
    TextureClass *p;
    BfmeHandleCX() : p(0) {}
    BfmeHandleCX(const BfmeHandleCX &other) : p(other.p) {
        if (p) p->Add_Ref();
    }
    ~BfmeHandleCX() {
        if (p) p->Release_Ref();
    }
    BfmeHandleCX &operator=(const BfmeHandleCX &other) {
        if (other.p) other.p->Add_Ref();
        if (p) p->Release_Ref();
        p = other.p;
        return *this;
    }
    StringClass Get_Texture_Name() const {
        const char *name = p ? p->Get_Name() : 0;
        StringClass result(name);
        return result;
    }
    bool operator==(const BfmeHandleCX &other) const { return p == other.p; }
    bool operator!=(const BfmeHandleCX &other) const { return p != other.p; }
};

// The texture getter's ledger name gives its four-byte owning result its own
// type; the layout is the same pointer.
class BFMEWaterTrackTextureHandle {
public:
    TextureClass *p;
    ~BFMEWaterTrackTextureHandle() {
        if (p) p->Release_Ref();
    }
};

BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char *name, int, int);

// 0x005D2040: owning assignment, source reference first, old reference second.
class Gen_005D2040 {
public:
    TextureClass *p;
    Gen_005D2040 &operator=(const Gen_005D2040 &other) {
        if (other.p) other.p->Add_Ref();
        if (p) p->Release_Ref();
        p = other.p;
        return *this;
    }
};

// 0x006C07A0: release the reference and clear the slot.
class Rva006C07A0 {
public:
    TextureClass *p;
    void go() {
        if (p) {
            p->Release_Ref();
            p = 0;
        }
    }
};


class MeshLoadContextClass {
    struct LegacyMaterialClass {
        StringClass Name;
        int VertexMaterialIdx;
        int ShaderIdx;
        int TextureIdx;
        LegacyMaterialClass() : VertexMaterialIdx(0), ShaderIdx(0), TextureIdx(0) {}
    };
public:
    W3dMeshHeader3Struct Header;
private:
    unsigned char afterHeader[0x94 - sizeof(W3dMeshHeader3Struct)];
    DynamicVectorClass<LegacyMaterialClass *> LegacyMaterials;
    DynamicVectorClass<ShaderClass> Shaders;
    DynamicVectorClass<VertexMaterialClass *> VertexMaterials;
    DynamicVectorClass<unsigned long> VertexMaterialCrcs;
    DynamicVectorClass<BfmeHandleCX> Textures;

    int Add_Shader(ShaderClass shader) {
        int index = Shaders.Count();
        Shaders.Add(shader);
        return index;
    }
    int Add_Vertex_Material(VertexMaterialClass *vmat) {
        vmat->Add_Ref();
        int index = VertexMaterials.Count();
        VertexMaterials.Add(vmat);
        return index;
    }
    int Add_Texture(const BfmeHandleCX &tex) {
        int index = Textures.Count();
        Textures.Add(tex);
        return index;
    }
    void Add_Legacy_Material(ShaderClass, VertexMaterialClass *, const BfmeHandleCX &);
    BfmeHandleCX Peek_Texture(int index);
    int Vertex_Material_Count() { return VertexMaterials.Count(); }
    int Texture_Count() { return Textures.Count(); }
    int Shader_Count() { return Shaders.Count(); }
    VertexMaterialClass *Peek_Vertex_Material(int index) { return VertexMaterials[index]; }
    ShaderClass Peek_Shader(int index) { return Shaders[index]; }
    friend class MeshModelClass;
};

class MeshMatDescClass {
public:
    void Set_Single_Material(VertexMaterialClass *vmat, int pass);
    void Set_Single_Shader(ShaderClass shader, int pass);
    void Set_Single_Texture(const BfmeHandleCX &tex, int pass, int stage);
};

class MeshGeometryClass {
protected:
    void Set_Flag(int flag, bool onoff) { if (onoff) Flags |= flag; else Flags &= ~flag; }
    unsigned char beforeFlags[0x18];
    int Flags;
};

class MeshModelClass : public MeshGeometryClass {
public:
    enum { SORT = 0x10 };
protected:
    bool read_v3_materials(ChunkLoadClass &cload, MeshLoadContextClass *context);
    void Set_Single_Texture(const BfmeHandleCX &tex, int pass = 0, int stage = 0) { CurMatDesc->Set_Single_Texture(tex, pass, stage); }
    void Set_Single_Material(VertexMaterialClass *vmat, int pass = 0) { CurMatDesc->Set_Single_Material(vmat, pass); }
    void Set_Single_Shader(ShaderClass shader, int pass = 0) { CurMatDesc->Set_Single_Shader(shader, pass); }
private:
    unsigned char beforeMatDesc[0x94 - 0x1c];
    MeshMatDescClass *DefMatDesc;
    MeshMatDescClass *AlternateMatDesc;
    MeshMatDescClass *CurMatDesc;
};

void MeshLoadContextClass::Add_Legacy_Material(ShaderClass shader,VertexMaterialClass * vmat,const BfmeHandleCX &tex)
{
	// create a new legacy material
	LegacyMaterialClass * mat = new LegacyMaterialClass;

	// add the shader if it is unique
	for (int si=0; si<Shaders.Count(); si++) {
		if (Shaders[si] == shader) break;
	}
	if (si == Shaders.Count()) {
		mat->ShaderIdx = Add_Shader(shader);
	} else {
		mat->ShaderIdx = si;
	}

	// add the vertex material if it is unique
	if (vmat == NULL) {
		mat->VertexMaterialIdx = -1;
	} else {
		unsigned long crc = vmat->Get_CRC();
		for (int vi=0; vi<VertexMaterialCrcs.Count(); vi++) {
			if (VertexMaterialCrcs[vi] == crc) break;
		}
		if (vi == VertexMaterials.Count()) {
			mat->VertexMaterialIdx = Add_Vertex_Material(vmat);
			VertexMaterialCrcs.Add(crc);
			WWASSERT(VertexMaterialCrcs.Count() == VertexMaterials.Count());
		} else {
			mat->VertexMaterialIdx = vi;
		}
	}

	// add the texture if it is unique
	if (tex.p == NULL) {
		mat->TextureIdx = -1;
	} else {
		for (int ti=0; ti<Textures.Count(); ti++) {
			if (Textures[ti] == tex) break;
			if (_strcmpi(Textures[ti].Get_Texture_Name(),tex.Get_Texture_Name()) == 0) break;
		}
		if (ti == Textures.Count()) {
			mat->TextureIdx = Add_Texture(tex);
		} else {
			mat->TextureIdx = ti;
		}
	}

	LegacyMaterials.Add(mat);
}

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
			Set_Flag(MeshModelClass::SORT, true);
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
				reinterpret_cast<Gen_005D2040 &>(texture) = (const Gen_005D2040 &)BFMEGetWaterTrackTexture(filename, 0, 0);
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
					reinterpret_cast<Gen_005D2040 &>(texture) = (const Gen_005D2040 &)BFMEGetWaterTrackTexture(filename, 0, 0);
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
