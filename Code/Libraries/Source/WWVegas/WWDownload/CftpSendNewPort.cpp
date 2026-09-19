// cl: /DNDEBUG /MD /EHs-c- /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /Ireference/shims/sweep
// WWDownload FTP.CPP Cftp::SendNewPort.

#include "PreRTS.h"
#include <cstdio>

typedef long HRESULT;

struct sockaddr_in
{
	unsigned short sin_family;
	unsigned short sin_port;
	unsigned long sin_addr;
	unsigned char sin_zero[ 8 ];
};

extern "C" int __stdcall socket( int, int, int );
extern "C" int __stdcall ioctlsocket( int, long, unsigned long * );
extern "C" int __stdcall bind( int, const void *, int );
extern "C" int __stdcall getsockname( int, void *, int * );
extern "C" int __stdcall listen( int, int );
extern "C" unsigned long __stdcall htonl( unsigned long );
bool Use_Non_Blocking_Mode( void );
unsigned long MyIPAddress( int );

#pragma comment(linker, "/alternatename:?RecvReply@Cftp@@QAEJPBDHPAH@Z=?d_00885570@@YAXXZ")

class Rva00885920Class
{
public:
	int d_00885530( const char *command, int size );
};

enum
{
	FTP_FAILED = 0x80040001,
	FTP_TRYING = 0x80040002,
	FTP_SUCCEEDED = 0,
	FTPREPLY_PORTOK = 200
};

class Cftp
{
public:
	virtual ~Cftp();
	HRESULT SendCommand( const char *command, int size );
	HRESULT RecvReply( const char *reply, int size, int *replyCode );
	int SendNewPort( void );

private:
	int m_iCommandSocket;
	int m_iDataSocket;
	sockaddr_in m_CommandSockAddr;
	sockaddr_in m_DataSockAddr;
	int m_iFilePos;
	int m_iBytesRead;
	int m_iFileSize;
	char m_szRemoteFilePath[ 128 ];
	char m_szRemoteFileName[ 128 ];
	char m_szLocalFilePath[ 128 ];
	char m_szLocalFileName[ 128 ];
	char m_szServerName[ 128 ];
	char m_szUserName[ 128 ];
	char m_szPassword[ 128 ];
	FILE *m_pfLocalFile;
	int m_iStatus;
	int m_sendNewPortStatus;
	int m_findStart;
};

int Cftp::SendNewPort( void )
{
	unsigned long uTemp;
	char command[ 256 ];
	int i, iReply;

	if( m_sendNewPortStatus == 0 )
	{
		m_iDataSocket = socket( 2, 1, 0 );

		if( m_iDataSocket < 0 )
		{
			return( FTP_FAILED );
		}

		uTemp = 1;

		if( Use_Non_Blocking_Mode() )
		{
			if( ioctlsocket( m_iCommandSocket, 0x8004667eL, &uTemp ) == -1 )
			{
				return( FTP_FAILED );
			}
		}

		memset( &m_DataSockAddr, 0, sizeof( m_DataSockAddr ) );
		m_DataSockAddr.sin_family = 2;
		m_DataSockAddr.sin_addr = htonl( 0 );
		m_DataSockAddr.sin_port = 0;

		if( bind( m_iDataSocket, (struct sockaddr *)&m_DataSockAddr, sizeof( m_DataSockAddr ) ) < 0 )
		{
			return( FTP_FAILED );
		}

		i = sizeof( m_DataSockAddr );
		getsockname( m_iDataSocket, (struct sockaddr *)&m_DataSockAddr, &i );
		listen( m_iDataSocket, 5 );

		uTemp = 1;

		if( Use_Non_Blocking_Mode() )
		{
			if( ioctlsocket( m_iDataSocket, 0x8004667eL, &uTemp ) == -1 )
			{
				return( FTP_FAILED );
			}
		}

		m_sendNewPortStatus = 1;
	}

	if( m_sendNewPortStatus == 1 )
	{
		memset( command, 0, 256 );

		i = MyIPAddress( m_iCommandSocket );

		if( i == FTP_FAILED )
		{
			return( FTP_FAILED );
		}

		sprintf( command, (const char *)0x01132e9c,
				i & 0xFF,
				( i >> 8 ) & 0xFF,
				( i >> 16 ) & 0xFF,
				( i >> 24 ) & 0xFF,
				m_DataSockAddr.sin_port & 0xFF,
				m_DataSockAddr.sin_port >> 8 );

		if( ( (Rva00885920Class *)this )->d_00885530( command, strlen( command ) ) < 0 )
		{
			return( FTP_TRYING );
		}

		m_sendNewPortStatus = 2;
	}

	if( m_sendNewPortStatus == 2 )
	{
		if( ( RecvReply( command, 256, &iReply ) != FTP_SUCCEEDED ) ||
			( iReply != FTPREPLY_PORTOK ) )
		{
			return( FTP_TRYING );
		}

		m_sendNewPortStatus = 0;
	}

	return( FTP_SUCCEEDED );
}
