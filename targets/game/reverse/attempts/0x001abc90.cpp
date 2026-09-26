// ?Rva001ABC90ParseWaypointChunk@@YA_NAAVChunkReader@@@Z
// partial score=0.43 date=2026-09-21
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Anonymous TerrainLogic chunk-parser callback, retail 0x001ABC90, size 550.
// Identity: called through an ILT thunk from TerrainLogic::loadMapAbi
// (Code/GameEngine/Source/GameLogic/Map/TerrainLogic_loadMap_Thunk.cpp);
// its last call (pinned 0x0001ADB1 -> 0x001AB600) is the Waypoint
// constructor banked in reverse/attempts/0x001ab600.cpp, and the
// `operator new(0xb0)` immediately before it matches that constructor's
// object size. Six Dict field fetches (GenKey::fetch + a Dict lookup, each
// key a distinct static GenKey global at retail VA) supply the
// constructor's id/name/labels/flag/extra fields.

typedef int Int;
typedef bool Bool;

inline void *operator new(unsigned int, void *place) { return place; }

enum NameKeyType { NAMEKEY_INVALID = 0 };

class BfmeRetString
{
public:
	BfmeRetString() { m_data = 0; }
	BfmeRetString(const BfmeRetString &other);		// retail 0x00887B60
	~BfmeRetString() { releaseBuffer(); }

	void set(const BfmeRetString &other);			// retail 0x00887C90

private:
	void releaseBuffer();					// retail 0x00887940
	void *m_data;
};

class GenKey
{
public:
	int fetch();						// pinned retail 0x00009304
};

extern GenKey g_key77B8, g_key77C0, g_key77C8, g_key77D0, g_key77E0, g_key77D8;

class Dict
{
public:
	BfmeRetString getAsciiString(NameKeyType key, Bool *exists) const;	// pinned retail 0x00068580
	Bool getBool(NameKeyType key, Bool *exists) const;			// pinned retail 0x00067E20
	Int getInt(NameKeyType key, Bool *exists) const;			// pinned retail 0x00067E70
};

struct Coord3D
{
	int x, y, z;
};

class Waypoint;

extern "C" void *__cdecl operator_new_0xb0(unsigned int size);

class Waypoint
{
public:
	Waypoint(int id, BfmeRetString name, const Coord3D *pLoc,
		BfmeRetString label1, BfmeRetString label2, BfmeRetString label3,
		Bool biDirectional, int extraField, BfmeRetString extraLabel);	// pinned retail 0x001AB600
};

class ChunkReader
{
public:
	const Coord3D *bfmeGoBWF();				// pinned retail 0x00087CC0
	Dict *getDict() { return (Dict *)((unsigned char *)this + 0x24); }

	unsigned char m_pad[0x24];
};

enum { WAYPOINT_ID_AUTO = 0x7ffffffe };

Bool Rva001ABC90ParseWaypointChunk(ChunkReader &file)
{
	const Coord3D *loc = file.bfmeGoBWF();
	Dict *dict = file.getDict();

	Bool exists = false;
	BfmeRetString name = dict->getAsciiString((NameKeyType)g_key77B8.fetch(), &exists);
	BfmeRetString label1 = dict->getAsciiString((NameKeyType)g_key77C0.fetch(), &exists);
	BfmeRetString label2 = dict->getAsciiString((NameKeyType)g_key77C8.fetch(), &exists);
	Bool biDirectional = dict->getBool((NameKeyType)g_key77D0.fetch(), &exists);

	void *raw = operator_new_0xb0(0xb0);
	if (raw)
	{
		BfmeRetString extraLabel = dict->getAsciiString((NameKeyType)g_key77E0.fetch(), &exists);
		Int extraField = dict->getInt((NameKeyType)g_key77D8.fetch(), &exists);

		new (raw) Waypoint(WAYPOINT_ID_AUTO, name, loc, label1, label2, BfmeRetString(),
			biDirectional, extraField, extraLabel);
	}

	return raw != 0;
}
