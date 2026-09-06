// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

#include "PreRTS.h"
#include <cstdio>

// Retail layout from WWDownload/ftp.h (Cftp is a friend-only leaf class; no
// other Cftp member has been reconstructed yet, so only the fields ZeroStuff
// actually touches are given real names/offsets here).
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDownload/ftp.h
class Cftp
{
public:
    Cftp();
    virtual ~Cftp();

    int AsyncGetHostByName( char *szName, struct sockaddr_in &address );

private:
    int m_iCommandSocket;
    int m_iDataSocket;

    unsigned char m_CommandSockAddr[16]; // struct sockaddr_in
    unsigned char m_DataSockAddr[16];    // struct sockaddr_in

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

    void ZeroStuff();
};

struct sockaddr_in
{
    unsigned short sin_family;
    unsigned short sin_port;
    unsigned long sin_addr;
    unsigned char sin_zero[ 8 ];
};

static sockaddr_in gThreadAddress;
static int gThreadFlag;
static unsigned long gThreadId;
static int gThreadState;

extern "C" __declspec(dllimport) void *__stdcall CreateThread(
    void *, unsigned long, void *, void *, unsigned long, unsigned long *);

enum
{
    FTPSTAT_INIT = 0
};

Cftp::Cftp()
{
    ZeroStuff();
}

// ?ZeroStuff@Cftp@@AAEXXZ
void Cftp::ZeroStuff()
{
    m_iBytesRead = 0;
    m_iFileSize = 0;
    m_szRemoteFilePath[0] = (char)0;
    m_szRemoteFileName[0] = (char)0;
    m_szLocalFilePath[0] = (char)0;
    m_szLocalFileName[0] = (char)0;
    m_szServerName[0] = (char)0;
    m_szUserName[0] = (char)0;
    m_szPassword[0] = (char)0;
    m_iDataSocket = 0;
    m_iCommandSocket = 0;
    m_iFilePos = 0;
    m_iStatus = FTPSTAT_INIT;
    m_sendNewPortStatus = 0;
    m_pfLocalFile = NULL;
    m_findStart = 0;
    memset(&m_CommandSockAddr, 0, sizeof(m_CommandSockAddr));
    memset(&m_DataSockAddr, 0, sizeof(m_DataSockAddr));
}

int Cftp::AsyncGetHostByName( char *szName, struct sockaddr_in &address )
{
    if ( gThreadState == 0 )
    {
        gThreadFlag = 0;
        memset( &gThreadAddress, 0, sizeof( gThreadAddress ) );

        if ( CreateThread( NULL, 0, (void *)0x00C85430, szName, 0,
                &gThreadId ) == NULL )
        {
            return 0x80040001;
        }
        gThreadState = 1;
    }
    if ( gThreadState == 1 )
    {
        if ( gThreadFlag )
        {
            address = gThreadAddress;
            address.sin_family = 2;
            gThreadState = 0;
            return 0;
        }
    }
    return 0x80040002;
}
