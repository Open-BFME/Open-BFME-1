// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// RVA 0x00345910; established ScriptEngine helper called by executeActions.
// Retail reads Parameter's real value (+0x0c) before the mode branch. The
// 0x44 virtual receives a by-value name and false; 0x6c receives only the name.
// Keep the FBA helper's established void* ABI: pass the real's raw stack bits.
// Parameter offsets also occur in the matched ScriptEngineRva00345a50.cpp.

typedef bool Bool;

#include "ascii_string.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	unsigned char m_pad00[0xc];
	float m_real;
	AsciiString m_string;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class ScriptAction
{
public:
	unsigned char m_pad00[8];
	int m_numParms;
	Parameter *m_parms[12];
	Parameter *getParameter(int index) { if (index >= 0 && index < m_numParms) return m_parms[index]; return 0; }
};

struct ScriptCounter
{
	int m_value;
};

class Rva000F72D0FrameCachedValue
{
public:
	float value(float range);
};

struct BfmeThingFBA
{
	float bfmeGoFBA(void *a);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual Rva000F72D0FrameCachedValue *unidentified44(AsciiString name, Bool flag);
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual BfmeThingFBA *unidentified6c(AsciiString name);

protected:
	ScriptCounter *bfmeCounter(AsciiString name);
	void Rva00345910(ScriptAction *action, Bool flag);
};

extern ScriptEngine *TheScriptEngine;

void ScriptEngine::Rva00345910(ScriptAction *action, Bool flag)
{
	ScriptCounter *counter = bfmeCounter(action->getParameter(0)->m_string);
	if (counter == 0)
		return;

	float result = 0.0f;
	float paramValue = action->getParameter(2)->m_real;
	if (flag)
	{
		Rva000F72D0FrameCachedValue *cached = TheScriptEngine->unidentified44(action->getParameter(1)->m_string, false);
		if (cached)
			result = cached->value(paramValue);
	}
	else
	{
		BfmeThingFBA *thing = TheScriptEngine->unidentified6c(action->getParameter(1)->m_string);
		if (thing)
			result = thing->bfmeGoFBA(*(void **)&paramValue);
	}
	counter->m_value = (int)result;
}
