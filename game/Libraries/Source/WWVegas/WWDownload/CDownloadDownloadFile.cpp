// cl: /DNDEBUG /MD /EHs-c- /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// WWDownload Download.cpp CDownload::DownloadFile.

#include "PreRTS.h"
#include <direct.h>
#include <string.h>
#include <sys/stat.h>

typedef const char *LPCSTR;
typedef long HRESULT;

enum
{
	DOWNLOADSTATUS_DONE = 0,
	DOWNLOADSTATUS_GO = 1,
	DOWNLOADSTATUS_FINDINGFILE = 4,
	DOWNLOAD_STATUSERROR = 0x80040002,
	DOWNLOAD_PARAMERROR = 0x80040001
};

class Rva00885980Class
{
public:
	int d_00885980( void );
};

class CDownload
{
public:
	HRESULT DownloadFile( LPCSTR server, LPCSTR username, LPCSTR password,
		LPCSTR file, LPCSTR localfile, LPCSTR regkey, bool tryresume );
	HRESULT PumpMessages();

private:
	char m_vtable[4];
	char m_Server[256];
	char m_Login[64];
	char m_Password[64];
	char m_File[256];
	char m_LocalFile[256];
	char m_LastLocalFile[256];
	char m_RegKey[256];
	int m_Status;
	int m_TimeStarted;
	int m_StartPosition;
	int m_FileSize;
	int m_BytesRead;
	bool m_TryResume;
	int m_predictions;
	int m_predictionTimes[8];
	void *m_Ftp;
	void *Listener;
};

HRESULT CDownload::DownloadFile( LPCSTR server, LPCSTR username, LPCSTR password,
	LPCSTR file, LPCSTR localfile, LPCSTR regkey, bool tryresume )
{
	if( ( m_Status != DOWNLOADSTATUS_DONE ) && ( m_Status != DOWNLOADSTATUS_FINDINGFILE ) )
	{
		return DOWNLOAD_STATUSERROR;
	}

	if( m_Status == DOWNLOADSTATUS_FINDINGFILE )
	{
		if( ( strcmp( m_Server, server ) ) || ( strcmp( m_Login, username ) ) )
		{
			( (Rva00885980Class *)m_Ftp )->d_00885980();
			m_Status = DOWNLOADSTATUS_DONE;
		}
	}

	if( ( server == NULL ) || ( username == NULL ) ||
		( password == NULL ) || ( file == NULL ) ||
		( localfile == NULL ) || ( regkey == NULL ) )
	{
		return DOWNLOAD_PARAMERROR;
	}

	_mkdir( "download" );

	strncpy( m_Server, server, sizeof( m_Server ) );
	strncpy( m_Login, username, sizeof( m_Login ) );
	strncpy( m_Password, password, sizeof( m_Password ) );
	strncpy( m_File, file, sizeof( m_File ) );
	strncpy( m_LocalFile, localfile, sizeof( m_LocalFile ) );
	strncpy( m_LastLocalFile, localfile, sizeof( m_LastLocalFile ) );
	strncpy( m_RegKey, regkey, sizeof( m_RegKey ) );
	m_TryResume = tryresume;
	m_StartPosition = 0;

	if( m_Status != DOWNLOADSTATUS_FINDINGFILE )
	{
		m_Status = DOWNLOADSTATUS_GO;
	}

	return 0;
}

// ?PumpMessages@CDownload@@QAEJXZ present-unmatched

extern unsigned int(__cdecl *g_bfmeNowVNH)();

extern "C" __declspec(dllimport) long __stdcall MulDiv(long, long, long);
extern "C" __declspec(dllimport) int __cdecl _strnicmp(
	const char *left, const char *right, unsigned int count);

class Rva00884DownloadListener
{
public:
	virtual HRESULT OnError(int error) = 0;
	virtual HRESULT OnEnd() = 0;
	virtual HRESULT OnQueryResume() = 0;
	virtual HRESULT OnProgressUpdate(int bytesread, int totalsize, int timetaken, int timeleft) = 0;
	virtual HRESULT OnStatusUpdate(int status) = 0;
};

