// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// AI::~AI at retail RVA 0x0014C3B0 and its scalar-deleting wrapper 0x0014C600.
// The wrapper calls this complete destructor through ILT 0x00002527; both
// are emitted from this one definition of the AI subsystem.
// The constructor at 0x0014C170 and vtable 0x010959A8 identify the owner.

class SubsystemInterface
{
public:
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
	virtual ~Snapshot() {}
	virtual void crc() {}
	virtual void xfer() {}
	virtual void loadPostProcess() {}
};

class PathfindServicesInterface
{
public:
	virtual void findPath() = 0;
	virtual void findClosestPath() = 0;
	virtual void findAttackPath() = 0;
	virtual void patchPath() = 0;
	virtual void findSafePath() = 0;
};

class Pathfinder : PathfindServicesInterface, public Snapshot
{
};

class TAiData : public Snapshot
{
private:
	char padding[0xf4];

public:
	TAiData *m_next;
};

namespace _STL
{
	template <class T>
	class allocator
	{
	};

	template <class Type, class Allocator>
	class _List_base
	{
	public:
		~_List_base();
	};

	template <class Type, class Allocator>
	class list : public _List_base<Type, Allocator>
	{
	public:
		~list() {}
	};
}

typedef _STL::list<int, _STL::allocator<int> > AIGroupList;

class AI : public SubsystemInterface, public Snapshot
{
public:
	virtual ~AI();
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}

private:
	Pathfinder *m_pathfinder;
	AIGroupList m_groupList;
	TAiData *m_aiData;
	unsigned int m_nextGroupID;
	int m_nextFormationID;
};

AI::~AI()
{
	if (m_pathfinder)
		delete m_pathfinder;
	m_pathfinder = 0;

	while (m_aiData)
	{
		TAiData *current = m_aiData;
		m_aiData = m_aiData->m_next;
		delete current;
	}
}
