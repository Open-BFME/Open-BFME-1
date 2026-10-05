// ?j_0001569f@@YIXPAX@Z
// partial score=0.2855 date=2026-10-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Igame /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug
// stlport

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "dx8wrapper.h"
#include "Libraries/Source/WWVegas/WWMath/matrix4.h"

class BfmeHandleCX
{
public:
	operator TextureBaseClass *&(void)
	{
		return *(TextureBaseClass **)&m_texture;
	}

private:
	void *m_texture;
};

extern void bfmeGo930G(void *, int);
extern void BaseHeightMapScorchSetShader(const ShaderClass &);
extern void BoxSetTexture(unsigned, TextureBaseClass *&);

struct Rva00785FD0GlobalState
{
	Matrix4 world;
};

#define Rva00785FD0State (*(Rva00785FD0GlobalState *)0x0134108C)
#define Rva00785FD0DirtyMask (*(unsigned *)0x0133F49C)
#define Rva00785FD0Half (*(volatile const float *)0x0107533C)
#define Rva00785FD0ModeTwoValue (*(volatile const float *)0x010A13C0)

struct Rva00785FD0Renderer
{
	unsigned char m_modeChanged;
	unsigned char m_pendingTextureChange;
	unsigned char m_padding02[2];
	BfmeHandleCX m_texture;
	unsigned m_mode;
	unsigned m_stencilGeneration;
	Matrix4 m_world;
	Matrix4 m_view;
	Matrix4 m_projection;
	void *m_vertexBuffer;
	int m_vertexOffset;
	int m_vertexCount;
	unsigned m_reserved;
};

// ?j_0001569f@@YIXPAX@Z
#define m_modeChanged (self->m_modeChanged)
#define m_pendingTextureChange (self->m_pendingTextureChange)
#define m_texture (self->m_texture)
#define m_mode (self->m_mode)
#define m_stencilGeneration (self->m_stencilGeneration)
#define m_world (self->m_world)
#define m_vertexOffset (self->m_vertexOffset)
#define m_vertexCount (self->m_vertexCount)
void __fastcall j_0001569f(void *object)
{
	Rva00785FD0Renderer *self = (Rva00785FD0Renderer *)object;
	if (m_vertexCount > 0)
	{
		int triangleCount = m_vertexCount / 3;
		unsigned short *offsetAddress = (unsigned short *)&m_vertexOffset;
		bfmeGo930G((void *)(unsigned long)*offsetAddress, triangleCount);
		m_vertexOffset += m_vertexCount;
		m_vertexCount = 0;
	}

	if (m_modeChanged)
	{
		unsigned shaderBits = (unsigned)(m_mode != 2) - 1;
		shaderBits &= 0xFFFF7F80;
		shaderBits += 0x001084B7;
		shaderBits &= 0xFFFFF8FF;
		shaderBits |= 0x1800;
		if (m_texture)
			shaderBits |= 0x10000;
		else
			shaderBits &= 0xFFFEFFFF;
		shaderBits &= 0xFFE3FFFF;

		if (DX8Wrapper::Has_Stencil())
		{
			if (m_mode == 0)
			{
				DX8Wrapper::Set_DX8_Render_State(0x34, 0);
			}
			else
			{
				DX8Wrapper::Set_DX8_Render_State(0x34, 1);
				DX8Wrapper::Set_DX8_Render_State(0x39, m_stencilGeneration);
				DX8Wrapper::Set_DX8_Render_State(0x3A, 0xFFFFFFFF);
				DX8Wrapper::Set_DX8_Render_State(0x3B, 0xFFFFFFFF);
				DX8Wrapper::Set_DX8_Render_State(0x36, 1);
				DX8Wrapper::Set_DX8_Render_State(0x35, 1);
				if (m_mode == 2)
				{
					DX8Wrapper::Set_DX8_Render_State(0x38, 8);
					DX8Wrapper::Set_DX8_Render_State(0x37, 3);
				}
				else if (m_mode == 1)
				{
					DX8Wrapper::Set_DX8_Render_State(0x38, 3);
					DX8Wrapper::Set_DX8_Render_State(0x37, 1);
				}
			}
		}
		else
		{
			if (m_mode == 2)
			{
				shaderBits |= 0x0F;
			}
			else if (m_mode == 1)
			{
				shaderBits &= 0xFFFFFFF3;
				shaderBits |= 3;
			}
			float z = Rva00785FD0Half;
			if (m_mode == 2)
				z = Rva00785FD0ModeTwoValue;
			m_world[2][3] = z;
		}

		DX8Wrapper::Set_Transform(D3DTS_WORLD, m_world);
		BaseHeightMapScorchSetShader(*(const ShaderClass *)&shaderBits);
		m_modeChanged = 0;
	}

	if (m_pendingTextureChange)
	{
		BoxSetTexture(0, m_texture);
		m_pendingTextureChange = 0;
	}
}
