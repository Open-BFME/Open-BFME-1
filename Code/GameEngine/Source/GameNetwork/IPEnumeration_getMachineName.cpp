// cl: /DNDEBUG /MD /EHsc
// readable body of ?getMachineName@IPEnumeration@@: Code/GameEngine/Source/GameNetwork/IPEnumeration.cpp
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &that);
	AsciiString(const char *text);

	static AsciiString TheEmptyString;

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/IPEnumeration.h
class IPEnumeration
{
public:
	AsciiString getMachineName(void);

private:
	void *m_IPlist;
	bool m_isWinsockInitialized;
};

AsciiString IPEnumeration::getMachineName(void)
{
	volatile int error = 0;

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
