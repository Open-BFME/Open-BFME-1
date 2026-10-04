// cl: /DNDEBUG /MD
//
// GiantBirdAIUpdate::privateFollowPathAppend, retail RVA 0x002C2830.
// The bird module keeps its dynamic path reset byte at +0x488 and uses the
// BFME movement-state range before forwarding to its specialized path method.

typedef bool Bool;

#include "../../../command_source_type.h"

enum AIStateType
{
	AI_STATE_UNKNOWN = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

// Retail reaches these through incremental-link thunks; call them directly.
extern void j_0000de68();
extern void j_00035f8f();
extern void j_000070cc();
extern void j_00046a65();
extern void j_0001e33a();

class PathVector
{
public:
	PathVector() : m_start(0), m_finish(0), m_endOfStorage(0)
	{
	}

	// Retail calls the vector's destructor through its incremental-link thunk.
	~PathVector()
	{
		typedef void (PathVector::*Fn)();
		union
		{
			void (*fn)();
			Fn call;
		} u = { j_0000de68 };
		(this->*u.call)();
	}

	unsigned int size() const
	{
		return static_cast<unsigned int>(m_finish - m_start);
	}

private:
	Coord3D *m_start;
	Coord3D *m_finish;
	Coord3D *m_endOfStorage;
};

struct FalseType
{
};

namespace _STL
{
void vectorLargeDeallocate(void *memory);
void vectorSmallDeallocate(void *memory, unsigned int bytes);
}

class SinglePathVector
{
public:
	SinglePathVector() : m_start(0), m_finish(0), m_endOfStorage(0)
	{
	}

	void initialize(unsigned int count, const Coord3D &value)
	{
		FalseType tag;
		typedef void (SinglePathVector::*Fn)(Coord3D *, const Coord3D &,
			const FalseType &, unsigned int, bool);
		union
		{
			void (*fn)();
			Fn call;
		} u = { j_000070cc };
		(this->*u.call)(m_finish, value, tag, count, true);
	}

	~SinglePathVector()
	{
		if (m_start)
		{
			unsigned int bytes =
				static_cast<unsigned int>(m_endOfStorage - m_start) * sizeof(Coord3D);
			if (bytes > 128)
				_STL::vectorLargeDeallocate(m_start);
			else
				_STL::vectorSmallDeallocate(m_start, bytes);
		}
	}

	private:
	Coord3D *m_start;
	Coord3D *m_finish;
	Coord3D *m_endOfStorage;
};

class AIStateMachine
{
public:
	int getGoalPathSize() const
	{
		return static_cast<int>(m_goalPath.size());
	}

	const Coord3D *getGoalPosition() const
	{
		return reinterpret_cast<const Coord3D *>(
			reinterpret_cast<const char *>(this) + 0x24);
	}

private:
	char m_padding[0x44];
	PathVector m_goalPath;
};

class Object;

class AIUpdateInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void privateFollowPath(const void *path,
		Object *ignoreObject, CommandSourceType commandSource, Bool exitProduction) = 0;
	virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void privateFollowPathAppend(const Coord3D *position,
		CommandSourceType commandSource) = 0;

	AIStateMachine *getStateMachine()
	{
		return *reinterpret_cast<AIStateMachine **>(
			reinterpret_cast<char *>(this) + 0x30);
	}
};

class GiantBirdAIUpdate : public AIUpdateInterface
{
	protected:
	virtual void privateFollowPathAppend(const Coord3D *position,
		CommandSourceType commandSource);
};

static __forceinline AIStateType birdStateType(const AIUpdateInterface *update)
{
	typedef AIStateType (AIUpdateInterface::*Fn)() const;
	union
	{
		void (*fn)();
		Fn call;
	} u = { j_0001e33a };
	return (update->*u.call)();
}

void GiantBirdAIUpdate::privateFollowPathAppend(const Coord3D *position,
	CommandSourceType commandSource)
{
	*(reinterpret_cast<unsigned char *>(this) + 0x488) = 0;

	if (birdStateType(this) == 0x3F6 && getStateMachine()->getGoalPathSize() > 0)
	{
		typedef void (AIStateMachine::*Fn)(const Coord3D *);
		union
		{
			void (*fn)();
			Fn call;
		} u = { j_00046a65 };
		(getStateMachine()->*u.call)(position);
		return;
	}

	if (birdStateType(this) > 0x3E8 && birdStateType(this) < 0x3FC &&
		birdStateType(this) != 0x3ED && birdStateType(this) != 0x3F4)
	{
		typedef void (PathVector::*Fn)(const Coord3D &);
		union
		{
			void (*fn)();
			Fn call;
		} u = { j_00035f8f };

		PathVector path;
		(path.*u.call)(*getStateMachine()->getGoalPosition());
		(path.*u.call)(*position);
		privateFollowPath(&path, 0, commandSource, false);
	}
	else
	{
		SinglePathVector path;
		path.initialize(1, *position);
		privateFollowPath(&path, 0, commandSource, false);
	}
}
