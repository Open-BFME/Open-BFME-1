// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii/Common /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// MapUtil loadMap (retail 0x00454B00, 802 B) and the out-of-line
// WaypointMap default constructor its NEW expression calls (0x00453D10, 61 B).
//
// Identity: the matched MapCache::addMap (0x004570F0) calls this body at the
// point where Zero Hour's addMap calls loadMap(fname); the body registers
// "HeightMapData", "WorldInfo" and "ObjectsList" with the matched callbacks
// ParseSizeOnlyInChunk, ParseWorldDictDataChunk and ParseObjectsDataChunk,
// allocates the waypoint map and computes mapDX/mapDY exactly as ZH loadMap.
// BFME adds a MapMetaData* parameter (addMap passes &md) whose +0x54 block is
// handed to the MPPositionList parser registration (matched ctor 0x00450460).
//
// WaypointMap: the matched BFME MapMetaData constructor (0x004543D0) inlines
// WaypointMap() : m_numStartSpots(0), zeroing +0xC after the map header, which
// is the 0x00453D10 body; MSVC keeps that inline constructor out of line in the
// NEW expression, giving retail's saved allocation and delete-on-throw state.
// Evidence: targets/game/reverse/identity_evidence/00453d10-waypointmap-ctor.md
//
// The parser, stream and registration views below carry only the fields and
// ABIs this body witnesses (DataChunkInput is BFME's 40-byte layout).

#include <string.h>
#include <map>

#include "AsciiString.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef unsigned short DataChunkVersionType;

class DataChunkInput;
class UserParser;
struct DataChunkInfo;

typedef Bool (*DataChunkParserPtr)(DataChunkInput &, DataChunkInfo *, void *);

class ChunkInputStream
{
public:
	virtual Int read(void *data, Int size) = 0;
	virtual UnsignedInt tell(void) = 0;
	virtual Bool absoluteSeek(UnsignedInt position) = 0;
	virtual Bool eof(void) = 0;
};

class CachedFileInputStream : public ChunkInputStream
{
public:
	CachedFileInputStream(void);
	~CachedFileInputStream(void);
	Bool open(AsciiString path);
	virtual Int read(void *data, Int size);
	virtual UnsignedInt tell(void);
	virtual Bool absoluteSeek(UnsignedInt position);
	virtual Bool eof(void);

private:
	Int m_size;
	char *m_buffer;
	Int m_pos;
};

class DataChunkInput
{
public:
	DataChunkInput(ChunkInputStream *stream);
	~DataChunkInput(void);
	UserParser *registerParser(const AsciiString &label,
		const AsciiString &parentLabel, DataChunkParserPtr parser,
		void *userData = 0);
	Bool parse(void *userData);

private:
	char m_layout[0x28];
};

// This is the proven parser-registration cleanup ABI.  It is a non-virtual
// view used only for the direct call at the retail 0x0000871A target; making
// it a base of DataChunkInput would corrupt that class's observed layout.
class BfmeSubVE
{
public:
	void bfmeDropVE(void *what);
};

class Rva00450460ParserRegistration
{
public:
	Rva00450460ParserRegistration(void *extra, DataChunkInput *table,
		AsciiString *labelOverride);

	~Rva00450460ParserRegistration(void)
	{
		m_vftable = (void *)0x0107C7D0;
		((BfmeSubVE *)m_table)->bfmeDropVE(m_parser);
	}

private:
	void *m_vftable;
	DataChunkInput *m_table;
	void *m_parser;
	void *m_extra;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class WaypointMap : public _STL::map<AsciiString, Coord3D>
{
public:
	WaypointMap() : m_numStartSpots(0) {}
	Int m_numStartSpots;
};

class MapMetaData;

// MapUtil file-scope state (ZH m_waypoints, m_width, m_height, m_borderSize,
// m_mapDX, m_mapDY); the retail addresses name them, as in MapCacheAddMap.cpp.
extern WaypointMap *Rva012F1588;
extern Int Rva012F1574;
extern Int Rva012F1578;
extern Int Rva012F157C;
extern Int Rva012F158C;
extern Int Rva012F1590;

// Chunk callbacks registered by this body (matched rows 0x004542E0,
// 0x0044F710 and 0x00454A60).
Bool ParseSizeOnlyInChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);
Bool ParseWorldDictDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);
Bool ParseObjectsDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);

// ?loadMap@@YA_NVAsciiString@@PAVMapMetaData@@@Z
Bool loadMap(AsciiString filename, MapMetaData *metadata)
{
	char tempBuf[260];
	char filenameBuf[260];
	AsciiString asciiFile;
	Int length = 0;

	strcpy(tempBuf, filename.str());
	length = strlen(tempBuf);
	if (length >= 4)
	{
		memset(filenameBuf, '\0', 260);
		strncpy(filenameBuf, tempBuf, length - 4);
	}

	CachedFileInputStream fileStrm;
	asciiFile = filename;
	if (!fileStrm.open(asciiFile))
		return false;

	ChunkInputStream *pStrm = &fileStrm;
	DataChunkInput file(pStrm);

	Rva012F1588 = new WaypointMap;

	file.registerParser(AsciiString("HeightMapData"),
		AsciiString::TheEmptyString, ParseSizeOnlyInChunk);
	file.registerParser(AsciiString("WorldInfo"),
		AsciiString::TheEmptyString, ParseWorldDictDataChunk);
	file.registerParser(AsciiString("ObjectsList"),
		AsciiString::TheEmptyString, ParseObjectsDataChunk);

	// No BFME MapMetaData layout is witnessed past +0x50; +0x54 is the
	// eight-record player block (Rva000C0C60MapPlayers) the MPPositionList
	// parser fills.
	Rva00450460ParserRegistration positionParser(
		(char *)metadata + 0x54, &file, 0);
	if (!file.parse(0))
		throw 0xDEAD0005;	// ZH ERROR_CORRUPT_FILE_FORMAT; retail throws it as unsigned int

	Rva012F158C = Rva012F1574 - 2 * Rva012F157C;
	Rva012F1590 = Rva012F1578 - 2 * Rva012F157C;

	return true;
}
