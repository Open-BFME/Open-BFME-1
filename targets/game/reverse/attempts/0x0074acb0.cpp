// ?load@Rva0074ACB0WorldHeightMap@@QAEXPAVDataChunkInput@@_N@Z
// partial score=0.22 date=2026-09-18
// ?load@Rva0074ACB0WorldHeightMap@@QAEXPAVDataChunkInput@@_N@Z present-unmatched
// Retail 0x0074ACB0, 1511 bytes.  The boundary is the RET 8 at +0x5E4;
// INT3 padding begins at +0x5E7.  The receiver layout and parser contracts
// below are limited to fields and callees witnessed in this body.
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringbaseascii/Common /ICode/Libraries/Source/WWVegas/WWLib

#include "AsciiString.h"

typedef bool Bool;

class UserParser;

typedef void (__cdecl *BfmeChunkParserVE)(void);

class BfmeParserRegistryVE
{
public:
	void *bfmeRegister(void *label, void *parentLabel,
		BfmeChunkParserVE parser, void *userData);
};

class BfmeSubVE
{
public:
	void bfmeDropVE(void *what);
};

// The dump calls the registration ILT through this address-derived contract.
// The one-word string view is the same object shape used by the neighboring
// parser-registration constructors; its destructor deliberately forwards to
// the landed releaseBuffer body.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
	void *m_data;
};

class DataChunkInput
{
public:
	Bool parse(void *userData);
};

class BfmeParserRegistrationVE
{
public:
	~BfmeParserRegistrationVE()
	{
		m_vftable = (void *)0x0107C7D0;
		reinterpret_cast<BfmeSubVE *>(m_table)->bfmeDropVE(m_parser);
	}

protected:
	void *m_vftable;
	DataChunkInput *m_table;
	UserParser *m_parser;
};

class Rva0074A3B0ParserRegistration : public BfmeParserRegistrationVE
{
public:
	Rva0074A3B0ParserRegistration(void *context, DataChunkInput *table,
		AsciiString *labelOverride);

private:
	void *m_context;
};

class Rva00088F50ParserRegistration : public BfmeParserRegistrationVE
{
public:
	Rva00088F50ParserRegistration(void *context, DataChunkInput *table,
		AsciiString *labelOverride);

private:
	void *m_context;
};

class Rva00190610ParserRegistration : public BfmeParserRegistrationVE
{
public:
	Rva00190610ParserRegistration(void *context, DataChunkInput *table,
		AsciiString *labelOverride);

private:
	void *m_context;
};

class Rva00190E10PolygonParser : public Rva00190610ParserRegistration
{
public:
	Rva00190E10PolygonParser(DataChunkInput *table, AsciiString *label);

private:
	void *m_context;
	int m_state;
};

class Rva0074A2C0ParserRegistration : public BfmeParserRegistrationVE
{
public:
	Rva0074A2C0ParserRegistration(void *context, DataChunkInput *table,
		AsciiString *labelOverride);

private:
	void *m_context;
};

class Rva0074A4A0ParserRegistration : public BfmeParserRegistrationVE
{
public:
	Rva0074A4A0ParserRegistration(void *context, DataChunkInput *table,
		AsciiString *labelOverride);

private:
	void *m_context;
};

class Rva0074A680ParserRegistration : public BfmeParserRegistrationVE
{
public:
	Rva0074A680ParserRegistration(DataChunkInput *table,
		AsciiString *labelOverride);
};

class Rva0074A590ParserRegistration : public BfmeParserRegistrationVE
{
public:
	Rva0074A590ParserRegistration(void *context, DataChunkInput *table,
		AsciiString *labelOverride);

private:
	void *m_context;
};

// 0x0109BFD4 is installed by the three local callback bindings in this body.
// Keeping the fields as ordinary words reproduces the retail manual-vtable
// stores instead of inventing a C++ virtual hierarchy.
class Rva0074ACB0ParserBinding
{
public:
	Rva0074ACB0ParserBinding(int first, int second, int third,
		BfmeParserRegistryVE *registry, void *label, void *parentLabel)
		: m_registry(registry)
	{
		m_vftable = (void *)0x0107C7D0;
		m_parser = registry->bfmeRegister(label, parentLabel,
			(BfmeChunkParserVE)0x0041579E, this);
		m_vftable = (void *)0x0109BFD4;
		m_first = first;
		m_second = second;
		m_third = third;
	}

