// cl: /DNDEBUG /MD /EHs-c-
// WWDownload FTP.CPP Cftp::GetNextFileBlock.

typedef char FILE;
typedef const char *LPCSTR;
typedef long HRESULT;

extern "C" __declspec(dllimport) char *__cdecl strncpy(
	char *, const char *, unsigned int);
extern "C" __declspec(dllimport) int __cdecl sprintf(
	char *, const char *, ...);
extern "C" __declspec(dllimport) unsigned int __cdecl strlen(const char *);
extern "C" __declspec(dllimport) FILE *__cdecl fopen(const char *, const char *);
extern "C" __declspec(dllimport) int __cdecl fclose(FILE *);
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(
	const void *, unsigned int, unsigned int, FILE *);
extern "C" __declspec(dllimport) int __cdecl rename(const char *, const char *);
extern "C" __declspec(dllimport) int __cdecl remove(const char *);
extern "C" __declspec(dllimport) int __cdecl _chmod(const char *, int);
extern "C" __declspec(dllimport) char *__cdecl _getcwd(char *, int);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char *);
extern "C" int __stdcall WSAGetLastError(void);
extern "C" int __stdcall recv(int, char *, int, int);
extern "C" int __stdcall send(int, const char *, int, int);

typedef void (__stdcall *Rva01358EA8Function)(const char *);

#pragma intrinsic(strlen)

enum
{
	FTP_SUCCEEDED = 0,
	FTP_FAILED = 0x80040001,
	FTP_TRYING = 0x80040002,
	FTPREPLY_TYPEOK = 200,
	FTPREPLY_RESTARTOK = 350,
	FTPREPLY_OPENBINARY = 150,
	FTPREPLY_CONTROLCLOSED = 421,
	FTPSTAT_FILEFOUND = 100,
	FTPSTAT_FILEOPEN = 180,
	FTPSTAT_SENTFILEPORT = 190,
	FTPSTAT_SENDINGTYPE = 200,
	FTPSTAT_SENTTYPE = 210,
	FTPSTAT_SENDINGREST = 220,
	FTPSTAT_SENTREST = 230,
	FTPSTAT_SENDINGRETR = 240,
	FTPSTAT_SENTRETR = 250,
	FTPSTAT_FILEDATAOPEN = 260,
	FTPSTAT_FILEDATACLOSED = 270,
	FTPSTAT_TRANSFERREPLY = 280,
	FTPSTAT_INIT = 0,
	FTPSTAT_LOGGEDIN = 60
};

class Rva00885390Class
{
public:
	void d_00885390(void);
};

class Rva00885920Class
{
public:
	int d_00885530(const char *, int);
	int d_00885920(void);
};

class Rva00885980Class
{
public:
	void d_00885960(void);
};

class Rva008859D0Class
{
public:
	void d_008859d0(const char *, char *);
};

bool Prepare_Directories(const char *, const char *);

class Cftp
{
public:
	virtual ~Cftp();
	int SendNewPort(void);
	HRESULT RecvReply(const char *, int, int *);
	HRESULT GetNextFileBlock(LPCSTR, int *);

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
	FILE *m_pfLocalFile;
	int m_iStatus;
	int m_sendNewPortStatus;
	int m_findStart;
};

