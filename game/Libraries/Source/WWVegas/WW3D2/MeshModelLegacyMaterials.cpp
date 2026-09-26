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
// BFME per-triangle legacy materials: 0x0096E3E0, complete 674 bytes.
// Mesh chunk 0x21 selects dispatcher arm 0x00970001, which calls this body.
// GeneralsMD meshmdlio.cpp supplies the material-index algorithm. BFME keeps
// owning texture handles, 16-bit polygon indices and Boolean load status.
// Context Header.NumMaterials is +0x30; vector counts are +0xBC/+0xD4/+0x104.
// The current material descriptor is MeshModel+0x9C. The final failure RET 8
// ends at 0x0096E681, before padding at 0x0096E682.
#include "w3d_file.h"
#include "shader.h"
#include "vector.h"
#include "sharebuf.h"
#include "vector3i.h"
typedef Vector3i16 TriIndex;

class VertexMaterialClass;

class TextureClass {
public:
    void Add_Ref() { ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4); }
    void Release_Ref();
};

class BfmeHandleCX {
public:
    TextureClass *p;

    BfmeHandleCX() : p(0) {}
    BfmeHandleCX(const BfmeHandleCX &other) : p(other.p) {
        if (p) {
            p->Add_Ref();
        }
    }
    bool operator==(const BfmeHandleCX &other) const { return p==other.p; }
    bool operator!=(const BfmeHandleCX &other) const { return p!=other.p; }
    ~BfmeHandleCX() {
        if (p) {
            p->Release_Ref();
        }
    }
};

class ChunkLoadClass {
public:
    unsigned long Cur_Chunk_Length();
    unsigned long Cur_Chunk_ID();
    bool Open_Chunk();
    bool Close_Chunk();
    unsigned long Read(void *buffer, unsigned long bytes);
};

class MeshMatDescClass {
public:
    void Set_Single_Shader(ShaderClass shader, int pass);
    void Set_Shader(int index, ShaderClass shader, int pass);
    void Set_Single_Material(VertexMaterialClass *material, int pass);
    void Set_Material(int index, VertexMaterialClass *material, int pass);
    void Set_Single_Texture(const BfmeHandleCX &texture, int pass, int stage);
    void Set_Texture(int index, const BfmeHandleCX &texture, int pass, int stage);
};

class MeshLoadContextClass {
    friend class MeshModelClass;
    struct LegacyMaterialClass {
        void *Name;
        int VertexMaterialIdx;
        int ShaderIdx;
        int TextureIdx;
    };
    W3dMeshHeader3Struct Header;
    W3dTexCoordStruct *TexCoords;
    W3dMaterialInfoStruct MatInfo;
    unsigned long PrelitChunkID;
    int CurPass;
    int CurTexStage;
    DynamicVectorClass<LegacyMaterialClass *> LegacyMaterials;
    DynamicVectorClass<ShaderClass> Shaders;
    DynamicVectorClass<VertexMaterialClass *> VertexMaterials;
    DynamicVectorClass<unsigned long> VertexMaterialCrcs;
    DynamicVectorClass<BfmeHandleCX> Textures;
    int Vertex_Material_Count() { return VertexMaterials.Count(); }
    int Texture_Count() { return Textures.Count(); }
    int Shader_Count() { return Shaders.Count(); }
    BfmeHandleCX Peek_Legacy_Texture(int index);
    ShaderClass Peek_Legacy_Shader(int legacy_material_index) {
        int si=LegacyMaterials[legacy_material_index]->ShaderIdx;
        return Shaders[si];
    }
    VertexMaterialClass *Peek_Legacy_Vertex_Material(int legacy_material_index) {
        int vi=LegacyMaterials[legacy_material_index]->VertexMaterialIdx;
        if (vi != -1) return VertexMaterials[vi];
        return 0;
    }
};
class MeshModelClass {
    unsigned char beforePolyCount[0x24];
    int PolyCount;
    int VertexCount;
    ShareBufferClass<TriIndex> *Poly;
    unsigned char beforeCurMatDesc[0x9c - 0x30];
    MeshMatDescClass *CurMatDesc;
    TriIndex *get_polys() { return Poly->Get_Array(); }
    int Get_Polygon_Count() const { return PolyCount; }
    void Set_Single_Material(VertexMaterialClass *material, int pass=0) { CurMatDesc->Set_Single_Material(material,pass); }
    void Set_Material(int index, VertexMaterialClass *material, int pass=0) { CurMatDesc->Set_Material(index,material,pass); }
    void Set_Single_Texture(const BfmeHandleCX &texture,int pass=0,int stage=0) { CurMatDesc->Set_Single_Texture(texture,pass,stage); }
    void Set_Texture(int index,const BfmeHandleCX &texture,int pass=0,int stage=0) { CurMatDesc->Set_Texture(index,texture,pass,stage); }
    void Set_Single_Shader(ShaderClass shader,int pass=0) { CurMatDesc->Set_Single_Shader(shader,pass); }
    void Set_Shader(int index,ShaderClass shader,int pass=0) { CurMatDesc->Set_Shader(index,shader,pass); }
protected:
    bool read_per_tri_materials(ChunkLoadClass &, MeshLoadContextClass *);
};

bool MeshModelClass::read_per_tri_materials(ChunkLoadClass & cload,MeshLoadContextClass * context)
{
	if (context->Header.NumMaterials == 1) return true;

	TriIndex * polys = get_polys();

	bool multi_mtl = (context->Vertex_Material_Count() > 1);
	bool multi_tex = (context->Texture_Count() > 1);
	bool multi_shad = (context->Shader_Count() > 1);

	if (!multi_mtl) {
		Set_Single_Material(context->Peek_Legacy_Vertex_Material(0));
	}
	if (!multi_tex) {
		Set_Single_Texture(context->Peek_Legacy_Texture(0));
	}
	if (!multi_shad) {
		Set_Single_Shader(context->Peek_Legacy_Shader(0));
	}

	/*
	** Read in each polygon's material id and assign pointer to the
	** shader, texture, and vertex material as needed.
	*/
	for (int i=0; i<Get_Polygon_Count(); i++) {

		// read in the mat id for this poly
		uint16 matid;

		if (cload.Read(&matid,sizeof(uint16)) != sizeof(uint16)) {
			return false;
		}

		if (multi_shad) {
			Set_Shader(i,context->Peek_Legacy_Shader(matid));
		}
		if (multi_tex) {
			Set_Texture(i,context->Peek_Legacy_Texture(matid));
		}
		if (multi_mtl) {
			Set_Material(polys[i].I,context->Peek_Legacy_Vertex_Material(matid));
			Set_Material(polys[i].J,context->Peek_Legacy_Vertex_Material(matid));
			Set_Material(polys[i].K,context->Peek_Legacy_Vertex_Material(matid));
		}
	}

	return true;
}


