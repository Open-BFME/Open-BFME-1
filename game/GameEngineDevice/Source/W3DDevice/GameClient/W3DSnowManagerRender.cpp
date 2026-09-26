// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims/sweep
// Retail 0x00725710..0x007259F9, full 745-byte RET4 body.
// W3DSnowManager identity: matched resource acquisition 0x00723FB0 and the
// surviving GeneralsMD W3DSnow.cpp render body share the weather overrides,
// material lifetime, point-sprite states and quad/point dispatch.
// BFME uses terrain extents instead of the older camera/frustum culling,
// adds the +0x3D gate, and binds 16-byte XYZ+diffuse vertices (FVF 0x42).
// The original weather pointer is cached across both getFinalOverride calls;
// reloading the global after the first call changes both semantics and codegen.
// Native material/shader headers preserve the witnessed refcount operations.
#define Matrix4x4 Matrix4
#include "winbase_shim.h"
#include "rendobj.h"
#include "shader.h"
#include "dx8wrapper.h"
#include "coord3d.h"

class Overridable {
public:
    const Overridable *getFinalOverride() const;
    void *vtable;
    const Overridable *next;
};
class Rva00725710Weather : public Overridable {
public:
    char pad08[0x30];
    unsigned char usePointSprites, snowEnabled;
};
extern Rva00725710Weather *g_bfmeGlo012F15F8;
static const Rva00725710Weather *weather(const Rva00725710Weather *p) {
    if (!p) return 0;
    if (p->next) return (const Rva00725710Weather *)p->next->getFinalOverride();
    return p;
}
struct Rva00725710Caps { char pad00[0x273]; unsigned char pointSprites; };
struct Rva00725710Map {
    char pad00[8];
    int width,height,border;
    char pad14[0x120E0-0x14];
    int originX,originY;
};
struct Rva00725710Terrain { char pad00[0x2FF4]; Rva00725710Map *map; };
class HeightMapRenderObjClass;
extern HeightMapRenderObjClass *TheTerrainRenderObject;
class View;
extern View *TheTacticalView;
// The 70 preceding vtable entries are unmodelled; retail calls +0x118.
class Rva00725710View {
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
    virtual const Coord3D &get3DCameraPosition() const;
};
// BFME uses D3D9's four-argument SetStreamSource, unlike the ZH D3D8 shim.
struct Rva00725710Device;
struct Rva00725710DeviceVtable {
    void *slots00[89];
    long (__stdcall *SetFVF)(Rva00725710Device *, unsigned);
    void *slots90[10];
    long (__stdcall *SetStreamSource)(Rva00725710Device *, unsigned, void *, unsigned, unsigned);
};
struct Rva00725710Device { Rva00725710DeviceVtable *vtable; };
void BoxSetTexture(unsigned,TextureBaseClass *&);
inline DWORD FtoDW745(float f) { return *((DWORD *)&f); }
class W3DSnowManager {
public:
    void render(RenderInfoClass &);
    bool ReAcquireResources();
    void renderAsQuads(RenderInfoClass &,int,int,int,int);
    void renderSubBox(RenderInfoClass &,int,int,int,int);
private:
    char pad00[0xC];
    float m_time,m_velocity,m_fullTimePeriod;
    float m_frequencyScaleX,m_frequencyScaleY,m_amplitude;
    float m_pointSize,m_maxPointSize,m_minPointSize,m_quadSize;
    float m_boxDimensions,m_emitterSpacing;
    unsigned char m_isVisible,m_flag3D;
    char pad3E[0x68-0x3E];
    void *m_indexBuffer;
    TextureBaseClass *m_snowTexture;
    void *m_vertexBuffer;
    int m_dwBase,m_dwFlush,m_dwDiscard,m_leafDim;
    float m_snowCeiling,m_heightTraveled;
    int m_totalRendered;
    float m_cullOverscan;
};
void W3DSnowManager::render(RenderInfoClass &rinfo) {
    const Rva00725710Weather *settings = g_bfmeGlo012F15F8;
    if (!weather(settings)->snowEnabled || !m_flag3D || !m_isVisible)
        return;
    int usePointSprites =
        ((const Rva00725710Caps *)DX8Wrapper::Get_Current_Caps())->pointSprites &&
        weather(settings)->usePointSprites;
    ((const Rva00725710View *)TheTacticalView)->get3DCameraPosition();
    Rva00725710Map *map=((Rva00725710Terrain *)TheTerrainRenderObject)->map;
    int border=map->border*2;
    int originX=(int)((float)map->originX*10.0f);
    int originY=(int)((float)map->originY*10.0f);
    int dimX=(int)((float)(map->width-border)*10.0f);
    int dimY=(int)((float)(map->height-border)*10.0f);
    m_heightTraveled=m_velocity*m_time;
    m_snowCeiling=m_boxDimensions;
    DX8Wrapper::Set_Shader(ShaderClass::_PresetAlphaShader);
    VertexMaterialClass *material=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
    DX8Wrapper::Set_Material(material);
    REF_PTR_RELEASE(material);
    if ((usePointSprites ? m_vertexBuffer : m_indexBuffer)==0)
        ReAcquireResources();
    BoxSetTexture(0,m_snowTexture);
    m_totalRendered=0;
    if (!usePointSprites) {
        renderAsQuads(rinfo,originX,originY,dimX,dimY);
        return;
    }
    DX8Wrapper::Apply_Render_State_Changes();
    DX8Wrapper::Set_DX8_Render_State(D3DRS_POINTSPRITEENABLE,1);
    DX8Wrapper::Set_DX8_Render_State(D3DRS_POINTSCALEENABLE,1);
    DX8Wrapper::Set_DX8_Render_State(D3DRS_POINTSIZE,FtoDW745(m_pointSize));
    DX8Wrapper::Set_DX8_Render_State(D3DRS_POINTSIZE_MIN,FtoDW745(m_minPointSize));
    DX8Wrapper::Set_DX8_Render_State(D3DRS_POINTSIZE_MAX,FtoDW745(m_maxPointSize));
    DX8Wrapper::Set_DX8_Render_State(D3DRS_POINTSCALE_A,FtoDW745(0.0f));
    DX8Wrapper::Set_DX8_Render_State(D3DRS_POINTSCALE_B,FtoDW745(0.0f));
    DX8Wrapper::Set_DX8_Render_State(D3DRS_POINTSCALE_C,FtoDW745(1.0f));
    Rva00725710Device *device=(Rva00725710Device *)DX8Wrapper::_Get_D3D_Device8();
    device->vtable->SetStreamSource(device,0,m_vertexBuffer,0,16);
    device=(Rva00725710Device *)DX8Wrapper::_Get_D3D_Device8();
    device->vtable->SetFVF(device,0x42);
    m_cullOverscan=m_quadSize+m_amplitude;
    m_dwBase=4096;
    renderSubBox(rinfo,originX,originY,dimX,dimY);
    DX8Wrapper::Set_DX8_Render_State(D3DRS_POINTSPRITEENABLE,0);
    DX8Wrapper::Set_DX8_Render_State(D3DRS_POINTSCALEENABLE,0);
}
