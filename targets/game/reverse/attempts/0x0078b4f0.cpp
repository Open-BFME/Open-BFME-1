// ?bfmeEnd982C@BfmeHub982@@QAEXXZ
// partial score=0.304 date=2026-10-01
// The matched caller in Rva00786060AptRoundedBounds.cpp names bfmeEnd982C.
// ILT 0x00008D4B pins that method name. The body proves field offsets. The inherited field labels remain hypotheses.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "dx8wrapper.h"
#include "Libraries/Source/WWVegas/WWMath/matrix4.h"
#include "vertmaterial.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

#define RendererDisplayWidth (*(unsigned *)0x012D6DB4)
#define RendererDisplayHeight (*(unsigned *)0x012D6DB8)

struct Rva0078B4F0DX8State : DX8Wrapper
{
    static __forceinline unsigned &dirty() { return render_state_changed; }
    static __forceinline Matrix4 &view() { return render_state.view; }
    static __forceinline Matrix4 &world() { return render_state.world; }
};

class SpawnBoneRow
{
public:
    SpawnBoneRow();
    void Set(float x, float y, float z, float w) { X=x; Y=y; Z=z; W=w; }
    float X, Y, Z, W;
};

class BfmeHandleCX { void *m_resource; };
class BfmeHub982
{
public:
    void bfmeEnd982C();
private:
    bool m_modeChanged;
    bool m_pendingTextureChange;
    unsigned char m_padding02[2];
    BfmeHandleCX m_texture;
    unsigned m_mode;
    unsigned m_stencilGeneration;
    Matrix4 m_world;
    Matrix4 m_view;
    Matrix4 m_projection;
    VertexBufferClass *m_vertexBuffer;
    unsigned m_vertexOffset;
    unsigned m_vertexCount;
    unsigned m_reserved;
};

void BfmeHub982::bfmeEnd982C()
{
    unsigned displayWidth = RendererDisplayWidth;
    unsigned displayHeight = RendererDisplayHeight;
    D3DVIEWPORT8 viewport;
    viewport.X = 0;
    viewport.Y = 0;
    viewport.Width = displayWidth;
    viewport.Height = displayHeight;
    viewport.MinZ = 0.0f;
    viewport.MaxZ = 1.0f;
    DX8Wrapper::Set_Viewport(&viewport);
    const unsigned viewIdentity = 0x80000;

    DX8Wrapper::Get_Transform(D3DTS_VIEW, m_view);
    DX8Wrapper::Get_Transform(D3DTS_PROJECTION, m_projection);
    if (!(Rva0078B4F0DX8State::dirty() & viewIdentity)) {
        Rva0078B4F0DX8State::dirty() |= viewIdentity | 2;
        Rva0078B4F0DX8State::view().Make_Identity();
        Matrix4 view(true);
        DX8Wrapper::Set_Transform(D3DTS_PROJECTION, view);
    }
    {
        Matrix4 transposedWorld = m_world.Transpose();
        SpawnBoneRow unusedWorldRows[4];
        Rva0078B4F0DX8State::world() = transposedWorld;
        Rva0078B4F0DX8State::dirty() |= 1;
        Rva0078B4F0DX8State::dirty() &= ~0x40000;
    }
    VertexMaterialClass *material = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
    DX8Wrapper::Set_Material(material);
    REF_PTR_RELEASE(material);
    DX8Wrapper::Set_Vertex_Buffer(m_vertexBuffer, 0);
    m_modeChanged = true;
    m_pendingTextureChange = true;
}
