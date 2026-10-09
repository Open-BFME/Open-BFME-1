// cl: /DNDEBUG /MD /EHs-c- /O2 /Ob2

typedef const char *LPCSTR;
typedef long HRESULT;
typedef long time_t;
#define NULL 0

extern "C" __declspec(dllimport) int __cdecl sprintf(
	char *buffer, const char *format, ...);
extern "C" __declspec(dllimport) void __cdecl _splitpath(
	const char *path, char *drive, char *directory, char *filename, char *extension);
extern "C" __declspec(dllimport) unsigned int __cdecl strlen(const char *text);
extern "C" __declspec(dllimport) char *__cdecl strcat(char *left, const char *right);
extern "C" __declspec(dllimport) int __cdecl sscanf(
	const char *buffer, const char *format, ...);
extern "C" __declspec(dllimport) int __cdecl strncmp(
	const char *left, const char *right, unsigned int count);
extern "C" void *__cdecl memset(void *buffer, int value, unsigned int size);
extern "C" int __stdcall send(int socket, const char *buffer, int size, int flags);
extern "C" int __stdcall recv(int socket, char *buffer, int size, int flags);

typedef void (__stdcall *Rva01358EA8Function)(const void *text);

enum
{
	FTP_SUCCEEDED = 0,
	FTP_FAILED = 0x80040001,
	FTP_TRYING = 0x80040002,
	FTPSTAT_LOGGEDIN = 60,
	FTPSTAT_FILEFOUND = 100,
	FTPSTAT_SENDINGCWD = 110,
	FTPSTAT_SENTCWD = 120,
	FTPSTAT_SENTPORT = 130,
	FTPSTAT_SENDINGLIST = 140,
	FTPSTAT_SENTLIST = 150,
	FTPSTAT_LISTDATAOPEN = 160,
	FTPSTAT_LISTDATARECVD = 170,
	FTPSTAT_LISTDATAREADY = 171,
	FTPSTAT_SIZING = 172,
	FTPREPLY_CWDOK = 250,
	FTPREPLY_OPENASCII = 150,
	FTPREPLY_COMPLETE = 226
};

class Cftp
{
public:
	HRESULT RecvReply(const char *reply, int size, int *replyCode);
	int SendNewPort(void);

};

class Rva00885920Class
{
public:
	char m_pad0[4];
	int m_socket4;
	int m_socket8;
	int d_00885920(void);
	inline int d_00885530(const char *command, int size);
};

class Rva00885980Class
{
public:
	void d_00885960(void);
};

class Rva00884Ftp
{
public:
	virtual ~Rva00884Ftp();
	HRESULT FindFile(LPCSTR remote, int *size);

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
};

extern "C" __declspec(dllimport) time_t __cdecl time(time_t *);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char *);
#pragma intrinsic(strlen)

static int s_iRemoteFileSize = -1;

