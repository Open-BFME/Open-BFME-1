// ?writeCacheINI@MapCache@@AAEX_N@Z
// partial score=0.71 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
// readable body of ?writeCacheINI@MapCache@@AAEX_N@Z: Code/GameEngine/Source/GameClient/MapUtil.cpp
//
// Retail 0x004550C0, 1814 bytes. BFME extends ZH's writer: isScenarioMP,
// Unicode displayName/description (quoted-printable), and eight PlayerPosition
// blocks (Human/Computer/LoadAIScripts/ForcePlayerTeam/AllowedFactions).
// MapMetaData special members stay out of line -- retail ctor/assign/dtor.
//
// Probe 2026-09-03: ours 1589B vs retail 1814B, frame sub esp,0x138 exact,
// this=ebx saved at [esp+0x30], mapDir zeroed at [esp+0x10], m_buildMapCache
// at GlobalData+0xB7D. First real miss: getMapDir/getUserMapDir hidden return
// at [esp+0x0C] vs retail [esp+0x14] (every later [esp+N] is 8B low). Extra
// named locals (mapKey, Coord3D pos, slash[8]) steal ebx or grow the frame.
// PlayerPosition skip compares each 0x14 slot to a function-scope static
// {1,1,1,-1, empty set} with the VC7 guard at 0x012F15E4 -- that inlined set
// ctor is the missing ~225B. Do not compile MapUtil.cpp (operator new rows).

