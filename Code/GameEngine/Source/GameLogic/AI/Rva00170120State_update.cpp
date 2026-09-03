// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned char Bool;
typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

extern const Real BfmeZeroRange;
extern void j_0000e570();
extern void j_0002cc23();

struct Rva00170120Object;

class Rva00170120Locomotor
{
public:
	Real check(Rva00170120Object *owner);
};

#pragma comment(linker, "/alternatename:?check@Rva00170120Locomotor@@QAEMPAURva00170120Object@@@Z=?j_0001a334@@YAXXZ")

struct Rva00170120AIUpdate
{
	void **m_vtable;
	unsigned char m_unreconstructed_004[0x1cc - 4];
	Rva00170120Locomotor *m_curLocomotor;
};

struct Rva00170120Object
{
	unsigned char m_unreconstructed_000[0x204];
	Rva00170120AIUpdate *m_ai;
};

struct Rva00170120StateMachine
{
	unsigned char m_unreconstructed_000[0x10];
	Rva00170120Object *m_owner;
};

class Rva00170120State
{
	unsigned char m_unreconstructed_004[0x18];
	Rva00170120StateMachine *m_machine;
	unsigned char m_unreconstructed_020[8];
	int m_mode;
	Bool m_check;

public:
	virtual StateReturnType update();
};

typedef Rva00170120Object *(__fastcall *Rva00170120GetGoal)(Rva00170120StateMachine *);
typedef StateReturnType (__fastcall *Rva00170120Tail)(Rva00170120State *);

StateReturnType Rva00170120State::update()
{
	Rva00170120Object *owner = m_machine->m_owner;
	Rva00170120AIUpdate *ai = owner->m_ai;
	Rva00170120Locomotor *curLocomotor = ai->m_curLocomotor;
	int check;
	if (curLocomotor)
	{
		check = curLocomotor->check(owner) == BfmeZeroRange;
	}
	else
		check = 0;

	m_check = check;
	Rva00170120Object *goal = ((Rva00170120GetGoal)j_0000e570)(m_machine);
	if (m_mode && goal == 0)
		return STATE_FAILURE;

	if (m_mode == 2)
		return ((Rva00170120Tail)j_0002cc23)(this);
	return STATE_CONTINUE;
}
