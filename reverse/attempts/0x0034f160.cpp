// ?getTeamNamed@ScriptEngine@@UAEPAVTeam@@VAsciiString@@_N@Z
// partial score=0.29 date=2026-09-23
// Retail 0x0034F160: BFME's by-value team lookup with the create flag.
// The slot, reference map and team context offsets are established by landed
// ScriptEngine callers, vtable evidence and the adjacent reference-map body.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <utility>

inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

__forceinline int bfmeCompareAscii(const AsciiString &left,
	const AsciiString &right)
{
	return ((const StringBase<char> *)&left)->compare(
		*(const StringBase<char> *)&right);
}

class BFMEScriptEngineFlagLookup
{
public:
	AsciiString canonicalFlagName(const AsciiString &name);
};

class Team;

class TeamPrototype
{
public:
	bool getIsSingleton() const { return (m_flags & 1) != 0; }
	int countTeamInstances();

	char m_pad0[0x10];
	AsciiString m_name;
	AsciiString m_owner;
	unsigned char m_flags;
	char m_pad1[3];
	char m_pad2[0x258];

	public:
	Team *m_teamInstanceList;
};

class Team
{
public:
	void *m_vtable;
	TeamPrototype *m_prototype;
	char m_pad0[0x29];
	unsigned char m_active;
	unsigned char m_created;

	const AsciiString &getName() const
	{
		return m_prototype == 0 ? *(const AsciiString *)0x01336E50
			: m_prototype->m_name;
	}
	const AsciiString &getOwnerName() const
	{
		return m_prototype == 0 ? *(const AsciiString *)0x01336E50
			: m_prototype->m_owner;
	}
};

class TeamFactory
{
public:
	Team *findTeamByID(unsigned int id);
	TeamPrototype *findTeamPrototype(const AsciiString &name,
		const AsciiString &ownerName);
	Team *createTeam(const AsciiString &ownerName,
		const AsciiString &name);
};

extern TeamFactory *TheTeamFactory;

AsciiString Rva00195FC0JoinPath(const AsciiString &left,
	const AsciiString &right);

typedef std::pair<AsciiString, AsciiString> Rva003455E0Key;

namespace _STL
{
template<class T> struct less;

template<> struct less<Rva003455E0Key>
{
	bool operator()(const Rva003455E0Key &left,
		const Rva003455E0Key &right) const
	{
		return left.first.compare(right.first) < 0
			|| (!(right.first.compare(left.first) < 0)
				&& left.second.compare(right.second) < 0);
	}
};
}

typedef unsigned int Rva003455E0MappedValue;
typedef std::map<Rva003455E0Key, Rva003455E0MappedValue>
	Rva003455E0Map;

class ScriptEngine
{
public:
#define SLOT(n) virtual void slot##n() = 0;
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06)
	SLOT(07) SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13)
	SLOT(14) SLOT(15) SLOT(16)
	virtual Team *getTeamNamed(AsciiString name, bool exact);
	void AppendDebugMessage(const AsciiString &message, bool forcePause);
#undef SLOT

private:
	char m_beforeReferenceMaps[0x16054];
	Rva003455E0Map m_unitReferences;
	Rva003455E0Map m_teamReferences;
	char m_beforeCallingTeam[0x101c];
	Team *m_callingTeam;
	char m_betweenContextTeams[4];
	Team *m_conditionTeam;
};

Team *ScriptEngine::getTeamNamed(AsciiString name, bool exact)
{
	if (name.compare("<This Team>") == 0)
	{
		if (m_callingTeam)
			return m_callingTeam;
		return m_conditionTeam;
	}

	AsciiString canonical =
		((BFMEScriptEngineFlagLookup *)this)->canonicalFlagName(name);

	Team *callingTeam = m_callingTeam;
	if (callingTeam)
	{
		if (bfmeCompareAscii(callingTeam->getName(), canonical) == 0)
		{
			if (bfmeCompareAscii(callingTeam->getOwnerName(), name) == 0)
				return callingTeam;
		}
	}

	Team *conditionTeam = m_conditionTeam;
	if (conditionTeam)
	{
		if (bfmeCompareAscii(conditionTeam->getName(), canonical) == 0)
		{
			if (bfmeCompareAscii(conditionTeam->getOwnerName(), name) == 0)
				return conditionTeam;
		}
	}

	{
		Rva003455E0Key key(canonical, name);
		Rva003455E0Map::iterator found = m_teamReferences.find(key);
		if (found != m_teamReferences.end())
			return TheTeamFactory->findTeamByID(found->second);
	}

	TeamPrototype *prototype =
		TheTeamFactory->findTeamPrototype(canonical, name);
	if (prototype == 0)
		return 0;

	if (prototype->getIsSingleton())
	{
		Team *theTeam = prototype->m_teamInstanceList;
		if (theTeam == 0)
			return 0;
		if (theTeam->m_active)
			return theTeam;
		if (!exact)
			return 0;
		if (!theTeam->m_active)
		{
			theTeam->m_created = 1;
			theTeam->m_active = 1;
		}
		return theTeam;
	}

	static int warnCount = 0;
	if (prototype->countTeamInstances() > 1)
	{
		if (warnCount < 10)
		{
			++warnCount;
			AppendDebugMessage(AsciiString(
				"***Referencing multiple team by unspecific instance:***"),
				false);
			AppendDebugMessage(Rva00195FC0JoinPath(canonical, name), false);
		}
	}

	Team *theTeam = prototype->m_teamInstanceList;
	if (theTeam)
		return theTeam;
	if (!exact)
		return 0;
	return TheTeamFactory->createTeam(canonical, name);
}
