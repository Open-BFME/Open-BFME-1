// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline
// stlport
// Four matched ScriptActions::executeAction callers and the
// SET_PLAYER_OWNERSHIP_OF_TYPE_COUNTER action template identify this method
// at RVA 0x002FD010 as ScriptActions::doSetPlayerOwnershipOfTypeCounter.

#include <vector>
#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef unsigned short UnsignedShort;

class ThingTemplate;

class Parameter
{
public:
	const AsciiString &getString() const
	{
		return *(const AsciiString *)((const char *)this + 0x10);
	}
};

class ScriptAction
{
public:
	char m_storage[0x44];
	Int field_0044;
};

struct ScriptCounter
{
public:
	Int field_0000;
};

class ObjectTypes
{
public:
	ObjectTypes();
	virtual ~ObjectTypes();
	Int prepForPlayerCounting(std::vector<const ThingTemplate *> &templates,
		std::vector<Int> &counts);

private:
	AsciiString m_listName;
	std::vector<AsciiString> m_objectTypes;
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

__declspec(noinline) ObjectTypesTemp::ObjectTypesTemp() : m_types(0)
{
	m_types = new ObjectTypes;
}

class Player
{
public:
	void countObjectsByThingTemplate(Int numTemplates,
		const ThingTemplate *const *templates, Bool ignoreDead, Int *counts,
		Bool ignoreUnderConstruction) const;
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(UnsignedShort &mask);
};

class ScriptEngine
{
friend class ScriptActions;
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
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void slot68() = 0;
	virtual void slot69() = 0;
	virtual void slot70() = 0;
	virtual void slot71() = 0;
	virtual void slot72() = 0;
	virtual void slot73() = 0;
	virtual void slot74() = 0;
	virtual void slot75() = 0;
	virtual void slot76() = 0;
	virtual void slot77() = 0;
	virtual void slot78() = 0;
	virtual void slot79() = 0;
	virtual void slot80() = 0;
	virtual void slot81() = 0;
	virtual void slot82() = 0;
	virtual void slot83() = 0;
	virtual void slot84() = 0;
	virtual void slot85() = 0;
	virtual void slot86() = 0;
	virtual void slot87() = 0;
	virtual void slot88() = 0;
	virtual void slot89() = 0;
	virtual void slot90() = 0;
	Int getFrameObjectCountChanged() const
	{
		return *(const Int *)((const char *)this + 0x170d8);
	}
	UnsignedShort unidentified_0034DB40(Parameter *parameter);
	protected:
	ScriptCounter *bfmeCounter(AsciiString name);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

class ScriptConditions
{
	friend class ScriptActions;
	protected:
	static void objectTypesFromParam(Parameter *parameter,
		ObjectTypes *objectTypes);
};

class ScriptActions
{
protected:
	void doSetPlayerOwnershipOfTypeCounter(ScriptAction *action,
		Parameter *type, Parameter *player, Parameter *counter, Bool includeDead);
};

void ScriptActions::doSetPlayerOwnershipOfTypeCounter(ScriptAction *action,
	Parameter *type, Parameter *player, Parameter *counter, Bool includeDead)
{
	if (TheScriptEngine->getFrameObjectCountChanged() == action->field_0044)
		return;

	UnsignedShort mask;
	std::vector<Int> counts;
	std::vector<const ThingTemplate *> templates;
	ObjectTypesTemp types;
	ScriptConditions::objectTypesFromParam(type, types.m_types);
	Int numTemplates = types.m_types->prepForPlayerCounting(templates, counts);
	if (!numTemplates)
		return;

	mask = TheScriptEngine->unidentified_0034DB40(player);
	Int value = 0;
		if (mask)
		{
			do
			{
				Player *thePlayer = ThePlayerList->getEachPlayerFromMask(mask);
				if (thePlayer)
				{
					thePlayer->countObjectsByThingTemplate(numTemplates,
						&(*templates.begin()), includeDead, &(*counts.begin()), true);
					Int subtotal = 0;
					for (std::vector<Int>::iterator it = counts.begin();
						it != counts.end(); ++it)
						subtotal += *it;
					value += subtotal;
				}
			} while (mask);
		}

		ScriptCounter *destination = TheScriptEngine->bfmeCounter(
			counter->getString());
		destination->field_0000 = value;
		action->field_0044 = TheScriptEngine->getFrameObjectCountChanged();
}
