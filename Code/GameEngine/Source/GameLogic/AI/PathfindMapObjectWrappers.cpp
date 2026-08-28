// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: the two pathfind-map object wrappers, retail 0x003D57F0 and
// 0x003D5810, 17 bytes each. Both carried only machine byte-dump rows;
// reverse/reloc_names.csv holds their names with identity=real.
//
// Neither touches this. Each forwards the object to the same helper with two
// constants -- 1 and 0 to add, 0 and 0 to remove -- and lets the helper clean
// the stack, so the helper is __stdcall.

class Object;

extern "C" void __stdcall BfmePathfindMapUpdate(Object *object, int add, int flags);

class BFMEPathfinderMapShim
{
public:
	void addObjectToPathfindMap(Object *object);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void removeObjectFromPathfindMap(Object *object);
};

// ?addObjectToPathfindMap@BFMEPathfinderMapShim@@QAEXPAVObject@@@Z
void BFMEPathfinderMapShim::addObjectToPathfindMap(Object *object)
{
	BfmePathfindMapUpdate(object, 1, 0);
}

// ?removeObjectFromPathfindMap@Pathfinder@@QAEXPAVObject@@@Z
void Pathfinder::removeObjectFromPathfindMap(Object *object)
{
	BfmePathfindMapUpdate(object, 0, 0);
}
