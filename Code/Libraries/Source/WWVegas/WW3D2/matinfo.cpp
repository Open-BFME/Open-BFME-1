// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : MatInfo.h                                                    *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/matinfo.cpp                            $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 6/15/01 5:50p                                               $*
 *                                                                                             *
 *                    $Revision:: 10                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "matinfo.h"
#include "wwdebug.h"
#include "meshmdl.h"
#include "texture.h"

// ??0MaterialInfoClass@@ present-unmatched
MaterialInfoClass::MaterialInfoClass(void)
{
}

// ??0MaterialInfoClass@@ present-unmatched
MaterialInfoClass::MaterialInfoClass(const MaterialInfoClass & src)
{
	for (int mi=0; mi<src.VertexMaterials.Count(); mi++) {
		VertexMaterialClass * vmat;
		vmat = src.VertexMaterials[mi]->Clone();
		VertexMaterials.Add(vmat);
	}
	
	for (int ti=0; ti<src.Textures.Count(); ti++) {
		TextureClass * tex = src.Textures[ti];
		tex->Add_Ref();
		Textures.Add(tex);
	}
}


// ??1MaterialInfoClass@@UAE@XZ present-unmatched
MaterialInfoClass::~MaterialInfoClass(void)
{
	Free();
}


// ?Clone@MaterialInfoClass@@QBEPAV1@XZ present-unmatched
MaterialInfoClass * MaterialInfoClass::Clone(void) const
{ 
	return W3DNEW MaterialInfoClass(*this); 
}

// ?Add_Texture@MaterialInfoClass@@QAEHPAVTextureClass@@@Z present-unmatched
int MaterialInfoClass::Add_Texture(TextureClass * tex)
{
	WWASSERT(tex != NULL);
	tex->Add_Ref();
	int index = Textures.Count();
	Textures.Add(tex);
	return index;
}

// ?Get_Texture_Index@MaterialInfoClass@@QAEHPBD@Z present-unmatched
int MaterialInfoClass::Get_Texture_Index(const char * name)
{
	for (int i=0; i<Textures.Count(); i++) {
		if (stricmp(name,Textures[i]->Get_Texture_Name()) == 0) {
			return i;
		}
	}
	return -1;
}

// ?Get_Texture@MaterialInfoClass@@QAEPAVTextureClass@@H@Z present-unmatched
TextureClass * MaterialInfoClass::Get_Texture(int index)
{
	WWASSERT(index >= 0);
	WWASSERT(index < Textures.Count());
	Textures[index]->Add_Ref();
	return Textures[index];
}

/*

// ?Set_Texture_Reduction_Factor@MaterialInfoClass@@ present-unmatched
void MaterialInfoClass::Set_Texture_Reduction_Factor(float trf)
{
	for (int i = 0; i < Textures.Count(); i++) {
		Textures[i]->Set_Reduction_Factor(trf);
	}
}


// ?Process_Texture_Reduction@MaterialInfoClass@@ present-unmatched
void MaterialInfoClass::Process_Texture_Reduction(void)
{
	for (int i = 0; i < Textures.Count(); i++) {
		Textures[i]->Process_Reduction();
	}
}
*/
// ?Free@MaterialInfoClass@@AAEXXZ present-unmatched
void MaterialInfoClass::Free(void) 
{
	int i;
	
	for (i=0; i<VertexMaterials.Count(); i++) {
		REF_PTR_RELEASE(VertexMaterials[i]);
	}
	VertexMaterials.Delete_All(); 

	for (i=0; i<Textures.Count(); i++) {
		REF_PTR_RELEASE(Textures[i]);
	}
	Textures.Delete_All();
}