// Open BFME 2: Code/Libraries/Source/WWVegas/WWDownload/FTP.CPP.
// ?FindFile@Rva00884Ftp@@QAEJPBDPAH@Z
HRESULT Rva00884Ftp::FindFile(LPCSTR szRemoteFileName, int *piSize)
{
	char command[256];
	static char listline[256];
	int i, iReply, iCode;
	char ext[10];

	if (m_findStart == 0)
		m_findStart = time(NULL);

	if ((time(NULL) - m_findStart) > 30)
	{
		m_findStart = 0;
		return FTP_FAILED;
	}

	_splitpath(szRemoteFileName, NULL, m_szRemoteFilePath + strlen(m_szRemoteFilePath),
		m_szRemoteFileName, ext);

	strcat(m_szRemoteFileName, ext);

	for (i = 0; i < (int)strlen(m_szRemoteFilePath); i++)
	{
		if (m_szRemoteFilePath[i] == '\\')
		{
			m_szRemoteFilePath[i] = '/';
		}
	}

	memset(command, 0, 256);

	if ((m_iStatus == FTPSTAT_LOGGEDIN) || (m_iStatus == FTPSTAT_FILEFOUND))
	{
		sprintf(command, "CWD %s\r\n", m_szRemoteFilePath);

		if (((Rva00885920Class *)this)->d_00885530(command, 6 + strlen(m_szRemoteFilePath)) < 0)
		{
			return FTP_TRYING;
		}

		m_iStatus = FTPSTAT_SENDINGCWD;
	}

	if (m_iStatus == FTPSTAT_SENDINGCWD)
	{
		HRESULT reply = ((Cftp *)this)->RecvReply(command, 256, &iReply);

		if ((reply == FTP_SUCCEEDED) && (iReply == 550))
		{
			m_findStart = 0;
			return FTP_FAILED;
		}

		if ((reply != FTP_SUCCEEDED) || (iReply != FTPREPLY_CWDOK))
		{
			return FTP_TRYING;
		}

		m_iStatus = FTPSTAT_SENTCWD;
	}

	if (m_iStatus == FTPSTAT_SENTCWD)
	{
		i = 0;
		while (((Cftp *)this)->SendNewPort() == FTP_TRYING)
		{
			i++;

			if (i == 1000)
			{
				return FTP_TRYING;
			}
		}

		m_iStatus = FTPSTAT_SENTPORT;
	}

	if (m_iStatus == FTPSTAT_SENTPORT)
	{
		sprintf(command, "LIST %s\r\n", m_szRemoteFileName);

		if (((Rva00885920Class *)this)->d_00885530(command, 7 + strlen(m_szRemoteFileName)) < 0)
		{
			return FTP_TRYING;
		}

		m_iStatus = FTPSTAT_SENDINGLIST;
	}

	if (m_iStatus == FTPSTAT_SENDINGLIST)
	{
		if ((((Cftp *)this)->RecvReply(command, 256, &iReply) != FTP_SUCCEEDED) ||
			(iReply != FTPREPLY_OPENASCII))
		{
			return FTP_TRYING;
		}

		m_iStatus = FTPSTAT_SENTLIST;
	}

	if (m_iStatus == FTPSTAT_SENTLIST)
	{
		i = ((Rva00885920Class *)this)->d_00885920();
		if (i != FTP_SUCCEEDED)
		{
			m_findStart = 0;
			return i;
		}
		m_iStatus = FTPSTAT_LISTDATAOPEN;
		memset(listline, 0, 256);
	}

	if (m_iStatus == FTPSTAT_LISTDATAOPEN)
	{
		recv(m_iDataSocket, listline, 256, 0);

		iCode = strlen(listline);
		if (iCode == 0)
		{
			return FTP_TRYING;
		}
		m_iStatus = FTPSTAT_LISTDATARECVD;
	}

	if (m_iStatus == FTPSTAT_LISTDATARECVD)
	{
		if ((((Cftp *)this)->RecvReply(command, 256, &iReply) != FTP_SUCCEEDED) ||
			(iReply != FTPREPLY_COMPLETE))
		{
			return FTP_TRYING;
		}

		m_iStatus = FTPSTAT_LISTDATAREADY;
		((Rva00885980Class *)this)->d_00885960();
	}

	if (m_iStatus == FTPSTAT_LISTDATAREADY)
	{
		sprintf(command, "SIZE %s\r\n", m_szRemoteFileName);

		if (((Rva00885920Class *)this)->d_00885530(command, 7 + strlen(m_szRemoteFileName)) < 0)
		{
			return FTP_TRYING;
		}

		m_iStatus = FTPSTAT_SIZING;
	}

	if (m_iStatus == FTPSTAT_SIZING)
	{
		if (((Cftp *)this)->RecvReply(command, 256, &iReply) == FTP_SUCCEEDED)
		{
			s_iRemoteFileSize = -1;
			if (iReply == 213)
			{
				if (sscanf(command, "%d %ld ", &iCode, &s_iRemoteFileSize) != 2)
					s_iRemoteFileSize = -1;
			}
		}
		m_iStatus = FTPSTAT_FILEFOUND;
	}

	m_findStart = 0;

	if (strncmp(listline, m_szRemoteFileName, sizeof(m_szRemoteFileName)) == 0)
	{

		return FTP_FAILED;
	}

	if (s_iRemoteFileSize >= 0)
	{
		if (piSize != NULL)
		{
			*piSize = s_iRemoteFileSize;
			m_iFileSize = s_iRemoteFileSize;
		}
		return FTP_SUCCEEDED;
	}

	if (sscanf(&listline[32], " %d ", &i) == 1)
	{
		if (piSize != NULL)
		{
			*piSize = i;
			m_iFileSize = i;
		}
		return FTP_SUCCEEDED;
	}

	return FTP_FAILED;
}

// ?d_00885530@Rva00885920Class@@QAEHPBDH@Z
inline int Rva00885920Class::d_00885530(const char *command, int size)
{
    int sent = send(m_socket4, command, size, 0);
    if (sent > 0)
    {
        OutputDebugStringA("-->");
        OutputDebugStringA(command);
        return FTP_SUCCEEDED;
    }
    return FTP_FAILED;
}
