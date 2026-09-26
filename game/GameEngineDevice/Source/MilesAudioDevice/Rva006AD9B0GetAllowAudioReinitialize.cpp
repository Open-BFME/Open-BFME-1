// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Open-BFME: ?rva006AD9B0@MilesAudioManager@@QAE_NXZ, retail 0x006AD9B0, 234 bytes.
//
// __thiscall member that ignores `this`: both retail callers load ecx right
// before calling ILT 0x0002F1D5, and the matched MilesAudioManager::rva006B86D0
// models the call as a MilesAudioManager member. The body builds a fresh
// OptionPreferences (which loads Options.ini in its own constructor), looks up
// the AllowAudioReinitialize key, and returns false only when the stored value
// case-insensitively equals "false" or "no"; a missing key, or any other value,
// returns true. ecx is never read. The method name is not proven, so it keeps
// its address token.
//
// callers: ?rva006B86D0@MilesAudioManager@@UAEXI@Z (via ILT) and the
// ?d_006b9c90@@YAXXZ dump.
//
// callees, in body order:
//   OptionPreferences::OptionPreferences(void) via ILT 0x0003713C -> 0x000904E0
//   StringBase<char>(const char *) 0x00888BC0 (the key temporary)
//   PreferenceMap::find via ILT 0x0000AEAC -> 0x00080600 (STLport _M_find<AsciiString>)
//   StringBase<char>::releaseBuffer 0x00887940 (key temporary destructor)
//   StringBase<char>(const StringBase &) 0x00887B60 (value copy)
//   AsciiString::compareNoCase(const char *) via ILT 0x000405E8 -> 0x00075E00
//   StringBase<char>::releaseBuffer 0x00887940 (value destructor)
//   OptionPreferences::~OptionPreferences() via ILT 0x00001307 -> 0x00090450
//
// string literals verified against the retail image: key = 0x0111C2A8
// "AllowAudioReinitialize", compares = 0x0111C2A0 "false", 0x010EBA88 "no"
//
// Frame (retail, after push esi): value esp+4, key esp+8, prefs esp+0xc..0x20.
// OptionPreferences is 20 bytes (vptr, 12-byte map, one trailing dword), as
// upstream UserPreferences.h has it. The key is the by-value temporary the
// find() call builds from the literal, and the value is a function-scope local
// after an early return; together they give the two strings separate slots,
// which a named key in a nested block (sharing the value's slot) does not.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const T *text);
	StringBase(const StringBase &other);
	void releaseBuffer();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *s) : StringBase<char>(s) {}
	AsciiString(const AsciiString &that) : StringBase<char>(that) {}
	~AsciiString() { releaseBuffer(); }

	int compareNoCase(const char *s) const throw();
};

struct PreferenceNode
{
	unsigned char m_unreconstructed_00[0x14];
	AsciiString m_value;								///< retail this+0x14
};

class PreferenceMap
{
public:
	PreferenceNode *find(const AsciiString &) const throw();
	PreferenceNode *end(void) const { return m_end; }

	PreferenceNode *m_end;
	unsigned char m_unreconstructed_04[8];
};

class OptionPreferences
{
public:
	OptionPreferences(void);
	virtual ~OptionPreferences();

	PreferenceMap m_prefs;
	unsigned char m_unreconstructed_10[4];
};

class PreferenceIterator
{
public:
	PreferenceIterator(PreferenceNode *node) : m_node(node) {}

	bool operator==(PreferenceNode *node) const
	{
		return m_node == node;
	}

	PreferenceNode *operator->(void) const
	{
		return m_node;
	}

private:
	PreferenceNode *m_node;
};

class MilesAudioManager
{
public:
	bool rva006AD9B0(void);
};

bool MilesAudioManager::rva006AD9B0(void)
{
	OptionPreferences prefs;
	PreferenceIterator it = prefs.m_prefs.find("AllowAudioReinitialize");
	if (it == prefs.m_prefs.end())
		return true;

	AsciiString value(it->m_value);
	if (value.compareNoCase("false") == 0 || value.compareNoCase("no") == 0)
		return false;

	return true;
}
