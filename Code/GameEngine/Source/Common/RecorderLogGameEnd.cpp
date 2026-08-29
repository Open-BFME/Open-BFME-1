// cl: /DNDEBUG /MD /EHsc

typedef long time_t;

extern "C" __declspec(dllimport) time_t __cdecl time(time_t *value);
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class RecorderClass
{
	unsigned char prefix[0x0c];
	void *m_file;

protected:
	void logGameEnd(void);
};

// ?logGameEnd@RecorderClass@@ present-unmatched
void RecorderClass::logGameEnd(void)
{
	if (!m_file)
		return;

	time_t endTime;
	time(&endTime);
	unsigned int duration = TheGameLogic->frame;
	unsigned int fileSize = ftell(m_file);

	if (!fseek(m_file, 12, 0))
		fwrite(&endTime, sizeof(time_t), 1, m_file);

	if (!fseek(m_file, 16, 0))
		fwrite(&duration, sizeof(unsigned int), 1, m_file);

	fseek(m_file, fileSize, 0);
}
