// cl: /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: DownloadManager.cpp //////////////////////////////////////////////////////
// Generals download manager code
// Author: Matthew D. Campbell, July 2002

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

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

DownloadManager *TheDownloadManager;

DownloadManager::~DownloadManager()
{
	delete m_download;
	if (m_winsockInit)
	{
		WSACleanup();
		m_winsockInit = false;
	}
}

// ?init@DownloadManager@@QAEXXZ present-unmatched
void DownloadManager::init( void )
{
}

// ?reset@DownloadManager@@QAEXXZ present-unmatched
void DownloadManager::reset( void )
{
}

HRESULT DownloadManager::update( void )
{
	return m_download->PumpMessages();
}

// ?downloadFile@DownloadManager@@UAEJVAsciiString@@00000_N@Z present-unmatched
HRESULT DownloadManager::downloadFile( AsciiString server, AsciiString username, AsciiString password, AsciiString file, AsciiString localfile, AsciiString regkey, Bool tryResume )
{
	return m_download->DownloadFile( server.str(), username.str(), password.str(), file.str(), localfile.str(), regkey.str(), tryResume );
}

// ?queueFileForDownload@DownloadManager@@QAEXVAsciiString@@00000_N@Z present-unmatched
void DownloadManager::queueFileForDownload( AsciiString server, AsciiString username, AsciiString password, AsciiString file, AsciiString localfile, AsciiString regkey, Bool tryResume )
{
	QueuedDownload q;
	q.file = file;
	q.localFile = localfile;
	q.password = password;
	q.regKey = regkey;
	q.server = server;
	q.tryResume = tryResume;
	q.userName = username;

	m_queuedDownloads.push_back(q);
}

// byte-exact reconstruction: game/GameEngine/Source/GameClient/DownloadManagerThunks.cpp
// ?downloadNextQueuedFile@DownloadManager@@QAEJXZ present-unmatched
HRESULT DownloadManager::downloadNextQueuedFile( void )
{
	QueuedDownload q;
	std::list<QueuedDownload>::iterator it = m_queuedDownloads.begin();
	if (it != m_queuedDownloads.end())
	{
		q = *it;
		m_queuedDownloads.pop_front();
		m_wasError = m_sawEnd = false;
		return downloadFile( q.server, q.userName, q.password, q.file, q.localFile, q.regKey, q.tryResume );
	}
	else
	{
		DEBUG_CRASH(("Starting non-existent download!"));
		return S_OK;
	}
}

AsciiString DownloadManager::getLastLocalFile( void )
{
	char buf[256] = "";
	m_download->GetLastLocalFile(buf, 256);
	return buf;
}

HRESULT DownloadManager::OnError( Int error )
{
	m_wasError = true;
	AsciiString s = "FTP:UnknownError";
	switch (error)
	{
		case DOWNLOADEVENT_NOSUCHSERVER:
			s = "FTP:NoSuchServer";
			break;
		case DOWNLOADEVENT_COULDNOTCONNECT:
			s = "FTP:CouldNotConnect";
			break;
		case DOWNLOADEVENT_LOGINFAILED:
			s = "FTP:LoginFailed";
			break;
		case DOWNLOADEVENT_NOSUCHFILE:
			s = "FTP:NoSuchFile";
			break;
		case DOWNLOADEVENT_LOCALFILEOPENFAILED:
			s = "FTP:LocalFileOpenFailed";
			break;
		case DOWNLOADEVENT_TCPERROR:
			s = "FTP:TCPError";
			break;
		case DOWNLOADEVENT_DISCONNECTERROR:
			s = "FTP:DisconnectError";
			break;
	}
	m_errorString = TheGameText->fetch(s);
	DEBUG_LOG(("DownloadManager::OnError(): %s(%d)\n", s.str(), error));
	return S_OK;
}

HRESULT DownloadManager::OnEnd()
{
	m_sawEnd = true;
	DEBUG_LOG(("DownloadManager::OnEnd()\n"));
	return S_OK;
}

HRESULT DownloadManager::OnQueryResume()
{
	DEBUG_LOG(("DownloadManager::OnQueryResume()\n"));
	//return DOWNLOADEVENT_DONOTRESUME;
	return DOWNLOADEVENT_RESUME;
}

HRESULT DownloadManager::OnProgressUpdate( Int bytesread, Int totalsize, Int timetaken, Int timeleft )
{
	DEBUG_LOG(("DownloadManager::OnProgressUpdate(): %d/%d %d/%d\n", bytesread, totalsize, timetaken, timeleft));
	return S_OK;
}

HRESULT DownloadManager::OnStatusUpdate( Int status )
{
	AsciiString s = "FTP:StatusNone";
	switch (status)
	{
		case DOWNLOADSTATUS_CONNECTING:
			s = "FTP:StatusConnecting";
			break;
		case DOWNLOADSTATUS_LOGGINGIN:
			s = "FTP:StatusLoggingIn";
			break;
		case DOWNLOADSTATUS_FINDINGFILE:
			s = "FTP:StatusFindingFile";
			break;
		case DOWNLOADSTATUS_QUERYINGRESUME:
			s = "FTP:StatusQueryingResume";
			break;
		case DOWNLOADSTATUS_DOWNLOADING:
			s = "FTP:StatusDownloading";
			break;
		case DOWNLOADSTATUS_DISCONNECTING:
			s = "FTP:StatusDisconnecting";
			break;
		case DOWNLOADSTATUS_FINISHING:
			s = "FTP:StatusFinishing";
			break;
		case DOWNLOADSTATUS_DONE:
			s = "FTP:StatusDone";
			break;
	}
	m_statusString = TheGameText->fetch(s);
	DEBUG_LOG(("DownloadManager::OnStatusUpdate(): %s(%d)\n", s.str(), status));
	return S_OK;
}
