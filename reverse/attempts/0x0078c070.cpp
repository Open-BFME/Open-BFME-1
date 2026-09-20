// ?rva0078C070@Rva00785FD0Renderer@@QAEXXZ
// partial score=0.05 date=2026-09-20
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode
// stlport

#include "Libraries/Source/WWVegas/WWMath/matrix4.h"

extern void d_0078b4f0(void);

#define Rva0078C070Uint32Scale (*(const float *)0x01075358)
#define Rva0078C070Half (*(const float *)0x0107533C)
#define Rva0078C070Two (*(const float *)0x01088830)
#define Rva0078C070MinusTwo (*(const float *)0x011203E4)
#define Rva0078C070MinusHalf (*(const float *)0x01095F9C)
#define Rva0078C070One (*(const float *)0x01075334)
#define Rva0078C070MinusOne (*(const float *)0x0109BF3C)
#define Rva0078C070Width (*(const unsigned *)0x012D6DB4)
#define Rva0078C070Height (*(const unsigned *)0x012D6DB8)
#define Rva0078C070Flag (*(const unsigned char *)0x0133F42B)
#define Rva0078C070DirtyMask (*(unsigned *)0x0133F49C)

struct Rva0078C070RenderState
{
	Matrix4 world;
};

#define Rva0078C070GlobalState (*(Rva0078C070RenderState *)0x0134108C)

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
	void *m_vertexBuffer;
	unsigned m_vertexOffset;
	unsigned m_vertexCount;
	unsigned m_reserved;
};

void Rva00785FD0Renderer::rva0078C070(void)
{
	m_mode = 0;
	m_stencilGeneration = 0;
	{
	float width = (float)(int)Rva0078C070Width;
	int widthValue = Rva0078C070Width;
	if (widthValue < 0) {
		width += Rva0078C070Uint32Scale;
	}
	float height = (float)(int)Rva0078C070Height;
	int heightValue = Rva0078C070Height;
	if (heightValue < 0) {
		height += Rva0078C070Uint32Scale;
	}
	unsigned char flagValue = Rva0078C070Flag;
	float worldTranslateX = Rva0078C070MinusOne;
	float worldTranslateY = 1.0f;

	if (flagValue == 0) {
		worldTranslateX = Rva0078C070MinusHalf / (width * Rva0078C070Half);
		worldTranslateY = Rva0078C070MinusHalf / (height * Rva0078C070MinusHalf);
		worldTranslateX = worldTranslateX - Rva0078C070One;
		worldTranslateY = worldTranslateY + Rva0078C070One;
	}

	m_world.Make_Identity();
	m_world[0][0] = Rva0078C070Two / width;
	m_world[1][1] = Rva0078C070MinusTwo / height;
	m_world[0][3] = worldTranslateX;
	m_world[1][3] = worldTranslateY;
	m_world[2][2] = 0.0f;
	m_world[2][3] = 0.5f;
	}

	Rva0078C070GlobalState.world = m_world.Transpose();
	Rva0078C070DirtyMask = (Rva0078C070DirtyMask & 0xfffbffff) | 1;
	m_vertexOffset = 0;
	d_0078b4f0();
}
