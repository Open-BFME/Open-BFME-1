// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: GameResultsCounter::~GameResultsCounter, retail 0x009DB350, 10
// bytes. The body carried only a machine byte-dump row;
// targets/game/reverse/reloc_names.csv holds the name with identity=real.
//
// One member, a Win32 handle at +0, closed through the import table. The handle
// is not null-checked and not cleared afterwards.

extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *handle);

class GameResultsCounter
{
public:
	~GameResultsCounter(void);

private:
	void *m_bfmeHandle;					// +0x00
};

// ??1GameResultsCounter@@QAE@XZ
GameResultsCounter::~GameResultsCounter(void)
{
	CloseHandle(m_bfmeHandle);
}
