// ?Rva00345910@ScriptEngine@@IAEXPAVScriptAction@@_N@Z
// partial score=0.38 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: retail 0x00345910 (249 B), ScriptEngine member (pin
// ?Rva00345910@ScriptEngine@@IAEXPAVScriptAction@@_N@Z). Evaluates the
// action's first parameter's string through ScriptEngine::bfmeCounter
// (0x00019ADD) to get a counter target; if it exists, resolves a second
// name (parameter[2] when flag is set, else parameter[1]) through one of
// two still-unidentified ScriptEngine virtuals (slot 0x44 / slot 0x6c)
// and stores the resulting cached-value/FBA read into the counter's own
// first field, falling back to 0.0f converted through __ftol2 when the
// lookup misses.
//
// Parameter's BFME layout (selector string at +0x10) matches the sibling
// conversion in ScriptEngineGetPlayerMaskFromParameter.cpp.

typedef bool Bool;

template <typename Char>
class StringBase
{
	friend class AsciiString;

public:
	int compare(const Char *) const;

private:
	StringBase(const StringBase<Char> &src);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString();

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }

	unsigned char m_pad00[0xc];
	int m_rawValue;
	AsciiString m_string;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class ScriptAction
{
public:
	unsigned char m_pad00[8];
	int m_numParams;
	Parameter *m_param0;
	Parameter *m_param1;
	Parameter *m_param2;
};

struct ScriptCounter
{
	int m_value;
};

class Rva000F72D0FrameCachedValue
{
public:
	float valueThunk(float range);
};

struct BfmeThingFBA
{
	float bfmeGoFBAThunk(void *a);
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
	virtual Rva000F72D0FrameCachedValue *unidentified44(AsciiString name);
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

	ScriptCounter *bfmeCounter(AsciiString name);

protected:
	void Rva00345910(ScriptAction *action, Bool flag);
};

extern ScriptEngine *TheScriptEngine;

void ScriptEngine::Rva00345910(ScriptAction *action, Bool flag)
{
	Parameter *param0 = (action->m_numParams > 0) ? action->m_param0 : 0;

	ScriptCounter *counter = bfmeCounter(param0->getString());
	if (counter == 0)
		return;

	float fallback = 0.0f;
	int result;

	if (flag)
	{
		Parameter *param2 = (action->m_numParams > 2) ? action->m_param2 : 0;
		int paramValue = param2->m_rawValue;

		Parameter *param1 = (action->m_numParams > 1) ? action->m_param1 : 0;
		Rva000F72D0FrameCachedValue *cached = TheScriptEngine->unidentified44(param1->getString());
		if (cached == 0)
		{
			result = (int)fallback;
		}
		else
		{
			float value = cached->valueThunk(*(float *)&paramValue);
			result = (int)value;
		}
	}
	else
	{
		Parameter *param1 = (action->m_numParams > 1) ? action->m_param1 : 0;
		BfmeThingFBA *thing = TheScriptEngine->unidentified6c(param1->getString());
		if (thing == 0)
		{
			result = (int)fallback;
		}
		else
		{
			Parameter *param2 = (action->m_numParams > 2) ? action->m_param2 : 0;
			int paramValue = param2->m_rawValue;
			float value = thing->bfmeGoFBAThunk((void *)paramValue);
			result = (int)value;
		}
	}

	counter->m_value = result;
}

// @?Rva00345910@ScriptEngine@@IAEXPAVScriptAction@@_N@Z 0x00345910
