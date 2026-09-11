// cl: /DNDEBUG /MD /EHs-c- /O2 /Ob2 /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas
// WWDownload FTP.CPP Cftp::LoginToServer.

typedef const char *LPCSTR;
typedef long HRESULT;

#define FTP_SUCCEEDED 0
#define FTP_FAILED 0x80040001
#define FTP_TRYING 0x80040002
#define FTPSTAT_CONNECTED 20
#define FTPSTAT_SENDINGUSER 30
#define FTPSTAT_SENTUSER 40
#define FTPSTAT_SENDINGPASS 50
#define FTPSTAT_LOGGEDIN 60
#define FTPREPLY_PASSWORD 331
#define FTPREPLY_LOGGEDIN 230
#define FTPREPLY_CONTROLCLOSED 421

extern "C" __declspec(dllimport) char *__cdecl strncpy(
	char *destination, const char *source, unsigned int count);
extern "C" __declspec(dllimport) int __cdecl sprintf(
	char *buffer, const char *format, ...);
extern "C" __declspec(dllimport) void *__cdecl memset(
	void *destination, int value, unsigned int count);
#pragma intrinsic(memset)
#pragma intrinsic(strlen)
extern "C" unsigned int __cdecl strlen(const char *text);
extern "C" int __stdcall send(int socket, const char *buffer, int size, int flags);
extern "C" __declspec(dllimport) void __stdcall Rva01358EA8(const char *text);

class Cftp
{
public:
	HRESULT RecvReply(const char *reply, int size, int *replyCode);
};

class Rva00884Ftp
{
public:
	virtual ~Rva00884Ftp();

	HRESULT LoginToServer(LPCSTR user, LPCSTR pass);

private:
	int m_iCommandSocket;
	int m_iDataSocket;
	unsigned char m_CommandSockAddr[16];
	unsigned char m_DataSockAddr[16];
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

	__forceinline HRESULT SendCommand(LPCSTR command, int size)
	{
		int result = send(m_iCommandSocket, command, size, 0);
		if (result > 0)
		{
			Rva01358EA8((const char *)0x01132E90);
			Rva01358EA8(command);
			return FTP_SUCCEEDED;
		}
		return FTP_FAILED;
	}

	__forceinline HRESULT SendCommandAfterUser(LPCSTR command, int size)
	{
		int result = send(m_iCommandSocket, command, size, 0);
		if (result > 0)
		{
			Rva01358EA8((const char *)0x01132E90);
			Rva01358EA8(command);
			return FTP_SUCCEEDED;
		}
		return FTP_FAILED;
	}
};

// ?LoginToServer@Rva00884Ftp@@QAEJPBD0@Z
HRESULT Rva00884Ftp::LoginToServer(LPCSTR user, LPCSTR pass)
{
	char command[256];
	int reply;

	strncpy(m_szUserName, user, 128);
	strncpy(m_szPassword, pass, 128);
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
		if (((Cftp *)this)->RecvReply(command, 256, &reply) != FTP_SUCCEEDED)
			return FTP_TRYING;

		if (reply != FTPREPLY_PASSWORD)
			return FTP_FAILED;

		m_iStatus = FTPSTAT_SENTUSER;
	}

	if (m_iStatus == FTPSTAT_SENTUSER)
	{
		sprintf(command, "PASS %s\r\n", m_szPassword);

		if (SendCommandAfterUser(command, 7 + strlen(m_szPassword)) < 0)
			return FTP_TRYING;

		m_iStatus = FTPSTAT_SENDINGPASS;
	}

	if (m_iStatus == FTPSTAT_SENDINGPASS)
	{
		if (((Cftp *)this)->RecvReply(command, 256, &reply) != FTP_SUCCEEDED)
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
