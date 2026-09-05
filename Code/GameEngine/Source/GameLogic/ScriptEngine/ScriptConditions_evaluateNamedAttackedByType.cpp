// cl: /DNDEBUG /DWIN32 /MD /EHsc
// ScriptConditions::evaluateNamedAttackedByType, retail 0x00327660.
// ZH twin old path: findObjectByID(sourceID) then ObjectTypes::isInSet(template name).

typedef bool Bool;
typedef int Int;

class AsciiString
{
public:
	char *m_text;
};

class Parameter
{
};

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	const AsciiString &getName() const
	{
		return *(const AsciiString *)((const char *)this + 0x20);
	}
};

class Thing
{
public:
	virtual ~Thing();
	const ThingTemplate *getTemplate() const;
	const ThingTemplate *m_template;
};

class DamageInfo
{
public:
	unsigned char m_beforeSourceID[8];
	Int m_sourceID;
};

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
	virtual const DamageInfo *getLastDamageInfo() const = 0;
};

class Object : public Thing
{
public:
	BodyModuleInterface *getBodyModule() const
	{
		return *(BodyModuleInterface **)((char *)this + 0x200);
	}
};

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
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
};

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

// ??0ObjectTypesTemp@@QAE@XZ  retail 0x002ED6C0
ObjectTypesTemp::ObjectTypesTemp() : m_types(0)
{
	m_types = new ObjectTypes;
}

extern ScriptEngine *TheScriptEngine;
extern GameLogic *TheGameLogic;

class ScriptConditions
{
protected:
	Bool evaluateNamedAttackedByType(Parameter *, Parameter *);
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
