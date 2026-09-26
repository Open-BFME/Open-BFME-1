// cl: /Igame/Libraries/Source/WWVegas/WWLib /DNDEBUG /MD /EHsc

#include "string_base.h"

typedef long time_t;

extern "C" __declspec(dllimport) time_t __cdecl time(time_t *value);
extern "C" __declspec(dllimport) long __cdecl ftell(void *stream);
extern "C" __declspec(dllimport) int __cdecl fseek(void *stream, long offset, int origin);
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *buffer, unsigned int size,
	unsigned int count, void *stream);

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class RecorderClass {
	unsigned char m_prefix[0x0c];
	void *m_file;

protected:
	void logGameStart(AsciiString options);
};

static time_t startTime;

void RecorderClass::logGameStart(AsciiString options)
{
	if (!m_file)
		return;

	time(&startTime);
	unsigned int fileSize = ftell(m_file);
	if (!fseek(m_file, 8, 0))
		fwrite(&startTime, sizeof(time_t), 1, m_file);
	fseek(m_file, fileSize, 0);
}