// ?GetNextFileBlock@Cftp@@QAEJPBDPAH@Z
HRESULT Cftp::GetNextFileBlock(LPCSTR szLocalFileName, int *piTotalRead)
{
	char command[256];
	int read, totread = 0;
	const int max_data_len = 10240;
	char data[max_data_len];
	int res, iReply;
	char downloadfilename[256];

	((Rva008859D0Class *)this)->d_008859d0(szLocalFileName, downloadfilename);
	strncpy(m_szLocalFileName, szLocalFileName, 256);

	if (m_iStatus == FTPSTAT_FILEFOUND)
	{
		if (m_iFilePos == 0)
		{
			if ((m_pfLocalFile = fopen(downloadfilename, "wb")) == 0)
				return FTP_FAILED;
		}
		else
		{
			if ((m_pfLocalFile = fopen(downloadfilename, "ab")) == 0)
				return FTP_FAILED;
		}
		m_iStatus = FTPSTAT_FILEOPEN;
	}

	if (m_iStatus == FTPSTAT_FILEOPEN)
	{
		if (((Cftp *)this)->SendNewPort() == FTP_SUCCEEDED)
			m_iStatus = FTPSTAT_SENTFILEPORT;
		else
			return FTP_TRYING;
	}

	if (m_iStatus == FTPSTAT_SENTFILEPORT)
	{
		sprintf(command, "TYPE I\r\n");
		if (send(m_iCommandSocket, command, strlen(command), 0) <= 0)
			return FTP_TRYING;
		Rva01358EA8Function callback =
			*(Rva01358EA8Function *)0x01358EA8;
		callback((const char *)0x01132E90);
		callback(command);
		m_iStatus = FTPSTAT_SENDINGTYPE;
	}

	if (m_iStatus == FTPSTAT_SENDINGTYPE)
	{
		if ((((Cftp *)this)->RecvReply(command, 256, &iReply) != FTP_SUCCEEDED) ||
			(iReply != FTPREPLY_TYPEOK))
			return FTP_TRYING;
		m_iStatus = FTPSTAT_SENTTYPE;
	}

	if (m_iStatus == FTPSTAT_SENTTYPE)
	{
		if (m_iFilePos == 0)
			m_iStatus = FTPSTAT_SENTREST;
		else
		{
			sprintf(command, "REST %d\r\n", m_iFilePos);
			if (((Rva00885920Class *)this)->d_00885530(command, strlen(command)) < 0)
				return FTP_TRYING;
			m_iStatus = FTPSTAT_SENDINGREST;
		}
	}

	if (m_iStatus == FTPSTAT_SENDINGREST)
	{
		res = ((Cftp *)this)->RecvReply(command, 256, &iReply);
		if ((res == FTP_FAILED) || (iReply == 502))
		{
			m_iFilePos = 0;
			fclose(m_pfLocalFile);
			m_pfLocalFile = fopen(downloadfilename, "wb");
		}
		else if ((res != FTP_SUCCEEDED) || (iReply != FTPREPLY_RESTARTOK))
			return FTP_TRYING;
		m_iStatus = FTPSTAT_SENTREST;
	}

	if (m_iStatus == FTPSTAT_SENTREST)
	{
		sprintf(command, "RETR %s\r\n", m_szRemoteFileName);
		if (((Rva00885920Class *)this)->d_00885530(command, strlen(command)) < 0)
			return FTP_TRYING;
		m_iStatus = FTPSTAT_SENDINGRETR;
	}

	if (m_iStatus == FTPSTAT_SENDINGRETR)
	{
		if ((((Cftp *)this)->RecvReply(command, 256, &iReply) != FTP_SUCCEEDED) ||
			(iReply != FTPREPLY_OPENBINARY))
			return FTP_TRYING;
		m_iStatus = FTPSTAT_SENTRETR;
	}

	if (m_iStatus == FTPSTAT_SENTRETR)
	{
		res = ((Rva00885920Class *)this)->d_00885920();
		if (res != FTP_SUCCEEDED)
			return res;
		m_iStatus = FTPSTAT_FILEDATAOPEN;
	}

	if (m_iStatus == FTPSTAT_FILEDATAOPEN)
	{
		do
		{
			read = recv(m_iDataSocket, data, max_data_len, 0);
			if (read > 0)
			{
				fwrite(data, 1, read, m_pfLocalFile);
				totread += read;
			}
		}
		while ((read > 0) && (totread < (max_data_len * 20)));

		m_iFilePos += totread;
		if (piTotalRead != 0)
			*piTotalRead = m_iFilePos;

		if (read < 0)
		{
			int wsa_err = WSAGetLastError();
			if ((wsa_err == 10054) || (wsa_err == 10057))
				read = 0;
		}

		if (read == 0)
		{
			if (m_iFilePos != m_iFileSize)
				return FTP_FAILED;
			m_iStatus = FTPSTAT_FILEDATACLOSED;
		}
		else
			return FTP_TRYING;
	}

	if (m_iStatus == FTPSTAT_FILEDATACLOSED)
	{
		((Rva00885980Class *)this)->d_00885960();
		fclose(m_pfLocalFile);
		m_pfLocalFile = 0;

		char downloadfilename[256];
		((Rva008859D0Class *)this)->d_008859d0(m_szLocalFileName, downloadfilename);

		char curdir[256];
		_getcwd(curdir, 256);
		Prepare_Directories(curdir, m_szLocalFileName);

		if (rename(downloadfilename, m_szLocalFileName) != 0)
		{
			_chmod(m_szLocalFileName, 0x180);
			remove(m_szLocalFileName);
			if (rename(downloadfilename, m_szLocalFileName) != 0)
				return FTP_FAILED;
		}

		((Rva00885920Class *)this)->d_00885530("BOGUSCOMMAND\r\n", strlen("BOGUSCOMMAND\r\n"));
		OutputDebugStringA("File closed, waiting for response.\n");
		m_iStatus = FTPSTAT_TRANSFERREPLY;
	}

	if (m_iStatus == FTPSTAT_TRANSFERREPLY)
	{
		iReply = 0;
		if (((Cftp *)this)->RecvReply(command, 256, &iReply) != FTP_SUCCEEDED)
			return FTP_TRYING;
		if (iReply == FTPREPLY_CONTROLCLOSED)
		{
			m_iStatus = FTPSTAT_INIT;
			m_iFilePos = 0;
			((Rva00885390Class *)this)->d_00885390();
		}
		else
		{
			m_iStatus = FTPSTAT_LOGGEDIN;
			m_iFilePos = 0;
		}
		return FTP_SUCCEEDED;
	}
	return FTP_FAILED;
}
