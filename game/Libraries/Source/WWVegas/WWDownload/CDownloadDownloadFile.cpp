// cl: /DNDEBUG /MD /EHs-c- /Ob2 /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
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

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern "C" __declspec(dllimport) int __stdcall MulDiv(int, int, int);
extern "C" __declspec(dllimport) int __cdecl _strnicmp(const char *, const char *, unsigned int);

enum {
    DOWNLOADSTATUS_NONE = 0,
    DOWNLOADSTATUS_CONNECTING = 2, DOWNLOADSTATUS_LOGGINGIN = 3,
    DOWNLOADSTATUS_DOWNLOADING = 6,
    DOWNLOADSTATUS_FINISHING = 8, DOWNLOAD_SUCCEEDED = 0,
    DOWNLOAD_NETWORKERROR = 0x80040003, DOWNLOAD_FILEERROR = 0x80040004,
    DOWNLOAD_REENTERERROR = 0x80040004, DOWNLOADEVENT_COULDNOTCONNECT = 2,
    DOWNLOADEVENT_LOGINFAILED = 3, DOWNLOADEVENT_NOSUCHFILE = 4,
    DOWNLOADEVENT_TCPERROR = 6, DOWNLOADEVENT_DONOTRESUME = 0x80040006,
    FTP_SUCCEEDED = 0, FTP_FAILED = 0x80040001
};

class Cftp {
public:
    HRESULT LoginToServer(LPCSTR, LPCSTR);
    HRESULT GetNextFileBlock(LPCSTR, int *);
};

// The matched recovery provider leaves its second stack word unused.
class Rva00886A20Class {
public:
    int d_00886a20(LPCSTR, int);
};

class Rva00884Ftp {
public:
    HRESULT ConnectToServer(LPCSTR);
    HRESULT FindFile(LPCSTR, int *);
    HRESULT RestartFrom(int i);
    virtual ~Rva00884Ftp();
    int m_iCommandSocket;
    char unknown08[0x2C - 8];
    int m_iFilePos;
    // ?Get_Command_Socket@Rva00884Ftp@@QBEHXZ absent-from-retail
    int Get_Command_Socket() const { return m_iCommandSocket; }
};

class Rva00884DownloadListener {
public:
    virtual HRESULT OnError(int) = 0;
    virtual HRESULT OnEnd() = 0;
    virtual HRESULT OnQueryResume() = 0;
    virtual HRESULT OnProgressUpdate(int, int, int, int) = 0;
    virtual HRESULT OnStatusUpdate(int) = 0;
};

class CDownload
{
public:
	HRESULT DownloadFile( LPCSTR server, LPCSTR username, LPCSTR password,
		LPCSTR file, LPCSTR localfile, LPCSTR regkey, bool tryresume );
	virtual HRESULT PumpMessages();

private:
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
	Rva00884Ftp *m_Ftp;
	Rva00884DownloadListener *Listener;
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

HRESULT Rva00884Ftp::RestartFrom(int i)
{
	*reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x2c) = i;
	return 0;
}

