// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?evaluateNamedAttackedByType@ScriptConditions@@IAE_NPAVParameter@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateNamedDestroyedByType@ScriptConditions@@IAE_NPAVParameter@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp

// The two ScriptConditions conditions that ask what kind of thing last damaged
// a named unit:
//
//   0x00327660  evaluateNamedAttackedByType   template NAMED_ATTACKED_BY_TYPE
//   0x00329950  evaluateNamedDestroyedByType  template 130, NAMED_DESTROYED_BY_OBJECTTYPE
//
// Both walk the same chain -- name the unit, take its body module's last
// DamageInfo, find the source object by ID, and test that object's template
// name against the ObjectTypes set the type parameter names. They differ in
// exactly two places: the destroyed one first requires the victim to be
// effectively dead (Object+0x344 bit 0), and the attacked one resolves the
// attacker's template through its override chain before testing it.
//
// The ObjectTypes set is built on the stack through ObjectTypesTemp, whose
// constructor both files also defined privately so the inline `delete` in its
// destructor would have something to construct. That definition is not this
// TU's to own -- the ledger row for ??0ObjectTypesTemp@@QAE@XZ lives in
// ObjectTypesTemp_ctor_Thunk.cpp -- but it has to be here to compile, and one
// copy is better than the two that were.
//
// The Thing/ThingTemplate model is the attacked body's, which is the larger of
// the two: ThingTemplate derives from Overridable so the override walk can be
// spelled, and Thing holds m_template at +0x04. Neither addition moves
// anything the destroyed body reads, because every offset it uses -- the body
// module at +0x200, the dead bit at +0x344, the template name at +0x20 -- is
// an explicit cast rather than a member.

typedef bool Bool;
typedef int Int;

#include "ascii_string.h"

class Parameter
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;
	Overridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	const AsciiString &getName() const
	{
		return *(const AsciiString *)((const char *)this + 0x20);
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	virtual ~Thing();
	const ThingTemplate *getTemplate() const;
	const ThingTemplate *m_template;			// this+0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfo
{
public:
	unsigned char m_beforeSourceID[8];
	Int m_sourceID;						// this+0x08
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BodyModuleInterface
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
	virtual const DamageInfo *getLastDamageInfo() const = 0;	// slot 15, vtable+0x3C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	BodyModuleInterface *getBodyModule() const
	{
		return *(BodyModuleInterface **)((char *)this + 0x200);
	}

	Bool isEffectivelyDead() const
	{
		return (*(unsigned char *)((char *)this + 0x344) & 1) != 0;
	}
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

// ObjectTypes is 20 bytes (vptr + list name + vector triple). Matched
// ObjectTypesTemp ctor at 0x002ED6C0 does push 0x14 / operator new /
// ObjectTypes ctor. virtual dtor declared so delete emits push 1 / call [vtbl].
class ObjectTypes
{
public:
	ObjectTypes();
	virtual ~ObjectTypes();
	Bool isInSet(const AsciiString &objectType) const;
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

extern ScriptEngine *TheScriptEngine;
extern GameLogic *TheGameLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	Bool evaluateNamedAttackedByType(Parameter *, Parameter *);
	Bool evaluateNamedDestroyedByType(Parameter *, Parameter *);
	static void objectTypesFromParam(Parameter *, ObjectTypes *);
};

// ?evaluateNamedAttackedByType@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateNamedAttackedByType(
	Parameter *pUnitParm, Parameter *pTypeParm)
{
	ObjectTypes *objectTypes;
	Object *theObj = TheScriptEngine->getUnitNamed(
		*(const AsciiString *)pUnitParm);
	if (theObj) {
		BodyModuleInterface *theBodyModule = theObj->getBodyModule();
		if (theBodyModule) {
			const DamageInfo *lastDamageInfo = theBodyModule->getLastDamageInfo();
			if (lastDamageInfo) {
				GameLogic *logic = TheGameLogic;
				Int id = lastDamageInfo->m_sourceID;
				Object *pAttacker = logic->findObjectByID(id);
				if (pAttacker) {
					const ThingTemplate *tmpl = pAttacker->m_template;
					if (tmpl) {
						if (tmpl->m_nextOverride)
							tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
						if (tmpl) {
							ObjectTypesTemp types;
							objectTypes = types.m_types;
							objectTypesFromParam(pTypeParm, objectTypes);
							return objectTypes->isInSet(
								pAttacker->getTemplate()->getName());
						}
					}
				}
			}
		}
	}
	return false;
}

// ?evaluateNamedDestroyedByType@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateNamedDestroyedByType(
	Parameter *pUnitParm, Parameter *pTypeParm)
{
	ObjectTypes *objectTypes;
	Object *theObj = TheScriptEngine->getUnitNamed(
		*(const AsciiString *)pUnitParm);
	if (theObj) {
		BodyModuleInterface *theBodyModule = theObj->getBodyModule();
		if (theBodyModule) {
			const DamageInfo *lastDamageInfo = theBodyModule->getLastDamageInfo();
			if (lastDamageInfo) {
				if (theObj->isEffectivelyDead()) {
					GameLogic *logic = TheGameLogic;
					Int id = lastDamageInfo->m_sourceID;
					Object *pAttacker = logic->findObjectByID(id);
					if (pAttacker) {
						if (pAttacker->getTemplate()) {
							ObjectTypesTemp types;
							objectTypes = types.m_types;
							objectTypesFromParam(pTypeParm, objectTypes);
							return objectTypes->isInSet(
								pAttacker->getTemplate()->getName());
						}
					}
				}
			}
		}
	}
	return false;
}
