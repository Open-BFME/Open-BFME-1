// cl: /DNDEBUG /MD /EHs-c- /O2 /Ob2 /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas
// WWDownload FTP.CPP Cftp::ConnectToServer.

typedef const char *LPCSTR;
typedef long HRESULT;

typedef unsigned int SOCKET;

struct in_addr
{
	union
	{
		unsigned long S_addr;
	} S_un;
};

#define s_addr S_un.S_addr

struct sockaddr
{
	unsigned short sa_family;
	char sa_data[14];
};

struct sockaddr_in
{
	short sin_family;
	unsigned short sin_port;
	in_addr sin_addr;
	char sin_zero[8];
};

struct fd_set
{
	unsigned int fd_count;
	SOCKET fd_array[64];
};

struct timeval
{
	long tv_sec;
	long tv_usec;
};

#define AF_INET 2
#define SOCK_STREAM 1
#define FIONBIO 0x8004667e
#define SOCKET_ERROR (-1)
#define INADDR_NONE 0xffffffff
#define WSAEWOULDBLOCK 10035
#define WSAEINVAL 10022
#define WSAEALREADY 10037
#define WSAEISCONN 10056

#define FTP_SUCCEEDED 0
#define FTP_FAILED 0x80040001
#define FTP_TRYING 0x80040002
#define FTPSTAT_INIT 0
#define FTPSTAT_CONNECTING 10
#define FTPSTAT_WAITINGSERVEROK 15
#define FTPSTAT_CONNECTED 20
#define FTPREPLY_SERVEROK 220

#define FD_ZERO(set) (((fd_set *)(set))->fd_count = 0)
#define FD_SET(socketHandle, set) do { \
	((fd_set *)(set))->fd_array[((fd_set *)(set))->fd_count++] = \
		(SOCKET)(socketHandle); \
} while (0)
#define FD_ISSET(socketHandle, set) \
	__WSAFDIsSet((SOCKET)(socketHandle), (fd_set *)(set))

extern "C" __declspec(dllimport) char *__cdecl strncpy(
	char *destination, const char *source, unsigned int count);
extern "C" void *__cdecl memset(void *destination, int value, unsigned int count);
#pragma intrinsic(memset)
extern "C" unsigned long __stdcall inet_addr(const char *name);
extern "C" unsigned short __stdcall htons(unsigned short port);
extern "C" SOCKET __stdcall socket(int addressFamily, int type, int protocol);
extern "C" int __stdcall ioctlsocket(
	SOCKET socketHandle, long command, unsigned long *argument);
extern "C" int __stdcall connect(
	SOCKET socketHandle, const sockaddr *name, int nameLength);
extern "C" int __stdcall closesocket(SOCKET socketHandle);
extern "C" int __stdcall WSAGetLastError(void);
extern "C" int __stdcall __WSAFDIsSet(SOCKET socketHandle, fd_set *set);
extern "C" int __stdcall select(
	int nfds, fd_set *readSet, fd_set *writeSet, fd_set *exceptSet,
	const timeval *timeout);
bool Use_Non_Blocking_Mode(void);

class Cftp
{
public:
	int AsyncGetHostByName(char *name, sockaddr_in &address);
	HRESULT RecvReply(const char *reply, int size, int *replyCode);
};

class Rva00884Ftp
{
public:
	virtual ~Rva00884Ftp();
	HRESULT ConnectToServer(LPCSTR serverName);

private:
	int m_iCommandSocket;
	int m_iDataSocket;
	sockaddr_in m_CommandSockAddr;
	sockaddr_in m_DataSockAddr;
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

// ?ConnectToServer@Cftp@@QAEJPBD@Z
HRESULT Rva00884Ftp::ConnectToServer(LPCSTR serverName)
{
	unsigned long uTemp;
	char buffer[256];
	int error;

	strncpy(m_szServerName, serverName, 128);

	if (m_iStatus == FTPSTAT_INIT)
	{
		sockaddr_in address;
		unsigned long serverIP;
		serverIP = inet_addr(m_szServerName);

		memset(&m_CommandSockAddr, 0, sizeof(m_CommandSockAddr));
		m_CommandSockAddr.sin_family = AF_INET;

		if (serverIP == INADDR_NONE)
		{
			if (((Cftp *)this)->AsyncGetHostByName(m_szServerName, address) == FTP_TRYING)
				return FTP_TRYING;

			if (address.sin_addr.s_addr == 0)
				return FTP_FAILED;

			m_CommandSockAddr = address;
			serverIP = m_CommandSockAddr.sin_addr.s_addr;
		}
		else
		{
			m_CommandSockAddr.sin_addr.s_addr = serverIP;
		}

		m_CommandSockAddr.sin_port = htons(21);
		m_iCommandSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (m_iCommandSocket < 0)
			return FTP_FAILED;

		uTemp = 1;
		if (Use_Non_Blocking_Mode())
		{
			if (ioctlsocket(m_iCommandSocket, FIONBIO, &uTemp) == SOCKET_ERROR)
				return FTP_FAILED;
		}

		m_iStatus = FTPSTAT_CONNECTING;
		if (connect(m_iCommandSocket,
			(const struct sockaddr *)&m_CommandSockAddr,
			sizeof(m_CommandSockAddr)) == -1)
		{
			error = WSAGetLastError();
			if ((error == WSAEWOULDBLOCK) || (error == WSAEINVAL) ||
				(error == WSAEALREADY))
				return FTP_TRYING;

			if (error != WSAEISCONN)
			{
				closesocket(m_iCommandSocket);
				return FTP_FAILED;
			}
		}
	}

	if (m_iStatus == FTPSTAT_CONNECTING)
	{
		fd_set writeSet;
		fd_set exceptionSet;
		FD_ZERO(&writeSet);
		FD_ZERO(&exceptionSet);
		FD_SET(m_iCommandSocket, &writeSet);
		FD_SET(m_iCommandSocket, &exceptionSet);
		timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 0;
		int result = select(m_iCommandSocket + 1, 0, &writeSet,
			&exceptionSet, &timeout);
		if (result == 0)
			return FTP_TRYING;
		if (FD_ISSET(m_iCommandSocket, &exceptionSet))
		{
			closesocket(m_iCommandSocket);
			return FTP_FAILED;
		}
		if (FD_ISSET(m_iCommandSocket, &writeSet))
			m_iStatus = FTPSTAT_WAITINGSERVEROK;
	}

	if (m_iStatus == FTPSTAT_WAITINGSERVEROK)
	{
		int replyCode;
		replyCode = 0;
		if (((Cftp *)this)->RecvReply(buffer, 256, &replyCode) != FTP_SUCCEEDED)
			return FTP_TRYING;
		if (replyCode != FTPREPLY_SERVEROK)
			return FTP_FAILED;
		m_iStatus = FTPSTAT_CONNECTED;
		return FTP_SUCCEEDED;
	}

	return FTP_FAILED;
}
