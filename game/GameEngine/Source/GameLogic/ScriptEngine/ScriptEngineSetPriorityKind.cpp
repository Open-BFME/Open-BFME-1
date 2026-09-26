// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// The retail caller and the attack-priority helpers identify this body as
// ScriptEngine::setPriorityKind at retail RVA 0x00340DC0.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "ascii_string.h"

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
	Int getInt(void) const { return m_integer; }
	const AsciiString &getString(void) const { return m_string; }

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

class ThingTemplate
{
public:
	Bool isKindOf(UnsignedInt kind) const
	{
		return (m_kindof[kind >> 5] & (1u << (kind & 31))) != 0;
	}

	ThingTemplate *friend_getNextTemplate(void) const
	{
		return m_nextTemplate;
	}

private:
	char m_unknown[0xC8];
	UnsignedInt m_kindof[3];
	char m_unknownAfterKindof[0x2B8];
	ThingTemplate *m_nextTemplate;
};

class ThingFactory
{
public:
	ThingTemplate *firstTemplate(void) const
	{
		return m_firstTemplate;
	}

private:
	char m_unknown[8];
	ThingTemplate *m_firstTemplate;
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
	AttackPriorityInfo *findAttackInfo(const AsciiString &name, Bool addIfNotFound);
	void AppendDebugMessage(const AsciiString &message, Bool forcePause);
	void setPriorityKind(ScriptAction *action);
};

void ScriptEngine::setPriorityKind(ScriptAction *action)
{
	AttackPriorityInfo *info = findAttackInfo(action->getParameter(0)->getString(), true);
	if (info == 0)
	{
		BFMERetailAsciiString message("***Error allocating attack priority set - fix or raise limit. ***");
		AppendDebugMessage(*(const AsciiString *)&message, false);
		return;
	}

	UnsignedInt kind = (UnsignedInt)action->getParameter(1)->getInt();
	Int priority = action->getParameter(2)->getInt();
	ThingTemplate *thingTemplate;
	for (thingTemplate = TheThingFactory->firstTemplate();
		 thingTemplate;
		 thingTemplate = thingTemplate->friend_getNextTemplate())
	{
		if (thingTemplate->isKindOf(kind))
			info->setPriority(thingTemplate, priority);
	}
}
