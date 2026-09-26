// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob1
// BFME's script-engine listener watches the generic script names owned by the
// current TeamPrototype.  The TeamPrototype and string views are local to this
// TU so their BFME-only offsets do not alter the shared headers.

typedef bool Bool;
typedef int Int;

extern const char g_bfmeEmptyAscii[];

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
	void concat(const T *str, Int len);

	protected:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
	StringHeader<T> *m_data;

	private:
	StringBase(const StringBase<T> &other);
	void releaseBuffer();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	const char *str() const
	{
		return m_data ? m_data->data : g_bfmeEmptyAscii;
	}
	Int getLength() const { return m_data ? m_data->length : 0; }
	void concat(const char *str, Int len)
	{
		((StringBase<char> *)this)->concat(str, len);
	}
	Int compare(const AsciiString &other) const;
};

class UnicodeString : private StringBase<char>
{
public:
	UnicodeString() {}
	~UnicodeString() {}
};

class Script;
class BfmeEnableListener;

class TeamPrototype
{
public:
	Script *getGenericScript(Int scriptToRetrieve, UnicodeString *outName);

private:
	friend class BfmeEnableListener;
	char m_pad[0x1F0];
	AsciiString m_teamGenericScripts[32];
};

class BfmeEnableListener
{
public:
	// ?notify@BfmeEnableListener@@QAE_NABVAsciiString@@0_N@Z
	Bool notify(const AsciiString &name, const AsciiString &canonical,
		Bool enabled);

private:
	char m_pad04[4];
	TeamPrototype *m_teamPrototype;
	char m_pad08[0x3C];
	unsigned char m_enabled[32];
};

// ?notify@BfmeEnableListener@@QAE_NABVAsciiString@@0_N@Z
Bool BfmeEnableListener::notify(const AsciiString &name,
	const AsciiString &canonical, Bool enabled)
{
	if (m_teamPrototype == 0)
		return false;
	if (m_teamPrototype->getGenericScript(0, 0) == 0)
		return false;

	{
		Bool changed = false;
		AsciiString canonicalName(canonical);
		__declspec(align(4)) char slash = '/';
		canonicalName.concat(&slash, 1);
		canonicalName.concat(name.str(), name.getLength());

		for (Int i = 0; i < 32; ++i)
		{
			AsciiString *genericScript =
				&m_teamPrototype->m_teamGenericScripts[i];
			UnicodeString scriptName;
			Script *script = m_teamPrototype->getGenericScript(i, &scriptName);
			Bool matchesName = false;
			if (script != 0)
			{
				if (canonical.compare((const AsciiString &)scriptName) == 0)
				{
					if (genericScript->compare(name) == 0)
						matchesName = true;
					if (genericScript->compare(canonicalName) == 0 || matchesName)
					{
						m_enabled[i] = enabled;
						changed = true;
					}
				}
			}
		}
		return changed;
	}
}
