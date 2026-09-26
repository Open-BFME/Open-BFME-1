// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// ?loadMapAbi@W3DTerrainLogic@@UAE_NVAsciiString@@PAVChunkInputStream@@_N2@Z

#include <string.h>
#include <vector>

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned short UnsignedShort;

#define MAP_HEIGHT_SCALE (0.625f)

struct Gen_t_006bea40_p8pod
{
	Int x;
	Int y;
};

typedef _STL::vector<Gen_t_006bea40_p8pod> BoundaryVector;

#include "string_base.h"

class AsciiString : public StringBase<char>
{
public:
	AsciiString(void) : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString(const char *text);
	~AsciiString();

	const char *str(void) const
	{
		static const char empty = 0;
		return m_data ? reinterpret_cast<const char *>(m_data) + 8 : &empty;
	}
};

class ChunkInputStream
{
public:
	virtual Int read(void *data, Int bytes);
	virtual Int tell(void);
	virtual void absoluteSeek(Int position);
};

class Rva0074EB10RefCountClass
{
public:
	void Release_Ref(void)
	{
		m_numRefs--;
		if (m_numRefs == 0)
			Delete_This();
	}

protected:
	virtual void Delete_This(void);

	private:
	Int m_numRefs;
};

class WorldHeightMap : public Rva0074EB10RefCountClass
{
public:
	WorldHeightMap(ChunkInputStream *, Bool);

	Int getXExtent(void) const { return m_width; }
	Int getYExtent(void) const { return m_height; }
	const BoundaryVector &getAllBoundaries(void) const { return m_boundaries; }
	static Int getMaxHeightValue(void) { return 0xffff; }

	UnsignedShort getHeight(Int xIndex, Int yIndex) const
	{
		Int ndx = xIndex + m_width * yIndex;
		if (ndx >= 0 && ndx < m_dataSize && m_data != 0)
			return m_data[ndx];
		return 0;
	}

private:
	Int m_width;
	Int m_height;
	Int m_borderSize;
	BoundaryVector m_boundaries;
	Int m_dataSize;
	UnsignedShort *m_data;
	char m_tail[0x120f0 - 0x28];
};

class TerrainLogic
{
public:
	Bool loadMapAbi(AsciiString filename, ChunkInputStream *stream,
		Bool tailFlag, Bool query);
};

class __declspec(novtable) W3DTerrainLogic
{
public:
	virtual Bool loadMapAbi(AsciiString filename, ChunkInputStream *stream,
		Bool tailFlag, Bool query);

private:
	char m_pad04[0x10 - 4];
	Int m_mapDX;
	Int m_mapDY;
	char m_pad18[0x24 - 0x18];
	BoundaryVector m_boundaries;
	Int m_activeBoundary;
	char m_pad34[0x18fc - 0x34];
	Real m_mapMinZ;
	Real m_mapMaxZ;
};

class MapCache;
#define TheMapCache (*(MapCache **)0x012F1594)

class BfmeXfJF
{
public:
	Bool bfmeLoadJF(Int timeOfDay);

	unsigned char m_bfmeHeadJF[0x218];
	Int m_timeOfDay;
};

#define TheWritableGlobalData (*(BfmeXfJF **)0x012ED5C8)

class BfmeGlobalData
{
public:
	unsigned char m_bfmeHeadJF[0x218];
	Int m_timeOfDay;
};

#define TheGlobalData (*(BfmeGlobalData **)0x012ED5C8)

class GameClient
{
public:
	virtual void pad00(void);
	virtual void pad04(void);
	virtual void pad08(void);
	virtual void pad0c(void);
	virtual void pad10(void);
	virtual void pad14(void);
	virtual void pad18(void);
	virtual void pad1c(void);
	virtual void pad20(void);
	virtual void pad24(void);
	virtual void pad28(void);
	virtual void pad2c(void);
	virtual void pad30(void);
	virtual void pad34(void);
	virtual void pad38(void);
	virtual void pad3c(void);
	virtual void pad40(void);
	virtual void pad44(void);
	virtual void pad48(void);
	virtual void pad4c(void);
	virtual void pad50(void);
	virtual void pad54(void);
	virtual void pad58(void);
	virtual void pad5c(void);
	virtual void pad60(void);
	virtual void setTimeOfDay(Int timeOfDay);
};

#define TheGameClient (*(GameClient **)0x012F1464)

Bool W3DTerrainLogic::loadMapAbi(AsciiString filename,
	ChunkInputStream *stream, Bool tailFlag, Bool query)
{
	if (!TheMapCache)
		return false;

	WorldHeightMap *terrainHeightMap;
	char tempBuf[260];
	char filenameBuf[260];
	Int length = 0;

	strcpy(tempBuf, filename.str());
	length = strlen(tempBuf);
	if (length >= 4)
	{
		memset(filenameBuf, '\0', 260);
		strncpy(filenameBuf, tempBuf, length - 4);
	}

	stream->absoluteSeek(0);
	terrainHeightMap = new WorldHeightMap(stream, true);
	if (terrainHeightMap)
	{
		m_mapDX = terrainHeightMap->getXExtent();
		m_mapDY = terrainHeightMap->getYExtent();
		m_boundaries = terrainHeightMap->getAllBoundaries();
		m_activeBoundary = 0;

		Int i;
		Int j;
		Int minHt;
		Int maxHt;
		minHt = terrainHeightMap->getMaxHeightValue();
		maxHt = 0;
		for (j = 0; j < m_mapDY; ++j)
		{
			for (i = 0; i < m_mapDX; ++i)
			{
				UnsignedShort cur = terrainHeightMap->getHeight(i, j);
				if (cur < minHt)
					minHt = cur;
				if (maxHt < cur)
					maxHt = cur;
			}
		}
		m_mapMinZ = minHt * MAP_HEIGHT_SCALE;
		m_mapMaxZ = maxHt * MAP_HEIGHT_SCALE;
		terrainHeightMap->Release_Ref();
	}
	else
	{
		return false;
	}

	if (reinterpret_cast<TerrainLogic *>(this)->loadMapAbi(
		filename, stream, tailFlag, query) == false)
		return false;

	BfmeXfJF *writableGlobalData = TheWritableGlobalData;
	Int timeOfDay = writableGlobalData->m_timeOfDay;
	if (writableGlobalData->bfmeLoadJF(timeOfDay))
	{
		BfmeGlobalData *globalData = TheGlobalData;
		GameClient *gameClient = TheGameClient;
		gameClient->setTimeOfDay(globalData->m_timeOfDay);
	}

	return true;
}

#pragma comment(linker, "/alternatename:?loadMap@W3DTerrainLogic@@UAE_NVAsciiString@@_N@Z=?loadMapAbi@W3DTerrainLogic@@UAE_NVAsciiString@@PAVChunkInputStream@@_N2@Z")
