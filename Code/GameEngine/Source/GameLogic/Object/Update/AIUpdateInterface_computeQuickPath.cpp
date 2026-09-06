// cl: /DNDEBUG /MD /EHsc
// Retail 0x002712D0: AIUpdateInterface::computeQuickPath.

typedef bool Bool;

#pragma warning(disable : 4716)

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

class Path
{
public:
	~Path();
};

class Pathfinder
{
public:
	void removeGoal(Object *object);
	Path *getAircraftPath(const Object *object, const Coord3D *destination);
};

class AI
{
public:
	char m_unreconstructed_00[0x0C];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;
extern void __cdecl operator delete(void *block);
extern void j_0000ca68();
extern void j_0001e6fa();
extern void j_00025d56();

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<122>
{
public:
	virtual void setLocomotorGoalNone() = 0;

	Bool computeQuickPath(const Coord3D *destination);

	char m_unreconstructed_04[4];
	Object *m_object;
	char m_unreconstructed_0C[0x134];
	Path *m_path;
	char m_unreconstructed_144[0x94];
	int m_locomotorGoalType;
	Coord3D m_locomotorGoalData;
	char m_unreconstructed_1E8[0x136];
	unsigned char m_waitingForPath;
	unsigned char m_isAttackPath;
	char m_unreconstructed_320[6];
	unsigned char m_isBlockedAndStuck;
};

Bool AIUpdateInterface::computeQuickPath(const Coord3D *destination)
{
	Object *object = m_object;

	typedef void (Pathfinder::*RemoveGoalCall)(Object *);
	union
	{
		void *asVoid;
		RemoveGoalCall asMember;
	} removeGoalCast;
	removeGoalCast.asVoid = (void *)j_00025d56;
	(TheAI->m_pathfinder->*removeGoalCast.asMember)(object);

	Path *oldPath = m_path;
	if (oldPath != 0)
	{
		typedef void (Path::*DestroyCall)();
		union
		{
			void *asVoid;
			DestroyCall asMember;
		} destroyCast;
		destroyCast.asVoid = (void *)j_0000ca68;
		(oldPath->*destroyCast.asMember)();
		operator delete(oldPath);
	}

	m_path = 0;
	m_waitingForPath = false;
	m_isBlockedAndStuck = false;
	m_isAttackPath = false;
	setLocomotorGoalNone();

	typedef Path *(Pathfinder::*GetAircraftPathCall)(const Object *, const Coord3D *);
	union
	{
		void *asVoid;
		GetAircraftPathCall asMember;
	} getAircraftPathCast;
	getAircraftPathCast.asVoid = (void *)j_0001e6fa;
	m_path = (TheAI->m_pathfinder->*getAircraftPathCast.asMember)(object, destination);
	if (m_path != 0)
	{
		m_locomotorGoalType = 4;
		m_locomotorGoalData = *destination;
	}
}
