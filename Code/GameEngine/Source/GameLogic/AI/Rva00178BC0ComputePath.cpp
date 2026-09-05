// cl: /DNDEBUG /MD
// Retail 0x00178BC0: the BFME move-state ComputePath29 body, byte-twin of
// ComputePath31 at 0x00178E30 (Rva00178E30ComputePath.cpp) -- identical 88
// bytes once relocations (the callee ILTs and the debug string literal
// address) are masked; the trace string itself differs (ComputePath29).

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void requestPath(Coord3D *goal, Bool adjustsDestination);
	void friend_startingMove();

private:
	unsigned char m_pad00[0x31e];

public:
	Bool m_waitingForPath;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
private:
	unsigned char m_pad00[0x204];

public:
	AIUpdateInterface *m_ai;
};

struct Rva00178BC0StateMachine
{
	unsigned char m_pad00[0x10];
	Object *m_owner;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual void baseSlot();

protected:
	unsigned char m_pad00[0x18];
	Rva00178BC0StateMachine *m_machine;
	unsigned char m_pad20[4];
	Coord3D m_goalPosition;
	unsigned char m_pad30[0x1d];
	Bool m_waitingForPath;

	Bool getAdjustsDestination() const;
};

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a(void);

typedef void (__cdecl *Rva00178BC0CritterDesyncLog)(void *, const char *);

class Rva00178BC0State : public AIInternalMoveToState
{
public:
	Bool computePath();
};

Bool Rva00178BC0State::computePath()
{
	if (g_012F0239 && g_012ED4FC)
	{
		((Rva00178BC0CritterDesyncLog)j_0003a17a)(g_012ED4FC,
			"CritterDesync: ComputePath29");
	}

	AIUpdateInterface *ai = m_machine->m_owner->m_ai;
	ai->requestPath(&m_goalPosition, getAdjustsDestination());
	m_waitingForPath = ai->m_waitingForPath;
	ai->friend_startingMove();
	return true;
}
