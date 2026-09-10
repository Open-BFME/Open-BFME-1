// ?doDisplayCounter@ScriptActions@@IAEXABVAsciiString@@0@Z
// partial score=0.55 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// DISPLAY_COUNTER at retail RVA 0x002F9660.  The executeAction case for
// DISPLAY_COUNTER names this handler; the retail path canonicalizes the
// counter key, appends '/', fetches its Unicode text, and installs a timer.

typedef bool Bool;

template <typename T>
struct StringHeader
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	void concat(const T *text, int length);

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase &other);
	~StringBase();

	StringHeader<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	const char *str() const
	{
		return m_data ? m_data->m_text : "";
	}

	int getLength() const
	{
		return m_data ? m_data->m_length : 0;
	}

	void concat(const char *text, int length)
	{
		((StringBase<char> *)this)->concat(text, length);
	}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other)
		: StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};

// This is the BFME flag/counter key lookup view already used by the matched
// ScriptEngine join helper; the address is the proven 0x36336 ILT.
class BFMEScriptEngineFlagLookup
{
	friend class ScriptActions;

	private:
	AsciiString canonicalFlagName(const AsciiString &name);
};

class ScriptEngine : public BFMEScriptEngineFlagLookup
{
};

class GameTextInterface
{
public:
	virtual void _slot00() = 0;
	virtual void _slot01() = 0;
	virtual void _slot02() = 0;
	virtual void _slot03() = 0;
	virtual void _slot04() = 0;
	virtual void _slot05() = 0;
	virtual void _slot06() = 0;
	virtual void _slot07() = 0;
	virtual void _slot08() = 0;
	virtual UnicodeString fetch(AsciiString key, Bool *unused = 0) = 0;
};

class InGameUI
{
public:
	void addNamedTimer(const AsciiString &name, const UnicodeString &text,
		Bool isCountdown);
};

extern void j_000165db();

class BfmeAddNamedTimerCall
{
public:
	void addNamedTimer(const AsciiString &name, const UnicodeString &text,
		Bool isCountdown);
};

static void bfmeAddNamedTimer(InGameUI *object, const AsciiString &name,
	const UnicodeString &text, Bool isCountdown)
{
	typedef void (BfmeAddNamedTimerCall::*AddNamedTimerCall)(
		const AsciiString &, const UnicodeString &, Bool);
	union
	{
		void *raw;
		AddNamedTimerCall member;
	} function;
	function.raw = (void *)j_000165db;
	(((BfmeAddNamedTimerCall *)object)->*function.member)(
		name, text, isCountdown);
}

extern ScriptEngine *TheScriptEngine;
extern GameTextInterface *TheGameText;
extern InGameUI *TheInGameUI;

class ScriptActions
{
protected:
	void doDisplayCounter(const AsciiString &counterName,
		const AsciiString &counterText);
};

// ?doDisplayCounter@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doDisplayCounter(const AsciiString &counterName,
	const AsciiString &counterText)
{
	AsciiString canonical =
		((BFMEScriptEngineFlagLookup *)TheScriptEngine)->canonicalFlagName(
			counterName);
	__declspec(align(4)) char slash = '/';
	canonical.concat(&slash, 1);
	canonical.concat(counterName.str(), counterName.getLength());
	UnicodeString translated = TheGameText->fetch(counterText);
	bfmeAddNamedTimer(TheInGameUI, canonical,
		translated, false);
}
