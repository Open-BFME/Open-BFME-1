// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Every ScriptConditions condition that resolves one unit by name through
// ScriptEngine's slot 26 and then asks that object a question:
//
//   0x003237F0  evaluateIsSiegeAttachedToWall     a module it carries
//   0x00325FC0  evaluateRva00325FC0               a name on its body
//   0x00327560  evaluateNamedUnitRankLevel        a rank on its body
//   0x0032B390  evaluateNamedReachedWaypointsEnd  the waypoint its AI finished
//
// They sat in four files that each carried a private copy of Parameter,
// AsciiString, Object and the ScriptEngine vtable, and every one of those had
// drifted.
//
// The vtable slot they all call appeared under three names and two signatures:
// getUnitNamed(Parameter *), getUnitNamed(const AsciiString &) and
// resolveUnitParameter(Parameter *). It is one slot -- +0x68 -- and one call:
// retail pushes the Parameter pointer unchanged, which works because Parameter
// carries its string at +0x10 and every caller hands over that address. Stated
// once as getUnitNamed(const AsciiString &), the two Parameter-typed callers
// cast, and all four bodies byte-match.
//
// One file went further and declared the whole vtable a second time as a
// "BfmeScriptConditionEngine" purely so it could reinterpret_cast
// TheScriptEngine at the call site. There is one engine and one vtable.
//
// Then the body pointer. Two files read the same pointer at Object+0x210 and
// disagreed about what it points at: a Body whose rank level is at +0x28, or a
// "BfmeObjectField210" whose name is at +0x08. It is one object, and one layout
// states both fields. What that object IS remains unproven -- the +0x210 owner
// type was never recovered -- so the class keeps the upstream Body name and
// nothing more is claimed for it.
//
// One half of that is now settled, and it is the half that mattered.
// ScriptConditionsCompare.cpp reads this same (Object+0x210)+0x28 and calls it
// m_health, which cannot be right: Object's body module is not at +0x210 at
// all. ?getBodyModule@Object@@QBEPAVBodyModuleInterface@@XZ at 0x00478720 is
// the whole accessor, `mov eax, [ecx+0x194]; ret`, so the body module lives at
// +0x194 and health is reached through THAT pointer. Zero Hour's
// evaluateUnitHealth agrees about the route -- it calls getBodyModule() twice,
// for getHealth() and getInitialHealth(), and divides to a percentage -- and
// the retail body at 0x00324020 does none of it: one load of
// (Object+0x210)+0x28, then a six-case jump table comparing it as a SIGNED
// INTEGER with setl/setle/sete/setge against Parameter+0x08. No second field,
// no division, no float anywhere. An integer read directly and compared is
// what a rank level looks like, not a health percentage, so m_health is the
// name to distrust here and m_rankLevel is the one the bytes fit.
//
// What +0x210 points at is still open, and the obvious route is closed: the
// only one-line `mov eax, [ecx+0x210]; ret` accessors in .text are a dup_
// placeholder at 0x000C88C0, an unclaimed body at 0x000F91F0, and
// ?winGetLayout@GameWindow@@ at 0x00478E20, which is a different class whose
// identical one-liner folded onto the same shape and so names nothing here.
// Identifying either that accessor or the unclaimed callers between 0x0032D643
// and 0x003307E0 -- the two conditions are reached only through ILT thunks
// 0x000361A1 and 0x00044DC3, called from bodies in that gap -- would finish it.
//
// Parameter drifted as usual: two files spelled it as a flat 0x10-byte run to
// the string, one as the Int at +0x08 with four unnamed bytes after it, and one
// never modelled it at all.
//
// AsciiString drifted last: a bare char* in two files, a BfmeStringData* in the
// third, plus a StringBase<char>::compare that only the waypoint body declares
// and only it needs -- retail's non-throwing compare call leaves no
// intermediate EH-state stores, so the throw() stays.

typedef bool Bool;
typedef int Int;
typedef float Real;

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *left, const char *right);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
template <class T> class StringBase
{
	friend class AsciiString;

	public:
	// Retail's non-throwing compare call leaves no intermediate EH-state stores.
	int compare(const StringBase &) const throw();

	private:
	StringBase(const StringBase &);
	~StringBase();
};

struct BfmeStringData { int references; unsigned short length; unsigned short capacity; char text[1]; };

class AsciiString
{
public:
	AsciiString(const char *text);
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();
	AsciiString &operator+=(const AsciiString &text);

	BfmeStringData *m_text;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return ((const StringBase<char> *)&left)->compare(
		*(const StringBase<char> *)&right) == 0;
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }
	Int getInt(void) const { return m_int; }

	unsigned char m_beforeInt[8];
	Int m_int;						// this+0x08
	Real m_real;						// this+0x0C
	AsciiString m_string;					// this+0x10
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Module;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