// ??0MaterialRemapperClass@@QAE@PAVMaterialInfoClass@@0@Z present-unmatched
MaterialRemapperClass::MaterialRemapperClass(MaterialInfoClass * src,MaterialInfoClass * dest) :
	TextureCount(0),
	TextureRemaps(NULL),
	VertexMaterialCount(0),
	VertexMaterialRemaps(NULL),
	LastSrcVmat(NULL),
	LastDestVmat(NULL),
	LastSrcTex(NULL),
	LastDestTex(NULL)
{
	WWASSERT(src);
	WWASSERT(dest);
	WWASSERT(src->Texture_Count() == dest->Texture_Count());
	WWASSERT(src->Vertex_Material_Count() == dest->Vertex_Material_Count());

	SrcMatInfo = src;
	SrcMatInfo->Add_Ref();
	DestMatInfo = dest;
	DestMatInfo->Add_Ref();

	if (src->Vertex_Material_Count() > 0) {
		VertexMaterialCount = src->Vertex_Material_Count();
		VertexMaterialRemaps = W3DNEWARRAY VmatRemapStruct[VertexMaterialCount];
		for (int i=0; i<src->Vertex_Material_Count(); i++) {
			VertexMaterialRemaps[i].Src = src->Peek_Vertex_Material(i);
			VertexMaterialRemaps[i].Dest = dest->Peek_Vertex_Material(i);
		}
	}

	if (src->Texture_Count() > 0) {
		TextureCount = src->Texture_Count();
		TextureRemaps = W3DNEWARRAY TextureRemapStruct[TextureCount];
		for (int i=0; i<src->Texture_Count(); i++) {
			TextureRemaps[i].Src = src->Peek_Texture(i);
			TextureRemaps[i].Dest = dest->Peek_Texture(i);
		}
	}
}

// ??1MaterialRemapperClass@@QAE@XZ
// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/MaterialRemapper.cpp

// ?Remap_Texture@MaterialRemapperClass@@QAEPAVTextureClass@@PAV2@@Z present-unmatched
TextureClass * MaterialRemapperClass::Remap_Texture(TextureClass * src)
{
	if (src == NULL) return src;
	if (src == LastSrcTex) return LastDestTex;
	for (int i=0; i<TextureCount; i++) {
		if (TextureRemaps[i].Src == src) {
			LastSrcTex = src;
			LastDestTex = TextureRemaps[i].Dest;
			return TextureRemaps[i].Dest;
		}
	}
	WWASSERT(0); // uh-oh didn't find the texture, what happend???
	return NULL;
}

VertexMaterialClass * MaterialRemapperClass::Remap_Vertex_Material(VertexMaterialClass * src)
{
	if (src == NULL) return src;
	if (src == LastSrcVmat) return LastDestVmat;
	for (int i=0; i<VertexMaterialCount; i++) {
		if (VertexMaterialRemaps[i].Src == src) {
			LastSrcVmat = src;
			LastDestVmat = VertexMaterialRemaps[i].Dest;
			return VertexMaterialRemaps[i].Dest;
		}
	}
	WWASSERT(0); // uh-oh didn't find the material, what happend???
	return NULL;
}

// ?Remap_Mesh@MaterialRemapperClass@@QAEXPBVMeshMatDescClass@@PAV2@@Z present-unmatched
void MaterialRemapperClass::Remap_Mesh(const MeshMatDescClass * srcmeshmatdesc, MeshMatDescClass * destmeshmatdesc)
{
	/*
	** Remap the vertex materials if there is at least one of them
	*/
	if (SrcMatInfo->Vertex_Material_Count() >= 1) {
	
		for (int pass = 0;pass < srcmeshmatdesc->Get_Pass_Count(); pass++) {

			if (srcmeshmatdesc->Has_Material_Array(pass)) {
				
				for (int vert_index = 0; vert_index < srcmeshmatdesc->Get_Vertex_Count(); vert_index++) {
					VertexMaterialClass * src = srcmeshmatdesc->Peek_Material(vert_index, pass);
					destmeshmatdesc->Set_Material(vert_index, Remap_Vertex_Material(src),pass);
				}

			} else {
			
				VertexMaterialClass * src = srcmeshmatdesc->Peek_Single_Material(pass);
				destmeshmatdesc->Set_Single_Material(Remap_Vertex_Material(src), pass);
				
			}
		}
	}
	
	/*
	** Remap the textures if there is at least one of them
	*/
	if (SrcMatInfo->Texture_Count() >= 1) {
	
		for (int pass = 0;pass < srcmeshmatdesc->Get_Pass_Count(); pass++) {

			for (int stage = 0; stage < MeshMatDescClass::MAX_TEX_STAGES; stage++) {
			
				if (srcmeshmatdesc->Has_Texture_Array(pass, stage)) {
					
					for (int poly_index = 0; poly_index < srcmeshmatdesc->Get_Polygon_Count(); poly_index++) {
						TextureClass * src = srcmeshmatdesc->Peek_Texture(poly_index, pass, stage);
						destmeshmatdesc->Set_Texture(poly_index, Remap_Texture(src), pass, stage);
					}

				} else {
				
					TextureClass * src = srcmeshmatdesc->Peek_Single_Texture(pass, stage);
					destmeshmatdesc->Set_Single_Texture(Remap_Texture(src), pass, stage);

				}
			}
		}
	}
}

// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/MaterialCollectorClass_ctor_Thunk.cpp
// ??0MaterialCollectorClass@@QAE@XZ present-unmatched
MaterialCollectorClass::MaterialCollectorClass(void)
{
	LastShader = ShaderClass(0xFFFFFFFF);
	LastMaterial = NULL;
	LastTexture = NULL;
}

// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/MaterialCollectorClassDestructorThunk.cpp
// ??1MaterialCollectorClass@@QAE@XZ present-unmatched
MaterialCollectorClass::~MaterialCollectorClass(void)
{
	Reset();
}

// BFME collector: owning texture handles. Layout witnesses and exact probe:
// build/unclaimed_map/astra_T/LAYOUTS.md. The two visible getter bodies are
// required for VC7.1 alias analysis; the array getter remains an opaque call.
class BfmeHandleCX
{
public:
    TextureClass *p;

    BfmeHandleCX() : p(0) {}
    BfmeHandleCX(const BfmeHandleCX &other) : p(other.p)
    {
        if (p) p->Add_Ref();
    }
    ~BfmeHandleCX()
    {
        if (p) p->Release_Ref();
    }
    BfmeHandleCX &operator=(const BfmeHandleCX &other)
    {
        if (other.p) other.p->Add_Ref();
        if (p) p->Release_Ref();
        p = other.p;
        return *this;
    }
    bool operator==(const BfmeHandleCX &other) const { return p == other.p; }
    bool operator!=(const BfmeHandleCX &other) const { return p != other.p; }
};

class Gen_0092F070 { public: BfmeHandleCX bfmeGet(int index,int pass,int stage) const; };

class Gen_0092C9D0
{
public:
    enum { MAX_TEX_STAGES = 2 };
    int PassCount;
    int VertexCount;
    int PolyCount;
    void *UV[8];
    int UVSource[4][2];
    void *ColorArray[2];
    int DCGSource[4];
    int DIGSource[4];
    BfmeHandleCX Texture[4][2];
    ShaderClass Shader[4];
    VertexMaterialClass *Material[4];
    void *TextureArray[4][2];
    void *MaterialArray[4];
    void *ShaderArray[4];

    VertexMaterialClass *Get_Single_Material(int pass) const
    {
        if (Material[pass]) Material[pass]->Add_Ref();
        return Material[pass];
    }
    __declspec(noinline) BfmeHandleCX bfmeGet(int pass, int stage) const { return Texture[pass][stage]; }
    VertexMaterialClass *Peek_Material(int index, int pass) const { return reinterpret_cast<const MeshMatDescClass*>(this)->Peek_Material(index,pass); }
    ShaderClass Get_Shader(int index, int pass) const { return reinterpret_cast<const MeshMatDescClass*>(this)->Get_Shader(index,pass); }
};

