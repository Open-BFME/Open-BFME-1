// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// BFME's implementation follows the released Zero Hour routine, returning
// the shared empty string when WinSock setup or hostname discovery fails.

typedef unsigned short WORD;

struct WSADATA
{
	WORD wVersion;
	unsigned char remainder[0x18e];
};

extern "C" __declspec(dllimport) int __stdcall WSAStartup(WORD version, WSADATA *data);
extern "C" __declspec(dllimport) int __stdcall WSACleanup(void);
extern "C" __declspec(dllimport) int __stdcall gethostname(char *name, int length);

void __cdecl operator delete(void *);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char>: its own copy ctor is the
// forwarder at 0x0005EE50 and it holds nothing of its own, so a caller that
// copies a string encodes the base body at 0x00887B60 directly. The delegation
// has to be visible here for this TU to encode the same call.
#include "string_base.h"

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &that) : StringBase<char>(that) {}
	AsciiString(const char *text);
	~AsciiString();

	static AsciiString TheEmptyString;

};

// BFME enumeration nodes omit the pooled base word present in Zero Hour;
// their next pointer is at +0x08.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/IPEnumeration.h
class EnumeratedIP
{
public:
	EnumeratedIP *getNext() const { return m_next; }

private:
	AsciiString m_text;
	unsigned int m_address;
	EnumeratedIP *m_next;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/IPEnumeration.h
class IPEnumeration
{
public:
	~IPEnumeration();
	AsciiString getMachineName(void);

private:
	EnumeratedIP *m_IPlist;
	bool m_isWinsockInitialized;
};

AsciiString IPEnumeration::getMachineName(void)
{
	if (!m_isWinsockInitialized)
	{
		WORD version = 0x0202;
		WSADATA data;
		if (WSAStartup(version, &data) != 0)
			return AsciiString::TheEmptyString;

		if ((unsigned char)data.wVersion != 2 ||
			(unsigned char)(data.wVersion >> 8) != 2)
		{
			WSACleanup();
			return AsciiString::TheEmptyString;
		}

		m_isWinsockInitialized = true;
	}

	char hostname[256];
	if (gethostname(hostname, sizeof(hostname)) != 0)
		return AsciiString::TheEmptyString;

	return AsciiString(hostname);
}

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
