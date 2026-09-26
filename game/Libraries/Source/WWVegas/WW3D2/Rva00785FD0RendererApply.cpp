// ?Rva0078C440@Rva00785FD0Renderer@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Igame /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "dx8wrapper.h"

#include "Libraries/Source/WWVegas/WWMath/matrix4.h"

class DX8VertexBufferClass;

class BfmeHandleCX
{
public:
    BfmeHandleCX() : m_resource(0) {}
    ~BfmeHandleCX();

private:
    void *m_resource;
};

class Rva00785FD0Renderer
{
public:
    void Rva0078C440(void);

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
    DX8VertexBufferClass *m_vertexBuffer;
    unsigned m_vertexOffset;
    unsigned m_vertexCount;
    unsigned m_reserved;
};

void __fastcall j_0001569f(void *renderer);
void Rva00933810StencilStateA(void);
void Rva00933B80StencilBlendA(void);
void Rva00933BF0StencilBlendB(void);

void Rva00785FD0Renderer::Rva0078C440(void)
{
    j_0001569f(this);
    DX8Wrapper::Set_Transform(D3DTS_VIEW, m_view);
    DX8Wrapper::Set_Transform(D3DTS_PROJECTION, m_projection);

    if (m_mode != 0 && DX8Wrapper::Has_Stencil())
        DX8Wrapper::Set_DX8_Render_State(0x34, 0);

    if (m_mode == 0)
    {
        Rva00933810StencilStateA();
        return;
    }
    if (m_mode == 2)
        Rva00933B80StencilBlendA();
    else if (m_mode == 1)
        Rva00933BF0StencilBlendB();
    *(unsigned *)0x012D7180 = m_stencilGeneration;
}
