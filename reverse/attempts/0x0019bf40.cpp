// ?parseSidesDataChunk@Rva0019BE80SidesList@@QAE_NAAVDataChunkInput@@PAUDataChunkInfo@@@Z
// partial score=0.25 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc
// Retail 0x0019BF40: SidesList's DataChunk parse callback -- the BFME variant
// of ZH SidesList::ParseSidesDataChunk (reference/CnC_Generals_Zero_Hour/
// GeneralsMD/Code/GameEngine/Source/GameLogic/Map/SidesList.cpp:243-319).
// Identity: direct sibling of the landed loadTeams (SidesList_rva0019BE80.cpp)
// and reset/clear (SidesListReset.cpp / SidesListClearSideStorage.cpp) and
// addPlayerByTemplate (SidesListAddPlayerByTemplate.cpp) bodies in this same
// directory -- identical 0x630/0x64c TeamRec offsets, identical
// clearSideStorageAt0019B4C0 clear-all, identical 0x18-byte side record at
// this+0x2c stepping up to 32 slots (count cached at this+0x28).
//
// BFME diverges from the ZH source in five ways proven directly from the
// disassembly: (1) this is a __thiscall member (this=SidesList*) taking only
// (DataChunkInput&, DataChunkInfo*) -- ZH's static function took an unused
// third void*userData and read the TheSidesList global instead of an
// implicit this; (2) a version>=6 gated extra byte flag stored at this+0x668
// right after the inlined clear(): `if (info->version>=6) m_flag668 =
// (file.readByte()!=0);`; (3) a 9999 safety clamp on each side's build-list
// count; (4) the team-list gate is narrowed to 2<=version<5 (ZH: unconditional
// >=2); (5) an outright early return for version>=5 that skips the
// PlayerScriptsList registration/parse/script-retrieval tail entirely (ZH
// always ran it). info->version is a 16-bit field (word compares throughout).

typedef int Int;

enum ErrorCode
{
	ERROR_BASE = 0xdead0001,
	ERROR_CORRUPT_FILE_FORMAT = (ERROR_BASE + 0x0004)
};

class Dict
{
public:
	~Dict() { releaseData(); }

private:
	void releaseData();
	void *m_data;
};

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString();

private:
	void *m_data;
};

class AsciiString : public BFMERetailAsciiString
{
public:
};

class UnicodeString : public BFMERetailAsciiString
{
public:
	void set(const UnicodeString &other);
};

struct DataChunkInfo
{
	AsciiString m_label;			// +0x00
	AsciiString m_parentLabel;		// +0x04
	unsigned short m_version;		// +0x08
};

class DataChunkInput
{
public:
	int readInt();
	char readByte();
	float readReal();
	Dict readDict();
	AsciiString readAsciiString();
	bool parse(void *userData);
};

class BfmeParserRegistrationVE
{
public:
	void *m_vftable;			// +0x00
	void *m_table;				// +0x04
	void *m_parser;				// +0x08
};

class Rva00352810ParserRegistration : public BfmeParserRegistrationVE
{
public:
	Rva00352810ParserRegistration(void *dataContext, void *localList,
		DataChunkInput *table, AsciiString *labelOverride);

private:
	void *m_0c;				// +0x0c
	void *m_10;				// +0x10
};

// Unlink-and-delete of the UserParser node registered above; the retail body
// inlines BfmeParserRegistrationVE's destructor as (a) a vtable reset to the
// base class's vftable and (b) this call on the node stored at m_parser.
// `this` is never read inside handle() -- only the stack-passed node matters.
class Q1Forwardee0000871A
{
public:
	void handle(int node);
};

class ScriptList
{
public:
	virtual ~ScriptList();
};

class BuildListInfo;

class Rva0019BE80TeamRec
{
public:
	void clear();
	int append(const Dict *dict);

private:
	unsigned char m_layout[0x1c];
};

// One 0x18-byte side record; bfmeInitCMC is the pinned initializer already
// proven by SidesListAddPlayerByTemplate.cpp's addSide-equivalent call.
class BfmeItemCMC
{
public:
	void bfmeInitCMC(void *dict);

	BuildListInfo *m_buildList;		// +0x00
private:
	unsigned char m_pad04[4];		// +0x04 (Dict m_dict)
public:
	ScriptList *m_scripts;			// +0x08
private:
	unsigned char m_pad0c[0x0c];		// +0x0c..+0x18 (Rva0019BE80UnicodeStrings)
};

// operator new(0x8c) is retail's exact allocation size for one BuildListInfo;
// placement-constructing into that raw block (rather than `new BuildListInfo`,
// whose sizeof we cannot reproduce without the full class) keeps the call
// shape -- push 0x8c; call operator new; null check; call ctor -- identical.
inline void *operator new(unsigned int, void *place) { return place; }

class BuildListInfo
{
public:
	virtual ~BuildListInfo();
	BuildListInfo();

	AsciiString m_buildingName;		// +0x04 (after the compiler's own vptr)
	AsciiString m_templateName;		// +0x08
	float m_locX;				// +0x0c
	float m_locY;				// +0x10
	float m_locZ;				// +0x14
	unsigned char m_pad18[8];		// +0x18..+0x20
	float m_angle;				// +0x20
	unsigned char m_initiallyBuilt;	// +0x24
	unsigned char m_pad25[3];
	int m_numRebuilds;			// +0x28
	BuildListInfo *m_next;			// +0x2c
	AsciiString m_script;			// +0x30
	int m_health;				// +0x34
	unsigned char m_whiner;			// +0x38
	unsigned char m_unsellable;		// +0x39
	unsigned char m_repairable;		// +0x3a
};

