// ?PumpMessages@CDownload@@QAEJXZ
// partial score=0.5 date=2026-09-09
// slot0/4 of CDownload vtable @0x01117B30 (siblings DownloadFile at slot2 landed in this same TU). This is the exact TU state (Code/Libraries/Source/WWVegas/WWDownload/CDownloadDownloadFile.cpp lines ~99-318). Ported CDownload::PumpMessages from reference/CnC_Generals_Zero_Hour GeneralsMD Download.cpp near-verbatim (member layout, enum values, control flow all confirmed against retail disasm line-by-line). All 5 real callees identified from retail bytes by push-order/signature analysis and pinned: ConnectToServer(0x00885B50), LoginToServer(0x00885D90), FindFile(0x00886020, verified real ghidra boundary sub esp,0x118;push ebp;mov ebp,ecx prologue), FileRecoveryPosition(0x00886A20), GetNextFileBlock(0x00886520); MulDiv via __declspec(dllimport)+__imp__MulDiv@12 pin. RestartFrom and m_iCommandSocket read modelled as raw offset+0x2c/+4 access (both inlined at retail too). compiled 1057B vs target 1065B (8B short), ~279/310 disassembly lines differ but it is ONE root cause: retail hoists a zero constant into edi for the whole function (reused ~15x for 'reenter=0' stores and the initial != 0 test) and pushes esi,edi as the first two callee-saved registers; this port's compiler instead picks ebp for the same zero role and pushes ebp,esi (this pointer still lands in esi in both -- only the zero-register identity differs). Tried: matching ZH source local-declaration order exactly (already matched); using explicit Cftp*/IDownload* locals instead of inline reinterpret_cast at each call site (made it WORSE, size gap grew from 1 to 8 bytes with extra sub esp -- reverted). Classic callee-saved register-identity scheduling residue, same class as 0x00949F30 this session; matches argument-shuttle-register.md's dominant-blocker pattern. Next lever to try: none safe to sweep in this shared TU (the // cl: flags line is shared with the already-matched DownloadFile sibling in the same file -- a flag sweep risks breaking that landed row; would need a scratch TU to test flags in isolation first).
// ?PumpMessages@CDownload@@QAEJXZ present-unmatched

extern int(__cdecl *g_bfmeNowVNH)();

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
	int timetaken = 0;
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
