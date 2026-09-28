// ?rva0078B4F0@Rva00785FD0Renderer@@QAEXXZ
// partial score=0.83 date=2026-09-28
// ?rva0078B4F0@Rva00785FD0Renderer@@QAEXXZ
// partial 2026-09-28 opus-5.5: probe shape 0.833 (was 0.814), 1613/1694 B, 1156 differing.
// Lever added: Get_Preset returns an add-ref'd material, so the caller releases it
// (REF_PTR_RELEASE) after Set_Material, as retail's tail shows.
// Still missing (~80 B): retail builds a 4x16-byte row temporary through the vector
// constructor iterator 0x0005C600 with the empty row ctor 0x000FBB40 (ILT 0x00045561)
// inside the WORLD Set_Transform, and keeps 0 in EBX and 0x80000 in EDI.
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
};

class BfmeHandleCX { void *m_resource; };
class Rva00785FD0Renderer
{
public:
    void rva0078B4F0();
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

void Rva00785FD0Renderer::rva0078B4F0()
{
    unsigned displayWidth = RendererDisplayWidth;
    unsigned displayHeight = RendererDisplayHeight;
    _ReadWriteBarrier();
    D3DVIEWPORT8 viewport = {0, 0, displayWidth, displayHeight, 0.0f, 1.0f};
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
    DX8Wrapper::Set_Transform(D3DTS_WORLD, m_world);
    VertexMaterialClass *material = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
    DX8Wrapper::Set_Material(material);
    REF_PTR_RELEASE(material);
    DX8Wrapper::Set_Vertex_Buffer(m_vertexBuffer, 0);
    m_modeChanged = true;
    m_pendingTextureChange = true;
}
