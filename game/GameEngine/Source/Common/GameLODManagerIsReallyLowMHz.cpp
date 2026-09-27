// cl: /DNDEBUG /MD /EHsc
// Open-BFME: GameLODManager::isReallyLowMHz() reads the BFME manager's
// CPU-frequency and low-MHz threshold fields at +0x171C and +0x1734.

typedef bool Bool;

class GameLODManager
{
public:
    Bool isReallyLowMHz() const;

private:
    char m_padding0[0x171C];
    int m_cpuFreq;
    char m_padding1[0x14];
    int m_reallyLowMHz;
};

Bool GameLODManager::isReallyLowMHz() const
{
    return m_cpuFreq < m_reallyLowMHz;
}

extern GameLODManager *TheGameLODManager;

// ?Rva00752E10ClampLod@@YAHXZ
int Rva00752E10ClampLod()
{
	int value = *reinterpret_cast<const int *>(reinterpret_cast<const char *>(TheGameLODManager) + 0x170c) - 1;
	if (value < 0) return 0;
	if (value > 2) return 2;
	return value;
}
