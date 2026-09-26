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

void Pathfinder::addObjectToPathfindMap(Object *object)
{
	updateAt003FA5B0(object, 1, 0);
}

void Pathfinder::removeObjectFromPathfindMap(Object *object)
{
	updateAt003FA5B0(object, 0, 0);
}