// The thing Object+0x210 points at. Two conditions read it -- one for the name
// at +0x08, one for the rank level at +0x28 -- and neither proves what it is.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class Body
{
public:
	Int getRankLevel(void) const { return m_rankLevel; }

	unsigned char m_beforeName[8];
	AsciiString m_name;					// this+0x08
	unsigned char m_beforeRankLevel[0x28 - 0x0C];
	Int m_rankLevel;					// this+0x28
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
	class Waypoint *getCompletedWaypoint() const
	{
		return *(class Waypoint **)((const char *)this + 0x13c);
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	AsciiString getPathLabel1() const;
	AsciiString getPathLabel2() const;
	AsciiString getPathLabel3() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Body *getBody(void) const { return m_body; }
	Module *findModule(NameKeyType key) const;
	AIUpdateInterface *getAIUpdateInterface() const
	{
		return *(AIUpdateInterface **)((const char *)this + 0x204);
	}

	unsigned char m_beforeBody[0x210];
	Body *m_body;						// this+0x210
};

class SiegeDeploySpecialPower
{
};

extern void j_00048112();

static __forceinline Bool isSiegeAttached(SiegeDeploySpecialPower *module)
{
	typedef Bool (SiegeDeploySpecialPower::*Function)() const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00048112;
	return (reinterpret_cast<SiegeDeploySpecialPower *>(module)->*fn.member)();
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;	// slot 26, vtable+0x68

	void AppendDebugMessage(const AsciiString &message, Bool pause);
};

extern ScriptEngine *TheScriptEngine;
extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	Bool evaluateIsSiegeAttachedToWall(Parameter *unitParm);
	Bool evaluateRva00325FC0(Parameter *, Parameter *);
	Bool evaluateNamedUnitRankLevel(Parameter *, Parameter *);
	Bool evaluateNamedReachedWaypointsEnd(Parameter *, Parameter *);
};

// ?evaluateIsSiegeAttachedToWall@ScriptConditions@@IAE_NPAVParameter@@@Z
Bool ScriptConditions::evaluateIsSiegeAttachedToWall(Parameter *unitParm)
{
	Object *unit = TheScriptEngine->getUnitNamed(*(const AsciiString *)unitParm);
	if (unit)
	{
		static NameKeyType key =
			TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
		Module *module = unit->findModule(key);
		if (module)
			return isSiegeAttached((SiegeDeploySpecialPower *)module);
	}
	return false;
}

// ?evaluateRva00325FC0@ScriptConditions@@IAE_NPAVParameter@@0@Z
// The retail body compares parameter+0x10 with the string at Object+0x210's
// +0x08. The original condition name is not proven by the matching body.
Bool ScriptConditions::evaluateRva00325FC0(
	Parameter *pUnitParm, Parameter *pNameParm)
{
	if (!pUnitParm)
		return false;
	if (!pNameParm)
		return false;

	Object *obj = TheScriptEngine->getUnitNamed(*(const AsciiString *)pUnitParm);
	if (!obj)
		return false;

	AsciiString name = pNameParm->getString();
	BfmeStringData *p = name.m_text;
	if (p && p->length) {
		Body *body = obj->m_body;
		if (body) {
			BfmeStringData *q = body->m_name.m_text;
			const char *right = p->text;
			const char *left = q ? q->text : "";
			return _strcmpi(left, right) == 0;
		}
	}

	return false;
}

// ?evaluateNamedUnitRankLevel@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateNamedUnitRankLevel(
	Parameter *pUnitParm, Parameter *pRankParm)
{
	static Bool warned = false;
	Object *pUnit = TheScriptEngine->getUnitNamed(
		*(const AsciiString *)pUnitParm);

	if (!pUnit) {
		if (!warned) {
			warned = true;
			AsciiString message(
				"ScriptConditions::evaluateNamedUnitRankLevel: Unit not found: ");
			message += pUnitParm->getString();
			TheScriptEngine->AppendDebugMessage(message, false);
		}
		return false;
	}

	Body *body = pUnit->getBody();
	if (!body)
		return false;

	return body->getRankLevel() >= pRankParm->getInt();
}

// ?evaluateNamedReachedWaypointsEnd@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateNamedReachedWaypointsEnd(Parameter *pUnitParm, Parameter *pWaypointPathParm)
{
	// Retail passes the first Parameter's address as the AsciiString reference
	// consumed by getUnitNamed, while the path Parameter uses its +0x10 string
	// member below. Preserve that BFME-specific ABI shape explicitly.
	Object *theObj = TheScriptEngine->getUnitNamed(
		*(const AsciiString *)pUnitParm);
	if (!theObj)
		return false;

	AIUpdateInterface *ai = theObj->getAIUpdateInterface();
	if (!ai)
		return false;

	const Waypoint *targetWay = ai->getCompletedWaypoint();
	if (!targetWay)
		return false;

	AsciiString pathName = pWaypointPathParm->getString();
	if (targetWay->getPathLabel1() == pathName)
		return true;
	if (targetWay->getPathLabel2() == pathName)
		return true;
	if (targetWay->getPathLabel3() == pathName)
		return true;

	return false;
}
