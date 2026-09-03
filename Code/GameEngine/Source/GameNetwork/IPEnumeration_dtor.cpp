// cl: /DNDEBUG /MD /EHsc
// readable body of ??1IPEnumeration@@: Code/GameEngine/Source/GameNetwork/IPEnumeration.cpp
// BFME's IPEnumeration teardown follows the released Zero Hour loop, with the
// retail EnumeratedIP layout placing its next pointer at +0x08.

extern "C" __declspec(dllimport) int __stdcall WSACleanup(void);

void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/IPEnumeration.h
class EnumeratedIP
{
public:
	EnumeratedIP *getNext() const { return m_next; }

private:
	AsciiString m_text;
	unsigned int m_address;
	EnumeratedIP *m_next;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/IPEnumeration.h
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
