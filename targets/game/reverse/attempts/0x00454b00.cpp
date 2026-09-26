// ?Rva00454B00LoadMap@@YA_NVAsciiString@@PAX@Z
// partial score=0.47 date=2026-09-23
// Clean C++ reconstruction of the 802-byte retail body at 0x00454B00.
// The address-derived function name is intentional: the caller proves a
// filename plus a second context pointer, while the semantic owner is not
// established independently.  The parser, stream, map and metadata views
// below are limited to the fields and ABIs witnessed by this body.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringbaseascii/Common /ICode/Libraries/Source/WWVegas/WWLib

#include <string.h>
#include <new>

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

// The 0x00453D10 callee is independently verified as the 0x10-byte
// map/sentinel initializer, despite its stale additive ledger spelling
// BfmeThingAVC.  Calling that body through its existing proven ABI keeps the
// target's operator-new/null-check/call sequence without claiming that name
// for the waypoint owner.
class BfmeThingAVC
{
public:
	BfmeThingAVC *bfmeInitAVC(void);

private:
	char m_layout[0x10];
};

class Rva00454B00WaypointMap
{
public:
	Rva00454B00WaypointMap(void)
	{
		((BfmeThingAVC *)this)->bfmeInitAVC();
	}

private:
	char m_layout[0x10];
};

// The body allocates the 0x10-byte map object and leaves it live globally.
#define Rva00454B00Waypoints (*(BfmeThingAVC **)0x012F1588)
#define Rva00454B00Width (*(Int *)0x012F1574)
#define Rva00454B00Height (*(Int *)0x012F1578)
#define Rva00454B00BorderSize (*(Int *)0x012F157C)
#define Rva00454B00MapDX (*(Int *)0x012F158C)
#define Rva00454B00MapDY (*(Int *)0x012F1590)

// The callback identities and ABIs are established by their matched rows;
// using their retail addresses here avoids importing a TU-local static name.
static DataChunkParserPtr const Rva00454B00ParseSizeOnly =
	(DataChunkParserPtr)0x004542E0;
static DataChunkParserPtr const Rva00454B00ParseWorldInfo =
	(DataChunkParserPtr)0x0044F710;
static DataChunkParserPtr const Rva00454B00ParseObjects =
	(DataChunkParserPtr)0x00454A60;

// ?Rva00454B00LoadMap@@YA_NVAsciiString@@PAX@Z
Bool Rva00454B00LoadMap(AsciiString filename, void *metadata)
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

	// Retail allocates 0x10 bytes, null-checks the returned pointer, and calls
	// the 0x00453D10 initializer on that storage.  Its callee body writes four
	// owner dwords and a 0x20-byte sentinel node, then returns the owner in EAX.
	BfmeThingAVC *waypoints =
		(BfmeThingAVC *)::operator new(sizeof(BfmeThingAVC));
	if (waypoints != 0)
	{
		new (waypoints) BfmeThingAVC;
		waypoints = waypoints->bfmeInitAVC();
	}
	Rva00454B00Waypoints = waypoints;

	file.registerParser(AsciiString("HeightMapData"),
		AsciiString::TheEmptyString, Rva00454B00ParseSizeOnly);
	file.registerParser(AsciiString("WorldInfo"),
		AsciiString::TheEmptyString, Rva00454B00ParseWorldInfo);
	file.registerParser(AsciiString("ObjectsList"),
		AsciiString::TheEmptyString, Rva00454B00ParseObjects);

	Rva00450460ParserRegistration positionParser(
		(char *)metadata + 0x54, &file, 0);
	if (!file.parse(0))
		throw 0xDEAD0005;

	Rva00454B00MapDX = Rva00454B00Width - 2 * Rva00454B00BorderSize;
	Rva00454B00MapDY = Rva00454B00Height - 2 * Rva00454B00BorderSize;

	return true;
}