class Rva00884Ftp
{
public:
	HRESULT ConnectToServer(LPCSTR server);
	HRESULT LoginToServer(LPCSTR user, LPCSTR pass);
	HRESULT FindFile(LPCSTR remote, int *size);
	HRESULT FileRecoveryPosition(LPCSTR localfile, LPCSTR regkey);
	HRESULT GetNextFileBlock(LPCSTR localfile, int *totalread);

	HRESULT RestartFrom(int i)
	{
		*reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x2c) = i;
		return 0;
	}

	int Get_Command_Socket() const
	{
		return *reinterpret_cast<const int *>(reinterpret_cast<const char *>(this) + 4);
	}
};

enum
{
	DOWNLOADSTATUS_NONE = 0,
	DOWNLOADSTATUS_CONNECTING = 2,
	DOWNLOADSTATUS_LOGGINGIN = 3,
	DOWNLOADSTATUS_DOWNLOADING = 6,
	DOWNLOADSTATUS_FINISHING = 8,
	DOWNLOAD_SUCCEEDED = 0,
	DOWNLOAD_NETWORKERROR = 0x80040003,
	DOWNLOAD_FILEERROR = 0x80040004,
	DOWNLOAD_REENTERERROR = 0x80040004,
	DOWNLOADEVENT_COULDNOTCONNECT = 2,
	DOWNLOADEVENT_LOGINFAILED = 3,
	DOWNLOADEVENT_NOSUCHFILE = 4,
	DOWNLOADEVENT_TCPERROR = 6,
	DOWNLOADEVENT_DONOTRESUME = 0x80040006,
	FTP_SUCCEEDED = 0,
	FTP_FAILED = 0x80040001
};

