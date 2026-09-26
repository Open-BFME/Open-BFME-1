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

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	void concat(const T *text, Int length);

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

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

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
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
