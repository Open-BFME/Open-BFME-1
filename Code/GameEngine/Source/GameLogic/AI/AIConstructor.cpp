// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <list>

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	unsigned char padding[4];
};

class Snapshot
{
public:
	Snapshot()
	{
		*(volatile unsigned int *)this = 0x01073744;
	}
	virtual ~Snapshot() {}
	virtual void crc() {}
	virtual void xfer() {}
	virtual void loadPostProcess() {}
};

class TAiData
{
public:
	TAiData();
	char padding[0xfc];
};

class Pathfinder
{
public:
	Pathfinder();
	char padding[0x24f20];
};

#pragma comment(linker, "/alternatename:??0Pathfinder@@QAE@XZ=?j_0000df12@@YAXXZ")

class AI : public SubsystemInterface, public Snapshot
{
public:
	AI();
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}

private:
	Pathfinder *m_pathfinder;
	_STL::list<void *> m_groupList;
	TAiData *m_aiData;
	int m_nextGroupID;
	int m_nextFormationID;
};

AI::AI() :
	m_nextGroupID(0),
	m_nextFormationID(0)
{
	m_aiData = new TAiData;
	m_pathfinder = new Pathfinder;
}