	~Rva0074ACB0ParserBinding()
	{
		m_vftable = (void *)0x0107C7D0;
		reinterpret_cast<BfmeSubVE *>(m_registry)->bfmeDropVE(m_parser);
	}

private:
	void *m_vftable;
	BfmeParserRegistryVE *m_registry;
	void *m_parser;
	int m_first;
	int m_second;
	int m_third;
};

class BfmeMapObjectListEntry
{
public:
	virtual void deleteThis(int freeIt) = 0;
};

struct Rva0074ACB0MapObjectListHolder
{
	BfmeMapObjectListEntry *head;
};

class BfmeMapObjectExtra
{
public:
	void bfmeReset();
};

class CameraMarkerList
{
public:
	void clear();
};

class SidesList
{
public:
	Bool validateSides();
};

class Rva0019BE80SidesList
{
public:
	void clearSideStorageAt0019B4C0();
};

class WorldHeightMap
{
public:
	static void setupAlphaTiles();
};

// The 0x00192720 helper initializes this temporary; its matched destructor is
// the 0x00191640 BfmeOwnCP body.  The two views intentionally share only the
// observed 0x9C-byte storage.
class BfmeOwnCP
{
public:
	~BfmeOwnCP();

private:
	char m_storage[0x9C];
};

class BfmeThingXB
{
public:
	BfmeThingXB *bfmeInitXB(void *first, void *second, void *third);
};

struct Rva0074ACB0Vec16Element { char bytes[0x10]; };
struct Rva0074ACB0Vec56Element { char bytes[0x38]; };

struct Rva0074ACB0Vec16
{
	Rva0074ACB0Vec16Element *first;
	Rva0074ACB0Vec16Element *last;
	void *capacity;
};

struct Rva0074ACB0Vec56
{
	Rva0074ACB0Vec56Element *first;
	Rva0074ACB0Vec56Element *last;
	void *capacity;
};

// BFME's WorldHeightMap fields are not the ZH header layout.  These offsets
// are independently witnessed by the matched destructor and by this body's
// direct loads/stores.
class Rva0074ACB0WorldHeightMap
{
public:
	char m_prefix[8];
	int m_width;                                      // +0x08
	int m_height;                                     // +0x0C
	char m_pad10[0x10];
	int m_dataSize;                                   // +0x20
	char m_pad24[0x68];
	void *m_tileNdxes;                                // +0x8C
	int *m_blendTileNdxes;                            // +0x90
	int *m_cliffInfoNdxes;                            // +0x94
	int *m_extraBlendTileNdxes;                       // +0x98
	char m_pad9C[0x8008];
	Rva0074ACB0Vec16 m_blendTileInfo;                 // +0x80A4
	Rva0074ACB0Vec56 m_cliffInfo;                     // +0x80B0
	char m_pad80BC[0x120E8 - 0x80BC];
	int m_drawWidth;                                  // +0x120E8
	int m_drawHeight;                                 // +0x120EC

	void load(DataChunkInput *file, Bool logicalDataOnly);
};

static BfmeParserRegistryVE *rva0074acb0Registry()
{
	return *(BfmeParserRegistryVE **)0x012EF428;
}

static Rva0074ACB0MapObjectListHolder *rva0074acb0MapObjects()
{
	return *(Rva0074ACB0MapObjectListHolder **)0x012ED5DC;
}

static BfmeMapObjectExtra *rva0074acb0MapObjectExtra()
{
	return (BfmeMapObjectExtra *)0x012ED5E0;
}

static CameraMarkerList *rva0074acb0CameraMarkers()
{
	return *(CameraMarkerList **)0x012F1600;
}

struct Rva0074ACB0GlobalData
{
	char m_pad00[0x4E];
	Bool m_stretchTerrain;                             // +0x4E
	char m_pad4F[1];
	Bool m_drawEntireTerrain;                          // +0x50
};

static Rva0074ACB0GlobalData *rva0074acb0GlobalData()
{
	return *(Rva0074ACB0GlobalData **)0x012ED5C8;
}

#define Rva0074ACB0GlobalDataRef (*(Rva0074ACB0GlobalData **)0x012ED5C8)

