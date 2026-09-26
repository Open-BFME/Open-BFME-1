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
// BFME material-index loading from the original meshmdlio.cpp algorithms.
// read_texture_ids: RVA 0x0096DB40, full 317 bytes. Texture-stage chunk 0x49
// selects arm 0x0096ED9D; its call at 0x0096EDA1 reaches this body and checks
// AL against 1. RET 8 at +0x13A ends before three INT3 bytes at +0x13D.
// The BFME owning texture handle ABI is shared with MaterialRemapMesh.cpp.
// Peek_Texture at 0x0096D080 indexes the context array at +0xF8, copies
// a four-byte handle, and increments its 16-bit reference count at +4.
// The local field views retain BFME layouts without changing shared headers.
#include "w3d_file.h"
#include "shader.h"

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
protected:
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
public:
    static ShaderClass NullShader;
    bool Has_Shader_Data(int pass) { return Shader[pass] != NullShader || ShaderArray[pass] != 0; }
    void Set_Single_Shader(ShaderClass shader, int pass);
    void Set_Shader(int index, ShaderClass shader, int pass);
    bool Has_Material_Data(int pass) { return Material[pass] != 0 || MaterialArray[pass] != 0; }
    void Set_Single_Material(VertexMaterialClass *material, int pass);
    void Set_Material(int index, VertexMaterialClass *material, int pass);
    bool Has_Texture_Data(int pass, int stage) {
        return Texture[pass][stage].p != 0 ||
               TextureArray[pass][stage] != 0;
    }
    void Set_Single_Texture(const BfmeHandleCX &texture, int pass, int stage);
    void Set_Texture(int index, const BfmeHandleCX &texture, int pass, int stage);
};

class MeshLoadContextClass {
    unsigned char padding_88[0x88];
public:
    unsigned long PrelitChunkID;
    int CurPass;
    int CurTexStage;
private:
    unsigned char padding_94[0xb0 - 0x94];
public:
    ShaderClass *Shaders;
private:
    unsigned char padding_b4[0xc8 - 0xb4];
public:
    VertexMaterialClass **VertexMaterials;
private:
    unsigned char padding_cc[0x10c - 0xcc];
public:
    MeshMatDescClass AlternateMatDesc;
private:
    friend class MeshModelClass;
    BfmeHandleCX Peek_Texture(int index);
public:
    ShaderClass Peek_Shader(unsigned long index) { return Shaders[index]; }
    VertexMaterialClass *Peek_Vertex_Material(unsigned long index) { return VertexMaterials[index]; }
};

