// ?rva0078C070@Rva00785FD0Renderer@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "dx8wrapper.h"
#include "vector2.h"
#include "Libraries/Source/WWVegas/WWMath/matrix4.h"

extern void j_00008d4b(void);

extern int g_Va012D6DB4;
extern int g_Va012D6DB8;
extern unsigned char g_Va0133F42B;

class DX8VertexBufferClass;

class BfmeHandleCX
{
private:
	void *m_resource;
};

class Rva00785FD0Renderer
{
public:
	void rva0078C070(void);

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

// ?rva0078C070@Rva00785FD0Renderer@@QAEXXZ
void Rva00785FD0Renderer::rva0078C070(void)
{
	m_mode = 0;
	m_stencilGeneration = 0;
	{
		Vector2 worldScale;
		float &worldScaleX = worldScale.X;
		float &worldScaleY = worldScale.Y;
		float width = (float)(unsigned)g_Va012D6DB4;
		worldScaleX = 2.0f / width;
		float height = (float)(unsigned)g_Va012D6DB8;
		worldScaleY = -2.0f / height;

		unsigned char flagValue = g_Va0133F42B;
		Vector2 worldTranslate;
		float &worldTranslateX = worldTranslate.X;
		float &worldTranslateY = worldTranslate.Y;
		worldTranslateX = -1.0f;
		worldTranslateY = 1.0f;

		if (flagValue != 0) {
			Vector2 bias;
			bias.X = -0.5f / (width * 0.5f);
			bias.Y = -0.5f / (height * -0.5f);
			worldTranslateX = bias.X - 1.0f;
			worldTranslateY = bias.Y + 1.0f;
		}

		m_world.Make_Identity();
		m_world[0][0] = worldScaleX;
		m_world[1][1] = worldScaleY;
		m_world[2][2] = 0.0f;
		m_world[0][3] = worldTranslateX;
		m_world[1][3] = worldTranslateY;
		m_world[2][3] = 0.5f;
	}

	DX8Wrapper::Set_Transform(D3DTS_WORLD, m_world);
	m_vertexOffset = 0;
	reinterpret_cast<void (__fastcall *)(void *)>(j_00008d4b)(this);
}
