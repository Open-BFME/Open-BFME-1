// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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