void Rva0074ACB0WorldHeightMap::load(DataChunkInput *file,
	Bool logicalDataOnly)
{
	int i = 0;
	Rva0074ACB0GlobalData *globalData = Rva0074ACB0GlobalDataRef;
	if (globalData && globalData->m_stretchTerrain)
	{
		m_drawWidth = 0x41;
		m_drawHeight = 0x41;
	}

	if (logicalDataOnly)
	{
		Rva0074A3B0ParserRegistration heightMapData(
			this, file, 0);

		reinterpret_cast<BfmeParserRegistryVE *>(file)->bfmeRegister(
			(void *)(BFMERetailAsciiString *)&BFMERetailAsciiString(
				(const char *)0x010F5EEC), (void *)0x01336E50,
			(BfmeChunkParserVE)0x00419FBA, 0);

		Rva00088F50ParserRegistration objectsList(
			(void *)0x012A7A48, file, 0);

		BfmeMapObjectListEntry *object =
			rva0074acb0MapObjects()->head;
		if (object)
			object->deleteThis(1);
		rva0074acb0MapObjects()->head = 0;
		rva0074acb0MapObjectExtra()->bfmeReset();

		Rva00190E10PolygonParser polygonTriggers(file, 0);

		reinterpret_cast<Rva0019BE80SidesList *>(
			*(void **)0x012EF428)->clearSideStorageAt0019B4C0();

		Rva0074ACB0ParserBinding sides(
			(int)*(void **)0x012EF428, 0x0044A755, 0,
			reinterpret_cast<BfmeParserRegistryVE *>(file),
			(void *)(BFMERetailAsciiString *)&BFMERetailAsciiString(
				(const char *)0x0109C028), (void *)0x01336E50);

		BfmeOwnCP teamsStorage;
		reinterpret_cast<BfmeThingXB *>(&teamsStorage)->bfmeInitXB(
			(void *)0x012EF428, file, 0);

		Rva0074ACB0ParserBinding teams(
			(int)*(void **)0x012EF428, 0x00443C93, 0,
			reinterpret_cast<BfmeParserRegistryVE *>(file),
			(void *)(BFMERetailAsciiString *)&BFMERetailAsciiString(
				(const char *)0x0109C1E4), (void *)0x01336E50);

		Rva0074ACB0ParserBinding libraryMaps(
			(int)*(void **)0x012EF428, 0x004283A3, 0,
			reinterpret_cast<BfmeParserRegistryVE *>(file),
			(void *)(BFMERetailAsciiString *)&BFMERetailAsciiString(
				(const char *)0x0109BFF0), (void *)0x01336E50);

		if (!file->parse(this))
			throw(0xDEAD0005);
	}
	else
	{
		Rva0074A2C0ParserRegistration heightMapData(
			this, file, 0);
		Rva0074A4A0ParserRegistration blendTileData(
			this, file, 0);
		Rva0074A680ParserRegistration globalLighting(file, 0);

		reinterpret_cast<BfmeParserRegistryVE *>(file)->bfmeRegister(
			(void *)(BFMERetailAsciiString *)&BFMERetailAsciiString(
				(const char *)0x0111D878), (void *)0x01336E50,
			(BfmeChunkParserVE)0x00408706, 0);

		rva0074acb0CameraMarkers()->clear();
		Rva0074A590ParserRegistration namedCameras(
			(char *)rva0074acb0CameraMarkers() + 0x80, file, 0);

		if (!file->parse(this))
			throw(0xDEAD0005);
	}

	if (!logicalDataOnly)
	{
		for (i = 0; i < m_dataSize; ++i)
		{
			if (m_cliffInfoNdxes[i] < 0 ||
				m_cliffInfoNdxes[i] >= m_cliffInfo.last - m_cliffInfo.first)
				m_cliffInfoNdxes[i] = 0;
			if (m_blendTileNdxes[i] < 0 ||
				m_blendTileNdxes[i] >= m_blendTileInfo.last - m_blendTileInfo.first)
				m_blendTileNdxes[i] = 0;
			if (m_extraBlendTileNdxes[i] < 0 ||
				m_extraBlendTileNdxes[i] >= m_blendTileInfo.last - m_blendTileInfo.first)
				m_extraBlendTileNdxes[i] = 0;
		}
	}

	if (Rva0074ACB0GlobalDataRef &&
		Rva0074ACB0GlobalDataRef->m_drawEntireTerrain)
	{
		m_drawWidth = m_width;
		m_drawHeight = m_height;
	}
	if (m_drawWidth > m_width)
		m_drawWidth = m_width;
	if (m_drawHeight > m_height)
		m_drawHeight = m_height;

	((SidesList *)*(void **)0x012EF428)->validateSides();
	WorldHeightMap::setupAlphaTiles();
}
