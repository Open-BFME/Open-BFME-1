// ?Flush@Rva00785FD0Renderer@@QAEXXZ
// partial score=0.19 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode
// stlport

#include "Libraries/Source/WWVegas/WWMath/matrix4.h"

class TextureBaseClass;

class ShaderClass
{
public:
	ShaderClass(unsigned value) : bits(value) {}
	unsigned bits;
};

class DX8Wrapper
{
public:
	static bool Has_Stencil(void);
	static void Set_DX8_Render_State(unsigned state, unsigned value);
};

class BfmeTextureRelease
{
public:
	void Release_Ref(void);
};

class BfmeHandleCX
{
public:
	operator TextureBaseClass *&(void)
	{
		return *(TextureBaseClass **)&m_texture;
	}

private:
	BfmeTextureRelease *m_texture;
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
#define Rva00785FD0Half (*(const float *)0x0107533C)
#define Rva00785FD0ModeTwoValue (*(const float *)0x010A13C0)

class Rva00785FD0Renderer
{
public:
	void Flush(void);

private:
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
	unsigned m_vertexOffset;
	int m_vertexCount;
	unsigned m_reserved;
};

// ?Flush@Rva00785FD0Renderer@@QAEXXZ
void Rva00785FD0Renderer::Flush(void)
{
	if (m_vertexCount > 0)
	{
		int triangleCount = m_vertexCount / 3;
		unsigned short offset = (unsigned short)m_vertexOffset;
		bfmeGo930G((void *)offset, triangleCount);
		m_vertexOffset += m_vertexCount;
		m_vertexCount = 0;
	}

	if (m_modeChanged)
	{
		unsigned shaderBits = m_mode == 2 ? 0x0101837 : 0x01098B7;
		ShaderClass shader(shaderBits);
		if (m_texture)
			shader.bits |= 0x10000;
		shader.bits &= 0xFFE3FFFF;

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
			float worldZ = Rva00785FD0Half;
			if (m_mode == 2)
			{
				shader.bits |= 0x0F;
				worldZ = Rva00785FD0ModeTwoValue;
			}
			else if (m_mode == 1)
			{
				shader.bits &= 0xFFFFFFF3;
				shader.bits |= 3;
			}
			m_world[2][3] = worldZ;
		}

		Rva00785FD0State.world = m_world.Transpose();
		Rva00785FD0DirtyMask = (Rva00785FD0DirtyMask & 0xFFFBFFFF) | 1;
		BaseHeightMapScorchSetShader(shader);
		m_modeChanged = 0;
	}

	if (m_pendingTextureChange)
	{
		BoxSetTexture(0, m_texture);
		m_pendingTextureChange = 0;
	}
}
