// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Clean C++ recovery of HIDE_COUNTER.
// Retail RVA 0x002F9790 (178 bytes).  script_engine.cpp sets
// m_actionTemplates[241].m_internalName to "HIDE_COUNTER", and executeAction's
// jump table at VA 0x0070D6A0 sends arm 241 to this body.  BFME prefixes the
// counter name with the slash-separated script scope before it drops the timer.

typedef int Int;

struct BfmeAsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_numChars;
	unsigned short m_unreconstructed06;
	char m_text[1];
};

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

	void concat(const char *text, Int length);
	void concat(char c) { concat(&c, 1); }

	const char *str(void) const { return m_data ? m_data->m_text : ""; }
	Int getLength(void) const { return m_data ? m_data->m_numChars : 0; }

private:
	BfmeAsciiStringData *m_data;
};

// The scope helper lives on the script engine singleton; its body at retail
// 0x003398F0 forwards to bfmeSlashOrDefaultName and returns the name by value.
class BfmeScriptEngineSlashName
{
public:
	AsciiString bfmeName(AsciiString &name);
};

class ScriptEngine
{
};

class InGameUI
{
public:
	void removeNamedTimer(const AsciiString &name);
};

extern ScriptEngine *TheScriptEngine;
extern InGameUI *TheInGameUI;

class ScriptActions
{
protected:
	void doHideCounter(AsciiString counterName);
};

// ?doHideCounter@ScriptActions@@IAEXVAsciiString@@@Z
void ScriptActions::doHideCounter(AsciiString counterName)
{
	AsciiString name =
		((BfmeScriptEngineSlashName *)TheScriptEngine)->bfmeName(counterName);
	name.concat('/');
	name.concat(counterName.str(), counterName.getLength());
	TheInGameUI->removeNamedTimer(name);
}