class Rva0019BE80SidesList
{
public:
	bool parseSidesDataChunk(DataChunkInput &file, DataChunkInfo *info);

private:
	void clearSideStorageAt0019B4C0();

	unsigned char m_prefix[0x28];
	int m_numSides;				// +0x28
	BfmeItemCMC m_sides[32];		// +0x2c
	int m_numSkirmishSides;
	BfmeItemCMC m_skirmishSides[32];
	Rva0019BE80TeamRec m_teamrec;		// +0x630
	Rva0019BE80TeamRec m_skirmishTeamrec;	// +0x64c
	unsigned char m_flag668;		// +0x668
};

bool Rva0019BE80SidesList::parseSidesDataChunk(DataChunkInput &file, DataChunkInfo *info)
{
	// TheSidesList->clear(): clearSideStorageAt0019B4C0() + both TeamRec
	// clears + m_flag668=1, inlined (matches the landed reset()/
	// clearSidesAndTeamsAt0019BE50 body exactly).
	clearSideStorageAt0019B4C0();
	m_teamrec.clear();
	m_skirmishTeamrec.clear();
	m_flag668 = 1;

	if (info->m_version >= 6)
		m_flag668 = (file.readByte() != 0) ? 1 : 0;

	Int count = file.readInt();
	clearSideStorageAt0019B4C0();		// TheSidesList->emptySides();

	for (Int i = 0; i < count; i++)
	{
		if (i >= 32)
			break;

		Dict d = file.readDict();

		if (m_numSides < 32)
		{
			m_sides[m_numSides].bfmeInitCMC((void *)&d);
			m_numSides = m_numSides + 1;
		}

		Int buildCount = file.readInt();
		if (buildCount > 9999)
			buildCount = 0;

		for (Int j = 0; j < buildCount; j++)
		{
			void *raw = ::operator new(0x8c);
			BuildListInfo *pBuildList = 0;
			if (raw)
				pBuildList = ::new (raw) BuildListInfo();

			{
				AsciiString buildingName = file.readAsciiString();
				((UnicodeString *)&pBuildList->m_buildingName)->set(*(UnicodeString *)&buildingName);
			}
			{
				AsciiString templateName = file.readAsciiString();
				((UnicodeString *)&pBuildList->m_templateName)->set(*(UnicodeString *)&templateName);
			}

			float locX = file.readReal();
			float locY = file.readReal();
			file.readReal();		// loc.z read then forced to ground level
			pBuildList->m_locX = locX;
			pBuildList->m_locY = locY;
			pBuildList->m_locZ = 0.0f;
			pBuildList->m_angle = file.readReal();
			pBuildList->m_initiallyBuilt = (file.readByte() != 0) ? 1 : 0;
			pBuildList->m_numRebuilds = file.readInt();

			if (info->m_version >= 3)
			{
				{
					AsciiString script = file.readAsciiString();
					((UnicodeString *)&pBuildList->m_script)->set(*(UnicodeString *)&script);
				}
				pBuildList->m_health = file.readInt();
				pBuildList->m_whiner = (file.readByte() != 0) ? 1 : 0;
				pBuildList->m_unsellable = (file.readByte() != 0) ? 1 : 0;
				pBuildList->m_repairable = (file.readByte() != 0) ? 1 : 0;
			}

			// SidesInfo::addToBuildList(pBuildList, j), inlined; the side
			// pointer is the same bounds-checked getSideInfo(i) accessor
			// shape used at the tail script-retrieval loop below.
			BfmeItemCMC *side = (i < m_numSides) ? &m_sides[i] : 0;
			BuildListInfo *pCur = 0;
			Int position = j;
			while (position)
			{
				position--;
				if (pCur == 0)
				{
					pCur = side->m_buildList;
				}
				else
				{
					if (pCur->m_next)
						pCur = pCur->m_next;
					else
						break;
				}
			}
			if (pCur == 0)
			{
				pBuildList->m_next = side->m_buildList;
				side->m_buildList = pBuildList;
			}
			else
			{
				pBuildList->m_next = pCur->m_next;
				pCur->m_next = pBuildList;
			}
		}
	}

	if (info->m_version >= 2 && info->m_version < 5)
	{
		Int teamCount = file.readInt();
		m_teamrec.clear();
		m_skirmishTeamrec.clear();
		for (Int t = 0; t < teamCount; t++)
		{
			Dict teamDict = file.readDict();
			m_teamrec.append(&teamDict);
		}
	}

	if (info->m_version >= 5)
		return true;

	ScriptList *scripts[32];
	Rva00352810ParserRegistration reg((void *)0, (void *)&scripts[0], &file, (AsciiString *)info);

	if (!file.parse(0))
		throw ERROR_CORRUPT_FILE_FORMAT;

	for (Int k = 0; k < count; k++)
	{
		if (k < m_numSides)
		{
			ScriptList *pSL = m_sides[k].m_scripts;
			if (pSL)
				delete pSL;
			m_sides[k].m_scripts = scripts[k];
		}
		else
		{
			if (scripts[k])
				delete scripts[k];
		}
		scripts[k] = 0;
	}

	reg.m_vftable = (void *)0x0107C7D0;
	((Q1Forwardee0000871A *)this)->handle((int)reg.m_parser);

	return true;
}
