// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Clean C++ recovery of HIDE_COUNTDOWN_TIMER.
// Retail RVA 0x002F99A0 (178 bytes).  script_engine.cpp sets
// m_actionTemplates[164].m_internalName to "HIDE_COUNTDOWN_TIMER", and
// executeAction's jump table at VA 0x0070D6A0 sends arm 164 to this body.  The
// code repeats doHideCounter at 0x002F9790 instruction for instruction, which is
// how ZH spells the pair of removeNamedTimer actions.

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
	void doHideCountdownTimer(AsciiString timerName);
};

// ?doHideCountdownTimer@ScriptActions@@IAEXVAsciiString@@@Z
void ScriptActions::doHideCountdownTimer(AsciiString timerName)
{
	AsciiString name =
		((BfmeScriptEngineSlashName *)TheScriptEngine)->bfmeName(timerName);
	name.concat('/');
	name.concat(timerName.str(), timerName.getLength());
	TheInGameUI->removeNamedTimer(name);
}
