// cl: /DNDEBUG /MD /EHs-c- /O2 /Ob2
// WWDownload FTP.CPP Cftp::LoginToServer.

typedef long HRESULT;

extern "C" __declspec(dllimport) int __cdecl sprintf(
    char *buffer, const char *format, ...);
extern "C" __declspec(dllimport) char *__cdecl strncpy(
    char *destination, const char *source, unsigned int count);
extern "C" __declspec(dllimport) unsigned int __cdecl strlen(
    const char *text);
#pragma intrinsic(strlen)
extern "C" void *__cdecl memset(void *buffer, int value, unsigned int size);
extern "C" int __stdcall send(int, const char *, int, int);
extern "C" int __stdcall recv(int socket, char *buffer, int size, int flags);
extern "C" int __stdcall WSAGetLastError(void);
extern "C" __declspec(dllimport) long __cdecl atol(const char *text);
extern "C" __declspec(dllimport) int __cdecl isdigit(int value);
extern "C" __declspec(dllimport) int __cdecl _strnicmp(
    const char *left, const char *right, unsigned int count);
extern "C" __declspec(dllimport) char *__cdecl strstr(
    const char *text, const char *find);
extern "C" __declspec(dllimport) void __stdcall Rva01358EA8(const void *text);

enum
{
    FTP_FAILED = 0x80040001,
    FTP_TRYING = 0x80040002,
    FTP_SUCCEEDED = 0,
    FTPSTAT_CONNECTED = 20,
    FTPSTAT_SENDINGUSER = 30,
    FTPSTAT_SENTUSER = 40,
    FTPSTAT_SENDINGPASS = 50,
    FTPSTAT_LOGGEDIN = 60,
    FTPREPLY_PASSWORD = 331,
    FTPREPLY_LOGGEDIN = 230,
    FTPREPLY_CONTROLCLOSED = 421
};

class Cftp
{
public:
    virtual ~Cftp();

    HRESULT SendCommand(const char *command, int size)
    {
        int sent = send(m_iCommandSocket, command, size, 0);
        if (sent > 0)
        {
            Rva01358EA8((void *)0x01132E90);
            Rva01358EA8((void *)command);
            return FTP_SUCCEEDED;
        }

        return FTP_FAILED;
    }

    HRESULT RecvReply(const char *reply, int size, int *replyCode);
    HRESULT LoginToServer(const char *userName, const char *password);

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

HRESULT Cftp::LoginToServer(const char *userName, const char *password)
{
    char command[256];
    int reply;

    strncpy(m_szUserName, userName, 128);
    strncpy(m_szPassword, password, 128);
    memset(command, 0, 256);

    if (m_iStatus == FTPSTAT_CONNECTED)
    {
        sprintf(command, "USER %s\r\n", m_szUserName);
        if (SendCommand(command, 7 + strlen(m_szUserName)) < 0)
            return FTP_TRYING;
        m_iStatus = FTPSTAT_SENDINGUSER;
    }

    if (m_iStatus == FTPSTAT_SENDINGUSER)
    {
        if (RecvReply(command, 256, &reply) != FTP_SUCCEEDED)
            return FTP_TRYING;
        if (reply != FTPREPLY_PASSWORD)
            return FTP_FAILED;

        m_iStatus = FTPSTAT_SENTUSER;
    }

    if (m_iStatus == FTPSTAT_SENTUSER)
    {
        sprintf(command, "PASS %s\r\n", m_szPassword);
        if (SendCommand(command, 7 + strlen(m_szPassword)) < 0)
            return FTP_TRYING;
        m_iStatus = FTPSTAT_SENDINGPASS;
    }

    if (m_iStatus == FTPSTAT_SENDINGPASS)
    {
        if (RecvReply(command, 256, &reply) != FTP_SUCCEEDED)
            return FTP_TRYING;

        if (reply != FTPREPLY_LOGGEDIN)
        {
            if (reply == FTPREPLY_CONTROLCLOSED)
                return FTP_FAILED;
            return FTP_TRYING;
        }

        m_iStatus = FTPSTAT_LOGGEDIN;
        return FTP_SUCCEEDED;
    }

	return FTP_FAILED;
}

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
