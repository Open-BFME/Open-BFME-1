// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Clean C++ recovery of ScriptActions::doExitSpecificBuilding.
// Retail RVA 0x003021A0 (122 bytes).  Action-template entry 107 is
// EXIT_SPECIFIC_BUILDING; the executeAction jump table dispatches that arm.
// BFME uses ScriptEngine's by-value slot 27 (+0x6c) for this lookup.

#include "StringInline.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum KindOfType
{
	KINDOF_STRUCTURE = 7
};

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

class Object;

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
	Bool isKindOf(KindOfType kind) const
	{
		return (m_kindOf[(UnsignedInt)kind >> 5]
			& (1u << ((UnsignedInt)kind & 31))) != 0;
	}

private:
	unsigned char m_beforeKindOf[0xc8 - 8];
	UnsignedInt m_kindOf[6];
};

class AICommandInterface
{
public:
	void aiEvacuate(Bool exposeStealthUnits, CommandSourceType source);
};

class AIUpdateInterface
{
private:
	unsigned char m_beforeCommands[0x20];

public:
	AICommandInterface m_commands;
};

class ContainModuleInterface
{
public:
#define CONTAIN_SLOT(n) virtual void slot##n(void) = 0
	CONTAIN_SLOT(00); CONTAIN_SLOT(01); CONTAIN_SLOT(02); CONTAIN_SLOT(03);
	CONTAIN_SLOT(04); CONTAIN_SLOT(05); CONTAIN_SLOT(06); CONTAIN_SLOT(07);
	CONTAIN_SLOT(08); CONTAIN_SLOT(09); CONTAIN_SLOT(10); CONTAIN_SLOT(11);
	CONTAIN_SLOT(12); CONTAIN_SLOT(13); CONTAIN_SLOT(14); CONTAIN_SLOT(15);
	CONTAIN_SLOT(16); CONTAIN_SLOT(17); CONTAIN_SLOT(18); CONTAIN_SLOT(19);
	CONTAIN_SLOT(20); CONTAIN_SLOT(21); CONTAIN_SLOT(22); CONTAIN_SLOT(23);
	CONTAIN_SLOT(24); CONTAIN_SLOT(25); CONTAIN_SLOT(26); CONTAIN_SLOT(27);
	CONTAIN_SLOT(28); CONTAIN_SLOT(29); CONTAIN_SLOT(30); CONTAIN_SLOT(31);
	CONTAIN_SLOT(32); CONTAIN_SLOT(33); CONTAIN_SLOT(34); CONTAIN_SLOT(35);
	CONTAIN_SLOT(36);
	virtual void removeAllContained(Bool exposeStealthUnits) = 0;
#undef CONTAIN_SLOT
};

class Object
{
public:
	Bool isKindOf(KindOfType kind) const
	{
		const ThingTemplate *thingTemplate = m_template;
		if (thingTemplate == 0)
		{
			thingTemplate = 0;
		}
		else if (thingTemplate->m_nextOverride != 0)
			thingTemplate = (const ThingTemplate *)
				thingTemplate->m_nextOverride->getFinalOverride();
		return thingTemplate->isKindOf(kind);
	}

	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	ContainModuleInterface *getContain() { return m_contain; }

private:
	void *m_vtable;
	const ThingTemplate *m_template;
	unsigned char m_beforeContain[0x1fc - 8];
	ContainModuleInterface *m_contain;
	unsigned char m_beforeAI[4];
	AIUpdateInterface *m_ai;
};

class ScriptEngine
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
	virtual Object *getUnitNamedByValue(AsciiString name) = 0;
};

typedef ScriptEngine ScriptEngineByValue;

extern ScriptEngine *TheScriptEngine;

extern void j_000344c3();
#pragma comment(linker, "/alternatename:?aiEvacuate@AICommandInterface@@QAEX_NW4CommandSourceType@@@Z=?j_000344c3@@YAXXZ")

class ScriptActions
{
protected:
	void doExitSpecificBuilding(const AsciiString &buildingName);
};

// ?doExitSpecificBuilding@ScriptActions@@IAEXABVAsciiString@@@Z
void ScriptActions::doExitSpecificBuilding(const AsciiString &buildingName)
{
	Object *theBuilding = ((ScriptEngineByValue *)TheScriptEngine)->
		getUnitNamedByValue(buildingName);
	if (!theBuilding)
		return;

	if (!theBuilding->isKindOf(KINDOF_STRUCTURE))
		return;

	AIUpdateInterface *ai = theBuilding->getAIUpdateInterface();
	if (ai)
	{
		ai->m_commands.aiEvacuate(false, CMD_FROM_SCRIPT);
		return;
	}

	ContainModuleInterface *contain = theBuilding->getContain();
	if (contain)
		contain->removeAllContained(false);
}
