// ?getAddresses@IPEnumeration@@QAEPAVEnumeratedIP@@XZ
// partial score=0.75 date=2026-08-31
// cl: /DNDEBUG /MD /EHsc
// Released Zero Hour logic with BFME's three-word EnumeratedIP layout.

typedef unsigned short WORD;
typedef unsigned int UnsignedInt;

struct WSADATA
{
	WORD wVersion;
	unsigned char remainder[0x18e];
};

struct hostent
{
	char *h_name;
	char **h_aliases;
	short h_addrtype;
	short h_length;
	char **h_addr_list;
};

extern "C" __declspec(dllimport) int __stdcall WSAStartup(WORD version, WSADATA *data);
extern "C" __declspec(dllimport) int __stdcall WSACleanup(void);
extern "C" __declspec(dllimport) int __stdcall gethostname(char *name, int length);
extern "C" __declspec(dllimport) hostent *__stdcall gethostbyname(const char *name);
extern "C" __declspec(dllimport) UnsignedInt __stdcall ntohl(UnsignedInt value);

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString(const AsciiString &that);
	~AsciiString();
	void format(const char *format, ...);

private:
	void *m_data;
};

class EnumeratedIP
{
public:
	EnumeratedIP();
	void setIPstring(AsciiString name);
	UnsignedInt getIP(void) const { return m_IP; }
	void setIP(UnsignedInt address) { m_IP = address; }
	EnumeratedIP *getNext(void) const { return m_next; }
	void setNext(EnumeratedIP *next) { m_next = next; }

private:
	AsciiString m_IPstring;
	UnsignedInt m_IP;
	EnumeratedIP *m_next;
};

class IPEnumeration
{
public:
	EnumeratedIP *getAddresses(void);

private:
	EnumeratedIP *m_IPlist;
	bool m_isWinsockInitialized;
};

EnumeratedIP *IPEnumeration::getAddresses(void)
{
	if (m_IPlist != 0)
		return m_IPlist;

	if (!m_isWinsockInitialized)
	{
		WSADATA data;
		if (WSAStartup(0x0202, &data) != 0)
			return 0;

		if ((unsigned char)data.wVersion != 2 ||
			(unsigned char)(data.wVersion >> 8) != 2)
		{
			WSACleanup();
			return 0;
		}
		m_isWinsockInitialized = true;
	}

	char hostname[256];
	if (gethostname(hostname, sizeof(hostname)) != 0)
		return 0;

	hostent *host = gethostbyname(hostname);
	if (host == 0)
		return 0;
	if (host->h_length != 4)
		return 0;

	int index = 0;
	char *entry;
	while ((entry = host->h_addr_list[index++]) != 0)
	{
		EnumeratedIP *newIP = new EnumeratedIP;
		AsciiString text;
		text.format("%d.%d.%d.%d", (unsigned char)entry[0],
			(unsigned char)entry[1], (unsigned char)entry[2],
			(unsigned char)entry[3]);

		UnsignedInt testIP = *reinterpret_cast<UnsignedInt *>(entry);
		UnsignedInt address = ntohl(testIP);
		newIP->setIPstring(text);
		newIP->setIP(address);

		if (m_IPlist == 0)
		{
			m_IPlist = newIP;
			newIP->setNext(0);
		}
		else if (newIP->getIP() < m_IPlist->getIP())
		{
			newIP->setNext(m_IPlist);
			m_IPlist = newIP;
		}
		else
		{
			EnumeratedIP *position = m_IPlist;
			while (position->getNext() != 0 &&
				position->getNext()->getIP() < newIP->getIP())
			{
				position = position->getNext();
			}
			newIP->setNext(position->getNext());
			position->setNext(newIP);
		}
	}

	return m_IPlist;
}
