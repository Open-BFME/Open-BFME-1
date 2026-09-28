// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// Identity correction: MeshClass vtable 0113C390 slot 1F8; ECX owns Model at C8.
// Return is void and the single stack argument is an unsigned packed RGB color.
// ZH Recolor_Mesh supplies the base algorithm; BFME adds the single-pass
// shader conversion and owning texture handles. MeshModel getter/setter
// forwarding and ShaderClass copy construction are required for exact bytes.
extern "C"
{
    __declspec(dllimport) char *__cdecl strchr(const char *, int);
    __declspec(dllimport) int __cdecl _strnicmp(const char *, const char *, unsigned);
    __declspec(dllimport) int __cdecl sprintf(char *, const char *, ...);
    __declspec(dllimport) char *__cdecl _strlwr(char *);
}
#include "vector3.h"
class VertexMaterialClass
{
  public:
    void Make_Unique();
    void Set_Ambient(const Vector3 &);
    void Set_Diffuse(const Vector3 &);
};
class TextureClass
{
  public:
    virtual const char *Get_Name();
    unsigned short refs;
    unsigned short pad6;
    int key;
    void Release_Ref();
};
struct BfmeHandleUZA
{
  public:
    TextureClass *p;
    ~BfmeHandleUZA()
    {
        if (p)
            p->Release_Ref();
    }
};
class BFMEWaterTrackTextureHandle
{
  public:
    TextureClass *p;
    ~BFMEWaterTrackTextureHandle()
    {
        if (p)
            p->Release_Ref();
    }
};
class BfmeHandleCX
{
  public:
    TextureClass *p;
    ~BfmeHandleCX()
    {
        if (p)
            p->Release_Ref();
    }
};
BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char *, int, int);
void *PeekHashMapValue008FF850(int);
bool Render_Obj_Exists(const char *);
void bfmeRegisterCX(const char *, int, int);
void bfmeRegisterCY(const char *, int, int);
class ShaderClass
{
  public:
    unsigned ShaderBits;
    ShaderClass()
    {
    }
    ShaderClass(unsigned x)
    {
        ShaderBits = x;
    }
    ShaderClass(const ShaderClass &s)
    {
        ShaderBits = s.ShaderBits;
    }
};
class MeshMatDescClass
{
  public:
    int PassCount;
    int Get_Pass_Count() const
    {
        return PassCount;
    }
    char pad04[0x90];
    ShaderClass Shader;
    ShaderClass Get_Shader(int pass) const
    {
        return (&Shader)[pass];
    }
    char pad98[0x20];
    void *field0b8;
    void Set_Single_Shader(ShaderClass, int);
};
class BfmeThingAUZA
{
  public:
    BfmeHandleUZA bfmeGoAUZA(int, int) const;
};
class BfmeThingBUZA
{
  public:
    BfmeHandleUZA bfmeGoBUZA(int, int) const;
};
class BfmeTexVGS;
class BfmeMeshVGT
{
  public:
    void bfmeSetVGT(BfmeTexVGS **, int, int);
};
class MeshModelClass
{
  public:
    virtual void Delete_This();
    int refs;
    char pad08[0x94];
    MeshMatDescClass *CurMatDesc;
    void Release_Ref()
    {
        if (--refs == 0)
            Delete_This();
    }
    void Replace_Texture(const BfmeHandleCX &, const BfmeHandleCX &);
    int Get_Pass_Count() const
    {
        return CurMatDesc->Get_Pass_Count();
    }
    ShaderClass Get_Shader(int pass) const
    {
        return CurMatDesc->Get_Shader(pass);
    }
    void Set_Single_Shader(ShaderClass shader, int pass)
    {
        CurMatDesc->Set_Single_Shader(shader, pass);
    }
};
class MaterialInfoClass
{
  public:
    virtual void Delete_This();
    int refs;
    void *pad08;
    VertexMaterialClass **VertexMaterials;
    int cap;
    int flags;
    int vertexCount;
    void *pad1c;
    void *pad20;
    TextureClass **textures;
    int cap28;
    int flags2c;
    int textureCount;
    void Release_Ref()
    {
        if (--refs == 0)
            Delete_This();
    }
    BfmeHandleCX Get_Texture(int i) const;
    void Replace_Texture(int i, const BFMEWaterTrackTextureHandle &h)
    {
        TextureClass *&dest = textures[i];
        if (h.p)
            ++h.p->refs;
        if (dest)
            dest->Release_Ref();
        dest = h.p;
    }
};
class MeshClass
{
  public:
    virtual void slot000();
    virtual void slot004();
    virtual void slot008();
    virtual void slot00c();
    virtual void slot010();
    virtual void slot014();
    virtual const char *Get_Name();
    virtual void slot01c();
    virtual void slot020();
    virtual void slot024();
    virtual void slot028();
    virtual void slot02c();
    virtual void slot030();
    virtual void slot034();
    virtual void slot038();
    virtual void slot03c();
    virtual void slot040();
    virtual void slot044();
    virtual void slot048();
    virtual void slot04c();
    virtual void slot050();
    virtual void slot054();
    virtual void slot058();
    virtual void slot05c();
    virtual void slot060();
    virtual void slot064();
    virtual void slot068();
    virtual void slot06c();
    virtual void slot070();
    virtual void slot074();
    virtual void slot078();
    virtual void slot07c();
    virtual void slot080();
    virtual void slot084();
    virtual void slot088();
    virtual void slot08c();
    virtual void slot090();
    virtual void slot094();
    virtual void slot098();
    virtual void slot09c();
    virtual void slot0a0();
    virtual void slot0a4();
    virtual void slot0a8();
    virtual void slot0ac();
    virtual void slot0b0();
    virtual void slot0b4();
    virtual void slot0b8();
    virtual void slot0bc();
    virtual void slot0c0();
    virtual void slot0c4();
    virtual void slot0c8();
    virtual void slot0cc();
    virtual void slot0d0();
    virtual void slot0d4();
    virtual void slot0d8();
    virtual void slot0dc();
    virtual void slot0e0();
    virtual void slot0e4();
    virtual void slot0e8();
    virtual void slot0ec();
    virtual void slot0f0();
    virtual void slot0f4();
    virtual void slot0f8();
    virtual void slot0fc();
    virtual void slot100();
    virtual void slot104();
    virtual void slot108();
    virtual void slot10c();
    virtual void slot110();
    virtual void slot114();
    virtual void slot118();
    virtual void slot11c();
    virtual void slot120();
    virtual void slot124();
    virtual void slot128();
    virtual void slot12c();
    virtual void slot130();
    virtual void slot134();
    virtual void slot138();
    virtual void slot13c();
    virtual void slot140();
    virtual void slot144();
    virtual void slot148();
    virtual void slot14c();
    virtual MaterialInfoClass *Get_Material_Info();
    char pad04[0xc4];
    MeshModelClass *Model;
    MeshModelClass *Get_Model()
    {
        if (Model)
            ++Model->refs;
        return Model;
    }
    virtual void slot154();
    virtual void slot158();
    virtual void slot15c();
    virtual void slot160();
    virtual void slot164();
    virtual void slot168();
    virtual void slot16c();
    virtual void slot170();
    virtual void slot174();
    virtual void slot178();
    virtual void slot17c();
    virtual void slot180();
    virtual void slot184();
    virtual void slot188();
    virtual void slot18c();
    virtual void slot190();
    virtual void slot194();
    virtual void slot198();
    virtual void slot19c();
    virtual void slot1a0();
    virtual void slot1a4();
    virtual void slot1a8();
    virtual void slot1ac();
    virtual void slot1b0();
    virtual void slot1b4();
    virtual void slot1b8();
    virtual void slot1bc();
    virtual void slot1c0();
    virtual void slot1c4();
    virtual void slot1c8();
    virtual void slot1cc();
    virtual void slot1d0();
    virtual void slot1d4();
    virtual void slot1d8();
    virtual void slot1dc();
    virtual void slot1e0();
    virtual void slot1e4();
    virtual void slot1e8();
    virtual void slot1ec();
    virtual void slot1f0();
    virtual void slot1f4();
    virtual void Recolor0092DF50(unsigned color);
};
void MeshClass::Recolor0092DF50(unsigned color)
{
    int i;
    MeshModelClass *model = Get_Model();
    MaterialInfoClass *material = Get_Material_Info();
    const char *name = Get_Name(), *meshName;
    if ((((meshName = strchr(name, '.')) != 0 && *(meshName++)) || ((meshName = name) != 0)) &&
        _strnicmp(meshName, "HOUSECOLOR", 10) == 0)
    {
        for (i = 0; i < material->vertexCount; ++i)
        {
            VertexMaterialClass *vmat = material->VertexMaterials[i];
            Vector3 rgb, rgb2;
            rgb.X = (float)((color >> 16) & 255) / 255.0f;
            rgb.Y = (float)((color >> 8) & 255) / 255.0f;
            rgb.Z = (float)(color & 255) / 255.0f;
            vmat->Make_Unique();
            rgb2.X = rgb.X;
            rgb2.Y = rgb.Y;
            rgb2.Z = rgb.Z;
            vmat->Set_Ambient(rgb2);
            rgb2.X = rgb.X;
            rgb2.Y = rgb.Y;
            rgb2.Z = rgb.Z;
            vmat->Set_Diffuse(rgb2);
        }
    }
    if (model->Get_Pass_Count() == 1 && !model->CurMatDesc->field0b8 &&
        !((const BfmeThingBUZA *)model)->bfmeGoBUZA(0, 1).p)
    {
        BfmeHandleUZA old = ((const BfmeThingAUZA *)model)->bfmeGoAUZA(0, 0);
        const char *name = (const char *)PeekHashMapValue008FF850(old.p ? old.p->key : -1);
        ShaderClass shader = model->Get_Shader(0);
        if (name && (shader.ShaderBits & 0x1e00000) == 0x1800000)
        {
            char buffer[256];
            sprintf(buffer, "#%d#%s", color, name);
            _strlwr(buffer);
            if (!Render_Obj_Exists(buffer))
                bfmeRegisterCY(name, (int)buffer, color);
            ((BfmeMeshVGT *)model->CurMatDesc)
                ->bfmeSetVGT((BfmeTexVGS **)&BFMEGetWaterTrackTexture(buffer, 0, 0), 0, 1);
            shader.ShaderBits = (shader.ShaderBits & ~0x400000) | 0x1a00000;
            model->Set_Single_Shader(shader, 0);
            if (material)
                material->Release_Ref();
            model->Release_Ref();
            return;
        }
    }
    for (i = 0; i < material->textureCount; ++i)
    {
        BfmeHandleCX old = material->Get_Texture(i);
        if (_strnicmp(old.p ? old.p->Get_Name() : 0, "ZHC", 3) == 0)
        {
            VertexMaterialClass *vmat = material->VertexMaterials[i];
            vmat->Make_Unique();
            char buffer[256];
            sprintf(buffer, "#%d#%s", color, old.p ? old.p->Get_Name() : 0);
            _strlwr(buffer);
            if (!Render_Obj_Exists(buffer))
                bfmeRegisterCX(old.p ? old.p->Get_Name() : 0, (int)buffer, color);
            BFMEWaterTrackTextureHandle tex = BFMEGetWaterTrackTexture(buffer, 0, 0);
            if (tex.p)
            {
                model->Replace_Texture(old, *(const BfmeHandleCX *)&tex);
                material->Replace_Texture(i, tex);
            }
        }
    }
    material->Release_Ref();
    model->Release_Ref();
}
