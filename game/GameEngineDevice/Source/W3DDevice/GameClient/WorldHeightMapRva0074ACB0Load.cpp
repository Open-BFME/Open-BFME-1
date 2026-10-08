// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii/Common /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x0074ACB0 (1511 bytes, RET 8): the parser-load helper BFME split
// out of WorldHeightMap::WorldHeightMap(ChunkInputStream *, Bool).  Its sole
// caller is that constructor (WorldHeightMap_stream_ctor.cpp), which passes
// its DataChunkInput local and the bool; the name keeps the address token
// because only the caller, not a symbol, identifies the helper.
//
// The body is the Zero Hour stream constructor's middle (stretchTerrain draw
// size, the two registration sets, parse-or-throw, the bad-map index patch,
// drawEntireTerrain and the clamp, TheSidesList->validateSides()) with BFME's
// scoped registrations: each registration object unregisters its UserParser
// in its destructor, so parse() runs inside each branch.  The bindings,
// BfmeOwnCP and the base registration follow the matched
// CachedSidesLoader0019EC80.cpp, which registers the same Teams /
// LibraryMapLists callbacks (ILT 0x4A755 and 0x283A3) on a SidesList.
//
// Offsets: m_width +0x08, m_dataSize +0x20 and m_cliffInfoNdxes +0x94 are
// layout-witnessed; m_height, m_blendTileNdxes, m_extraBlendTileNdxes and
// m_drawWidthX/m_drawHeightY are the ZH members this body uses in the same
// statements (height beside width; the three index arrays in the ZH patch
// loop order; the draw size set to 65 under m_stretchTerrain and to the map
// size under m_drawEntireTerrain).  The two element vectors keep offset names.

#include "AsciiString.h"

// Retail inlines ~AsciiString: temporaries are released by a direct call to
// StringBase<char>::releaseBuffer (0x00887940), not the ??1AsciiString stub.
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

typedef int Int;
typedef bool Bool;

enum ErrorCode
{
	ERROR_CORRUPT_FILE_FORMAT = 0xDEAD0005
};

class UserParser;
struct DataChunkInfo;

class DataChunkInput
{
public:
	Bool parse(void *userData);
	UserParser *registerParser(const AsciiString &name, const AsciiString &label,
		Bool (*parser)(DataChunkInput &, DataChunkInfo *, void *), void *userData);
};

class BfmeSubVE
{
public:
	void bfmeDropVE(void *value);
};

typedef Bool (*ChunkParserCallback)(DataChunkInput &, DataChunkInfo *, void *);

// Retail vtable 0x0107C7D0: BfmeParserBindingBaseVE's vftable, i.e.
// ??_7BfmeParserBindingBaseVE@@6B@ (targets/game/reverse/dir32_addresses.csv).
// The declaration carries no C++ name: __identifier spells the retail symbol
// exactly, so the stores below reference the defining name.
extern "C" int __identifier("??_7BfmeParserBindingBaseVE@@6B@")[];
extern int g_0109BFD4[];
void j_0001579e();
void j_0004a755();
void j_00043c93();
void j_000283a3();

// ---- parser registrations ---------------------------------------------

class BfmeParserRegistrationVE
{
public:
	BfmeParserRegistrationVE(DataChunkInput *file, const AsciiString &label,
		const AsciiString &parent)
	{
		m_vftable = __identifier("??_7BfmeParserBindingBaseVE@@6B@");
		m_file = file;
		m_parser = file->registerParser(label, parent,
			(ChunkParserCallback)j_0001579e, this);
	}

	~BfmeParserRegistrationVE()
	{
		m_vftable = __identifier("??_7BfmeParserBindingBaseVE@@6B@");
		((BfmeSubVE *)m_file)->bfmeDropVE(m_parser);
	}

protected:
	void *m_vftable;
	DataChunkInput *m_file;
	UserParser *m_parser;
};

class SidesList;

#pragma pointers_to_members(full_generality, multiple_inheritance)
typedef Bool (SidesList::*Rva0074ACB0SidesCallback)(DataChunkInput &, DataChunkInfo *);

static __forceinline Rva0074ACB0SidesCallback rva0074ACB0Callback(unsigned int address)
{
	union Bits
	{
		Rva0074ACB0SidesCallback method;
		struct
		{
			unsigned int address;
			int adjustment;
		} words;
	} bits;
	bits.words.address = address;
	bits.words.adjustment = 0;
	return bits.method;
}

