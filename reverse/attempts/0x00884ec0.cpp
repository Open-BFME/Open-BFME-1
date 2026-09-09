// ?PumpMessages@CDownload@@QAEJXZ
// partial score=0.45 date=2026-09-09
// slot0/4 of CDownload vtable @0x01117B30. This is the exact TU state (Code/Libraries/Source/WWVegas/WWDownload/CDownloadDownloadFile.cpp lines ~99-318 as of this session), one increment ahead of the prior 0.5 stash. NEW FINDING this session: the prior worker's stated 'ONE root cause' (edi vs ebp zero-register hoisting) was only HALF the picture. Fix #1 (this stash): declaring m_TimeStarted and g_bfmeNowVNH's return as unsigned int (matching retail's unsigned magic-number division by 1000 at the timetaken computation -- retail emits 'mul ecx' after 'mov eax,0x10624dd3', unsigned reciprocal-multiply for /1000; our prior int-typed version emitted 'imul ecx', the signed form) ALSO fixes the edi/ebp register selection: bytes +0000..+0084 now match retail EXACTLY (verified via tools/probe.py, no diffs in that whole span, whereas the prior stash mismatched starting at +0008 push-order). This confirms the earlier register theory was a downstream SYMPTOM of the signed/unsigned mismatch, not an independent scheduling residue -- the type fix should be kept by whoever continues this body.
// Fix #2 (NOT yet solved, new first diff after Fix #1, at +0085): once past the CONNECTING-state block, retail hoists 'Listener' (this+0x5c4) into ESI and reuses it as the vtable receiver for the OnError call ('mov esi,[esi+0x5c4]; mov edx,[esi]; push 2; mov ecx,esi; call [edx]'), i.e. it caches the reinterpret_cast<Listener> pointer in a register ACROSS the vtable load and the call. Our compile instead computes it straight into ECX inline each time and never revisits ESI. Tried naming a local 'Rva00884DownloadListener *listener = reinterpret_cast<...>(Listener);' scoped inside just the OnError-on-FTP_FAILED block: ZERO effect on codegen (MSVC still folds it back to the same ECX-direct form) -- same negative result the prior worker got for Cftp*/IDownload* locals, so this is not simply a naming problem; it likely needs the local hoisted OUTSIDE the inner if/else (i.e. one Listener* fetched once at the top of the CONNECTING block, reused by both the success and failure paths) to force MSVC to keep it live in a register across the branch. NOT tried yet: hoisting one shared local per per-state block (not per call site) for Listener AND for Ftp; this is the next lever to try before any G-flag sweep.
// compiled 1047B vs target 1065B (18B short with fix #1 applied; was 1057B/8B short before). The larger raw gap is because fix #2's block is now the visible blocker across a much longer span (was previously masked because the guarded-import identity check couldn't even get past the pre-fix-#1 relocation-layout drift far enough to report it cleanly). t=45min model=sonnet (this session, continuing from the 0.5 stash) score=0.45 (numerically closer to 0 is a smaller size gap, but the earlier score of 0.5 predates this session's confirmation that the true first-diff mechanism is unsigned-vs-signed division, not raw register scheduling -- keep fix #1, hunt fix #2 next).
// ?PumpMessages@CDownload@@QAEJXZ present-unmatched

extern unsigned int(__cdecl *g_bfmeNowVNH)();

extern "C" __declspec(dllimport) long __stdcall MulDiv(long, long, long);

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
