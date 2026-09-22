// ?parseSidesDataChunk@Rva0019BE80SidesList@@QAE_NAAVDataChunkInput@@PAUDataChunkInfo@@@Z
// partial score=0.7067669 date=2026-09-22
// ?parseSidesDataChunk@Rva0019BE80SidesList@@QAE_NAAVDataChunkInput@@PAUDataChunkInfo@@@Z
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath
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

// Corrected attempt, 2026-09-22: 1195/1197 bytes, 351 masked differences.
// This remains evidence, not matched source. The native Coord3D copy/assignment
// variant is the closest measured candidate; its D8-byte frame differs from
// retail CC. The released POD Coord3D variant has the right CC frame but is
// 1179 bytes with 603 differences. Neither establishes the inlined type family.
// See reverse/attempt_history/0x0019bf40/20260922-review.md for the independently
// decoded behavior fixes and the unresolved coordinate-copy contract.

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

#include "ascii_string.h"
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &that) { x=that.x; y=that.y; z=that.z; }
inline Coord3DBase &Coord3DBase::operator=(const Coord3DBase &that)
{
    struct Raw { unsigned int x,y,z; };
    *(Raw *)this=*(const Raw *)&that;
    return *this;
}
inline Coord3D &Coord3D::operator=(const Coord3D &that)
{
    Coord3DBase *base=this; *base=that; return *this;
}
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

class Q1Forwardee0000871A { public: void handle(int node); };
class BfmeParserRegistrationVE
{
public:
    virtual ~BfmeParserRegistrationVE()
    {
        ((Q1Forwardee0000871A *)m_table)->handle((int)m_parser);
    }
    virtual bool parse(DataChunkInput &, DataChunkInfo *) = 0;
protected:
    DataChunkInput *m_table;
    void *m_parser;
};
class Rva00352810ParserRegistration : public BfmeParserRegistrationVE
{
public:
    Rva00352810ParserRegistration(void *dataContext, void *localList,
        DataChunkInput *table, AsciiString *labelOverride);
    virtual bool parse(DataChunkInput &, DataChunkInfo *);
private:
    void *m_0c;
    void *m_10;
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

class BuildListInfo
{
public:
	virtual ~BuildListInfo();
	BuildListInfo();
    void setLocation(Coord3D loc) { m_location=loc; }
    void setBuildingName(AsciiString name) { m_buildingName=name; }
    void setTemplateName(AsciiString name) { m_templateName=name; }
    void setScript(AsciiString name) { m_script=name; }

	AsciiString m_buildingName;		// +0x04 (after the compiler's own vptr)
	AsciiString m_templateName;		// +0x08
	Coord3D m_location; // +0x0c
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
    unsigned char m_remaining3b[0x8c-0x3b];
};

typedef char BuildListSize[sizeof(BuildListInfo)==0x8c?1:-1];

class Rva0019BE80SidesList
{
public:
	bool parseSidesDataChunk(DataChunkInput &file, DataChunkInfo *info);

private:
	void clearSideStorageAt0019B4C0();
    BfmeItemCMC *getSideInfo(int index) { return index>=0 && index<m_numSides ? &m_sides[index] : 0; }

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
    else
        m_flag668 = 1;

	Int count = file.readInt();
	clearSideStorageAt0019B4C0();		// TheSidesList->emptySides();

	for (Int i = 0; i < count; i++)
	{
		if (i >= 32)
			break;

		Dict d = file.readDict();

		if (m_numSides < 32)
		{
			int oldCount=m_numSides;
            m_numSides=oldCount+1;
            m_sides[oldCount].bfmeInitCMC((void *)&d);
		}

		Int buildCount = file.readInt();
		if (buildCount > 9999)
			buildCount = 0;

		for (Int j = 0; j < buildCount; j++)
		{
			BuildListInfo *pBuildList = new BuildListInfo();

			pBuildList->setBuildingName(file.readAsciiString());
			pBuildList->setTemplateName(file.readAsciiString());

            Coord3D loc;
            loc.x=file.readReal();
            loc.y=file.readReal();
            loc.z=file.readReal();
            loc.z=0;
            pBuildList->setLocation(loc);
			pBuildList->m_angle = file.readReal();
			pBuildList->m_initiallyBuilt = (file.readByte() != 0) ? 1 : 0;
			pBuildList->m_numRebuilds = file.readInt();

			if (info->m_version >= 3)
			{
				pBuildList->setScript(file.readAsciiString());
				pBuildList->m_health = file.readInt();
				pBuildList->m_whiner = (file.readByte() != 0) ? 1 : 0;
				pBuildList->m_unsellable = (file.readByte() != 0) ? 1 : 0;
				pBuildList->m_repairable = (file.readByte() != 0) ? 1 : 0;
			}

			// SidesInfo::addToBuildList(pBuildList, j), inlined; the side
			// pointer is the same bounds-checked getSideInfo(i) accessor
			// shape used at the tail script-retrieval loop below.
			BfmeItemCMC *side = getSideInfo(i);
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
		count = file.readInt();
		m_teamrec.clear();
		m_skirmishTeamrec.clear();
		for (Int t = 0; t < count; t++)
		{
			Dict teamDict = file.readDict();
			m_teamrec.append(&teamDict);
		}
	}

	if (info->m_version >= 5)
		return true;

	ScriptList *scripts[32];
	count=0;
	Rva00352810ParserRegistration reg((void *)&scripts[0], (void *)&count, &file, (AsciiString *)info);

	if (!file.parse(0))
		throw ERROR_CORRUPT_FILE_FORMAT;

	for (Int k = 0; k < count; k++)
	{
		if (k < m_numSides)
		{
			ScriptList *pSL = getSideInfo(k)->m_scripts;
			if (pSL)
				delete pSL;
			getSideInfo(k)->m_scripts = scripts[k];
		}
		else
		{
			if (scripts[k])
				delete scripts[k];
		}
		scripts[k] = 0;
	}


	return true;
}
