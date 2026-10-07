// cl: /DNDEBUG /MD /EHs-c-

extern "C" int __stdcall closesocket( int );
extern "C" __declspec(dllimport) int __cdecl fclose( void* );
// Cftp's complete destructor, retail 0x00885AF0. It re-seats Cftp's one-slot
// vftable 0x01132ECC (slot 0 = the matched ??_GCftp, 0x00886AA0); the same
// table is installed by the matched ??0Cftp (0x00885AD0) and the ledger pins
// ??1Cftp@@UAE@XZ here. It closes the two sockets and the local file.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDownload/ftp.h
class Cftp
{
public:
	virtual ~Cftp();

private:
	int m_iCommandSocket;					// +0x04
	int m_iDataSocket;					// +0x08
	char m_bfmePad0C[0x3AC];
	void *m_pfLocalFile;					// +0x3B8
};

// ??1Cftp@@UAE@XZ
Cftp::~Cftp()
{
	if ( m_iDataSocket )
	{
		closesocket( m_iDataSocket );
		m_iDataSocket = 0;
	}
	if ( m_iCommandSocket )
	{
		closesocket( m_iCommandSocket );
		m_iCommandSocket = 0;
	}
	if ( m_pfLocalFile )
	{
		fclose( m_pfLocalFile );
		m_pfLocalFile = 0;
	}
}
