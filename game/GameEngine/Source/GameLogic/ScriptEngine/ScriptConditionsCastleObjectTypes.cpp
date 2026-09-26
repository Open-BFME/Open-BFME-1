// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// ScriptConditions condition at retail 0x003240F0 (230 bytes): name a unit
// through ScriptEngine slot 26, find its CastleBehavior module by name key,
// build an ObjectTypes set from the type parameter and ask the castle about it.
//
// Owner: reached only from the ScriptConditions condition dispatch (call sites
// 0x0032E1A6 and 0x0032E1B6 through ILT thunk 0x00010AF5), which hands it
// getParameter(0) and getParameter(1) exactly as the neighbouring cases hand
// them to evaluateTeamExitedAreaEntirely (0x00324F60) and
// evaluateTeamExitedAreaPartially (0x00324FF0); it calls the protected static
// ScriptConditions::objectTypesFromParam. The condition's own name is not
// proven, so the method keeps its address.
//
// The ObjectTypesTemp constructor is defined here as in
// ScriptConditionsNamedByType.cpp: with its body visible MSVC keeps m_types in
// esi across both calls and the destructor, as retail does. Declared-only, it
// reloads the member and grows to 234 bytes. The ledger row for
// ??0ObjectTypesTemp@@QAE@XZ stays in ObjectTypesTemp_ctor_Thunk.cpp.
typedef bool Bool;
typedef int Int;

#include "ascii_string.h"

class Parameter
{
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Module *findModule(NameKeyType key) const;
};

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
};

// ObjectTypes is 20 bytes; virtual dtor so delete emits push 1 / call [vtbl].
class ObjectTypes
{
public:
	ObjectTypes();
	virtual ~ObjectTypes();
private:
	void *m_listName;
	void *m_objTypesBegin;
	void *m_objTypesEnd;
	void *m_objTypesCap;
};

class ObjectTypesTemp
{
public:
	ObjectTypes *m_types;
	ObjectTypesTemp();
	~ObjectTypesTemp()
	{
		if (m_types)
			delete m_types;
	}
};

// ??0ObjectTypesTemp@@QAE@XZ  retail 0x002ED6C0; the row that claims it is
// game/GameEngine/Source/GameLogic/ScriptEngine/ObjectTypesTemp_ctor_Thunk.cpp.
ObjectTypesTemp::ObjectTypesTemp() : m_types(0)
{
	m_types = new ObjectTypes;
}

class CastleBehavior
{
public:
	Bool rva00370340(ObjectTypes *types);
};

extern ScriptEngine *TheScriptEngine;
extern NameKeyGenerator *TheNameKeyGenerator;

class ScriptConditions
{
protected:
	Bool evaluateRva003240F0(Parameter *, Parameter *);
	static void objectTypesFromParam(Parameter *, ObjectTypes *);
};

// ?evaluateRva003240F0@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateRva003240F0(
	Parameter *pTypeParm, Parameter *pUnitParm)
{
	Object *obj = TheScriptEngine->getUnitNamed(*(const AsciiString *)pUnitParm);
	if (!obj)
		return false;

	static NameKeyType key = TheNameKeyGenerator->nameToKey("CastleBehavior");
	CastleBehavior *castle = (CastleBehavior *)obj->findModule(key);
	if (!castle)
		return false;

	ObjectTypesTemp types;
	ObjectTypes *objectTypes = types.m_types;
	objectTypesFromParam(pTypeParm, objectTypes);
	return castle->rva00370340(objectTypes) != false;
}