class BfmeThingBUZA
{
    unsigned char beforePolyCount[0x24];
    int PolyCount;
    int VertexCount;
    unsigned char beforeCurMatDesc[0x9c - 0x2c];
    Gen_0092C9D0 *CurMatDesc;

public:
    int Get_Pass_Count() const { return CurMatDesc->PassCount; }
    int Get_Vertex_Count() const { return VertexCount; }
    int Get_Polygon_Count() const { return PolyCount; }
    bool Has_Material_Array(int pass) const { return CurMatDesc->MaterialArray[pass] != 0; }
    bool Has_Shader_Array(int pass) const { return CurMatDesc->ShaderArray[pass] != 0; }
    bool Has_Texture_Array(int pass, int stage) const { return CurMatDesc->TextureArray[pass][stage] != 0; }
    VertexMaterialClass *Peek_Material(int index, int pass) const { return CurMatDesc->Peek_Material(index, pass); }
    VertexMaterialClass *Get_Single_Material(int pass) const
    {
        return CurMatDesc->Get_Single_Material(pass);
    }
    ShaderClass Get_Shader(int index, int pass) const { return CurMatDesc->Get_Shader(index, pass); }
    ShaderClass Get_Single_Shader(int pass) const { return CurMatDesc->Shader[pass]; }
    __declspec(noinline) BfmeHandleCX bfmeGoBUZA(int pass, int stage) const { return CurMatDesc->bfmeGet(pass, stage); }
};

class Rva009306E0Collector
{
public:

private:
    DynamicVectorClass<ShaderClass> Shaders;
    DynamicVectorClass<VertexMaterialClass *> VertexMaterials;
    DynamicVectorClass<BfmeHandleCX> Textures;
    ShaderClass LastShader;
    VertexMaterialClass *LastMaterial;
    BfmeHandleCX LastTexture;

    int Find_Vertex_Material(VertexMaterialClass *material) const
    {
        for (int i = 0; i < VertexMaterials.Count(); ++i) {
            if (VertexMaterials[i] == material) return i;
        }
        return -1;
    }

    int Find_Texture(TextureClass *texture) const
    {
        for (int i = 0; i < Textures.Count(); ++i) {
            if (Textures[i].p == texture) return i;
        }
        return -1;
    }

public:
    void Add_Vertex_Material(VertexMaterialClass *material)
    {
        if (material == 0) return;
        if (material == LastMaterial) return;
        if (Find_Vertex_Material(material) != -1) return;
        VertexMaterials.Add(material);
        material->Add_Ref();
        LastMaterial = material;
    }

    void Add_Texture(const BfmeHandleCX &texture)
    {
        if (texture.p == 0) return;
        if (texture.p == LastTexture.p) return;
        if (Find_Texture(texture.p) != -1) return;
        Textures.Add(texture);
        LastTexture = texture;
    }
};

void MaterialCollectorClass::Collect_Materials(MeshModelClass *legacyMesh)
{
    BfmeThingBUZA *mesh=reinterpret_cast<BfmeThingBUZA*>(legacyMesh);
    Rva009306E0Collector *collector=reinterpret_cast<Rva009306E0Collector*>(this);
    for (int pass = 0; pass < mesh->Get_Pass_Count(); pass++) {
        if (mesh->Has_Material_Array(pass)) {
            for (int vertex = 0; vertex < mesh->Get_Vertex_Count(); vertex++) {
                collector->Add_Vertex_Material(mesh->Peek_Material(vertex, pass));
            }
        } else {
            VertexMaterialClass *material = mesh->Get_Single_Material(pass);
            collector->Add_Vertex_Material(material);
            if (material) material->Release_Ref();
        }

        if (mesh->Has_Shader_Array(pass)) {
            for (int polygon = 0; polygon < mesh->Get_Polygon_Count(); polygon++) {
                Add_Shader(mesh->Get_Shader(polygon, pass));
            }
        } else {
            ShaderClass shader = mesh->Get_Single_Shader(pass);
            Add_Shader(shader);
        }

        for (int stage = 0; stage < Gen_0092C9D0::MAX_TEX_STAGES; stage++) {
            if (mesh->Has_Texture_Array(pass, stage)) {
                for (int poly_index = 0; poly_index < mesh->Get_Polygon_Count(); poly_index++) {
                    BfmeHandleCX texture = reinterpret_cast<const Gen_0092F070*>(mesh)->bfmeGet(poly_index, pass, stage);
                    collector->Add_Texture(texture);
                }
            } else {
                BfmeHandleCX texture = mesh->bfmeGoBUZA(pass, stage);
                collector->Add_Texture(texture);
            }
        }
    }
}

