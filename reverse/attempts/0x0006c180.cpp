// ?d_0006c180@@YAXXZ
// partial score=0.9953 date=2026-09-18
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /Ireference/shims/sweep

#include <windows.h>
#include <string.h>

extern "C" __declspec(dllimport) char *__stdcall GetEnvironmentStrings(void);
__declspec(dllimport) void __cdecl bfmeFree1035(void *);
extern "C" void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)

class GameEngine
{
public:
	void Rva0006C180(void *value);

private:
	char m_padding[0x10];
	int m_childProcessCount;
	HANDLE m_childProcesses[7];
};

void GameEngine::Rva0006C180(void *value)
{
	__declspec(align(8)) char modulePath[0x200];

	if (m_childProcessCount > 0)
		return;
	if ((int)value < 1)
		return;
	if ((int)value > 7)
		value = (void *)7;

	GetModuleFileNameA(0, modulePath, 0x200);
	char *environment = GetEnvironmentStrings();
	int environmentLength = 0;
	{
		char *entry = environment;
		while (*entry != 0)
		{
			int length = (int)strlen(entry);
			environmentLength += length + 1;
			entry += length + 1;
		}
	}

	environmentLength += 0x3e8;
	char *commandLine = GetCommandLineA();
	char *environmentCopy;
	environmentCopy = (char *)malloc(environmentLength);
	int count = 0;
	if ((int)value > 0)
	{
		PROCESS_INFORMATION processInformation;
		int number = 1;
		HANDLE *processSlot = m_childProcesses;
		count = (int)value;
		for (int remaining = (int)value; remaining > 0; --remaining)
		{
			char *cursor = environmentCopy;
			cursor += sprintf(cursor, "_EA_RTS_HEADLESS=%i", number) + 1;
			cursor += sprintf(cursor, "_EA_RTS_FILENAME=");
			GetModuleFileNameA(0, cursor, 0x100);
			char *extension = strrchr(cursor, '.');
			int suffixLength = sprintf(extension, "-%i.exe", number);
			cursor = extension + suffixLength + 1;

			{
				char *entry = environment;
				while (*entry != 0)
				{
					do
						*cursor++ = *entry++;
					while (cursor[-1] != 0);
				}
			}
			*cursor = 0;

			STARTUPINFOA startupInformation;
			memset(&startupInformation, 0, sizeof(startupInformation));
			startupInformation.cb = 0x44;
			CreateProcessA(modulePath, commandLine, 0, 0, 0, 0x208,
				environmentCopy, 0, &startupInformation, &processInformation);
			*processSlot++ = processInformation.hProcess;
			++number;
		}
	}

	m_childProcessCount = count;
	bfmeFree1035(environmentCopy);
}
