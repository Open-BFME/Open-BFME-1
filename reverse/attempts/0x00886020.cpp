// ?FindFile@Rva00884Ftp@@QAEJPBDPAH@Z
// partial score=0.9 date=2026-09-19
// cl: /DNDEBUG /MD /EHs-c- /O2 /Ob2
// WWDownload FTP.CPP Cftp::FindFile.

typedef const char *LPCSTR;
typedef long HRESULT;
typedef long time_t;
#define NULL 0

extern "C" __declspec(dllimport) int __cdecl sprintf(
	char *buffer, const char *format, ...);
extern "C" __declspec(dllimport) char *__cdecl _splitpath(
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
	int RecvData(char *data, int size)
	{
		return recv(m_iDataSocket, data, size, 0);
	}

private:
	int m_iCommandSocket;
	int m_iDataSocket;
};

class Rva00885920Class
{
public:
	int d_00885920(void);
	int d_00885530(const char *command, int size);
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

static char *const g_listline = (char *)0x01336D10;

HRESULT Rva00884Ftp::FindFile(LPCSTR szRemoteFileName, int *piSize)
{
	char command[256];
	static char *listline = g_listline;
	int i, iReply;
	char ext[10];
	int sendingCwdStatus = FTPSTAT_SENDINGCWD;
	Rva01358EA8Function callback;
	time_t (__cdecl *timeFunction)(time_t *) =
		*(time_t (__cdecl **)(time_t *))0x013594F0;

	if (m_findStart == 0)
		m_findStart = timeFunction(NULL);

	if ((timeFunction(NULL) - m_findStart) > 30) {
		m_findStart = 0;
		return FTP_FAILED;
	}

	_splitpath(szRemoteFileName, NULL, m_szRemoteFilePath + strlen(m_szRemoteFilePath),
		m_szRemoteFileName, ext);
	strcat(m_szRemoteFileName, ext);

	for (i = 0; i < (int)strlen(m_szRemoteFilePath); ++i) {
		if (m_szRemoteFilePath[i] == '\\')
			m_szRemoteFilePath[i] = '/';
	}

	memset(command, 0, 256);

	callback = *(Rva01358EA8Function *)0x01358EA8;
	if ((m_iStatus == FTPSTAT_LOGGEDIN) || (m_iStatus == FTPSTAT_FILEFOUND)) {
		sprintf(command, (const char *)0x01132F10, m_szRemoteFilePath);
		if (send(m_iCommandSocket, command, 6 + strlen(m_szRemoteFilePath), 0) > 0) {
			callback((const void *)0x01132E90);
			callback((const void *)command);
			m_iStatus = sendingCwdStatus;
		} else {
			return FTP_TRYING;
		}
	}

	if (m_iStatus == sendingCwdStatus) {
		HRESULT reply = ((Cftp *)this)->RecvReply(command, 256, &iReply);
		if ((reply == FTP_SUCCEEDED) && (iReply == 550)) {
			m_findStart = 0;
			return FTP_FAILED;
		}
		if ((reply != FTP_SUCCEEDED) || (iReply != FTPREPLY_CWDOK))
			return FTP_TRYING;
		m_iStatus = FTPSTAT_SENTCWD;
	}

	if (m_iStatus == FTPSTAT_SENTCWD) {
		i = 0;
		for (; ((Cftp *)this)->SendNewPort() == FTP_TRYING; ) {
			++i;
			if (i == 1000)
				return FTP_TRYING;
		}
		m_iStatus = FTPSTAT_SENTPORT;
	}

	if (m_iStatus == FTPSTAT_SENTPORT) {
		callback = *(Rva01358EA8Function *)0x01358EA8;
		sprintf(command, (const char *)0x01132F04, m_szRemoteFileName);
		if (send(m_iCommandSocket, command, 7 + strlen(m_szRemoteFileName), 0) > 0) {
			callback((const void *)0x01132E90);
			callback((const void *)command);
			m_iStatus = FTPSTAT_SENDINGLIST;
		} else {
			return FTP_TRYING;
		}
	}

	if (m_iStatus == FTPSTAT_SENDINGLIST) {
		if ((((Cftp *)this)->RecvReply(command, 256, &iReply) != FTP_SUCCEEDED) ||
			(iReply != FTPREPLY_OPENASCII))
			return FTP_TRYING;
		m_iStatus = FTPSTAT_SENTLIST;
	}

	if (m_iStatus == FTPSTAT_SENTLIST) {
		i = ((Rva00885920Class *)this)->d_00885920();
		if (i != FTP_SUCCEEDED) {
			m_findStart = 0;
			return i;
		}
		m_iStatus = FTPSTAT_LISTDATAOPEN;
		memset(listline, 0, 256);
	}

	if (m_iStatus == FTPSTAT_LISTDATAOPEN) {
		((Cftp *)this)->RecvData(listline, 256);
		if (strlen(listline) == 0)
			return FTP_TRYING;
		m_iStatus = FTPSTAT_LISTDATARECVD;
	}

	if (m_iStatus == FTPSTAT_LISTDATARECVD) {
		if ((((Cftp *)this)->RecvReply(command, 256, &iReply) != FTP_SUCCEEDED) ||
			(iReply != FTPREPLY_COMPLETE))
			return FTP_TRYING;
		m_iStatus = FTPSTAT_LISTDATAREADY;
	}

	((Rva00885980Class *)this)->d_00885960();

	if (m_iStatus == FTPSTAT_LISTDATAREADY) {
		sprintf(command, (const char *)0x01132EF8, m_szRemoteFileName);
		if (((Rva00885920Class *)this)->d_00885530(
				command, 7 + strlen(m_szRemoteFileName)) < 0)
			return FTP_TRYING;
		m_iStatus = FTPSTAT_SIZING;
	}

	if (m_iStatus == FTPSTAT_SIZING) {
		if ((((Cftp *)this)->RecvReply(command, 256, &iReply) != FTP_SUCCEEDED) ||
			(iReply != 213))
			return FTP_TRYING;

		*(int *)0x012D4D68 = -1;
		if (sscanf(command, (const char *)0x01132EF0,
				&i, (int *)0x012D4D68) != 2)
			*(int *)0x012D4D68 = -1;
	}

	m_iStatus = FTPSTAT_FILEFOUND;
	m_findStart = 0;

	if (strncmp(listline, m_szRemoteFileName, sizeof(m_szRemoteFileName)) == 0)
		return FTP_FAILED;

	if (sscanf(&listline[32], (const char *)0x010E8928, &i) == 1) {
		if (piSize != NULL)
			*piSize = i;
		m_iFileSize = i;
		return FTP_SUCCEEDED;
	}

	return FTP_FAILED;
}
