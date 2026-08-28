// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

typedef void *HANDLE;
typedef int BOOL;

extern "C" __declspec(dllimport) BOOL __stdcall TerminateProcess(
	HANDLE process, unsigned int exitCode);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameEngine.h
class GameEngine
{
public:
	virtual void slot00(void);

private:
	void _bfme_terminateChildProcesses(void);

	char m_unknown04[0x0C];
	int m_childProcessCount;
	HANDLE m_childProcesses[7];
};

void GameEngine::_bfme_terminateChildProcesses(void)
{
	for (int index = 0; index < m_childProcessCount; ++index)
		TerminateProcess(m_childProcesses[index], 0);
	m_childProcessCount = 0;
}
