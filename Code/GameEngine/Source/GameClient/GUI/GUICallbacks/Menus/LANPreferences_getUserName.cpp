// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /ICode/Libraries/Source/WWVegas/WWLib
// stlport

// LANPreferences::getUserName at retail RVA 0x00086540 (422 bytes).
// The retail caller and the adjacent LANPreferences methods place this body
// on the UserPreferences map at this + 4. The reference LanLobbyMenu.cpp
// supplies the matching UserName, IPEnumeration, and quoted-printable flow.

#include "string_base.h"
#include <map>

class AsciiString
{
public:
	AsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

private:
	char *m_text;
};

class UnicodeString
{
public:
	UnicodeString() { m_data = 0; }
	UnicodeString(const UnicodeString &other)
	{
		((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
			*(const StringBase<wchar_t> *)&other);
	}
	~UnicodeString();

	UnicodeString &operator=(const UnicodeString &other)
	{
		((StringBase<wchar_t> *)this)->set(*(const StringBase<wchar_t> *)&other);
		return *this;
	}

	void translate(const AsciiString &other);
	void trim() { ((StringBase<wchar_t> *)this)->trim(); }
	bool isEmpty() const
	{
		return m_data == 0 || *(const unsigned short *)((const char *)m_data + 4) == 0;
	}

private:
	void *m_data;
};

template <typename T>
bool operator<(const StringBase<T> &left, const StringBase<T> &right);

inline bool operator<(const AsciiString &left, const AsciiString &right)
{
	return *(const StringBase<char> *)&left < *(const StringBase<char> *)&right;
}

typedef std::map<AsciiString, AsciiString> PreferenceMap;

class BfmePreferenceMap : public PreferenceMap
{
public:
	const_iterator find(const AsciiString &key) const throw()
	{
		return PreferenceMap::find(key);
	}
};

class UserPreferences : public BfmePreferenceMap
{
public:
	virtual ~UserPreferences();
};

class LANPreferences : public UserPreferences
{
public:
	UnicodeString getUserName(void);
};

class IPEnumeration
{
public:
	IPEnumeration();
	~IPEnumeration();
	AsciiString getMachineName();

private:
	void *m_IPlist;
	bool m_isWinsockInitialized;
};

UnicodeString QuotedPrintableToUnicodeString(AsciiString original);

UnicodeString LANPreferences::getUserName(void)
{
	UnicodeString ret;
	LANPreferences::const_iterator it = find("UserName");
	if (it == end())
	{
		IPEnumeration IPs;
		ret.translate(IPs.getMachineName());
		return ret;
	}

	ret = QuotedPrintableToUnicodeString(it->second);
	ret.trim();
	if (ret.isEmpty())
	{
		IPEnumeration IPs;
		ret.translate(IPs.getMachineName());
		return ret;
	}

	return ret;
}
