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
class Snapshot
{
public:
	virtual ~Snapshot() {}
};

class BuffManager;

class BuffManagerRegistry
{
public:
	void add(BuffManager *manager);
	void remove(BuffManager *manager);
};

extern BuffManagerRegistry *TheGameClientClientUpdate;

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
	TheGameClientClientUpdate->add(this);
}

BuffManager::~BuffManager()
{
	TheGameClientClientUpdate->remove(this);
	m_mode = 0;
}