// Open BFME 2: Code/Libraries/Source/WWVegas/WWDownload/CDownloadDownloadFile.cpp.
// ?PumpMessages@CDownload@@UAEJXZ
HRESULT CDownload::PumpMessages()
{
	int iResult = 0;
	int timetaken = 0;
	int averagetimepredicted = -1;
	static int reenter = 0;

	/* Avoid reentrancy. */

   ////DBGMSG("Download Pump");

	if( reenter != 0 )
	{
		return( DOWNLOAD_REENTERERROR );
	}

	reenter = 1;


	if( m_Status == DOWNLOADSTATUS_GO )
	{
		// Check to see whether the file already exists locally 

/***********
		if (m_TryResume == false)
		{
			m_StartPosition = 0;
		}
		else if(	( m_StartPosition = m_Ftp->FileRecoveryPosition( m_LocalFile, m_RegKey ) ) != 0 )
		{
			if( Listener->OnQueryResume() == DOWNLOADEVENT_DONOTRESUME )
			{
				m_Ftp->RestartFrom( 0 );
				m_StartPosition = 0;
			}
		}
************/

		// Tell the client that we're starting to connect.

		Listener->OnStatusUpdate( DOWNLOADSTATUS_CONNECTING );
		
		m_Status = DOWNLOADSTATUS_CONNECTING;
	}


	if( m_Status == DOWNLOADSTATUS_CONNECTING )
	{
		// Connect to the server
      //////////DBGMSG("Connect to Server");
				
		iResult = m_Ftp->ConnectToServer( m_Server );
      ////////////DBGMSG("out of FTP connect");

		if( iResult == FTP_SUCCEEDED )
		{
			m_Status = DOWNLOADSTATUS_LOGGINGIN;
		}
		else
		{
			if( iResult == FTP_FAILED )
			{
				// Tell the client we couldn't connect
            ///////////DBGMSG("Couldn't connect");
				Listener->OnError( DOWNLOADEVENT_COULDNOTCONNECT );
				reenter = 0;
				return DOWNLOAD_NETWORKERROR;
			}
		}
		reenter = 0;
		return DOWNLOAD_SUCCEEDED;
	}

	if( m_Status == DOWNLOADSTATUS_LOGGINGIN )
	{
		// Login to the server
      ////////////DBGMSG("Login to server");

		iResult = reinterpret_cast<Cftp *>(m_Ftp)->LoginToServer( m_Login, m_Password );

		if( iResult == FTP_SUCCEEDED )
		{
			Listener->OnStatusUpdate( DOWNLOADSTATUS_FINDINGFILE );
			m_Status = DOWNLOADSTATUS_FINDINGFILE;
		}

		if( iResult == FTP_FAILED )
		{
			// Tell the client we couldn't log in

			Listener->OnError( DOWNLOADEVENT_LOGINFAILED );
			reenter = 0;
			return( DOWNLOAD_NETWORKERROR );
		}

		reenter = 0;
		return DOWNLOAD_SUCCEEDED;
	}

	if(( m_Status == DOWNLOADSTATUS_FINDINGFILE ) && (strlen(m_File)))
	{
		
		// Find the file on the server
      ///////////DBGMSG("Find File");

		if( m_Ftp->FindFile( m_File, &m_FileSize ) == FTP_FAILED )
		{
			// Tell the client we couldn't find the file

			Listener->OnError( DOWNLOADEVENT_NOSUCHFILE );
			reenter = 0;
			return( DOWNLOAD_FILEERROR );
		}

		if( m_FileSize > 0 )
		{
			// First check to see if we already have the complete file in the proper dest location...
			//
			// Note, we will only skip the download if the file is a patch.  Patch files should
			//   never ever change so this is not a concern.
			//
			// We identify patches because they are written into the patches folder.
			struct _stat statdata;
			if (	(_stat(m_LocalFile, &statdata) == 0) && 
					(statdata.st_size == m_FileSize) && 
					(_strnicmp(m_LocalFile, "patches\\", strlen("patches\\"))==0)) {
				// OK, no need to download this again....

				m_Status				= DOWNLOADSTATUS_FINDINGFILE;  // ready to find another file
				m_TimeStarted		= 0;
				m_StartPosition	= 0;
				m_FileSize			= 0;
				m_BytesRead			= 0;
				m_File[ 0 ]			= '\0';
				m_LocalFile[ 0 ]	= '\0';
			
				Listener->OnEnd();

				reenter = 0;
				return DOWNLOAD_SUCCEEDED;
			}


			//
			// Check if we can do a file resume
			//
			if (m_TryResume == false)
			{
				m_StartPosition = 0;
			}
			else if(	( m_StartPosition = reinterpret_cast<Rva00886A20Class *>(m_Ftp)->d_00886a20( m_LocalFile, reinterpret_cast<int>(m_RegKey) ) ) != 0 )
			{
				if( Listener->OnQueryResume() == DOWNLOADEVENT_DONOTRESUME )
				{
					m_Ftp->RestartFrom( 0 );
					m_StartPosition = 0;
				}
			}
			// end resume check


			m_Status = DOWNLOADSTATUS_DOWNLOADING;

			// Tell the client we're starting to download

			Listener->OnStatusUpdate( DOWNLOADSTATUS_DOWNLOADING );
		}

		reenter = 0;
		return DOWNLOAD_SUCCEEDED;
	}

	if( m_Status == DOWNLOADSTATUS_DOWNLOADING )
	{

		// Get the next chunk of the file
      ///DBGMSG("Get Next File Block");

		iResult = reinterpret_cast<Cftp *>(m_Ftp)->GetNextFileBlock( m_LocalFile, &m_BytesRead );

		if( m_TimeStarted == 0 )
		{
			// This is the first time through here - record the starting time.
			m_TimeStarted = timeGetTime();
		}

		if( iResult == FTP_SUCCEEDED )
		{
			m_Status = DOWNLOADSTATUS_FINISHING;
		}
		else
		{
			if( iResult == FTP_FAILED )
			{
				Listener->OnError( DOWNLOADEVENT_TCPERROR );
				reenter = 0;
				return( DOWNLOAD_NETWORKERROR );
			}
		}

		// Calculate time taken so far, and predict how long there is left.
		// The prediction returned is the average of the last 8 predictions.

		timetaken = ( timeGetTime() - m_TimeStarted ) / 1000;

		//////////if( m_BytesRead > 0 ) // NAK - RP said this is wrong
      if( ( m_BytesRead - m_StartPosition ) > 0 )
		{
			// Not the first read.
			int predictionIndex = ( m_predictions++ ) & 0x7;
			m_predictionTimes[ predictionIndex ] = MulDiv( timetaken, (m_FileSize - m_BytesRead), (m_BytesRead - m_StartPosition) );
			//__int64 numerator = ( m_FileSize - m_BytesRead )  * timetaken;
			//__int64 denominator = ( m_BytesRead - m_StartPosition );
			//m_predictionTimes[ predictionIndex ] = numerator/denominator;
			//m_predictionTimes[ predictionIndex ] = ( ( m_FileSize - m_BytesRead )  * timetaken ) / ( m_BytesRead - m_StartPosition );
			//m_predictionTimes[ predictionIndex ] = ( ( m_FileSize - m_BytesRead ) / ( m_BytesRead - m_StartPosition ) * timetaken );

			DEBUG_LOG(("About to OnProgressUpdate() - m_FileSize=%d, m_BytesRead=%d, timetaken=%d, numerator=%d",
				m_FileSize, m_BytesRead, timetaken, ( ( m_FileSize - m_BytesRead )  * timetaken )));
			DEBUG_LOG((", m_startPosition=%d, denominator=%d, predictionTime=%d\n",
				m_StartPosition, ( m_BytesRead - m_StartPosition ), predictionIndex));
			DEBUG_LOG(("vals are %d %d %d %d %d %d %d %d\n",
				m_predictionTimes[ 0 ], m_predictionTimes[ 1 ], m_predictionTimes[ 2 ], m_predictionTimes[ 3 ],
				m_predictionTimes[ 4 ], m_predictionTimes[ 5 ], m_predictionTimes[ 6 ], m_predictionTimes[ 7 ]));

			if( m_predictions > 8 )
			{
				// We've had enough time to build up a few predictions, so calculate
				// an average.
				averagetimepredicted = ( m_predictionTimes[ 0 ] + m_predictionTimes[ 1 ] +
										 m_predictionTimes[ 2 ] + m_predictionTimes[ 3 ] +
										 m_predictionTimes[ 4 ] + m_predictionTimes[ 5 ] +
										 m_predictionTimes[ 6 ] + m_predictionTimes[ 7 ] ) / 8;
			}
			else
			{
				// Wait a while longer before passing a "real" prediction
				averagetimepredicted = -1;
			}

		}
		else
		{
			averagetimepredicted = -1;
		}

		// Update the client's progress bar (or whatever)

		Listener->OnProgressUpdate( m_BytesRead, m_FileSize, timetaken, averagetimepredicted + 1);
	}


	if( m_Status == DOWNLOADSTATUS_FINISHING )
	{
		if (m_Ftp->Get_Command_Socket())
			m_Status = DOWNLOADSTATUS_FINDINGFILE;  // ready to find another file
		else
			m_Status = DOWNLOADSTATUS_DONE;			// command channel closed, connect again...

		m_TimeStarted		= 0;
		m_StartPosition		= 0;
		m_FileSize			= 0;
		m_BytesRead			= 0;
		m_File[ 0 ]			= '\0';
		m_LocalFile[ 0 ]	= '\0';
	
		Listener->OnEnd();
	}

	reenter = 0;
	return DOWNLOAD_SUCCEEDED;
}
