// cl: /DNDEBUG /MD /EHsc

// The map update preserves the receiver in ECX and cleans three stack arguments.

class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void addObjectToPathfindMap(Object *object);
	void removeObjectFromPathfindMap(Object *object);
	void updateAt003FA5B0(Object *object, int add, int flags);
};

// Retail calls ILT 0x0000BF28, which the ledger defines as ?j_0000bf28@@YAXXZ.
extern void j_0000bf28();
typedef void (Pathfinder::*Pathfinder003FA5B0Call)(Object *, int, int);
template<class T> T iltMemberCall(void (*p)()) { union { void (*plain)(); T member; } call; call.plain = p; return call.member; }

void Pathfinder::addObjectToPathfindMap(Object *object)
{
	(this->*iltMemberCall<Pathfinder003FA5B0Call>(j_0000bf28))(object, 1, 0);
}

void Pathfinder::removeObjectFromPathfindMap(Object *object)
{
	(this->*iltMemberCall<Pathfinder003FA5B0Call>(j_0000bf28))(object, 0, 0);
}
