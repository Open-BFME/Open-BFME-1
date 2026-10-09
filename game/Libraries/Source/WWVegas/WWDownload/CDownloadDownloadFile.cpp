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

// The unmatched PumpMessages reconstruction used unimplemented FTP member
// names. Keep only this TU's verified DownloadFile and RestartFrom bodies.
// Retail 0x00884EB0 is the emitted restart-position setter (12 bytes).
class Rva00884Ftp
{
public:
	HRESULT RestartFrom(int i);
};

HRESULT Rva00884Ftp::RestartFrom(int i)
{
	*reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x2c) = i;
	return 0;
}
