// cl: /DNDEBUG /MD /EHs-c- /O2 /Ob2
// WWDownload FTP.CPP Cftp::RecvReply.

typedef long HRESULT;

extern "C" int __stdcall recv(int socket, char *buffer, int size, int flags);
extern "C" int __stdcall WSAGetLastError(void);
extern "C" __declspec(dllimport) long __cdecl atol(const char *text);
extern "C" __declspec(dllimport) int __cdecl isdigit(int value);
extern "C" __declspec(dllimport) int __cdecl _strnicmp(
	const char *left, const char *right, unsigned int count);
extern "C" __declspec(dllimport) unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)
extern "C" __declspec(dllimport) char *__cdecl strstr(
	const char *text, const char *find);
extern "C" __declspec(dllimport) void __stdcall Rva01358EA8(
	const char *text);

class Cftp
{
public:
	virtual ~Cftp();
	HRESULT RecvReply(const char *reply, int size, int *replyCode);

private:
	int m_iCommandSocket;
	int m_iDataSocket;
	char m_CommandSockAddr[16];
	char m_DataSockAddr[16];
	int m_iFilePos;
	int m_iBytesRead;
	int m_iFileSize;
	char m_szRemoteFilePath[128];
	char m_szRemoteFileName[128];
	char m_szLocalFilePath[128];
	char m_szLocalFileName[128];
	char m_szServerName[128];
	char m_szUserName[128];
	char m_szPassword[128];
	void *m_pfLocalFile;
	int m_iStatus;
	int m_sendNewPortStatus;
	int m_findStart;
};

HRESULT Cftp::RecvReply(const char *reply, int size, int *replyCode)
{
	char *pc = (char *)reply;
	const char *debugPrefix = (const char *)0x01132E98;
	int readval;

	while (1)
	{
		readval = recv(m_iCommandSocket, pc, size - 1, 2);
		pc[size - 1] = 0;
		if (readval > 0)
			pc[readval] = 0;

		if (readval < 0)
		{
			if (WSAGetLastError() == 0x2746 ||
				WSAGetLastError() == 0x2749)
				readval = 0;
			else
				return 0x80040002;
		}

		if (readval == 0)
		{
			*replyCode = 421;
			return 0;
		}

		if (readval < 3)
			return 0x80040002;

		char *end = strstr(pc, "\r\n");
		if (end == 0)
			return 0x80040002;

		recv(m_iCommandSocket, pc, end - pc + 2, 0);

		Rva01358EA8(debugPrefix);
		Rva01358EA8(pc);
		const char *bogusResponse = (const char *)0x01132E94;
		if (_strnicmp(pc, bogusResponse, strlen(bogusResponse)) == 0)
			continue;

		if (isdigit(pc[0]) == 0)
			continue;

		if (replyCode != 0)
			*replyCode = (int)atol(pc);

		return 0;
	}
}
