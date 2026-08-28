// cl: /DNDEBUG /MD /EHsc
// readable body of ?ReAcquireResources@W3DVolumetricShadowManager@@QAE_NXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow.cpp

// Retail 0x007C1180, 179 bytes. Two allocations, each the standard MSVC
// expansion of new with a constructor: push the size, call operator new, park
// the raw pointer in the one four-byte local the frame has, test it, and only
// then run the constructor -- with an exception state written around the
// constructor so a throw there frees the block. The states are 0 for the first
// and 1 for the second, which is why the second never returns to -1: nothing
// follows it.
//
// The arguments and sizes name the two classes exactly. 0x20 bytes taking
// (2, 0x7530, 1, 0) is DX8VertexBufferClass; 0x18 bytes taking (0x7530, 1) is
// DX8IndexBufferClass, whose row at 0x0091D0A0 is the uint-width alias. 0x7530
// is 30000 in both.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.h
class DX8VertexBufferClass
{
public:
	enum UsageType
	{
		USAGE_DEFAULT = 0,
		USAGE_DYNAMIC = 1
	};

	DX8VertexBufferClass(UnsignedInt fvf, UnsignedShort count, UsageType usage, UnsignedInt flags);

private:
	char m_bfmeBody[0x20];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.h
class DX8IndexBufferClass
{
public:
	enum UsageType
	{
		USAGE_DEFAULT = 0,
		USAGE_DYNAMIC = 1
	};

	DX8IndexBufferClass(UnsignedInt count, UsageType usage);

private:
	char m_bfmeBody[0x18];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DVolumetricShadow.h
class W3DVolumetricShadowManager
{
public:
	Bool ReAcquireResources(void);

private:
	DX8VertexBufferClass *m_bfmeVertexBuffer;			// +0x00
	DX8IndexBufferClass *m_bfmeIndexBuffer;				// +0x04
};

// ?ReAcquireResources@W3DVolumetricShadowManager@@QAE_NXZ
Bool W3DVolumetricShadowManager::ReAcquireResources(void)
{
	if (m_bfmeVertexBuffer == 0)
		m_bfmeVertexBuffer = new DX8VertexBufferClass(2, 30000, DX8VertexBufferClass::USAGE_DYNAMIC, 0);

	if (m_bfmeIndexBuffer == 0)
		m_bfmeIndexBuffer = new DX8IndexBufferClass(30000, DX8IndexBufferClass::USAGE_DYNAMIC);

	return true;
}
