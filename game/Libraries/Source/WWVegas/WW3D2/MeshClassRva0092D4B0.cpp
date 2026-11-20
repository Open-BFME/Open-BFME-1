// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// MeshClass vtable slot 127 (0x1FC), retail 0x0092D4B0 (419 bytes), the slot
// after Recolor0092DF50 (MeshRecolor0092DF50.cpp, whose class view this TU
// reuses). Unless the mesh name has no extension, or its extension matches
// the second argument, it recolours the model's first-pass texture the way
// Recolor0092DF50 does for its single-pass case: "#<color>#<texture>" is
// lowered, registered when no render object has that name, installed through
// the water-track texture and the pass gets the converted single shader. The
// slot's name is unknown, so the method keeps an address-derived name.
extern "C"
{
    __declspec(dllimport) char *__cdecl strchr(const char *, int);
    __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);
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
class TextureBaseClass { public: void Release_Ref(); };

class BFMEWaterTrackTextureHandle
{
  public:
    TextureClass *p;
    ~BFMEWaterTrackTextureHandle()
    {
        if (p)
            ((TextureBaseClass *)p)->Release_Ref();
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
    virtual void rva0092D4B0(int color, const char *skipExtension);
};
// Retail inlines MeshClass::Get_Model (0x0092CF80); a file-local helper keeps
// the expansion without emitting a second COMDAT body under that name.
static __forceinline MeshModelClass *meshModelRef(MeshClass *mesh)
{
    if (mesh->Model)
        ++mesh->Model->refs;
    return mesh->Model;
}
void MeshClass::rva0092D4B0(int color, const char *skipExtension)
{
    const char *name = Get_Name();
    if (!name)
        return;
    const char *extension = strchr(name, '.');
    if (!extension)
        return;
    ++extension;
    if (skipExtension && !_strcmpi(extension, skipExtension))
        return;
    MeshModelClass *model = meshModelRef(this);
    BfmeHandleUZA old = ((const BfmeThingAUZA *)model)->bfmeGoAUZA(0, 0);
    const char *textureName = (const char *)PeekHashMapValue008FF850(old.p ? old.p->key : -1);
    if (textureName)
    {
        char buffer[256];
        sprintf(buffer, "#%d#%s", color, textureName);
        _strlwr(buffer);
        if (!Render_Obj_Exists(buffer))
            bfmeRegisterCY(textureName, (int)buffer, color);
        ShaderClass shader = model->Get_Shader(0);
        ((BfmeMeshVGT *)model->CurMatDesc)
            ->bfmeSetVGT((BfmeTexVGS **)&BFMEGetWaterTrackTexture(buffer, 0, 0), 0, 1);
        shader.ShaderBits = (shader.ShaderBits & ~0x400000) | 0x1a00000;
        model->Set_Single_Shader(shader, 0);
    }
    if (model)
        model->Release_Ref();
}