class MeshModelClass {
    unsigned char padding_00[0x18];
public:
    unsigned long Flags;
    char SortLevel;
    unsigned char beforePolyCount[7];
    int PolyCount;
    int VertexCount;
private:
    unsigned char padding_2c[0x94 - 0x2c];
public:
    MeshMatDescClass *DefMatDesc;
    enum FlagsType { SORT = 0x10 };
    void Set_Flag(FlagsType flag, bool onoff) { if (onoff) Flags |= flag; else Flags &= ~flag; }
    int Get_Vertex_Count() const { return VertexCount; }
    int Get_Polygon_Count() const {
        return PolyCount;
    }
protected:
    bool read_texture_ids(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_vertex_material_ids(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_shader_ids(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_dcg(ChunkLoadClass &, MeshLoadContextClass *);
    bool read_dig(ChunkLoadClass &, MeshLoadContextClass *);
    bool read_texture_stage(ChunkLoadClass &, MeshLoadContextClass *);
    bool read_scg(ChunkLoadClass &, MeshLoadContextClass *) { return true; }
    bool read_material_pass(ChunkLoadClass &, MeshLoadContextClass *);
};

bool MeshModelClass::read_texture_ids(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
    unsigned long texid;
    int pass = context->CurPass;
    int stage = context->CurTexStage;
    MeshMatDescClass *matdesc = DefMatDesc;

    if (DefMatDesc->Has_Texture_Data(pass, stage)) {
        matdesc = &(context->AlternateMatDesc);
    }

    if (cload.Cur_Chunk_Length() == 1 * sizeof(unsigned long)) {
        cload.Read(&texid, sizeof(texid));
        matdesc->Set_Single_Texture(context->Peek_Texture(texid), pass, stage);
    } else {
        for (int i = 0; i < Get_Polygon_Count(); i++) {
            cload.Read(&texid, sizeof(unsigned long));
            if (texid != 0xffffffff) {
                matdesc->Set_Texture(i, context->Peek_Texture(texid), pass, stage);
            }
        }
    }

    return true;
}

// read_vertex_material_ids: RVA 0x0096D300, complete 190 bytes. Material
// pass chunk 0x39 selects arm 0x0096FB9F; its call at 0x0096FBA3 reaches
// this body. RET 8 at +0xBB ends before two INT3 bytes at +0xBE.
bool MeshModelClass::read_vertex_material_ids(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
    unsigned long vmat;
    MeshMatDescClass *matdesc = DefMatDesc;

    if (DefMatDesc->Has_Material_Data(context->CurPass)) {
        matdesc = &(context->AlternateMatDesc);
    }

    if (cload.Cur_Chunk_Length() == 1 * sizeof(unsigned long)) {
        cload.Read(&vmat, sizeof(vmat));
        matdesc->Set_Single_Material(context->Peek_Vertex_Material(vmat),
                                     context->CurPass);
    } else {
        for (int i = 0; i < Get_Vertex_Count(); i++) {
            cload.Read(&vmat, sizeof(unsigned long));
            matdesc->Set_Material(i, context->Peek_Vertex_Material(vmat),
                                  context->CurPass);
        }
    }

    return true;
}

// read_shader_ids: RVA 0x0096D3C0, complete 320 bytes. Material-pass chunk
// 0x3A selects arm 0x0096FBAA; its call at 0x0096FBAE reaches this loader.
// RET 8 occupies +0x13D..+0x13F; read_dcg starts immediately at 0x0096D500.
// ShaderClass comes from the existing BFME header; only the enclosing field
// views differ from the reference. NullShader marks an unused pass.
bool MeshModelClass::read_shader_ids(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
    MeshMatDescClass *matdesc = DefMatDesc;
    if (DefMatDesc->Has_Shader_Data(context->CurPass)) {
        matdesc = &(context->AlternateMatDesc);
    }

    unsigned long shaderid;
    if (cload.Cur_Chunk_Length() == 1 * sizeof(unsigned long)) {
        cload.Read(&shaderid, sizeof(shaderid));
        ShaderClass shader = context->Peek_Shader(shaderid);
        matdesc->Set_Single_Shader(shader, context->CurPass);

        if ((context->CurPass == 0) &&
            (shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO) &&
            (shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_DISABLE) &&
            (SortLevel == 0)) {
            Set_Flag(SORT, true);
        }
    } else {
        for (int i = 0; i < Get_Polygon_Count(); i++) {
            cload.Read(&shaderid, sizeof(unsigned long));
            ShaderClass shader = context->Peek_Shader(shaderid);
            matdesc->Set_Shader(i, shader, context->CurPass);

            if ((context->CurPass == 0) &&
                (shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO) &&
                (shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_DISABLE) &&
                (SortLevel == 0)) {
                Set_Flag(SORT, true);
            }
        }
    }

    return true;
}

// read_material_pass: RVA 0x0096FB60, complete 196-byte compiler span.
// The 0x38 chunk arm in read_prelit_material selects this dispatcher.
// RET 8 at +0x93 ends the executable code; jump table +0x98..+0xB3 and
// selectors +0xB4..+0xC3 are part of the function. Twelve following INT3
// bytes are padding. Chunk 0x3E (SCG) uses the original inline no-op success.
bool MeshModelClass::read_material_pass(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
    context->CurTexStage = 0;

    while (cload.Open_Chunk()) {
        bool error = true;

        switch (cload.Cur_Chunk_ID()) {
            case W3D_CHUNK_VERTEX_MATERIAL_IDS:
                error = read_vertex_material_ids(cload, context);
                break;

            case W3D_CHUNK_SHADER_IDS:
                error = read_shader_ids(cload, context);
                break;

            case W3D_CHUNK_DCG:
                error = read_dcg(cload, context);
                break;

            case W3D_CHUNK_DIG:
                error = read_dig(cload, context);
                break;

            case W3D_CHUNK_SCG:
                error = read_scg(cload, context);
                break;

            case W3D_CHUNK_TEXTURE_STAGE:
                error = read_texture_stage(cload, context);
                break;
        }

        if (error != true) {
            return error;
        }
        cload.Close_Chunk();
    }

    context->CurPass++;
    return true;
}