HRESULT CDownload::PumpMessages()
{
	int iResult = 0;
	unsigned int timetaken = 0;
	int averagetimepredicted = -1;
	static int reenter = 0;

	if (reenter != 0) {
		return DOWNLOAD_REENTERERROR;
	}

	reenter = 1;

	if (m_Status == DOWNLOADSTATUS_GO) {
		reinterpret_cast<Rva00884DownloadListener *>(Listener)->OnStatusUpdate(DOWNLOADSTATUS_CONNECTING);
		m_Status = DOWNLOADSTATUS_CONNECTING;
	}

	if (m_Status == DOWNLOADSTATUS_CONNECTING) {
		iResult = reinterpret_cast<Rva00884Ftp *>(m_Ftp)->ConnectToServer(m_Server);

		if (iResult == FTP_SUCCEEDED) {
			m_Status = DOWNLOADSTATUS_LOGGINGIN;
		}
		else {
			if (iResult == FTP_FAILED) {
				reinterpret_cast<Rva00884DownloadListener *>(Listener)->OnError(DOWNLOADEVENT_COULDNOTCONNECT);
				reenter = 0;
				return DOWNLOAD_NETWORKERROR;
			}
		}
		reenter = 0;
		return DOWNLOAD_SUCCEEDED;
	}

	if (m_Status == DOWNLOADSTATUS_LOGGINGIN) {
		iResult = reinterpret_cast<Rva00884Ftp *>(m_Ftp)->LoginToServer(m_Login, m_Password);

		if (iResult == FTP_SUCCEEDED) {
			reinterpret_cast<Rva00884DownloadListener *>(Listener)->OnStatusUpdate(DOWNLOADSTATUS_FINDINGFILE);
			m_Status = DOWNLOADSTATUS_FINDINGFILE;
		}

		if (iResult == FTP_FAILED) {
			reinterpret_cast<Rva00884DownloadListener *>(Listener)->OnError(DOWNLOADEVENT_LOGINFAILED);
			reenter = 0;
			return DOWNLOAD_NETWORKERROR;
		}

		reenter = 0;
		return DOWNLOAD_SUCCEEDED;
	}

	if ((m_Status == DOWNLOADSTATUS_FINDINGFILE) && (strlen(m_File))) {

		if (reinterpret_cast<Rva00884Ftp *>(m_Ftp)->FindFile(m_File, &m_FileSize) == FTP_FAILED) {
			reinterpret_cast<Rva00884DownloadListener *>(Listener)->OnError(DOWNLOADEVENT_NOSUCHFILE);
			reenter = 0;
			return DOWNLOAD_FILEERROR;
		}

		if (m_FileSize > 0) {

			struct _stat statdata;
			if ((_stat(m_LocalFile, &statdata) == 0) &&
				(statdata.st_size == m_FileSize) &&
				(_strnicmp(m_LocalFile, "patches\\", strlen("patches\\")) == 0)) {

				m_Status			= DOWNLOADSTATUS_FINDINGFILE;
				m_TimeStarted		= 0;
				m_StartPosition		= 0;
				m_FileSize			= 0;
				m_BytesRead			= 0;
				m_File[0]			= '\0';
				m_LocalFile[0]		= '\0';

				reinterpret_cast<Rva00884DownloadListener *>(Listener)->OnEnd();

				reenter = 0;
				return DOWNLOAD_SUCCEEDED;
			}

			if (m_TryResume == false) {
				m_StartPosition = 0;
			}
			else if ((m_StartPosition = reinterpret_cast<Rva00884Ftp *>(m_Ftp)->FileRecoveryPosition(m_LocalFile, m_RegKey)) != 0) {
				if (reinterpret_cast<Rva00884DownloadListener *>(Listener)->OnQueryResume() == DOWNLOADEVENT_DONOTRESUME) {
					reinterpret_cast<Rva00884Ftp *>(m_Ftp)->RestartFrom(0);
					m_StartPosition = 0;
				}
			}

			m_Status = DOWNLOADSTATUS_DOWNLOADING;

			reinterpret_cast<Rva00884DownloadListener *>(Listener)->OnStatusUpdate(DOWNLOADSTATUS_DOWNLOADING);
		}

		reenter = 0;
		return DOWNLOAD_SUCCEEDED;
	}

	if (m_Status == DOWNLOADSTATUS_DOWNLOADING) {

		iResult = reinterpret_cast<Rva00884Ftp *>(m_Ftp)->GetNextFileBlock(m_LocalFile, &m_BytesRead);

		if (m_TimeStarted == 0) {
			m_TimeStarted = g_bfmeNowVNH();
		}

		if (iResult == FTP_SUCCEEDED) {
			m_Status = DOWNLOADSTATUS_FINISHING;
		}
		else {
			if (iResult == FTP_FAILED) {
				reinterpret_cast<Rva00884DownloadListener *>(Listener)->OnError(DOWNLOADEVENT_TCPERROR);
				reenter = 0;
				return DOWNLOAD_NETWORKERROR;
			}
		}

		timetaken = (g_bfmeNowVNH() - m_TimeStarted) / 1000;

		if ((m_BytesRead - m_StartPosition) > 0) {

			int predictionIndex = (m_predictions++) & 0x7;
			m_predictionTimes[predictionIndex] = MulDiv(timetaken, (m_FileSize - m_BytesRead), (m_BytesRead - m_StartPosition));

			if (m_predictions > 8) {
				averagetimepredicted = (m_predictionTimes[0] + m_predictionTimes[1] +
					m_predictionTimes[2] + m_predictionTimes[3] +
					m_predictionTimes[4] + m_predictionTimes[5] +
					m_predictionTimes[6] + m_predictionTimes[7]) / 8;
			}
			else {
				averagetimepredicted = -1;
			}
		}
		else {
			averagetimepredicted = -1;
		}

		reinterpret_cast<Rva00884DownloadListener *>(Listener)->OnProgressUpdate(m_BytesRead, m_FileSize, timetaken, averagetimepredicted + 1);
	}

	if (m_Status == DOWNLOADSTATUS_FINISHING) {
		if (reinterpret_cast<Rva00884Ftp *>(m_Ftp)->Get_Command_Socket())
			m_Status = DOWNLOADSTATUS_FINDINGFILE;
		else
			m_Status = DOWNLOADSTATUS_NONE;

		m_TimeStarted		= 0;
		m_StartPosition		= 0;
		m_FileSize			= 0;
		m_BytesRead			= 0;
		m_File[0]			= '\0';
		m_LocalFile[0]		= '\0';

		reinterpret_cast<Rva00884DownloadListener *>(Listener)->OnEnd();
	}

	reenter = 0;
	return DOWNLOAD_SUCCEEDED;
}
