// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// LANPreferences::getPreferredMap at retail RVA 0x00086A20, 377B (ZH LanLobbyMenu.cpp;
// byte-twin of the Skirmish body). Three levers made it exact (docs/shape_levers.md):
// find() carries throw() so the "Map" temporary needs no EH state around the
// lookup; the by-value strings use the StringInline shape (inline forwarders to
// StringBase<char>) so the QuotedPrintable temporary is built in place; and the
// tail is the ZH one -- isEmpty tests the 16-bit length at +4 of the data block,
// then isValidMap(ret, TRUE) decides the getDefaultMap(TRUE) fallback (TRUE lives
// in ebx for both calls, hence push ebx).
// Same shape as the ZH source (reference/.../LanLobbyMenu.cpp:160), but the
// retail callee list has no isValidMap call, so BFME dropped that guard:
// only the "not found" and "empty after decode" branches fall back to
// getDefaultMap(TRUE). Model follows the minimal-shim style proven for
// Code/GameEngine/Source/Common/Gen_0009E3D0_LANPreferences_getPreferredColor.cpp.

template <typename T> struct StringInlineData
{
	unsigned short m_refCount;
	unsigned short m_reserved;
	unsigned short m_length;	// +4: the word retail tests in isEmpty
	unsigned short m_pad;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();
	StringInlineData<T> *m_data;
};

// reference/shims/stringinline/StringInline.h shape: by-value temporaries are
// built in place only when the copy ctor and dtor are INLINE forwarders to the
// StringBase<char> that owns the out-of-line bodies.
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	AsciiString &operator=( const AsciiString &other );

	bool isEmpty() const
	{
		return m_data == 0 || m_data->m_length == 0;
	}

	void trim();

	const char *str() const
	{
		return m_data ? m_data->m_text : "";
	}
};

AsciiString QuotedPrintableToAsciiString(AsciiString original);
AsciiString getDefaultMap(bool useIfNotFound);
bool isValidMap(AsciiString map, bool flag);   // by value + a zero flag, returns al

struct PreferenceNode
{
	char m_pad[0x14];
	AsciiString m_value;
};

class PreferenceMap
{
public:
	PreferenceNode *find(const AsciiString &) const throw();
	PreferenceNode *end() const
	{
		return m_end;
	}

private:
	PreferenceNode *m_end;
};

class UserPreferences : public PreferenceMap
{
public:
	virtual ~UserPreferences();
};

class LANPreferences : public UserPreferences
{
public:
	AsciiString getPreferredMap(void);
};

// ?getPreferredMap@LANPreferences@@QAE?AVAsciiString@@XZ
AsciiString LANPreferences::getPreferredMap(void)
{
	AsciiString ret;
	PreferenceNode *it = find("Map");
	if (it == end())
	{
		ret = getDefaultMap(true);
		return ret;
	}

	ret = QuotedPrintableToAsciiString(it->m_value);
	ret.trim();
	if (!ret.isEmpty() && isValidMap(ret, true))
		return ret;

	ret = getDefaultMap(true);
	return ret;
}
