// ?rva006BEB90@W3DTerrainLogic@@UAE_NVAsciiString@@PAVChunkInputStream@@_N2@Z
// partial score=0.99 date=2026-09-26
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// BFME retail RVA 0x006BEB90. Adapted from the Zero Hour W3DTerrainLogic::loadMap
// with the BFME stream argument, 16-bit height samples, and witnessed field offsets.
#include <vector>
#include <cstring>
#include "string_base.h"

typedef int Int;
typedef bool Bool;
typedef float Real;

// STLport's already-matched eight-byte POD boundary-vector instantiation.
struct Gen_t_006bea40_p8pod { Int x, y; };
typedef _STL::vector<Gen_t_006bea40_p8pod> BoundaryVector;

class AsciiString : public StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	const char *str() const { return m_data ? reinterpret_cast<const char *>(m_data) + 8 : ""; }
};

class ChunkInputStream
{
public:
	virtual Int read(void *, Int) = 0;
	virtual Int tell() = 0;
	virtual void absoluteSeek(Int) = 0;
	virtual Bool eof() = 0;
};

class WorldHeightMap
{
public:
	WorldHeightMap(ChunkInputStream *, Bool);
	virtual void deleteThis();
	void release() { if (--m_refCount == 0) deleteThis(); }
	Int getXExtent() const { return m_width; }
	Int getYExtent() const { return m_height; }
	const BoundaryVector &getAllBoundaries() const { return m_boundaries; }
	Int getMaxHeightValue() const { return 65535; }
	unsigned short getHeight(Int x, Int y) const {
		Int ndx = x + m_width * y;
		if (ndx >= 0 && ndx < m_dataSize && m_data) return m_data[ndx];
		return 0;
	}
private:
	Int m_refCount;
	Int m_width;
	Int m_height;
	Int m_border;
	BoundaryVector m_boundaries;
	Int m_dataSize;
	unsigned short *m_data;
	char m_rest[0x120f0 - 0x28];
};

class MapCache;
extern MapCache *TheMapCache;
extern Real g_bfmeHeightScale;

class TerrainLogic
{
public:
	virtual void unused00() = 0;
	Bool loadMapAbi(AsciiString filename, ChunkInputStream *stream, Bool tailFlag, Bool query);
private:
	char m_pad[0x10 - 4];
};

// This exact global is the BFME time-setting object matched at 0x00082AA0.
class BfmeXfJF
{
public:
	char m_pad[0x218];
	Int m_timeOfDay;
	Bool bfmeLoadJF(Int timeOfDay);
};
extern BfmeXfJF *TheWritableGlobalData;

class BfmeGameClient
{
public:
#define BFME_SLOT(n) virtual void slot##n() = 0;
	BFME_SLOT(00) BFME_SLOT(01) BFME_SLOT(02) BFME_SLOT(03)
	BFME_SLOT(04) BFME_SLOT(05) BFME_SLOT(06) BFME_SLOT(07)
	BFME_SLOT(08) BFME_SLOT(09) BFME_SLOT(10) BFME_SLOT(11)
	BFME_SLOT(12) BFME_SLOT(13) BFME_SLOT(14) BFME_SLOT(15)
	BFME_SLOT(16) BFME_SLOT(17) BFME_SLOT(18) BFME_SLOT(19)
	BFME_SLOT(20) BFME_SLOT(21) BFME_SLOT(22) BFME_SLOT(23)
	BFME_SLOT(24)
	virtual void setTimeOfDay(Int timeOfDay) = 0;
};
extern BfmeGameClient *TheGameClient;

class W3DTerrainLogic : public TerrainLogic
{
public:
	virtual Bool rva006BEB90(AsciiString filename, ChunkInputStream *stream,
		Bool tailFlag, Bool query);
private:
	Int m_mapDX;
	Int m_mapDY;
	char m_pad18[0x24 - 0x18];
	BoundaryVector m_boundaries;
	Int m_activeBoundary;
	char m_pad34[0x18fc - 0x34];
	Real m_mapMinZ;
	Real m_mapMaxZ;
};

Bool W3DTerrainLogic::rva006BEB90(AsciiString filename,
	ChunkInputStream *stream, Bool tailFlag, Bool query)
{
	if (!TheMapCache) return false;

	char tempBuf[260];
	char filenameBuf[260];
	strcpy(tempBuf, filename.str());
	Int length = strlen(tempBuf);
	if (length >= 4) {
		memset(filenameBuf, 0, 260);
		strncpy(filenameBuf, tempBuf, length - 4);
	}

	stream->absoluteSeek(0);
	WorldHeightMap *heightMap = new WorldHeightMap(stream, true);
	if (!heightMap) return false;

	m_mapDX = heightMap->getXExtent();
	m_mapDY = heightMap->getYExtent();
	m_boundaries = heightMap->getAllBoundaries();
	m_activeBoundary = 0;
	Int minHt = heightMap->getMaxHeightValue();
	Int maxHt = 0;
	for (Int j = 0; j < m_mapDY; j++) {
		for (Int i = 0; i < m_mapDX; i++) {
			unsigned short cur = heightMap->getHeight(i,j);
			if (cur < minHt) minHt = cur;
			if (maxHt < cur) maxHt = cur;
		}
	}
	m_mapMinZ = minHt * g_bfmeHeightScale;
	m_mapMaxZ = maxHt * g_bfmeHeightScale;
	heightMap->release();

	if (TerrainLogic::loadMapAbi(filename, stream, tailFlag, query)) {
		Int timeOfDay = TheWritableGlobalData->m_timeOfDay;
		if (TheWritableGlobalData->bfmeLoadJF(timeOfDay)) {
			BfmeXfJF *writable = TheWritableGlobalData;
			BfmeGameClient *client = TheGameClient;
			Int updatedTimeOfDay = writable->m_timeOfDay;
			client->setTimeOfDay(updatedTimeOfDay);
		}
		return true;
	}
	return false;
}
