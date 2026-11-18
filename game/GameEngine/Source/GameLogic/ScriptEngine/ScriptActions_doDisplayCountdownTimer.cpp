// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Clean C++ recovery of DISPLAY_COUNTDOWN_TIMER.
// Retail RVA 0x002F9870 (235 bytes).  script_engine.cpp sets
// m_actionTemplates[163].m_internalName to "DISPLAY_COUNTDOWN_TIMER", and
// executeAction's jump table at VA 0x0070D6A0 sends arm 163 to this body.  The
// first parameter arrives by value and this body releases it; the second stays a
// const reference, so MSVC parks the GameText result in its dead argument slot.

#include "../../../Include/Common/ScalarTypes.h"


struct BfmeAsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_numChars;
	unsigned short m_unreconstructed06;
	char m_text[1];
};

#include "../../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"
inline UnicodeString::UnicodeString(const UnicodeString &that) { ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&that); }
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }


class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void concat(const char *text, Int length)
	{
		StringBase<char>::concat(text, length);
	}
	void concat(char c) { concat(&c, 1); }

	const char *str(void) const
	{
		const BfmeAsciiStringData *data = (const BfmeAsciiStringData *)m_data;
		return data ? data->m_text : "";
	}
	Int getLength(void) const
	{
		const BfmeAsciiStringData *data = (const BfmeAsciiStringData *)m_data;
		return data ? data->m_numChars : 0;
	}
};


class BfmeScriptEngineSlashName
{
public:
	AsciiString bfmeName(AsciiString &name);
};

class ScriptEngine
{
};

class GameTextInterface
{
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
	virtual UnicodeString fetch(AsciiString label, Bool *exists) = 0;
};

class InGameUI
{
public:
	void addNamedTimer(const AsciiString &name, const UnicodeString &text,
		Bool countdown);
};

extern ScriptEngine *TheScriptEngine;
extern GameTextInterface *TheGameText;
extern InGameUI *TheInGameUI;

class ScriptActions
{
protected:
	void doDisplayCountdownTimer(AsciiString timerName,
		const AsciiString &timerText);
};

// ?doDisplayCountdownTimer@ScriptActions@@IAEXVAsciiString@@ABV2@@Z
void ScriptActions::doDisplayCountdownTimer(AsciiString timerName,
	const AsciiString &timerText)
{
	AsciiString name =
		((BfmeScriptEngineSlashName *)TheScriptEngine)->bfmeName(timerName);
	name.concat('/');
	name.concat(timerName.str(), timerName.getLength());
	TheInGameUI->addNamedTimer(name, TheGameText->fetch(timerText, 0), true);
}
