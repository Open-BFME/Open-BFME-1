// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class BuffEntry
{
public:
	BuffEntry();
	~BuffEntry();

private:
	char m_retailLayout[0x44];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface() {}
};

class BuffManager;

class BuffManagerRegistry
{
public:
	void add(BuffManager *manager);
	void remove(BuffManager *manager);
};

extern BuffManagerRegistry *TheGameClientClientUpdate;

class BuffManager : public SubsystemInterface
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
