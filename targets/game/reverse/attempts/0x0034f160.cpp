// ?getTeamNamed@ScriptEngine@@UAEPAVTeam@@VAsciiString@@_N@Z
// partial score=0.4355 date=2026-10-09
// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib

// stlport
#include "ascii_string.h"
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <utility>

__forceinline int bfmeCompareAscii(const AsciiString &left,
	const AsciiString &right)
{
	return ((const StringBase<char> *)&left)->compare(
		*(const StringBase<char> *)&right);
}

class BfmeScriptEngineSlashName
{
public:
	AsciiString bfmeName(AsciiString &name);

private:
	char m_pad[0x17088];
	AsciiString m_fallback;
};

class BFMEScriptEngineFlagLookup
{
public:
	AsciiString canonicalFlagName(AsciiString &name);
};

extern const AsciiString Rva01336E50EmptyAscii;

class Team;

class TeamPrototype
{
public:
	bool getIsSingleton() const { return (m_flags & 1) != 0; }
	int countTeamInstances();
	const AsciiString &getName() const { return m_name; }
	const AsciiString &getOwnerName() const { return m_owner; }
	Team *getFirstItemIn_TeamInstanceList() const { return m_teamInstanceList; }

	char m_pad0[0x10];
	AsciiString m_name;
	AsciiString m_owner;
	union { unsigned int m_flags; char m_pad1[4]; };
	char m_pad2[0x258];

	public:
	Team *m_teamInstanceList;
};

class Team
{
public:
	void *m_vtable;
	TeamPrototype *m_prototype;
	unsigned int m_id;
	char m_pad0[0x25];
	bool m_active;
	bool m_created;

	bool isActive() { return m_active; }
	void setActive()
	{
		if (!m_active)
		{
			m_created = true;
			m_active = true;
		}
	}

	const AsciiString &getName() const
	{
		return m_prototype == 0 ? Rva01336E50EmptyAscii
			: m_prototype->getName();
	}
	const AsciiString &getOwnerName() const
	{
		return m_prototype == 0 ? Rva01336E50EmptyAscii
			: m_prototype->getOwnerName();
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
		((BfmeScriptEngineSlashName *)this)->bfmeName(name);

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
		Team *theTeam = prototype->getFirstItemIn_TeamInstanceList();
		if (theTeam && theTeam->isActive())
			return theTeam;
		if (theTeam && exact)
		{
			theTeam->setActive();
			return theTeam;
		}
		return 0;
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

	Team *theTeam = prototype->getFirstItemIn_TeamInstanceList();
	if (theTeam)
		return theTeam;
	if (exact)
	{
		theTeam = TheTeamFactory->createTeam(canonical, name);
		return theTeam;
	}
	return 0;
}
