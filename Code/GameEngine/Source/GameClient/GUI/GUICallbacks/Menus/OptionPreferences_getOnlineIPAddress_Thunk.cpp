// cl: /DNDEBUG /MD /EHsc
// stlport
// Clean implementation of OptionPreferences::getOnlineIPAddress.

#include <map>

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *, const void *, unsigned int);

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &source);
};

struct AsciiStringData
{
	unsigned char m_header[4];
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

class AsciiString
{
public:
	AsciiString();
	AsciiString(const char *text);
	AsciiString(const AsciiString &source)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&source);
	}
	~AsciiString();

	int compareNoCase(const AsciiString &source) const
	{
		int sourceLength = source.m_data
			? ((const AsciiStringData *)source.m_data)->m_length : 0;
		const char *sourceText = source.m_data
			? ((const AsciiStringData *)source.m_data)->m_text : "";

		int thisLength = m_data
			? ((const AsciiStringData *)m_data)->m_length : 0;
		const char *thisText = m_data
			? ((const AsciiStringData *)m_data)->m_text : "";

		int length = thisLength;
		if (length >= sourceLength)
			length = sourceLength;

		int result = _memicmp(thisText, sourceText, length);
		if (result == 0)
			result = thisLength - sourceLength;
		return result;
	}

private:
	void *m_data;
};

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const;
};
}

typedef _STL::map<AsciiString, AsciiString, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, AsciiString> > > PreferenceMap;

template AsciiString &PreferenceMap::operator[](const AsciiString &);

class UserPreferences : public PreferenceMap
{
public:
	virtual ~UserPreferences();
	virtual bool load(AsciiString filename);
	virtual bool write(void);
};

class OptionPreferences : public UserPreferences
{
public:
	unsigned getOnlineIPAddress(void);
};

class EnumeratedIP
{
public:
	AsciiString getIPstring(void);
	unsigned getIP(void) const { return m_IP; }
	EnumeratedIP *getNext(void) const { return m_next; }

private:
	AsciiString m_IPstring;
	unsigned m_IP;
	EnumeratedIP *m_next;
};

class IPEnumeration
{
public:
	IPEnumeration();
	~IPEnumeration();
	EnumeratedIP *getAddresses(void);

private:
	EnumeratedIP *m_IPlist;
	bool m_isWinsockInitialized;
};

class GlobalData
{
public:
	unsigned char m_unreconstructed_00[0xB10];
	unsigned m_defaultIP;
};

extern GlobalData *TheWritableGlobalData;

unsigned OptionPreferences::getOnlineIPAddress(void)
{
	AsciiString selectedIP = (*this)["GameSpyIPAddress"];
	IPEnumeration IPs;
	EnumeratedIP *IPlist = IPs.getAddresses();
	while (IPlist)
	{
		if (selectedIP.compareNoCase(IPlist->getIPstring()) == 0)
		{
			return IPlist->getIP();
		}
		IPlist = IPlist->getNext();
	}
	return TheWritableGlobalData->m_defaultIP;
}
