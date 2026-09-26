// cl: /DNDEBUG /MD /EHsc
// Clean C++ recovery of the HAS_COMMAND_POINTS_TO_BUILD_TEAM condition.
// Retail RVA 0x003262C0 (364 bytes).  The ScriptConditions dispatcher at
// 0x0032D720 reads the condition type from Condition+4, subtracts 5, and jumps
// through the table at RVA 0x0032FB4C.  Slot 120 holds arm VA 0x0072F3FC, which
// passes two Condition parameters through ILT 0x00014E34 to this body, so the
// condition type is 125.  script_conditions.cpp sets
// m_conditionTemplates[125].m_internalName to "HAS_COMMAND_POINTS_TO_BUILD_TEAM"
// and gives it two parameters.
// The rounded average member count is its own local because retail keeps the
// ThingTemplate pointer in edi across __ftol2 and loads the command-point field
// afterwards; folding the two into one expression loads the field first.

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned short UnsignedShort;

// The copy constructor and destructor forward inline to StringBase<char>, whose
// bodies the ledger names at retail 0x00887B60 and 0x00887940.  A copy
// constructor declared on AsciiString itself resolves to a different thunk.
template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class ThingTemplate
{
public:
	Int getCommandPoints(void) const { return m_commandPoints; }

private:
	unsigned char m_beforeCommandPoints[0x4b4];
	Int m_commandPoints;
};

struct BfmeTeamMemberSlot
{
	Int m_minUnits;
	Int m_maxUnits;
	AsciiString m_templateName;
};

class TeamPrototype
{
public:
	unsigned char m_beforeMembers[0x130];
	BfmeTeamMemberSlot m_members[7];
	Int m_memberCount;
};

class Rva000C7C30Holder
{
public:
	Int get(Int which) const;
};

class Player
{
public:
	const Rva000C7C30Holder *commandPoints(void) const
	{
		return (const Rva000C7C30Holder *)((const char *)this + 0x30);
	}
};

class BfmeScriptEngineSlashName
{
public:
	AsciiString bfmeName(AsciiString &name);
};

class ScriptEngine
{
public:
	UnsignedShort unidentified_0034DB40(Parameter *player);
};

class TeamFactory
{
public:
	TeamPrototype *findTeamPrototype(const AsciiString &canonical,
		const AsciiString &name);
};

class PlayerList
{
public:
	Player *getPlayerFromMask(UnsignedShort mask);
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

struct Rva0020AA00Registry;
struct Rva002EE330PlayerList;

extern ScriptEngine *TheScriptEngine;
extern TeamFactory *TheTeamFactory;
extern Rva002EE330PlayerList *Rva002EE330ThePlayers;
extern Rva0020AA00Registry *Rva0020AA00TheRegistry;
extern const Real g_bfmeK1253;

class ScriptConditions
{
protected:
	Bool evaluateHasCommandPointsToBuildTeam(Parameter *player, Parameter *team);
};

// ?evaluateHasCommandPointsToBuildTeam@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateHasCommandPointsToBuildTeam(Parameter *player,
	Parameter *team)
{
	AsciiString teamName = team->getString();
	AsciiString canonical =
		((BfmeScriptEngineSlashName *)TheScriptEngine)->bfmeName(teamName);
	TeamPrototype *prototype =
		TheTeamFactory->findTeamPrototype(canonical, teamName);
	if (prototype == 0)
		return false;

	UnsignedShort mask = TheScriptEngine->unidentified_0034DB40(player);
	if (mask == 0)
		return false;

	Player *thePlayer =
		((PlayerList *)Rva002EE330ThePlayers)->getPlayerFromMask(mask);
	if (thePlayer == 0)
		return false;

	Int available = thePlayer->commandPoints()->get(1);
	Int required = 0;
	for (Int i = 0; i < prototype->m_memberCount; ++i)
	{
		const ThingTemplate *tmpl =
			((BfmeThingFactory *)Rva0020AA00TheRegistry)
				->findTemplate(prototype->m_members[i].m_templateName);
		if (tmpl != 0)
		{
			Int total = prototype->m_members[i].m_minUnits +
				prototype->m_members[i].m_maxUnits;
			Int average = (Int)((Real)total * g_bfmeK1253);
			required += tmpl->getCommandPoints() * average;
		}
	}
	return required <= available;
}
