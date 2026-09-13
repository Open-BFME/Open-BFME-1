// cl: /DNDEBUG /MD
//
// GiantBirdAIUpdate::privateFollowPathAppend, retail RVA 0x002C2830.
// The bird module keeps its dynamic path reset byte at +0x488 and uses the
// BFME movement-state range before forwarding to its specialized path method.

typedef bool Bool;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 1
};

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

class PathVector
{
public:
	PathVector() : m_start(0), m_finish(0), m_endOfStorage(0)
	{
	}

	~PathVector();
	unsigned int size() const
	{
		return static_cast<unsigned int>(m_finish - m_start);
	}
	void push_back(const Coord3D &value);

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
		insertInitial(m_finish, value, tag, count, true);
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
	void insertInitial(Coord3D *position, const Coord3D &value,
		const FalseType &tag, unsigned int count, bool atEnd);

	Coord3D *m_start;
	Coord3D *m_finish;
	Coord3D *m_endOfStorage;
};

#pragma comment(linker, "/alternatename:??1PathVector@@QAE@XZ=?j_0000de68@@YAXXZ")
#pragma comment(linker, "/alternatename:?push_back@PathVector@@QAEXABUCoord3D@@@Z=?j_00035f8f@@YAXXZ")
#pragma comment(linker, "/alternatename:?insertInitial@SinglePathVector@@QAEXPAUCoord3D@@ABU2@ABUFalseType@@I_N@Z=?j_000070cc@@YAXXZ")
#pragma comment(linker, "/alternatename:?appendGoalPath@AIStateMachine@@QAEXPBUCoord3D@@@Z=?j_00046a65@@YAXXZ")
#pragma comment(linker, "/alternatename:?getStateTypeForBird@AIUpdateInterface@@QBE?AW4AIStateType@@XZ=?j_0001e33a@@YAXXZ")

class AIStateMachine
{
public:
	void appendGoalPath(const Coord3D *position);

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

	AIStateType getStateTypeForBird() const;

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

void GiantBirdAIUpdate::privateFollowPathAppend(const Coord3D *position,
	CommandSourceType commandSource)
{
	*(reinterpret_cast<unsigned char *>(this) + 0x488) = 0;

	if (getStateTypeForBird() == 0x3F6 && getStateMachine()->getGoalPathSize() > 0)
	{
		getStateMachine()->appendGoalPath(position);
		return;
	}

	if (getStateTypeForBird() > 0x3E8 && getStateTypeForBird() < 0x3FC &&
		getStateTypeForBird() != 0x3ED && getStateTypeForBird() != 0x3F4)
	{
		PathVector path;
		path.push_back(*getStateMachine()->getGoalPosition());
		path.push_back(*position);
		privateFollowPath(&path, 0, commandSource, false);
	}
	else
	{
		SinglePathVector path;
		path.initialize(1, *position);
		privateFollowPath(&path, 0, commandSource, false);
	}
}
