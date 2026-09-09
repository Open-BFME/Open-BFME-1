// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode
// stlport

// Retail 0x0078B310 constructs the named Rva00785FD0Renderer object.
// The 0x00782ED0 allocator passes its 0xE0 object to ILT 0x0003164C,
// which jumps here.  The named setMode/stencil/destructor routes prove the
// mode, stencil-generation, texture-handle, and vertex-buffer members below.

#include "Libraries/Source/WWVegas/WWMath/matrix4.h"

class DX8VertexBufferClass
{
public:
	enum UsageType { USAGE_DEFAULT = 0, USAGE_DYNAMIC = 1 };

	DX8VertexBufferClass(unsigned fvf, unsigned short count, UsageType usage,
		unsigned vertex_size);
	virtual ~DX8VertexBufferClass();

private:
	unsigned char m_body[0x1c];
};

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
	Rva00785FD0Renderer();

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

Rva00785FD0Renderer::Rva00785FD0Renderer()
	:
		m_modeChanged(false),
		m_pendingTextureChange(false),
		m_mode(0),
		m_stencilGeneration(0),
		m_world(true),
		m_view(true),
		m_projection(true),
		m_vertexBuffer(0),
		m_vertexOffset(0),
		m_vertexCount(0),
		m_reserved(0)
{
	m_vertexBuffer = new DX8VertexBufferClass(
		0x242, 0x4e20, DX8VertexBufferClass::USAGE_DYNAMIC, 0);
}
