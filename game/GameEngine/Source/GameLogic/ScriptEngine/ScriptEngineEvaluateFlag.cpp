// cl: /DNDEBUG /MD /EHsc

extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);
#pragma intrinsic(memcmp)

template <class T> struct StringData
{
	int m_refs;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	int getInt() const { return m_integer; }
	const AsciiString &getString() const { return m_string; }

private:
	char m_unknown[8];
	int m_integer;
	float m_real;
	AsciiString m_string;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Condition
{
public:
	Parameter *getParameter(int index)
	{
		if (index >= 0 && index < m_numParms)
			return m_parameters[index];
		return 0;
	}

private:
	char m_unknown[8];
	int m_numParms;
	Parameter *m_parameters[12];
};

struct FlagInteractionNode
{
	FlagInteractionNode *m_next;
	FlagInteractionNode *m_previous;
	AsciiString m_name;
};

struct FlagInteractionList
{
	FlagInteractionNode *m_header;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
protected:
	bool *bfmeFlagForWrite(AsciiString name);
	bool evaluateFlag(Condition *condition);

private:
	char m_unknown[0x17270];
	FlagInteractionList m_uiInteractions;
};

bool ScriptEngine::evaluateFlag(Condition *condition)
{
	bool *flag = bfmeFlagForWrite(
		condition->getParameter(0)->getString());
	bool desired = condition->getParameter(1)->getInt() != 0;
	bool actual = *flag != 0;
	if (desired == actual)
		return true;

	FlagInteractionNode *header = m_uiInteractions.m_header;
	for (FlagInteractionNode *node = header->m_next;
		node != header; node = node->m_next)
	{
		if (node->m_name.compare(
			condition->getParameter(0)->getString()) == 0)
		{
			return true;
		}
	}
	return false;
}