#include <stdio.h>
#include <string.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char Bool;
typedef float Real;

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	struct Data
	{
		Int m_refCount;
		UnsignedShort m_length;
		UnsignedShort m_capacity;
		T m_text[1];
	};
	Data *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void set(const AsciiString &other);
	void concat(const char *text, Int len);
	void toLower();
	bool startsWithNoCase(const char *text, Int len) const;

	const char *str() const { return m_data ? m_data->m_text : ""; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<UnsignedShort>
{
public:
	UnicodeString() : StringBase<UnsignedShort>() {}
	UnicodeString(const UnicodeString &other) : StringBase<UnsignedShort>(other) {}
	~UnicodeString() {}

	const UnsignedShort *str() const { return m_data ? m_data->m_text : (const UnsignedShort *)L""; }
};

struct Coord3D
{
	Real x, y, z;
};

struct Region3D
{
	Coord3D lo, hi;
};

struct WinTimeStamp
{
	UnsignedInt m_lowTimeStamp;
	UnsignedInt m_highTimeStamp;
};

struct RbNode
{
	RbNode *left;
	RbNode *parent;
	RbNode *right;
	Int color;
	AsciiString key;
};

struct WaypointNode : RbNode
{
	Coord3D pos;
};

struct ListNode
{
	ListNode *next;
	ListNode *prev;
	Coord3D pos;
};

struct FactionNode : RbNode
{
};

struct PlayerSlot
{
	Bool m_human;
	Bool m_computer;
	Bool m_loadAIScripts;
	Int m_forcePlayerTeam;
	FactionNode *m_factionHeader;
	UnsignedInt m_factionCount;
	UnsignedInt m_factionPad;
};

class MapMetaData
{
public:
	MapMetaData();
	MapMetaData &operator=(const MapMetaData &);
	~MapMetaData();

	UnicodeString m_displayName;
	UnicodeString m_description;
	Region3D m_extent;
	Int m_numPlayers;
	Bool m_isMultiplayer;
	Bool m_isScenarioMP;
	Bool m_isOfficial;
	UnsignedInt m_filesize;
	UnsignedInt m_CRC;
	WinTimeStamp m_timestamp;
	WaypointNode *m_waypointHeader;
	unsigned char m_waypointRest[0x0C];
	ListNode *m_supplySentinel;
	ListNode *m_techSentinel;
	AsciiString m_fileName;
	PlayerSlot m_players[8];
	unsigned char m_tail[16];
};

struct MapNode : RbNode
{
	MapMetaData value;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char _pad_b7d[0xB7D];
	Bool m_buildMapCache;
};

extern GlobalData *TheWritableGlobalData;

class FileSystem
{
public:
	Bool createDirectory(AsciiString directory);
};

extern FileSystem *TheFileSystem;

AsciiString AsciiStringToQuotedPrintable(AsciiString original);
AsciiString UnicodeStringToQuotedPrintable(UnicodeString original);

RbNode *rbIncrement(RbNode *node);
bool rbTreesEqual(RbNode *beginA, RbNode *headerA, RbNode *beginB);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapCache
{
public:
	AsciiString getUserMapDir() const;
	AsciiString getMapDir() const;

private:
	void writeCacheINI(bool userDir);
	MapNode *m_header;
};

static bool playerSlotIsDefault(const PlayerSlot *slot)
{
	static PlayerSlot s_default = { 1, 1, 1, (Int)-1, 0, 0, 0 };
	if (slot->m_human != s_default.m_human)
		return false;
	if (slot->m_computer != s_default.m_computer)
		return false;
	if (slot->m_loadAIScripts != s_default.m_loadAIScripts)
		return false;
	if (slot->m_forcePlayerTeam != s_default.m_forcePlayerTeam)
		return false;
	if (slot->m_factionCount != s_default.m_factionCount)
		return false;
	return rbTreesEqual(slot->m_factionHeader ? slot->m_factionHeader->left : 0,
		slot->m_factionHeader,
		s_default.m_factionHeader ? s_default.m_factionHeader->left : 0);
}

// ?writeCacheINI@MapCache@@AAEX_N@Z
void MapCache::writeCacheINI(bool userDir)
{
	AsciiString mapDir;
	if (!userDir || TheWritableGlobalData->m_buildMapCache)
		mapDir.set(getMapDir());
	else
		mapDir.set(getUserMapDir());

	AsciiString filepath(mapDir);
	char slash = '\\';
	filepath.concat(&slash, 1);

	TheFileSystem->createDirectory(mapDir);
	filepath.concat("MapCache.ini", 12);

	FILE *fp = fopen(filepath.str(), "w");
	if (fp == 0)
		return;

	fprintf(fp, "; FILE: %s /////////////////////////////////////////////////////////////\n", filepath.str());
	fprintf(fp, "; This INI file is auto-generated - do not modify\n");
	fprintf(fp, "; /////////////////////////////////////////////////////////////////////////////\n");
	mapDir.toLower();

	MapMetaData md;
	for (MapNode *it = (MapNode *)m_header->left; it != m_header; it = (MapNode *)rbIncrement(it))
	{
		const char *dir = mapDir.str();
		Int dirLen = 0;
		if (dir)
			dirLen = (Int)strlen(dir);
		if (!it->key.startsWithNoCase(dir, dirLen))
			continue;

		md = it->value;
		fprintf(fp, "\nMapCache %s\n", AsciiStringToQuotedPrintable(it->key).str());
		fprintf(fp, "  fileSize = %u\n", md.m_filesize);
		fprintf(fp, "  fileCRC = %u\n", md.m_CRC);
		fprintf(fp, "  timestampLo = %d\n", md.m_timestamp.m_lowTimeStamp);
		fprintf(fp, "  timestampHi = %d\n", md.m_timestamp.m_highTimeStamp);
		fprintf(fp, "  isOfficial = %s\n", md.m_isOfficial ? "yes" : "no");
		fprintf(fp, "  isMultiplayer = %s\n", md.m_isMultiplayer ? "yes" : "no");
		fprintf(fp, "  isScenarioMP = %s\n", md.m_isScenarioMP ? "yes" : "no");
		fprintf(fp, "  numPlayers = %d\n", md.m_numPlayers);
		fprintf(fp, "  extentMin = X:%2.2f Y:%2.2f Z:%2.2f\n", md.m_extent.lo.x, md.m_extent.lo.y, md.m_extent.lo.z);
		fprintf(fp, "  extentMax = X:%2.2f Y:%2.2f Z:%2.2f\n", md.m_extent.hi.x, md.m_extent.hi.y, md.m_extent.hi.z);
		fprintf(fp, "  displayName = %s\n", UnicodeStringToQuotedPrintable(md.m_displayName).str());
		fprintf(fp, "  description = %s\n", UnicodeStringToQuotedPrintable(md.m_description).str());

		WaypointNode *whead = md.m_waypointHeader;
		for (WaypointNode *w = (WaypointNode *)whead->left; w != whead; w = (WaypointNode *)rbIncrement(w))
			fprintf(fp, "  %s = X:%2.2f Y:%2.2f Z:%2.2f\n", w->key.str(), w->pos.x, w->pos.y, w->pos.z);

		for (ListNode *n = md.m_techSentinel->next; n != md.m_techSentinel; n = n->next)
			fprintf(fp, "  techPosition = X:%2.2f Y:%2.2f Z:%2.2f\n", n->pos.x, n->pos.y, n->pos.z);

		for (ListNode *n = md.m_supplySentinel->next; n != md.m_supplySentinel; n = n->next)
			fprintf(fp, "  supplyPosition = X:%2.2f Y:%2.2f Z:%2.2f\n", n->pos.x, n->pos.y, n->pos.z);

		for (Int i = 0; i < 8; ++i)
		{
			PlayerSlot *slot = &md.m_players[i];
			if (playerSlotIsDefault(slot))
				continue;
			fprintf(fp, "  PlayerPosition %d\n", i + 1);
			fprintf(fp, "    Human = %s\n", slot->m_human ? "Yes" : "No");
			fprintf(fp, "    Computer = %s\n", slot->m_computer ? "Yes" : "No");
			fprintf(fp, "    LoadAIScripts = %s\n", slot->m_loadAIScripts ? "Yes" : "No");
			fprintf(fp, "    ForcePlayerTeam = %d\n", slot->m_forcePlayerTeam);
			if (slot->m_factionHeader && slot->m_factionCount)
			{
				fprintf(fp, "    AllowedFactions =");
				FactionNode *fhead = slot->m_factionHeader;
				for (FactionNode *f = (FactionNode *)fhead->left; f != fhead; f = (FactionNode *)rbIncrement(f))
					fprintf(fp, " %s", f->key.str());
				fprintf(fp, "\n");
			}
			fprintf(fp, "  END\n");
		}
		fprintf(fp, "END\n\n");
	}

	fclose(fp);
}
