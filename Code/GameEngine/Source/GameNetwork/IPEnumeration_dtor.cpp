// cl: /DNDEBUG /MD /EHsc
// BFME's IPEnumeration teardown follows the released Zero Hour loop, with the
// retail EnumeratedIP layout placing its next pointer at +0x08.

extern "C" __declspec(dllimport) int __stdcall WSACleanup(void);

void __cdecl operator delete(void *);

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class EnumeratedIP
{
public:
	EnumeratedIP *getNext() const { return m_next; }

private:
	AsciiString m_text;
	unsigned int m_address;
	EnumeratedIP *m_next;
};

class IPEnumeration
{
public:
	~IPEnumeration();

private:
	EnumeratedIP *m_IPlist;
	bool m_isWinsockInitialized;
};

IPEnumeration::~IPEnumeration()
{
	if (m_isWinsockInitialized)
	{
		WSACleanup();
		m_isWinsockInitialized = false;
	}

	EnumeratedIP *ip = m_IPlist;
	while (ip != 0)
	{
		ip = ip->getNext();
		delete m_IPlist;
		m_IPlist = ip;
	}
}
