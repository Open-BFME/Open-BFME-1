// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// readable body of ?ReAcquireResources@WaterTracksRenderSystem@@QAEXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterTracks.cpp
// BFME retail 0x007AAD20: WaterTracksRenderSystem::ReAcquireResources.

#define WATER_VB_PAGES 1000

typedef unsigned short UnsignedShort;

// BFME's resource classes have the same witnessed refcount/vtable prefix as
// the neighboring TerrainTracks converter, but their full headers introduce
// constructor overloads that are not part of this retail call shape.
class RefCountedResource
{
public:
	virtual void Delete_This(void);

	void Release_Ref(void)
	{
		--m_refCount;
		if (m_refCount == 0)
			Delete_This();
	}

	int m_refCount;
};

class IndexBufferClass
{
public:
	class WriteLockClass
	{
		IndexBufferClass *m_indexBuffer;
		UnsignedShort *m_indices;

	public:
		WriteLockClass(IndexBufferClass *indexBuffer, int flags = 0);
		~WriteLockClass(void);

		UnsignedShort *Get_Index_Array(void)
		{
			return m_indices;
		}
	};
};

class DX8IndexBufferClass : public RefCountedResource
{
public:
	typedef IndexBufferClass::WriteLockClass WriteLockClass;

	enum UsageType
	{
		USAGE_DEFAULT = 0,
		USAGE_DYNAMIC = 1
	};

	DX8IndexBufferClass(unsigned indexCount, UsageType usage = USAGE_DEFAULT);

private:
	unsigned char m_bfmeTail[0x10];
};

class DX8VertexBufferClass : public RefCountedResource
{
public:
	enum UsageType
	{
		USAGE_DEFAULT = 0,
		USAGE_DYNAMIC = 1
	};

	DX8VertexBufferClass(unsigned fvf, UnsignedShort vertexCount,
		UsageType usage, unsigned vertexSize);

private:
	unsigned char m_bfmeTail[0x18];
};

enum
{
	DX8_FVF_XYZDUV1 = 0x142
};

class Rva007AAD20WaterTracksRenderSystem
{
public:
	// The first two fields are the BFME resource pointers.  The remaining
	// prefix is intentionally opaque; only the witnessed scalar offsets below
	// participate in this body.
	DX8VertexBufferClass *m_vertexBuffer;
	DX8IndexBufferClass *m_indexBuffer;
	unsigned char m_beforeStripSizeX[0x10];
	int m_stripSizeX;
	int m_stripSizeY;
	int m_batchStart;
	float m_level;

	void ReAcquireResources(void);
};

// ?ReAcquireResources@WaterTracksRenderSystem@@QAEXXZ
void Rva007AAD20WaterTracksRenderSystem::ReAcquireResources(void)
{
	int i, j, k;

	if (m_indexBuffer)
	{
		m_indexBuffer->Release_Ref();
		*(DX8IndexBufferClass * volatile *)&m_indexBuffer = 0;
	}
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release_Ref();
		*(DX8VertexBufferClass * volatile *)&m_vertexBuffer = 0;
	}

	int idxCount = (m_stripSizeY - 1) * (m_stripSizeX * 2 + 2) - 2;

	m_indexBuffer = new DX8IndexBufferClass(idxCount);

	{
		DX8IndexBufferClass::WriteLockClass lockIdxBuffer((IndexBufferClass *)m_indexBuffer);
		unsigned short *ib = lockIdxBuffer.Get_Index_Array();

		for (i = 0, j = 0, k = 0; i < idxCount; j++)
		{
			for (; k < (m_stripSizeX * (j + 1)); k++, i += 2)
			{
				ib[i] = (unsigned short)k + m_stripSizeX;
				ib[i + 1] = (unsigned short)k;
			}
			if (i < idxCount)
			{
				ib[i] = k - 1;
				ib[i + 1] = k + m_stripSizeX;
				i += 2;
			}
		}
	}

	m_vertexBuffer = new DX8VertexBufferClass(
		DX8_FVF_XYZDUV1,
		(UnsignedShort)(m_stripSizeX * m_stripSizeY * WATER_VB_PAGES),
		DX8VertexBufferClass::USAGE_DYNAMIC, 0);
	m_batchStart = 0;
}
