// ?d_002f9790@@YAXXZ
// partial score=0.95 date=2026-09-10
// Retail 0x002F9790. The adjacent display-counter body and the named caller

template <typename T>
struct StringHeader
{
	int ref_count;
	unsigned short length;
	unsigned short capacity;
	T data[1];
};

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	void concat(const T *str, int len);

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
		return m_data ? m_data->data : (const char *)0x0107388B;
	}
	int getLength() const { return m_data ? m_data->length : 0; }
	void concat(const char *str, int len)
	{
		((StringBase<char> *)this)->concat(str, len);
	}
};

class BFMEScriptEngineFlagLookup
{
	public:
	AsciiString canonicalFlagName(const AsciiString &name);
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
	void doHideCounter(const AsciiString &counterName);
};

// ?doHideCounter@ScriptActions@@IAEXABVAsciiString@@@Z
void ScriptActions::doHideCounter(const AsciiString &counterName)
{
	AsciiString canonical;
	canonical =
		((BFMEScriptEngineFlagLookup *)TheScriptEngine)->canonicalFlagName(counterName);
	__declspec(align(4)) char slash = '/';
	canonical.concat(&slash, 1);
	canonical.concat(canonical.str(), canonical.getLength());
	TheInGameUI->removeNamedTimer(canonical);
}
