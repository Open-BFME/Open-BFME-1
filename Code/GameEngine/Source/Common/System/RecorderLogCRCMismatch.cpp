// cl: /DNDEBUG /MD /EHsc

extern "C" __declspec(dllimport) long __cdecl ftell(void *stream);
extern "C" __declspec(dllimport) int __cdecl fseek(void *stream, long offset, int origin);
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *buffer, unsigned int size,
	unsigned int count, void *stream);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char prefix[0x3c];
	unsigned int frame;
};

extern GameLogic *TheGameLogic;
extern int OpenBFME5_netCRCInterval;

// BFME extends the recorder state after ReplayGameInfo with the CRC interval
// and the frame at which the mismatch was observed.
class RecorderClass
{
	unsigned char prefix[0x0c];
	void *m_file;
	unsigned char replayState[0x298 - 0x10];
	int m_networkCRCInterval;
	unsigned int m_crcMismatchFrame;

public:
	void logCRCMismatch(void);
};

void RecorderClass::logCRCMismatch(void)
{
	if (!m_file)
		return;

	m_networkCRCInterval = OpenBFME5_netCRCInterval;
	m_crcMismatchFrame = TheGameLogic->frame;
	unsigned int fileSize = ftell(m_file);

	if (!fseek(m_file, 20, 0))
		fwrite(&m_networkCRCInterval, sizeof(m_networkCRCInterval), 1, m_file);

	if (!fseek(m_file, 24, 0))
		fwrite(&m_crcMismatchFrame, sizeof(m_crcMismatchFrame), 1, m_file);

	fseek(m_file, fileSize, 0);
}
