// ?Rva006AD9B0GetAllowAudioReinitialize@@YA_NXZ
// partial score=0.966 date=2026-09-21
//
// Free-standing helper: builds a fresh OptionPreferences (which loads
// Options.ini in its own constructor), looks up the AllowAudioReinitialize
// key, and returns false only when the stored value case-insensitively
// equals "false" or "no"; a missing key, or any other value, returns true.
// No `this` pointer is read anywhere in the retail body -- it is not an
// OptionPreferences member, it constructs and destroys its own local
// OptionPreferences before returning.
//
// callers (still unnamed dumps, no name evidence): ?d_006b86d0@@YAXXZ
// @ carved.csv; ?d_006b9c90@@YAXXZ @ d_006b9500.asm
//
// callees, in body order:
//   OptionPreferences::OptionPreferences(void) via ILT 0x0003713C -> 0x000904E0 (matched)
//   AsciiString(const char *) 0x00888BC0 (retail calls the StringBase base ctor
//     directly, alias ??0BFMERetailAsciiString@@QAE@PBD@Z; SEE CAVEAT below)
//   PreferenceMap::find via ILT 0x0000AEAC -> 0x00080600 (STLport _M_find<AsciiString>, matched)
//   AsciiString::releaseBuffer()/~AsciiString() 0x00887940 (matched, key destructor)
//   AsciiString(const AsciiString &) 0x00887B60 (retail calls the StringBase base
//     copy ctor directly, alias ??0GameSpyGroupRoom@@QAE@ABV0@@Z; SEE CAVEAT below)
//   AsciiString::compareNoCase(const char *) via ILT 0x000405E8 -> 0x00075E00,
//     pinned as ?compareNoCase@AsciiString@@QBEHPBD@Z; returns 0 on a
//     case-insensitive match, and retail's two `test eax,eax; je fail`
//     sequences fire on that zero, so retail returns false exactly when the
//     stored value equals "false" or "no" and true for anything else
//     (including a missing key)
//   AsciiString::releaseBuffer()/~AsciiString() 0x00887940 (matched, value destructor)
//   OptionPreferences::~OptionPreferences() via ILT 0x00001307 -> 0x00090450 (matched)
//
// string literals verified against the retail image: key = 0x0111C2A8
// "AllowAudioReinitialize", compares = 0x0111C2A0 "false", 0x010EBA88 "no"
//
// PROBE STATE: 234/234 bytes, 8 non-reloc byte(s) differ (score ~0.966).
// Every remaining diff is the SAME 4-byte esp offset shift (our locals start
// at esp+8, retail's at esp+0xc). The current declarations model the polymorphic
// OptionPreferences object with PreferenceMap at this+4 and keep the
// iterator as a one-pointer object. That model preserves the 234-byte body and fixes the
// downstream `lea [esi+0x14]; push` shape, but it does not move the four-byte
// local base offset. Declaring `it` before or after `prefs`, adding an unused
// int, taking `(void)&it`, and using a volatile `it` also did not move the
// offset. The volatile form drops ESI caching and makes the body much worse.
//
// The StringBase<char> model below is intentional. Its inline AsciiString
// constructors select the retail StringBase constructor and copy bodies at
// 0x00888BC0 and 0x00887B60, while releaseBuffer() selects 0x00887940. The
// compareNoCase member keeps the pinned AsciiString ILT at 0x000405E8.

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
	unsigned char m_unreconstructed_10[8];
};

class PreferenceIterator
{
public:
	PreferenceIterator(void) : m_node(0) {}

	PreferenceIterator &operator=(PreferenceNode *node)
	{
		m_node = node;
		return *this;
	}

	bool operator!=(PreferenceNode *node) const
	{
		return m_node != node;
	}

	PreferenceNode *operator->(void) const
	{
		return m_node;
	}

private:
	PreferenceNode *m_node;
};

bool Rva006AD9B0GetAllowAudioReinitialize(void)
{
	OptionPreferences prefs;
	PreferenceIterator it;

	{
		AsciiString key("AllowAudioReinitialize");
		it = prefs.m_prefs.find(key);
	}

	if (it != prefs.m_prefs.end())
	{
		AsciiString value(it->m_value);
		if (value.compareNoCase("false") == 0 || value.compareNoCase("no") == 0)
			return false;
	}

	return true;
}
