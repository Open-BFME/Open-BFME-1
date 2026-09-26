// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// Clean C++ recovery of ScriptConditions::evaluateHasUnits.
// Retail RVA 0x0032A2E0 (346 bytes); executeCondition's
// TEAM_HAS_UNITS arm names this body.

typedef bool Bool;
typedef int Int;

class AsciiString;

// BFME's AsciiString is the one-word StringBase view.  Keeping the copy and
// destruction in the base is important: evaluateHasUnits owns a local copy
// and passes further copies by value to ScriptEngine::getTeamNamed.
template <typename T> struct BfmeStringData
{
	Int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

template <typename T> class StringBase
{
friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase &other);
	~StringBase();

public:
	Int compare(const char *text) const;
	Int compare(const StringBase &other) const;

protected:
	BfmeStringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	Int compare(const char *text) const
	{
		return ((const StringBase<char> *)this)->compare(text);
	}

	Int compare(const AsciiString &other) const
	{
		return ((const StringBase<char> *)this)->compare(
			*(const StringBase<char> *)&other);
	}
};

// Script parameters keep their string at +0x10, as shown by the initial copy
// constructor's source load in the retail body.
class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class TeamPrototype;

// The BFME team prototype pointer is at Team+0x04.  Team's vptr occupies the
// first word, so this local view does not assume the ZH tail layout.
class Team
{
public:
	virtual void slot00() = 0;
	TeamPrototype *m_proto;

	Bool hasAnyUnits() const;
};

// The prototype name is at +0x14 and its instance-list head at +0x274 in the
// BFME image.  Only those two fields are used here.
class TeamPrototype
{
public:
	unsigned char m_beforeName[0x14];
	AsciiString m_name;
	unsigned char m_beforeInstances[0x274 - 0x18];
	Team *m_teamInstanceList;
};

// ScriptEngine slot 17 is the by-value team lookup used twice by retail.
class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;
};

class TeamFactory
{
};

// These are the real ILT entries used by the target body.  The declarations
// stay TU-local instead of asserting an unproven source identity for their
// destination bodies.  Their ABIs are established by the actual ILT targets,
// rather than by the call sites alone:
//
//   0x000064F6 -> 0x000F4C10 (179 B, matched Team::hasAnyUnits): ECX is the
//   Team object, there are no stack arguments, AL is the Bool result, and the
//   target ends in a plain RET.  Its first load is Team+0x0C, corroborating the
//   object view used by the matched Team member-query body.
//
//   0x00022A70 -> 0x000C8A30 (4 B): `mov eax,[ecx+0x14]; ret`.  This is a
//   zero-argument __thiscall accessor returning the next Team pointer; the
//   +0x10/+0x14 instance-list pair is independently visible in the Team
//   prototype list source.
//
//   0x0002AB9E -> 0x000F2320 (195 B): the target saves ECX as its factory,
//   reads the incoming pointer at [esp+4] (shown as [esp+0x2C] after its
//   prologue), and ends in `ret 4`.  It therefore consumes one
//   const-AsciiString* stack argument on a TeamFactory __thiscall and returns
//   the lookup pointer in EAX.  The body forwards the lookup through the
//   two-key helper at 0x00040A39, which is why only the one-argument adapter
//   is exposed here.
extern void j_000064f6();
extern void j_00022a70();
extern void j_0002ab9e();

static Bool bfmeHasAnyUnits(Team *team)
{
	typedef Bool (Team::*Function)() const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000064f6;
	return (reinterpret_cast<Team *>(team)->*fn.member)();
}

static Team *bfmeNextTeamInstance(Team *team)
{
	typedef Team *(Team::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00022a70;
	return (reinterpret_cast<Team *>(team)->*fn.member)();
}

static TeamPrototype *bfmeFindTeamPrototype(TeamFactory *factory,
	const AsciiString &name)
{
	typedef TeamPrototype *(TeamFactory::*Function)(const AsciiString &);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0002ab9e;
	return (reinterpret_cast<TeamFactory *>(factory)->*fn.member)(name);
}

// The fallback object is AsciiString::TheEmptyString at retail 0x01336E50.
// Its one-word storage is layout-compatible with AsciiString's base view.
struct BfmeEmptyString
{
	void *m_data;
};

extern BfmeEmptyString Rva01336E50Str;
extern ScriptEngine *TheScriptEngine;
extern TeamFactory *TheTeamFactory;

class BfmeTeamInstanceIterator
{
public:
	BfmeTeamInstanceIterator(Team *current) : m_current(current) {}

	Bool done() const { return m_current == 0; }
	Team *cur() const { return m_current; }

	void advance()
	{
		if (m_current)
			m_current = bfmeNextTeamInstance(m_current);
	}

private:
	Team *m_current;
};

class ScriptConditions
{
protected:
	Bool evaluateHasUnits(Parameter *);
};

// ?evaluateHasUnits@ScriptConditions@@IAE_NPAVParameter@@@Z
Bool ScriptConditions::evaluateHasUnits(Parameter *pTeamParm)
{
	AsciiString desiredTeamName = pTeamParm->getString();
	if (desiredTeamName.compare((const char *)0x010E1FD0) == 0)
	{
		Team *theTeam = TheScriptEngine->getTeamNamed(desiredTeamName, false);
		if (theTeam)
			return bfmeHasAnyUnits(theTeam);
		return false;
	}

	Team *thisTeam = TheScriptEngine->getTeamNamed(
		AsciiString((const char *)0x010E1FD0), false);
	if (thisTeam)
	{
		const AsciiString *thisTeamName =
			(const AsciiString *)&Rva01336E50Str;
		if (thisTeam->m_proto)
			thisTeamName = &thisTeam->m_proto->m_name;
		if (thisTeamName->compare(desiredTeamName) == 0)
			return bfmeHasAnyUnits(thisTeam);
	}

	TeamPrototype *prototype =
		bfmeFindTeamPrototype(TheTeamFactory, desiredTeamName);
	if (prototype)
	{
		BfmeTeamInstanceIterator iter(prototype->m_teamInstanceList);
		for (; !iter.done(); iter.advance())
		{
			if (bfmeHasAnyUnits(iter.cur()))
				return true;
		}
	}

	return false;
}
