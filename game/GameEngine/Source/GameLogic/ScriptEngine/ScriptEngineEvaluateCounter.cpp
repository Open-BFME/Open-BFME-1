// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// ScriptEngine::evaluateCounter at RVA 0x003457F0.
// The 193-byte instruction body and six-entry jump table at 0x003458B4
// occupy 220 bytes, including a three-byte alignment instruction.
// The condition dispatcher and upstream counter comparison switch identify it;
// matched evaluateFlag/evaluateTimer witness the BFME named-counter lookup.
#include "ascii_string.h"
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

class Parameter
{
public:
	enum
	{
		LESS_THAN, LESS_EQUAL, EQUAL, GREATER_EQUAL, GREATER, NOT_EQUAL
	};
	int getInt() const { return m_int; }
	const AsciiString &getString() const { return m_string; }

private:
	char m_unknown[8];
	int m_int;
	float m_real;
	AsciiString m_string;
};

class Condition
{
public:
	Parameter *getParameter(int ndx)
	{
		if (ndx >= 0 && ndx < m_numParms)
			return m_parms[ndx];
		return 0;
	}

private:
	char m_unknown[8];
	int m_numParms;
	Parameter *m_parms[12];
};

struct ScriptCounter
{
	int m_value;
	bool m_isCountdownTimer;
	bool m_isMillisecondTimer;
};

class ScriptEngine
{
protected:
	ScriptCounter *bfmeCounter(AsciiString name);
	bool evaluateCounter(Condition *condition);
};

bool ScriptEngine::evaluateCounter(Condition *condition)
{
	ScriptCounter *counter = bfmeCounter(
		condition->getParameter(0)->getString());
	int value = condition->getParameter(2)->getInt();
	switch (condition->getParameter(1)->getInt())
	{
	case Parameter::LESS_THAN:
		return counter->m_value < value;
	case Parameter::LESS_EQUAL:
		return counter->m_value <= value;
	case Parameter::EQUAL:
		return counter->m_value == value;
	case Parameter::GREATER_EQUAL:
		return counter->m_value >= value;
	case Parameter::GREATER:
		return counter->m_value > value;
	case Parameter::NOT_EQUAL:
		return counter->m_value != value;
	}
	return false;
}
