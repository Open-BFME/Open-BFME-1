// cl: /DNDEBUG /MD
//
// Address-derived recovery for the BFME goal setup body at 0x002BC260.

extern void j_0000a795();
extern void j_00049ae9();

class Rva002BC260Global
{
public:
	void initialize(void *a, void *b, void *c, void *d, void *e, unsigned char f);
};

class Rva002BC260Goal
{
public:
	virtual void unused000();
	virtual void unused004();
	virtual void configure(int a, int b, int c, int d, int e, int f);
	void finalize();

private:
	unsigned char m_unreconstructed00c[0x50];
};

struct Rva002BC260Coord3D
{
	float x;
	float y;
	float z;
};

class Rva002BC260GoalOwner
{
public:
	void run(void *arg1, void *arg2, void *arg3, unsigned char arg4);

private:
	unsigned char m_unreconstructed000[8];
	void *m_goalArguments;
	unsigned char m_unreconstructed00c[0x3f4];
	Rva002BC260Goal m_goal;
	Rva002BC260Coord3D m_source;
	unsigned char m_unreconstructed460[8];
	int m_unreconstructed468;
	unsigned char m_unreconstructed46c;
	unsigned char m_unreconstructed46d[0xf];
	Rva002BC260Coord3D m_destination;
};

class AerialPathfinder;
extern AerialPathfinder *TheAerialPathfinder;

void Rva002BC260GoalOwner::run(void *arg1, void *arg2, void *arg3, unsigned char arg4)
{
	Rva002BC260Goal *goal = &m_goal;
	typedef void (Rva002BC260Global::*Init)(void *, void *, void *, void *, void *, unsigned char);
	union { void (*fn)(); Init call; } init = { j_0000a795 };
	(((Rva002BC260Global *)TheAerialPathfinder)->*init.call)(m_goalArguments, arg1, goal, arg2, arg3, arg4);
	goal->configure(1, 0xfa0, 0x447a0000, 0x447a0000, 0, 0);
	typedef void (Rva002BC260Goal::*Finalize)();
	union { void (*fn)(); Finalize call; } finalize = { j_00049ae9 };
	(goal->*finalize.call)();
	m_destination = m_source;
	m_unreconstructed468 = 0;
	m_unreconstructed46c = 0;
}
