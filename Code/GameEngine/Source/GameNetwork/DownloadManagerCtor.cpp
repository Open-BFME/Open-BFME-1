// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#define Matrix4x4 Matrix4
#define _STLP_NO_EXCEPTIONS 1
#include "PreRTS.h"

#include "GameClient/GameText.h"
#include "GameNetwork/DownloadManager.h"
#include "string_base.h"

// BFME inlines UnicodeString's copy-set through the wide StringBase body at
// 0x00888530.  The reference UnicodeString declaration otherwise leaves an
// out-of-line UnicodeString::set call, whose ledger alias is the narrow body.
inline void UnicodeString::set( const UnicodeString &stringSrc )
{
	reinterpret_cast<StringBase<WideChar> &>( *this ).set(
		reinterpret_cast<const StringBase<WideChar> &>( stringSrc ) );
}

DownloadManager::DownloadManager()
{
	m_download = NEW CDownload(this);
	m_wasError = m_sawEnd = false;
	
	//Added By Sadullah Nader
	//Initializations missing and needed
	
	m_queuedDownloads.clear();
	
	//

	m_statusString = TheGameText->fetch("FTP:StatusIdle");

	// ----- Initialize Winsock -----
	m_winsockInit = true;
	WORD verReq = MAKEWORD(2, 2);
	WSADATA wsadata;

	int err = WSAStartup(verReq, &wsadata);
	if (err != 0)
	{
		m_winsockInit = false;
	}
	else
	{
		if ((LOBYTE(wsadata.wVersion) != 2) || (HIBYTE(wsadata.wVersion) !=2))
		{
			WSACleanup();
			m_winsockInit = false;
		}
	}

}
