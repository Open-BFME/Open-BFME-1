// cl: /DNDEBUG /MD
// Retail 0x00173680: AIMoveToStateSA::computePath.  The constructor at
// 0x00173620 and the onEnter/update bodies at 0x001737C0/0x00173900 share
// vftable 0x01098FA8.  Slot +0x44 identifies this body as computePath.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
class AIUpdateInterface;

class StateMachine
{
public:
	char m_pad00[0x10];
	Object *m_owner;
	char m_pad14[0x10];
	Coord3D m_goalPosition;
};

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_position;
	char m_pad44[0x1c0];
	AIUpdateInterface *m_ai;
};

class Rva00027BC9Object : public Object
{
public:
	void getPosition(Coord3D *out);
};

template <int N>
class AIUpdateVTable : public AIUpdateVTable<N - 1>
{
public:
	virtual void unused(char (*)[N]);
};

template <>
class AIUpdateVTable<0>
{
};

class AIUpdateInterface : public AIUpdateVTable<122>
{
public:
	bool bfmeBlocksFormationRefresh();
	void requestPath(Coord3D *, bool);
	void reset();
	virtual void slot1e8();
};

class AI
{
public:
	char m_pad00[0x0c];
	class Rva00032B46Pathfinder *m_pathfinder;
};

class Rva00032B46Pathfinder
{
public:
	bool check(Object *, Coord3D *, bool, bool);
};

class Rva0003BC05State
{
public:
	bool check(Coord3D *, Object *);
};

class Rva0001246DAIUpdateInterface : public AIUpdateInterface
{
public:
	void reset();
};

class GameLogic
{
public:
	char m_pad00[0x3c];
	unsigned int m_frame;
};

class AIInternalMoveToState
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();

protected:
	char m_pad04[0x18];
	StateMachine *m_machine;
	char m_pad20[4];
	Coord3D m_goalPosition;
	char m_pad30[0x1d];
	unsigned char m_waitingForPath;

	bool getAdjustsDestination() const;
};

class Rva00173620State : public AIInternalMoveToState
{
public:
	unsigned int m_okToRepathTimes;
	unsigned char m_checkForPath;

	virtual bool computePath();
};

extern AI *TheAI;
extern GameLogic *TheBfmeGameLogic;
extern void j_0000e570();
extern void j_00027bc9();
extern void j_00032b46();
extern void j_0003bc05();
extern void j_0003bcff();
extern void j_0001246d();

typedef Object *(__fastcall *GetGoalObject)(StateMachine *);
bool Rva00173620State::computePath()
{
	if (m_waitingForPath)
		return true;

	if (((GetGoalObject)j_0000e570)(m_machine))
	{
		Rva00027BC9Object *goal = (Rva00027BC9Object *)((GetGoalObject)j_0000e570)(m_machine);
		m_goalPosition = goal->m_position;
		goal->getPosition(&m_goalPosition);
	}
	else
	{
		m_goalPosition = m_machine->m_goalPosition;
	}

	Object *owner = m_machine->m_owner;
	if (TheAI->m_pathfinder->check(
		owner, &m_goalPosition, false, false) ||
		((Rva0003BC05State *)this)->check(&m_goalPosition, owner))
	{
		AIUpdateInterface *ai = m_machine->m_owner->m_ai;
		ai->requestPath(&m_goalPosition, getAdjustsDestination());
		unsigned char waiting = *(reinterpret_cast<unsigned char *>(ai) + 0x31e);
		m_waitingForPath = waiting;
		((Rva0001246DAIUpdateInterface *)ai)->reset();
		return true;
	}

	m_checkForPath = 1;
	m_okToRepathTimes = TheBfmeGameLogic->m_frame + 0x32;
	AIUpdateInterface *ai = owner->m_ai;
	if (!ai)
		return true;
	if (!ai->bfmeBlocksFormationRefresh())
		return true;
	ai->slot1e8();
	return true;
}
