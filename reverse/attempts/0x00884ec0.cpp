// ?PumpMessages@CDownload@@QAEJXZ
// partial score=0.45 date=2026-09-09
// slot0/4 of CDownload vtable @0x01117B30. Continues the 0.45 stash (which itself fixed
// signed/unsigned division to reach +0000..+0084 exact). This session: (1) added the
// explicit `extern "C" __declspec(dllimport) int __cdecl _strnicmp(...)` declaration used
// elsewhere in this codebase (parseModelConditionFlags.cpp, CftpRecvReply.cpp) -- without it
// tools/explain_mismatch.py's guarded-DIR32-import check for __imp___strnicmp cannot even be
// evaluated meaningfully (it fails on a garbage IAT-RVA lookup regardless, because the guard
// reads retail bytes at the SAME FILE OFFSET as our compiled __imp___strnicmp relocation site,
// and our function is still 18B short of retail well before that offset -- so the guard is a
// symptom of the still-open +0x85 issue below, not a separate bug; fixing the declaration is
// still correct hygiene and should be kept). (2) also made `timetaken` unsigned int (matching
// m_TimeStarted's type from the prior fix; consistent with retail's unsigned division, and
// does not change bytes yet since it's used downstream of the still-open blocker). NO byte
// progress this session -- confirmed prior worker's +0085 finding is still exactly the wall:
// retail hoists Listener (this+0x5c4) into ESI and reuses it as the OnError-call receiver
// across the vtable deref+call ('mov esi,[esi+0x5c4]; mov edx,[esi]; push 2; mov ecx,esi;
// call [edx]' -- 15 bytes), ours computes it straight into ECX and skips the extra
// register-to-register copy ('mov ecx,[esi+0x5c4]; mov edx,[ecx]; push 2; call [edx]' --
// 13 bytes, 2B shorter per occurrence, ~9 occurrences across the function = the 18B gap).
// NEW NEGATIVE RESULTS this session (both regress, do not retry):
//   (a) hoisting `Rva00884DownloadListener *listener = ...Listener;` unconditionally at the
//       TOP of the function (before or after the `reenter` reentrancy guard, before the
//       DOWNLOADSTATUS_GO block) breaks the ALREADY-EXACT +0000..+0084 prefix: MSVC adds a
//       THIRD callee-saved register push (ebx) to the prologue -- even on the immediate
//       `if (reenter != 0) return ...;` path that never touches Listener -- because MSVC's
//       register allocation is a whole-function pass sensitive to every local's existence,
//       not just its live range. Confirmed twice (before and after the guard-check line).
//   (b) hoisting the SAME local scoped to just the CONNECTING block (declared right after
//       `iResult = ...ConnectToServer(...)`, used by only the FTP_FAILED sub-branch) makes
//       MSVC load Listener EAGERLY right after the call, before the `iResult == FTP_SUCCEEDED`
//       branch test -- retail loads it lazily, only inside the failure branch. Wrong shape,
//       and the register is STILL ecx-based, not esi. The prior worker's "scoped inside just
//       the OnError block" attempt (also zero effect) plus this attempt now rule out every
//       plain local-declaration placement tried so far for this single call site.
// REMAINING IDEA (not tried): AGENTS.md explicitly warns this class of pure register-choice
// residue (no operand/shape difference, only WHICH register + an extra mov) is often NOT
// source-controllable at /O2. Before spending more time on locals, try the doc's G-flag sweep
// (/G5 /G6 /G7 /Ot /Og /Oy-) once, or accept this as the residue floor for this body.
// compiled 1047B vs target 1065B (18B short, unchanged from the 0.45 stash). t=40min
// model=sonnet score=0.45

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
