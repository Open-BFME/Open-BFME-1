// cl: /DNDEBUG /MD
//
// Address-derived recovery for the BFME state-action body at 0x002BCE00.

typedef float Real;
typedef int Int;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;

class AIUpdateInterface
{
public:
	void ignoreObstacle(Object *object);
};

class BfmeSubCSA
{
public:
	bool bfmeAskCSA();
};

class Rva002BC470StateAction
{
public:
	void finish(void *argument);
};

class BfmeSub30_7F0
{
public:
	virtual void unused000() = 0;
	virtual void unused004() = 0;
	virtual void unused008() = 0;
	virtual void unused00c() = 0;
	virtual void unused010() = 0;
	virtual void beginAction() = 0;
	virtual void unused018() = 0;
	virtual void unused01c() = 0;
	virtual void signalAction(Int code) = 0;
	void bfmeSetGoalPosition(const Coord3D *position);
	void step2(void *argument);
};

class Rva002BCE00Path
{
public:
	Real *m_begin;
	Real *m_end;
};

class Rva002BCE00StateAction : public AIUpdateInterface
{
public:
	void run(Rva002BCE00Path *path, Object *obstacle, void *finishArgument,
		void *unused);

private:
	unsigned char m_unreconstructed000[8];
	BfmeSubCSA *m_object;
	unsigned char m_unreconstructed00c[0x24];
	BfmeSub30_7F0 *m_sink;
	unsigned char m_unreconstructed034[0x42c];
	Int m_actionStarted;
};

void Rva002BCE00StateAction::run(Rva002BCE00Path *path, Object *obstacle,
	void *finishArgument, void *unused)
{
	if (m_object->bfmeAskCSA())
	{
		m_sink->beginAction();

		Real *begin = path->m_begin;
		Real *end = path->m_end;
		int count = ((char *)end - (char *)begin) / 12;
		if (count != 0)
		{
			Real *last = begin + count * 3 - 3;
			Coord3D goal;
			volatile Real *goalFields = (volatile Real *)&goal;
			volatile Real *source = (volatile Real *)last;
			goalFields[0] = source[0];
			goalFields[1] = source[1];
			goalFields[2] = source[2];
			m_sink->bfmeSetGoalPosition((const Coord3D *)&goal);
		}

		m_sink->step2(path);
		((Rva002BC470StateAction *)this)->finish(finishArgument);
		ignoreObstacle(obstacle);
		m_sink->signalAction(0x3f6);
		m_actionStarted = 1;
	}
}
