// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class BuffEntry
{
public:
	BuffEntry();
	~BuffEntry();

private:
	char m_retailLayout[0x44];
};

// The base table these destructors restore last is 0x01073744, Snapshot's
// (??0Snapshot at 0x0006B180 installs it); SubsystemInterface's is 0x01141640.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void crc(Xfer *) = 0;
	virtual void xfer(Xfer *) = 0;
	virtual void loadPostProcess() = 0;
};

class BuffManager;

class BuffManagerRegistry
{
public:
	void add(BuffManager *manager);
	void remove(BuffManager *manager);
};

// 0x012F1464 is EA's `GameClient *TheGameClient`
// (?TheGameClient@@3PAVGameClient@@A, defined in GameClient.cpp); this TU
// keeps its BuffManagerRegistry view of it and casts at the use.
class GameClient;
extern GameClient *TheGameClient;
static inline BuffManagerRegistry *theGameClientView() { return (BuffManagerRegistry *)TheGameClient; }

class BuffManager : public Snapshot
{
public:
	BuffManager(int mode);
	virtual ~BuffManager();

private:
	int m_mode;
	BuffEntry m_entries[6];
};

BuffManager::BuffManager(int mode) : m_mode(mode)
{
	theGameClientView()->add(this);
}

BuffManager::~BuffManager()
{
	theGameClientView()->remove(this);
	m_mode = 0;
}
