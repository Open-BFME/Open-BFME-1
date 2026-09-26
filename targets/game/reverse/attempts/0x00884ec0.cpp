// ?PumpMessages@CDownload@@QAEJXZ
// partial score=0.45 date=2026-09-20
// slot0/4 of CDownload vtable @0x01117B30. Continuing the 0.45 stash (5th session on this
// body). This session synced the actual Code/ TU (CDownloadDownloadFile.cpp) with the prior
// stash's two fixes -- `unsigned int timetaken` and the explicit `_strnicmp` dllimport decl --
// which were sitting only in the stash and not yet applied to the tree; that alone reproduces
// the 0.45/1047B state exactly (verified: `python3 tools/probe.py ... 0x00884EC0` -> 1047 vs
// 1065, 18B short, identical evidence to the prior bank).
// NEW THIS SESSION (both negative):
//   (a) Declared a `Rva00884DownloadListener *listener = ...Listener;` local scoped to the
//       INNERMOST block, immediately adjacent to the call, at all four call sites that show
//       the ESI-reuse pattern below (CONNECTING-fail OnError, LOGIN-fail OnError, FINDFILE-fail
//       OnError, and the DOWNLOADSTATUS_DOWNLOADING OnStatusUpdate wrapped in its own `{ }`).
//       This is narrower than both prior sessions' placements (top-of-function, and top-of-
//       CONNECTING-block-before-the-branch-test): the local's live range here is confined to a
//       single straight-line tail with no intervening branch. Zero byte effect -- probe.py
//       reports the identical 1047B/18B-short result, same first-diff evidence at +0x85.
//       MSVC 7.1's register allocator clearly does not key off block-local declaration scope at
//       all for this call; reverted (kept out of the committed tree to keep the diff minimal).
//   (b) `python3 tools/shape_family_levers.py CDownloadDownloadFile.cpp --families
//       sib,register,bool,test,copy,store,loop,branch,constant,frame` produced only 6 choices,
//       ALL store-reorder pairs (independent field-clear statement swaps) -- none touch the
//       Listener/OnError call sites at all, because the family detector keys off adjacent
//       independent stores, not virtual-call receiver materialization. Ran shape_search.py over
//       all 6 choices (8 trial combinations via the plateau search) anyway: no improving
//       candidate, confirmed by evidence.json.
// ROOT-CAUSE REFINEMENT (disassembled the full retail 1065B body via dis_retail.py, mapped all
// 9 Listener/vtable call sites): the "this dies right after this call -> retail hoists Listener
// into ESI, then copies to ECX" pattern is NOT a uniform, source-visible rule. It holds for
// +0x85 (OnError/COULDNOTCONNECT), +0xf6 (OnError/LOGINFAILED), +0x163 (OnError/NOSUCHFILE) and
// +0x268 (OnStatusUpdate/DOWNLOADING) -- all early in the function, before EBX/EBP get pushed at
// +0x118/+0x119. But the OTHER "this-dies-immediately" call, OnError(DOWNLOADEVENT_TCPERROR) at
// +0x389 (reached by a forward jump from the DOWNLOADING block, physically laid out AFTER the
// m_predictionTimes averaging block, with EBX/EBP already pushed and EDI repurposed to cache
// g_bfmeNowVNH's function pointer instead of a stable 0-constant), uses the SAME direct
// ECX-load shape our code already produces -- no ESI hoist. So the lever is not "does `this`
// die after the call": something about EBX/EBP occupancy or EDI's changed role by that point in
// the whole-function allocation pass flips the choice back. This is exactly the class of
// residue AGENTS.md/docs/shape_levers.md calls compiler-internal register-identity choice, now
// confirmed non-uniform even within one function, across 5 independent sessions (t=70,45,40,7
// and this one) with zero net byte movement since the 0.5->0.45 signed/unsigned fix landed.
// Everything else in the body (control flow, member offsets, enum values, all 5 Cftp callees,
// the two OnEnd/OnQueryResume/OnProgressUpdate calls with a pre-loaded ECX across intervening
// field-clear stores) is confirmed correct against the disassembly line-by-line; the ONLY open
// residue is this register-choice gap. compiled 1047B vs target 1065B (18B short, unchanged).
// t=35min model=claude-sonnet-5 score=0.45

// cl: /DNDEBUG /MD /EHs-c- /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
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
