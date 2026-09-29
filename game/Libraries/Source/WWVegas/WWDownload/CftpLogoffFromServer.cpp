// cl: /DNDEBUG /MD /EHs-c-
// WWDownload FTP.CPP Cftp::LogoffFromServer.

typedef long HRESULT;

extern "C" int __stdcall send(int, const char *, int, int);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char *);

class Rva00885390Class
{
public:
	void d_00885390(void);
};

#pragma comment(linker, "/alternatename:?RecvReply@Cftp@@QAEJPBDHPAH@Z=?d_00885570@@YAXXZ")

class Cftp
{
public:
	virtual ~Cftp();
	HRESULT RecvReply(const char *, int, int *);
	HRESULT LogoffFromServer(void);

private:
	int m_iCommandSocket;
	int m_iDataSocket;
	char m_pad0C[0x3AC];
	void *m_pfLocalFile;
	int m_iStatus;
	int m_sendNewPortStatus;
	int m_findStart;

	void CloseSockets(void);
	void ZeroStuff(void);
};

typedef void (__stdcall *Rva01358EA8Function)(const char *);
HRESULT Cftp::LogoffFromServer(void)
{
	char reply[50];
	int retCode;

	switch (m_iStatus)
	{
	case 70:
		if (send(m_iCommandSocket, "QUIT\r\n", 6, 0) > 0)
		{
			Rva01358EA8Function callback = OutputDebugStringA;
			callback("-->");
			callback("QUIT\r\n");
			m_iStatus = 80;
		}
		else
		{
			return 0x80040001;
		}
	case 80:
		{
			int replyResult = RecvReply(reply, 50, &retCode);
			if (replyResult == 0)
			{
				if (retCode == 221)
				{
					((Rva00885390Class *)this)->d_00885390();
					ZeroStuff();
					return 0;
				}
				m_iStatus = 70;
				return 0x80040002;
			}

			return replyResult == 0x80040001 ? 0x80040001 : 0x80040002;
		}
	default:
		m_iStatus = 70;
		return 0x80040002;
	}
}
