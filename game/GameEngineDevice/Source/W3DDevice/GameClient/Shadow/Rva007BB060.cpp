// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas
#include "dx8wrapper.h"

// Retail RVA 0x007BB060, 929 bytes through ret at 0x007BB400 then int3.
// This is not invalidateCachedLightPositions: no receiver is read. It draws
// 256 test quads and passes the render target to 0x007B93E0, whose literal is
// SurfaceTest.tga. Keep the enclosing routine's identity address-derived.

#include "wwstring.h"
#include "vertmaterial.h"
#include "texture.h"
#include "shader.h"

struct Rva007BB060TextureRef
{
    TextureBaseClass *texture;
    Rva007BB060TextureRef() : texture(0) {}
    ~Rva007BB060TextureRef() { if (texture) texture->Release_Ref(); }
    operator TextureBaseClass *&() { return texture; }
};
void BoxSetTexture(unsigned int stage, TextureBaseClass *&texture);

struct Rva007BB060Surface;
struct Rva007BB060SurfaceVtable {
    void *unknown00[2];
    unsigned long (__stdcall *Release)(Rva007BB060Surface *);
};
struct Rva007BB060Surface { Rva007BB060SurfaceVtable *vtable; };
struct Rva007BB060Device;
struct Rva007BB060DeviceVtable {
    void *unknown00[38];
    long (__stdcall *GetRenderTarget)(Rva007BB060Device *, unsigned int, Rva007BB060Surface **);
    void *unknown9c[18];
    long (__stdcall *SetRenderState)(Rva007BB060Device *, unsigned int, unsigned int);
    void *unknowne8[25];
    long (__stdcall *DrawPrimitiveUP)(Rva007BB060Device *, unsigned int, unsigned int, const void *, unsigned int);
    void *unknown150[5];
    long (__stdcall *SetFVF)(Rva007BB060Device *, unsigned int);
};
struct Rva007BB060Device { Rva007BB060DeviceVtable *vtable; };

class Rva007BB060View {
public:
#define VIEW_SLOT(n) virtual void slot##n();
    VIEW_SLOT(00) VIEW_SLOT(01) VIEW_SLOT(02) VIEW_SLOT(03) VIEW_SLOT(04)
    VIEW_SLOT(05) VIEW_SLOT(06) VIEW_SLOT(07) VIEW_SLOT(08) VIEW_SLOT(09)
    VIEW_SLOT(10) VIEW_SLOT(11) VIEW_SLOT(12) VIEW_SLOT(13) VIEW_SLOT(14)
    virtual int getWidth();
    VIEW_SLOT(16)
    virtual int getHeight();
    VIEW_SLOT(18)
    virtual void getOrigin(int *x, int *y);
#undef VIEW_SLOT
};

// 012F1600 is EA's tactical view singleton, defined once as
// View *TheTacticalView in game/GameEngine/Source/GameClient/View.cpp.
class View;
extern View *TheTacticalView;
static inline Rva007BB060View *theTacticalView() { return (Rva007BB060View *)TheTacticalView; }
extern VertexMaterialClass *Rva01340EC4Material;
extern unsigned int Rva0133F49CChanged;
extern bool Rva012D6DFCShaderDirty;
// 0x012D6E08 is ShaderClass::_PresetOpaqueShader; shader.h declares the identity.
extern unsigned int Rva01340EC0Shader;


void Rva007B93E0(Rva007BB060Surface *surface);

struct Rva007BB060Position {
    float x, y, z, w;
    Rva007BB060Position() {}
    Rva007BB060Position(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
};
struct Rva007BB060Vertex { Rva007BB060Position position; unsigned int color; };

void Rva007BB060()
{
    Rva007BB060Device *device = reinterpret_cast<Rva007BB060Device *>(DX8Wrapper::_Get_D3D_Device8());
    if (!device) return;

    int x, y;
    theTacticalView()->getOrigin(&x, &y);
    int width = theTacticalView()->getWidth();
    int height = theTacticalView()->getHeight();

    VertexMaterialClass *material = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
    if (material) material->Add_Ref();
    if (Rva01340EC4Material) Rva01340EC4Material->Release_Ref();
    Rva01340EC4Material = material;
    Rva0133F49CChanged |= 0x4000;
    if (material) material->Release_Ref();
    if (Rva012D6DFCShaderDirty || ShaderClass::_PresetOpaqueShader.Get_Bits() != Rva01340EC0Shader) {
        Rva01340EC0Shader = ShaderClass::_PresetOpaqueShader.Get_Bits();
        Rva0133F49CChanged |= 0x8000;
        StringClass text;
    }

    { Rva007BB060TextureRef texture; BoxSetTexture(0, texture); }
    { Rva007BB060TextureRef texture; BoxSetTexture(1, texture); }
    DX8Wrapper::Apply_Render_State_Changes();

    device->vtable->SetFVF(device, 0x44);
    device->vtable->SetRenderState(device, 7, 1);
    device->vtable->SetRenderState(device, 23, 8);
    device->vtable->SetRenderState(device, 52, 1);
    device->vtable->SetRenderState(device, 56, 3);
    device->vtable->SetRenderState(device, 55, 1);
    device->vtable->SetRenderState(device, 58, ~0U);
    device->vtable->SetRenderState(device, 9, 1);

    Rva007BB060Vertex vertices[4];
    vertices[0].position = Rva007BB060Position((float)(x + width), (float)(y + height), 0, 1);
    vertices[1].position = Rva007BB060Position((float)(x + width), 0, 0, 1);
    vertices[2].position = Rva007BB060Position((float)x, (float)(y + height), 0, 1);
    vertices[3].position = Rva007BB060Position((float)x, 0, 0, 1);

    for (int i = 0; i < 256; ++i) {
        unsigned int color = (((i & 0xf0) << 12) + (i & 0xf)) << 4;
        vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = color;
        device->vtable->SetRenderState(device, 57, i);
        device->vtable->DrawPrimitiveUP(device, 5, 2, vertices, sizeof(vertices[0]));
    }
    device->vtable->SetRenderState(device, 9, 2);
    device->vtable->SetRenderState(device, 52, 0);

    Rva007BB060Surface *surface = 0;
    reinterpret_cast<Rva007BB060Device *>(DX8Wrapper::_Get_D3D_Device8())->vtable->GetRenderTarget(reinterpret_cast<Rva007BB060Device *>(DX8Wrapper::_Get_D3D_Device8()), 0, &surface);
    Rva007B93E0(surface);
    surface->vtable->Release(surface);
}
