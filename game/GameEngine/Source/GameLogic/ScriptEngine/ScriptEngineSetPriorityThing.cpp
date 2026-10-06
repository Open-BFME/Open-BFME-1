// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// ScriptEngine::setPriorityThing at retail RVA 0x0033E040. The executeActions
// caller and EA's own label (ea_evidence.csv) establish the identity.

#include <vector>
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;

class BfmeStringLiteralBase
{
	friend class BFMERetailAsciiString;

private:
	BfmeStringLiteralBase(const char *string);
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *string)
	{
		((BfmeStringLiteralBase *)this)->BfmeStringLiteralBase::BfmeStringLiteralBase(string);
	}

	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	char *m_data;
};

class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }
	Int getInt(void) const { return m_integer; }

private:
	char m_unknown[8];
	Int m_integer;
	float m_real;
	AsciiString m_string;
};

class ScriptAction
{
public:
	Parameter *getParameter(Int index)
	{
		if (index >= 0 && index < m_parameterCount)
			return m_parameters[index];
		return 0;
	}

private:
	char m_unknown[8];
	Int m_parameterCount;
	Parameter *m_parameters[12];
};

class ObjectTypes
{
private:
	AsciiString m_listName;
	std::vector<AsciiString> m_objectTypes;

protected:
	virtual void crc(void *xfer);
	virtual void xfer(void *xfer);
	virtual void loadPostProcess(void);

public:
	unsigned int getListSize(void) const { return m_objectTypes.size(); }
	AsciiString getNthInList(Int index) const;
};

class ThingTemplate;

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

class AttackPriorityInfo
{
public:
	void setPriority(const ThingTemplate *thing, Int priority);
};

class ScriptEngine
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual ObjectTypes *getObjectTypes(const AsciiString &objectTypeList);

protected:
	AttackPriorityInfo *findAttackInfo(const AsciiString &name, Bool addIfNotFound);
public:
	void AppendDebugMessage(const AsciiString &message, Bool forcePause);

	protected:
	void setPriorityThing(ScriptAction *action);
};

extern ScriptEngine *TheScriptEngine;

// ?setPriorityThing@ScriptEngine@@IAEXPAVScriptAction@@@Z
void ScriptEngine::setPriorityThing(ScriptAction *action)
{
	AsciiString typeArgument = action->getParameter(1)->getString();
	ObjectTypes *types = TheScriptEngine->getObjectTypes(typeArgument);
	if (!types)
	{
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(typeArgument);
		if (!thingTemplate)
		{
			{
				BFMERetailAsciiString message("***Attempting to set attack priority on an invalid thing:***");
				AppendDebugMessage(*(const AsciiString *)&message, false);
			}
			AppendDebugMessage(action->getParameter(0)->getString(), false);
			return;
		}

		AttackPriorityInfo *info = findAttackInfo(action->getParameter(0)->getString(), true);
		if (!info)
		{
			BFMERetailAsciiString message("***Error allocating attack priority set - fix or raise limit. ***");
			AppendDebugMessage(*(const AsciiString *)&message, false);
			return;
		}
		info->setPriority(thingTemplate, action->getParameter(2)->getInt());
		return;
	}

	else
	{
		for (Int typeIndex = 0; typeIndex < types->getListSize(); typeIndex++)
		{
			AsciiString thisTypeName = types->getNthInList(typeIndex);
			const ThingTemplate *thisType = TheThingFactory->findTemplate(thisTypeName);
			if (!thisType)
			{
				{
					BFMERetailAsciiString message("***Attempting to set attack priority on an invalid thing:***");
					AppendDebugMessage(*(const AsciiString *)&message, false);
				}
				AppendDebugMessage(action->getParameter(0)->getString(), false);
				return;
			}

			AttackPriorityInfo *info = findAttackInfo(action->getParameter(0)->getString(), true);
			if (!info)
			{
				BFMERetailAsciiString message("***Error allocating attack priority set - fix or raise limit. ***");
				AppendDebugMessage(*(const AsciiString *)&message, false);
				return;
			}
			info->setPriority(thisType, action->getParameter(2)->getInt());
		}
		return;
	}
}
