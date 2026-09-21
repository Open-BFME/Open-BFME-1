// ?Collect_Materials@MaterialCollectorClass@@QAEXPAVMeshModelClass@@@Z
// partial score=0.19 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/Wwutil /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source
#include "shader.h"
#include "vector.h"
#include "texture.h"
#include "vertmaterial.h"

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

class MeshMatDescClass
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

    VertexMaterialClass *Peek_Material(int index, int pass) const throw();
    ShaderClass Get_Shader(int index, int pass) const throw();
};

class MeshModelClass
{
    unsigned char beforePolyCount[0x24];
    int PolyCount;
    int VertexCount;
    unsigned char beforeCurMatDesc[0x9c - 0x2c];
    MeshMatDescClass *CurMatDesc;

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
        VertexMaterialClass *material = CurMatDesc->Material[pass];
        if (material) material->Add_Ref();
        return material;
    }
    ShaderClass Get_Shader(int index, int pass) const { return CurMatDesc->Get_Shader(index, pass); }
    ShaderClass Get_Single_Shader(int pass) const { return CurMatDesc->Shader[pass]; }
    BfmeHandleCX Get_Texture(int index, int pass, int stage) const;
    BfmeHandleCX Get_Single_Texture(int pass, int stage) const;
};

class MaterialCollectorClass
{
public:
    void Collect_Materials(MeshModelClass *mesh);
    void Add_Shader(ShaderClass shader);

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

void MaterialCollectorClass::Collect_Materials(MeshModelClass *mesh)
{
    for (int pass = 0; pass < mesh->Get_Pass_Count(); pass++) {
        if (mesh->Has_Material_Array(pass)) {
            for (int vertex = 0; vertex < mesh->Get_Vertex_Count(); vertex++) {
                Add_Vertex_Material(mesh->Peek_Material(vertex, pass));
            }
        } else {
            VertexMaterialClass *material = mesh->Get_Single_Material(pass);
            Add_Vertex_Material(material);
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

        for (int stage = 0; stage < MeshMatDescClass::MAX_TEX_STAGES; stage++) {
            if (mesh->Has_Texture_Array(pass, stage)) {
                for (int poly_index = 0; poly_index < mesh->Get_Polygon_Count(); poly_index++) {
                    BfmeHandleCX texture = mesh->Get_Texture(poly_index, pass, stage);
                    Add_Texture(texture);
                }
            } else {
                BfmeHandleCX texture = mesh->Get_Single_Texture(pass, stage);
                Add_Texture(texture);
            }
        }
    }
}
