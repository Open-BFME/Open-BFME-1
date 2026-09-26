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
// BFME MeshModelClass::read_shaders, RVA 0x0096EA60, complete 197 bytes.
// read_prelit_material chunk 0x29 selects arm 0x0096FCAE; the call at
// 0x0096FCB2 reaches this body. The main read_chunks dispatcher agrees.
// This is the array of 16-byte W3dShaderStruct values, converted by
// W3dUtilityClass::Convert_Shader and appended to the context shader vector.
// ShaderCount is context+0x80; DynamicVectorClass<ShaderClass> is at +0xAC.
// The final RET 8 at 0x0096EB22 ends before INT3 padding at 0x0096EB25.
// Original algorithm: GeneralsMD WW3D2/meshmdlio.cpp. Actual vector/shader
// headers are reused; the BFME default shader word is explicit below.
#include "w3d_file.h"
#include "shader.h"
#include "w3d_util.h"
#include "vector.h"
class ChunkLoadClass {
public:
    unsigned long Read(void *, unsigned long);
    bool Open_Chunk();
    bool Close_Chunk();
};
class TextureClass
{
public:
    void Add_Ref(void)
    {
        ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
    }
    void Release_Ref(void);
};

class BfmeHandleCX
{
public:
    BfmeHandleCX(void) : p(0) {}
    BfmeHandleCX(const BfmeHandleCX &other) : p(other.p)
    {
        if (p) p->Add_Ref();
    }
    ~BfmeHandleCX(void)
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

    TextureClass *p;
};


BfmeHandleCX Load_Texture(ChunkLoadClass &cload);

class VertexMaterialClass {
public:
    virtual void Delete_This();
    VertexMaterialClass();
    bool Load_W3D(ChunkLoadClass &);
    void Add_Ref() { ++RefCount; }
    void Release_Ref() { if (--RefCount == 0) Delete_This(); }
private:
    int RefCount;
    unsigned char fields[0x6c - 8];
};

class MeshLoadContextClass {
    friend class MeshModelClass;
    struct LegacyMaterialClass {
        unsigned char nameAndMaterialIndices[0x0c];
        int TextureIdx;
    };
    unsigned char beforeInfo[0x78];
    W3dMaterialInfoStruct MatInfo;
    unsigned char passAndStage[0x94-0x88];
    DynamicVectorClass<LegacyMaterialClass *> LegacyMaterials;
    DynamicVectorClass<ShaderClass> Shaders;
    DynamicVectorClass<VertexMaterialClass *> VertexMaterials;
    unsigned char beforeTextures[0xf4-0xc4-sizeof(DynamicVectorClass<VertexMaterialClass *> )];
    DynamicVectorClass<BfmeHandleCX> Textures;
    BfmeHandleCX Peek_Texture(int index);
    BfmeHandleCX Peek_Legacy_Texture(int legacy_material_index);
    int Add_Texture(const BfmeHandleCX &tex) { int index=Textures.Count(); Textures.Add(tex); return index; }
    int Add_Vertex_Material(VertexMaterialClass *vmat) { vmat->Add_Ref(); int index=VertexMaterials.Count(); VertexMaterials.Add(vmat); return index; }
    int Add_Shader(ShaderClass shader) {
        int index=Shaders.Count();
        Shaders.Add(shader);
        return index;
    }
};
class MeshModelClass {
protected:
    bool read_shaders(ChunkLoadClass &, MeshLoadContextClass *);
    bool read_vertex_materials(ChunkLoadClass &, MeshLoadContextClass *);
    bool read_textures(ChunkLoadClass &, MeshLoadContextClass *);
};
bool MeshModelClass::read_shaders(ChunkLoadClass &cload,MeshLoadContextClass *context)
{
    W3dShaderStruct shader;
    for (unsigned int i=0;i<context->MatInfo.ShaderCount;i++) {
        if (cload.Read(&shader,sizeof(shader)) != sizeof(shader)) return false;
        // BFME default shader word; the shared header retains the legacy cull bit.
        ShaderClass newshader(0x0010441b);
        W3dUtilityClass::Convert_Shader(shader,&newshader);
        int index=context->Add_Shader(newshader);
    }
    return true;
}

// BFME vertex-material list reader: 0x0096EB30, complete 272 bytes.
// Prelit chunk 0x2A selects arm 0x0096FCA3 and call 0x0096FCA7. The
// 0x6C-byte allocation calls the named VertexMaterial constructor, then
// the Boolean Load_W3D. The context vector starts at +0xC4. Both success
// and failure release the temporary reference; RET 8 at 0x0096EC3D ends
// immediately before the next function at 0x0096EC40.
bool MeshModelClass::read_vertex_materials(ChunkLoadClass &cload,MeshLoadContextClass *context)
{
    while (cload.Open_Chunk()) {
        VertexMaterialClass *vmat=new VertexMaterialClass;
        bool error=vmat->Load_W3D(cload);
        if (error != true) {
            vmat->Release_Ref();
            return error;
        }
        context->Add_Vertex_Material(vmat);
        vmat->Release_Ref();
        cload.Close_Chunk();
    }
    return true;
}

// BFME texture list reader: 0x0096EC40, complete 283 bytes. Prelit chunk
// 0x30 and the main mesh dispatcher call this body. Load_Texture returns an
// owning handle; nonempty handles enter the context vector at +0xF4.
// RET 8 at 0x0096ED58 ends before five INT3 bytes at 0x0096ED5B.
bool MeshModelClass::read_textures(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
    BfmeHandleCX newtex = ::Load_Texture(cload);
    while (newtex.p != 0) {
        context->Add_Texture(newtex);
        newtex = ::Load_Texture(cload);
    }
    return true;
}

// BFME legacy-material texture lookup: 0x0096DF10, complete 62 bytes.
// The material paths call this at 0x0096E483 and 0x0096E565 with a hidden
// owning-handle result. LegacyMaterials data is at +0x98 and TextureIdx at
// entry+0x0C. GeneralsMD lookup semantics survive with BFME's handle return.
// The last RET 8 ends at 0x0096DF4D, before two INT3 padding bytes.
BfmeHandleCX MeshLoadContextClass::Peek_Legacy_Texture(int legacy_material_index)
{
    int ti = LegacyMaterials[legacy_material_index]->TextureIdx;
    if (ti != -1) {
        return Peek_Texture(ti);
    }
    return BfmeHandleCX();
}
