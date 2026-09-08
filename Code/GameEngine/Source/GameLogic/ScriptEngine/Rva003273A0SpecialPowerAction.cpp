// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
//
// Raw-ABI reconstruction of retail RVA 0x003273A0.  The entry is a
// thiscall with three Parameter * arguments, but the surviving caller set
// does not identify its ScriptActions operation.  Keep that unresolved part
// address-derived while preserving the observed string, vcall, and helper
// routes.

// Scratch-only canonical StringBase model.  The wrapper is a private
// StringBase<char> so its copy and destruction relocations name the actual
// vendor AAE StringBase bodies rather than a TU-local alias.
template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};
class AsciiString;
class UnicodeString;
class BfmeAsciiStringArg;
template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;
	friend class BfmeAsciiStringArg;
private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();
	StringInlineData<T> *m_data;
};
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};
typedef bool Bool;
typedef int Int;
typedef unsigned short PlayerMaskType;

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 2
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }
	void setCachedValue(Int value) { m_cachedValue = value; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
	unsigned char m_beforeCachedValue[0x0c];
	Int m_cachedValue;
};

class Player;
class Team;
class Object;
class SpecialPowerTemplate;
class SpecialPowerStore;
class ActionManager
{
public:
	Bool canDoSpecialPowerAtLocation(const Object *object,
		const Coord3D *location, CommandSourceType commandSource,
		const SpecialPowerTemplate *power, const Object *objectInWay,
		unsigned int commandOptions, Bool checkSourceRequirements);
};

// Retail's BFME by-value string argument uses the out-of-line StringBase
// copy/destructor route at 0x00887B60/0x00887940.
class ScriptEngine
{
};

// The first direct call is the existing ScriptEngine parameter-mask thunk.
class BfmeScriptEngineParameterMaskCall
{
public:
	PlayerMaskType getPlayerMask(Parameter *parameter);
};

class PlayerList
{
};

class BfmePlayerListMaskCall
{
public:
	Player *getPlayerFromMask(PlayerMaskType mask);
};

// The helper's EAX is consumed as the source object for the final action
// query, but its owner/name is not established by a named caller.
class Rva003273A0OpaqueSourceCall
{
public:
	void *resolve(void);
};

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
};

// Slot 17 is the retail getTeamNamed entry; the second Bool is visible in
// the push immediately before the first local string argument.
class BfmeScriptEngineVtbl44
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;
};

class Team
{
public:
	Bool hasAnyObjects(Bool includeSpecialObjects) const;
	Coord3D *getEstimateTeamPosition(Coord3D *position) const;
};

class BfmeActionManagerSpecialPowerLocationCall
{
public:
	Bool canDoSpecialPowerAtLocation(const Object *object,
		const Coord3D *location, Int commandSource,
		const SpecialPowerTemplate *power, const Object *objectInWay,
		unsigned int commandOptions, Bool checkSourceRequirements);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern SpecialPowerStore *TheSpecialPowerStore;
extern ActionManager *TheActionManager;

extern void j_000230b5(void);
extern void j_0001dde5(void);
extern void j_00005a6a(void);
extern void j_00020f04(void);
extern void j_0001478b(void);
extern void j_0002990b(void);
extern void j_00011914(void);

static __forceinline PlayerMaskType bfmeGetPlayerMask(
	ScriptEngine *engine, Parameter *parameter)
{
	typedef PlayerMaskType (BfmeScriptEngineParameterMaskCall::*Function)(
		Parameter *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000230b5;
	return (reinterpret_cast<BfmeScriptEngineParameterMaskCall *>(engine)->*
		fn.member)(parameter);
}

static __forceinline Player *bfmeGetPlayerFromMask(PlayerList *players,
	PlayerMaskType mask)
{
	typedef Player *(BfmePlayerListMaskCall::*Function)(PlayerMaskType);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0001dde5;
	return (reinterpret_cast<BfmePlayerListMaskCall *>(players)->*fn.member)(
		mask);
}

static __forceinline void *bfmeResolveSource(Player *player)
{
	typedef void *(Rva003273A0OpaqueSourceCall::*Function)(void);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00005a6a;
	return (reinterpret_cast<Rva003273A0OpaqueSourceCall *>(player)->*
		fn.member)();
}

static __forceinline Bool bfmeHasAnyObjects(Team *team)
{
	typedef Bool (Team::*Function)(Bool) const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0001478b;
	return (reinterpret_cast<const Team *>(team)->*fn.member)(false);
}

static __forceinline Coord3D *bfmeGetEstimateTeamPosition(const Team *team,
	Coord3D *position)
{
	typedef Coord3D *(Team::*Function)(Coord3D *) const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0002990b;
	return (reinterpret_cast<const Team *>(team)->*
		fn.member)(position);
}

static __forceinline Bool bfmeCanDoSpecialPowerAtLocation(
	ActionManager *manager, const Object *object, const Coord3D *location,
	Int commandSource, const SpecialPowerTemplate *power,
	const Object *objectInWay, unsigned int commandOptions,
	Bool checkSourceRequirements)
{
	typedef Bool (BfmeActionManagerSpecialPowerLocationCall::*Function)(
		const Object *, const Coord3D *, Int, const SpecialPowerTemplate *,
		const Object *, unsigned int, Bool);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00011914;
	return (reinterpret_cast<BfmeActionManagerSpecialPowerLocationCall *>(
		manager)->*fn.member)(object, location, commandSource, power,
		objectInWay, commandOptions, checkSourceRequirements);
}

class Rva003273A0SpecialPowerAction
{
public:
	Bool execute(Parameter *playerParameter, Parameter *powerParameter,
		Parameter *teamParameter);
};

Bool Rva003273A0SpecialPowerAction::execute(Parameter *playerParameter,
	Parameter *powerParameter, Parameter *teamParameter)
{
	PlayerMaskType mask = bfmeGetPlayerMask(TheScriptEngine, playerParameter);
	Player *player = bfmeGetPlayerFromMask(ThePlayerList, mask);
	if (!player)
		return false;

	void *source = bfmeResolveSource(player);
	if (!source)
		return false;

	const SpecialPowerTemplate *power =
		((SpecialPowerStore *)TheSpecialPowerStore)
			->findSpecialPowerTemplate(powerParameter->getString());
	if (!power) {
		powerParameter->setCachedValue(-1);
		return false;
	}

	Team *team = ((BfmeScriptEngineVtbl44 *)TheScriptEngine)->getTeamNamed(
		teamParameter->getString(), false);
	if (!team || !bfmeHasAnyObjects(team))
		return false;

	Coord3D position;
	return TheActionManager->canDoSpecialPowerAtLocation((const Object *)source,
		bfmeGetEstimateTeamPosition(team, &position), CMD_FROM_SCRIPT, power,
		0, 0, true);
}
