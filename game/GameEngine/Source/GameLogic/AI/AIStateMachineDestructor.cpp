// cl: /DNDEBUG /MD /EHsc

struct Coord3D
{
	float x;
	float y;
	float z;
};

class State
{
public:
	virtual ~State();
};

class Squad
{
public:
	virtual ~Squad();
	void deleteInstance() { delete this; }
};

struct AIUpdate
{
	void **m_vtable;
	char m_unknown[0x224 - 4];

	void notifyStateMachineChanged()
	{
		typedef void (__fastcall *Notify)(AIUpdate *);
		((Notify)m_vtable[0x224 / 4])(this);
	}
};

struct Object
{
	char m_unknown[0x204];
	AIUpdate *m_ai;
};

namespace _STL
{
	struct random_access_iterator_tag
	{
	};

	template <class InputIterator, class OutputIterator, class Distance>
	OutputIterator __copy(InputIterator, InputIterator, OutputIterator,
		const random_access_iterator_tag &, Distance *);

	extern template Coord3D *__copy<Coord3D *, Coord3D *, int>(Coord3D *, Coord3D *,
		Coord3D *, const random_access_iterator_tag &, int *);
}

class GoalPath
{
public:
	Coord3D *begin() { return m_start; }
	Coord3D *end() { return m_finish; }

	void erase()
	{
		Coord3D *start = m_start;
		Coord3D *finish = m_finish;
		_STL::random_access_iterator_tag tag;
		m_finish = _STL::__copy(finish, finish, start, tag, (int *)0);
	}

	Coord3D *m_start;
	Coord3D *m_finish;
	Coord3D *m_end;
};

class __declspec(novtable) AIStateMachine
{
	protected:
	virtual ~AIStateMachine();

	public:
	char m_unknown[0x0c];
	Object *m_owner;
	char m_gap14[0x30];
	GoalPath m_goalPath;
	void *m_goalWaypoint;
	Squad *m_goalSquad;
	State *m_temporaryState;
	int m_temporaryStateFrameEnd;

	void notifyOwner()
	{
		AIUpdate *ai = m_owner->m_ai;
		if (ai)
			ai->notifyStateMachineChanged();
	}
};

typedef void (__fastcall *AIStateMachineClear)(AIStateMachine *machine);
typedef void (__fastcall *AIStateMachineBaseClear)(AIStateMachine *machine);

extern void j_00027566();
extern void j_0001e47f();

// ??1AIStateMachine@@MAE@XZ
AIStateMachine::~AIStateMachine()
{
	if (m_temporaryState)
	{
		if (m_temporaryStateFrameEnd == -1)
			return;
		((AIStateMachineClear)j_00027566)(this);
	}

	((AIStateMachineBaseClear)j_0001e47f)(this);

	Squad *goalSquad = (m_goalPath.erase(),
		(Squad *)*(volatile Squad **)&m_goalSquad);
	m_goalWaypoint = 0;
	if (goalSquad)
		goalSquad->deleteInstance();
	m_goalSquad = 0;
	notifyOwner();
}