// ?Reset@MaterialCollectorClass@@QAEXXZ present-unmatched
void MaterialCollectorClass::Reset(void)
{
	for (int ti=0; ti<Textures.Count(); ti++) {
		REF_PTR_RELEASE(Textures[ti]);
	}
	for (int vi=0; vi<VertexMaterials.Count(); vi++) {
		REF_PTR_RELEASE(VertexMaterials[vi]);
	}
	Textures.Clear();
	VertexMaterials.Clear();
	Shaders.Clear();
}

// ?Add_Texture@MaterialCollectorClass@@QAEXPAVTextureClass@@@Z present-unmatched
void MaterialCollectorClass::Add_Texture(TextureClass * tex)
{
	if (tex == NULL) return;
	if (tex == LastTexture) return;
	if (Find_Texture(tex) != -1) return;
	Textures.Add(tex);
	tex->Add_Ref();
	LastTexture = tex;
}

void MaterialCollectorClass::Add_Shader(ShaderClass shader)
{
	if (shader == LastShader) return;
	if (Find_Shader(shader) != -1) return;
	Shaders.Add(shader);
	LastShader = shader;
}

void MaterialCollectorClass::Add_Vertex_Material(VertexMaterialClass * vmat)
{
	if (vmat == NULL) return;
	if (vmat == LastMaterial) return;
	if (Find_Vertex_Material(vmat) != -1) return;
	VertexMaterials.Add(vmat);
	vmat->Add_Ref();
	LastMaterial = vmat;
}

// ?Get_Shader_Count@MaterialCollectorClass@@QAEHXZ present-unmatched
int MaterialCollectorClass::Get_Shader_Count(void)
{
	return Shaders.Count();
}

// ?Get_Vertex_Material_Count@MaterialCollectorClass@@QAEHXZ present-unmatched
int MaterialCollectorClass::Get_Vertex_Material_Count(void)
{
	return VertexMaterials.Count();
}

// ?Get_Texture_Count@MaterialCollectorClass@@QAEHXZ present-unmatched
int MaterialCollectorClass::Get_Texture_Count(void)
{
	return Textures.Count();
}
	
ShaderClass MaterialCollectorClass::Peek_Shader(int i)
{
	return Shaders[i];
}

// ?Peek_Texture@MaterialCollectorClass@@QAEPAVTextureClass@@H@Z present-unmatched
TextureClass * MaterialCollectorClass::Peek_Texture(int i)
{
	return Textures[i];
}

VertexMaterialClass * MaterialCollectorClass::Peek_Vertex_Material(int i)
{
	return VertexMaterials[i];
}

int MaterialCollectorClass::Find_Shader(const ShaderClass & shader)
{
	for (int si=0; si<Shaders.Count(); si++) {
		if (Shaders[si] == shader) {
			return si;
		}
	}
	return -1;
}

// ?Find_Texture@MaterialCollectorClass@@QAEHPAVTextureClass@@@Z present-unmatched
int MaterialCollectorClass::Find_Texture(TextureClass * tex)
{
	for (int ti=0; ti<Textures.Count(); ti++) {
		if (Textures[ti] == tex) {
			return ti;
		}
	}
	return -1;
}

int MaterialCollectorClass::Find_Vertex_Material(VertexMaterialClass * mat)
{
	for (int vi=0; vi<VertexMaterials.Count(); vi++) {
		if (VertexMaterials[vi] == mat) {
			return vi;
		}
	}
	return -1;
}

// Retain the two independently matched inline getter COMDATs: the BFME
// collector below no longer calls the legacy pointer-based MeshModel getter.
VertexMaterialClass *(MeshMatDescClass::*const Rva0092EFC0MaterialGetter)(int) const = &MeshMatDescClass::Get_Single_Material;
VertexMaterialClass *(MeshModelClass::*const Rva0092F010MaterialGetter)(int) const = &MeshModelClass::Get_Single_Material;