class BfmeParserBindingVE : public BfmeParserRegistrationVE
{
public:
	__forceinline BfmeParserBindingVE(SidesList *owner, Rva0074ACB0SidesCallback callback,
		DataChunkInput *file, const AsciiString &label)
		: BfmeParserRegistrationVE(file, label, AsciiString::TheEmptyString)
	{
		m_vftable = g_0109BFD4;
		m_owner = owner;
		m_callback = callback;
	}

private:
	SidesList *m_owner;
	Rva0074ACB0SidesCallback m_callback;
};

class Rva0074A3B0ParserRegistration : public BfmeParserRegistrationVE
{
public:
	Rva0074A3B0ParserRegistration(void *context, DataChunkInput *file, AsciiString *label);

private:
	void *m_context;
};

class Rva00088F50ParserRegistration : public BfmeParserRegistrationVE
{
public:
	Rva00088F50ParserRegistration(void *context, DataChunkInput *file, AsciiString *label);

private:
	void *m_context;
};

class Rva00190E10PolygonParser : public BfmeParserRegistrationVE
{
public:
	Rva00190E10PolygonParser(DataChunkInput *file, AsciiString *label);

private:
	char m_body[0x0c];
};

class Rva0074A2C0ParserRegistration : public BfmeParserRegistrationVE
{
public:
	Rva0074A2C0ParserRegistration(void *context, DataChunkInput *file, AsciiString *label);

private:
	void *m_context;
};

class Rva0074A4A0ParserRegistration : public BfmeParserRegistrationVE
{
public:
	Rva0074A4A0ParserRegistration(void *context, DataChunkInput *file, AsciiString *label);

private:
	void *m_context;
};

class Rva0074A680ParserRegistration : public BfmeParserRegistrationVE
{
public:
	Rva0074A680ParserRegistration(DataChunkInput *file, AsciiString *label);
};

class Rva0074A590ParserRegistration : public BfmeParserRegistrationVE
{
public:
	Rva0074A590ParserRegistration(void *context, DataChunkInput *file, AsciiString *label);

private:
	void *m_context;
};

class BfmeThingXB
{
public:
	BfmeThingXB *bfmeInitXB(void *owner, void *file, void *label);
};

// 0x00192720 is the out-of-line constructor of this registration (it returns
// this); 0x00191640 is its matched destructor.
class BfmeOwnCP
{
public:
	__forceinline BfmeOwnCP(SidesList *owner, DataChunkInput *file, AsciiString *label)
	{
		((BfmeThingXB *)this)->bfmeInitXB(owner, file, label);
	}

	~BfmeOwnCP();

private:
	char m_storage[0x9c];
};

// ---- globals --------------------------------------------------------------

class GlobalData
{
public:
	char m_pad00[0x4e];
	Bool m_stretchTerrain;			// +0x4E
	Bool m_useHalfHeightMap;		// +0x4F
	Bool m_drawEntireTerrain;		// +0x50
};

extern GlobalData *TheWritableGlobalData;

class SidesList
{
public:
	Bool validateSides();
};

// The matched body is a private member (AAE); this helper is its caller.
class Rva0019BE80SidesList
{
	friend class WorldHeightMap;

private:
	void clearSideStorageAt0019B4C0();
};

class Rva001A0320Owner
{
public:
	void fillAll();
};

extern SidesList *TheSidesList;

class Rva0074ACB0MapObject
{
public:
	virtual ~Rva0074ACB0MapObject();
};

class BfmeMapObjectListHolder;

extern BfmeMapObjectListHolder *BfmeTheMapObjectListHolder;

class Dict
{
public:
	void clear();
};

extern Dict g_Va012ED5E0;
extern char g_Va012A7A48[];
extern unsigned int *RvaGlobal012A7A48;
class View
{
public:
	void clearMarkers0045C8A0();

	char m_pad00[0x80];
	char m_field80[4];
};

extern View *TheTacticalView;

class BaseHeightMapRenderObjClass
{
public:
	static Bool ParseEnvironmentData(DataChunkInput &file, DataChunkInfo *info, void *userData);
};

// ZH WorldHeightMap.cpp's file-static helper, inlined here as in retail.
static void freeListOfMapObjects()
{
	if (*reinterpret_cast<Rva0074ACB0MapObject **>(BfmeTheMapObjectListHolder))
	{
		delete *reinterpret_cast<Rva0074ACB0MapObject **>(BfmeTheMapObjectListHolder);
		*reinterpret_cast<Rva0074ACB0MapObject **>(BfmeTheMapObjectListHolder) = 0;
	}
	g_Va012ED5E0.clear();
}

// ---- WorldHeightMap ---------------------------------------------------------

struct Rva0074ACB0Element10
{
	char m_bytes[0x10];
};

