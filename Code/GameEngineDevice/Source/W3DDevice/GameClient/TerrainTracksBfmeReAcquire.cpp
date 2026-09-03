// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath
// readable body of ?ReAcquireResources@TerrainTracksRenderObjClassSystem@@QAEXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainTracks.cpp
// BFME retail 0x0072EC10: TerrainTracksRenderObjClassSystem::ReAcquireResources.

typedef int Int;
typedef unsigned short UnsignedShort;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
struct GlobalData
{
	char m_pad[0x1F0];
	Int m_maxTerrainTracks;
};

extern GlobalData *TheGlobalData;

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

	Int m_refCount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.h
class IndexBufferClass
{
public:
	class WriteLockClass
	{
		IndexBufferClass *m_indexBuffer;
		UnsignedShort *m_indices;

	public:
		WriteLockClass(IndexBufferClass *indexBuffer, Int flags = 0);
		~WriteLockClass(void);

		UnsignedShort *Get_Index_Array(void)
		{
			return m_indices;
		}
	};
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.h
class DX8IndexBufferClass : public RefCountedResource
{
public:
	enum UsageType
	{
		USAGE_DEFAULT = 0,
		USAGE_DYNAMIC = 1
	};

	DX8IndexBufferClass(unsigned indexCount, UsageType usage = USAGE_DEFAULT);

private:
	char m_bfmeTail[0x10];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.h
class DX8VertexBufferClass : public RefCountedResource
{
public:
	enum UsageType
	{
		USAGE_DEFAULT = 0,
		USAGE_DYNAMIC = 1
	};

	DX8VertexBufferClass(unsigned fvf, UnsignedShort vertexCount, UsageType usage,
		unsigned vertexSize);

private:
	char m_bfmeTail[0x18];
};

enum
{
	DX8_FVF_XYZDUV1 = 0x142
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainTracks.h
class TerrainTracksRenderObjClassSystem
{
public:
	void ReAcquireResources(void);

private:
	DX8VertexBufferClass *m_vertexBuffer;
	DX8IndexBufferClass *m_indexBuffer;
	char m_pad[0x14];
	Int m_maxTankTrackEdges;
};

void TerrainTracksRenderObjClassSystem::ReAcquireResources(void)
{
	Int i;
	const Int numModules = TheGlobalData->m_maxTerrainTracks;

	if (m_indexBuffer != 0)
	{
		m_indexBuffer->Release_Ref();
		m_indexBuffer = 0;
	}
	if (m_vertexBuffer != 0)
	{
		m_vertexBuffer->Release_Ref();
		m_vertexBuffer = 0;
	}

	m_indexBuffer = ::new DX8IndexBufferClass((m_maxTankTrackEdges - 1) * 6);

	{
		IndexBufferClass::WriteLockClass lockIdxBuffer((IndexBufferClass *)m_indexBuffer);
		UnsignedShort *ib = lockIdxBuffer.Get_Index_Array();

		for (i = 0; i < (m_maxTankTrackEdges - 1); i++)
		{
			ib[3] = ib[0] = (UnsignedShort)(i * 2);
			ib[1] = (UnsignedShort)(i * 2 + 1);
			ib[4] = ib[2] = (UnsignedShort)((i + 1) * 2 + 1);
			ib[5] = (UnsignedShort)((i + 1) * 2);
			ib += 6;
		}
	}

	m_vertexBuffer = ::new DX8VertexBufferClass(
		DX8_FVF_XYZDUV1,
		(UnsignedShort)(numModules * m_maxTankTrackEdges * 2),
		DX8VertexBufferClass::USAGE_DYNAMIC,
		0);
}
