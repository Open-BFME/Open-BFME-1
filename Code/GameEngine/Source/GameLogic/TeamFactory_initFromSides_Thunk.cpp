// cl: /DNDEBUG /MD /EHsc
// readable body of ?initFromSides@TeamFactory@@QAEXPAVSidesList@@@Z: Code/GameEngine/Source/Common/RTS/Team.cpp

enum NameKeyType { NAMEKEY_INVALID = 0 };
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class StaticNameKey
{
public:
	NameKeyType key() const;
	operator NameKeyType() const { return key(); }
};

extern StaticNameKey TheKey_teamName;
extern StaticNameKey TheKey_teamOwner;
extern StaticNameKey TheKey_teamIsSingleton;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Dict.h
class Dict
{
public:
	AsciiString getAsciiString(NameKeyType key, Bool *exists = 0) const;
	Bool getBool(NameKeyType key, Bool *exists = 0) const;

private:
	void *m_data;
};

struct TeamInfoSlot
{
	short next;
	short previous;
	short reserved;
	short free;
	int generation;
	Dict dict;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/SidesList.h
class SidesList
{
private:
	// BFME's SidesList owns several side/skirmish tables before the team pool.
	char m_retailPrefix[0x63c];

public:
	TeamInfoSlot *m_teams;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamFactory
{
public:
	void initFromSides(SidesList *sides);
	void clear();
	void initTeam(const AsciiString &name, const AsciiString &owner,
		Bool singleton, Dict *dict);
};

typedef char TeamInfoSlotSizeMustMatchRetail[
	(sizeof(TeamInfoSlot) == 16) ? 1 : -1];

void TeamFactory::initFromSides(SidesList *sides)
{
	clear();

	for (int index = sides->m_teams[0].next; index != 0;
		index = sides->m_teams[index].next)
	{
		TeamInfoSlot &team = sides->m_teams[index];
		if (team.free == 0)
		{
			Dict *dict = &team.dict;
			AsciiString name = dict->getAsciiString(TheKey_teamName);
			AsciiString owner = dict->getAsciiString(TheKey_teamOwner);
			Bool singleton = dict->getBool(TheKey_teamIsSingleton);
			initTeam(name, owner, singleton, dict);
		}
	}
}