struct Rva0074ACB0Element24
{
	char m_bytes[0x24];
};

template <class T>
class Rva0074ACB0Vector
{
public:
	unsigned int size() const
	{
		return m_finish - m_start;
	}

	T *m_start;
	T *m_finish;
	T *m_end_of_storage;
};

class WorldHeightMap
{
public:
	static void setupAlphaTiles();

protected:
	static Bool ParseWorldDictDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);
	void parse(DataChunkInput &input, Bool parseSizeOnly);

private:
	void *m_vftable;
	Int m_numRefs;
	Int m_width;				// +0x08
	Int m_height;				// +0x0C
	char m_pad10[0x10];
	Int m_dataSize;				// +0x20
	char m_pad24[0x6c];
	Int *m_blendTileNdxes;			// +0x90
	Int *m_cliffInfoNdxes;			// +0x94
	Int *m_extraBlendTileNdxes;		// +0x98
	char m_pad9c[0x8008];
	Rva0074ACB0Vector<Rva0074ACB0Element10> m_vector80A4;	// +0x80A4
	Rva0074ACB0Vector<Rva0074ACB0Element24> m_vector80B0;	// +0x80B0
	char m_pad80bc[0x120e8 - 0x80bc];
	Int m_drawWidthX;			// +0x120E8
	Int m_drawHeightY;			// +0x120EC
};

void WorldHeightMap::parse(DataChunkInput &file, Bool parseSizeOnly)
{
	if (TheWritableGlobalData && TheWritableGlobalData->m_stretchTerrain)
	{
		m_drawWidthX = 65;
		m_drawHeightY = 65;
	}

	if (parseSizeOnly)
	{
		Rva0074A3B0ParserRegistration heightMapData(this, &file, 0);
		file.registerParser(AsciiString("WorldInfo"), AsciiString::TheEmptyString,
			ParseWorldDictDataChunk, 0);
		Rva00088F50ParserRegistration objectsList(&RvaGlobal012A7A48, &file, 0);

		freeListOfMapObjects();

		Rva00190E10PolygonParser polygonTriggers(&file, 0);
		((Rva0019BE80SidesList *)TheSidesList)->clearSideStorageAt0019B4C0();

		BfmeParserBindingVE teams(TheSidesList, rva0074ACB0Callback((unsigned int)j_0004a755),
			&file, AsciiString("Teams"));
		BfmeOwnCP scripts(TheSidesList, &file, 0);
		BfmeParserBindingVE sides(TheSidesList, rva0074ACB0Callback((unsigned int)j_00043c93),
			&file, AsciiString("SidesList"));
		BfmeParserBindingVE libraries(TheSidesList, rva0074ACB0Callback((unsigned int)j_000283a3),
			&file, AsciiString("LibraryMapLists"));

		if (!file.parse(this))
			throw ERROR_CORRUPT_FILE_FORMAT;

		((Rva001A0320Owner *)TheSidesList)->fillAll();
	}
	else
	{
		Rva0074A2C0ParserRegistration heightMapData(this, &file, 0);
		Rva0074A4A0ParserRegistration blendTileData(this, &file, 0);
		Rva0074A680ParserRegistration globalLighting(&file, 0);
		file.registerParser(AsciiString("EnvironmentData"), AsciiString::TheEmptyString,
			BaseHeightMapRenderObjClass::ParseEnvironmentData, 0);
		TheTacticalView->clearMarkers0045C8A0();
		Rva0074A590ParserRegistration namedCameras(TheTacticalView->m_field80, &file, 0);

		if (!file.parse(this))
			throw ERROR_CORRUPT_FILE_FORMAT;

		for (Int i = 0; i < m_dataSize; i++)
		{
			if (m_cliffInfoNdxes[i] < 0 || m_cliffInfoNdxes[i] >= m_vector80B0.size())
				m_cliffInfoNdxes[i] = 0;
			if (m_blendTileNdxes[i] < 0 || m_blendTileNdxes[i] >= m_vector80A4.size())
				m_blendTileNdxes[i] = 0;
			if (m_extraBlendTileNdxes[i] < 0 || m_extraBlendTileNdxes[i] >= m_vector80A4.size())
				m_extraBlendTileNdxes[i] = 0;
		}
	}

	if (TheWritableGlobalData && TheWritableGlobalData->m_drawEntireTerrain)
	{
		m_drawWidthX = m_width;
		m_drawHeightY = m_height;
	}
	if (m_drawWidthX > m_width)
		m_drawWidthX = m_width;
	if (m_drawHeightY > m_height)
		m_drawHeightY = m_height;

	TheSidesList->validateSides();
	setupAlphaTiles();
}
