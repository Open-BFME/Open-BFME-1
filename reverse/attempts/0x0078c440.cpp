// ?d_0078c440@@YAXXZ
// partial score=0.85 date=2026-09-16
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /ICode /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWDebug
// Retail 0x0078C440.  This is the renderer's view/projection state handoff;
// the address-derived method name preserves the unresolved semantic identity.

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "dx8wrapper.h"

void __fastcall j_0001569f(void *renderer);
void Rva00933810StencilStateA(void);
void Rva00933B80StencilBlendA(void);
void Rva00933BF0StencilBlendB(void);

struct Rva0078C440Device
{
    void **vtable;
};

typedef long (__stdcall *Rva0078C440SetTransform)(
    Rva0078C440Device *, unsigned, const Matrix4 *);

class Rva00785FD0Renderer
{
public:
    void Rva0078C440(void);

private:
    unsigned char m_modeChanged;
    unsigned char m_pendingTextureChange;
    unsigned char m_padding02[2];
    void *m_texture;
    unsigned m_mode;
    unsigned m_stencilGeneration;
    Matrix4 m_world;
    Matrix4 m_view;
    Matrix4 m_projection;
    void *m_vertexBuffer;
    unsigned m_vertexOffset;
    unsigned m_vertexCount;
    unsigned m_reserved;
};

void Rva00785FD0Renderer::Rva0078C440(void)
{
    j_0001569f(this);

    DX8Wrapper::Set_Transform(D3DTS_VIEW, m_view);

    Matrix4 projection = m_projection.Transpose();

    Rva0078C440Device *device = *(Rva0078C440Device **)0x01340534;
    ((Rva0078C440SetTransform)device->vtable[0xB0 / 4])(
        device, 3, &projection);
    *(unsigned *)0x01340500 = 0;
    *(unsigned *)0x0133F498 = 0;
    ++number_of_DX8_calls;

    if (m_mode != 0 && DX8Wrapper::Has_Stencil())
        DX8Wrapper::Set_DX8_Render_State(0x34, 0);

    if (m_mode == 0)
        Rva00933810StencilStateA();
    else if (m_mode == 2)
    {
        Rva00933B80StencilBlendA();
        *(unsigned *)0x012D7180 = m_stencilGeneration;
    }
    else if (m_mode == 1)
    {
        Rva00933BF0StencilBlendB();
        *(unsigned *)0x012D7180 = m_stencilGeneration;
    }
}
