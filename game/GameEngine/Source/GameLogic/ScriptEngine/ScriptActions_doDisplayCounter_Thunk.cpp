// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME5: clean C++ recovery of DISPLAY_COUNTER.

typedef int Int;
typedef bool Bool;

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
	void doDisplayCounter(AsciiString counterName,
		const AsciiString &counterText);
};

// ?doDisplayCounter@ScriptActions@@IAEXVAsciiString@@ABV2@@Z
void ScriptActions::doDisplayCounter(AsciiString counterName,
	const AsciiString &counterText)
{
	AsciiString name =
		((BfmeScriptEngineSlashName *)TheScriptEngine)->bfmeName(counterName);
	name.concat('/');
	name.concat(counterName.str(), counterName.getLength());
	TheInGameUI->addNamedTimer(name, TheGameText->fetch(counterText, 0), false);
}
