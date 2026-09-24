// ?rva0023BE60@Rva0023BE60Receiver@@QAE_NPAVObject@@@Z
// partial score=0.968 date=2026-09-24
// cl: /DNDEBUG /MD /EHs-c-

struct Coord3D { float x, y, z; };
typedef unsigned int ObjectID;

class Overridable {
public:
	Overridable *getFinalOverride() const;
	char pad000[4];
	Overridable *next;
	char pad008[0xC8 - 8];
	unsigned flagsC8;
	char padCC[8];
	unsigned flagsD4;
};

class Object {
public:
	char pad000[4];
	Overridable *runtime;
	char pad008[0x38 - 8];
	Coord3D position;
	char pad044[0x74 - 0x44];
	ObjectID id;
	char pad078[0x214 - 0x78];
	Object *owner;
};

class Rva003E4680Pathfinder {
public:
	int rva003E4680(Object *, const Coord3D *, ObjectID *);
};

class AI {
public:
	char pad000[0xC];
	Rva003E4680Pathfinder *pathfinder;
};

class GameLogic {
public:
	Object *findObjectByID(int);
};

extern AI *TheAI;
extern GameLogic *TheBfmeGameLogic;

class Rva0023BE60Receiver {
public:
	char pad000[8];
	Object *objectAt8;
	bool rva0023BE60(Object *target);
};

bool Rva0023BE60Receiver::rva0023BE60(Object *target)
{
	Overridable *targetData = target->runtime;
	if (targetData && targetData->next)
		targetData = targetData->next->getFinalOverride();
	if (targetData->flagsC8 & 0x800)
		return true;

	ObjectID nearby[16];
	Rva003E4680Pathfinder *pathfinder = TheAI->pathfinder;
	Object *owner = objectAt8;
	int count = pathfinder->rva003E4680(target, &target->position, nearby);
	ObjectID ownerId;
	GameLogic *logic;
	int i = 0;
	if (count <= 0) goto done;
	ownerId = owner->id;
	logic = TheBfmeGameLogic;
	for (; i < count; ++i) {
		ObjectID id = nearby[i];
		if (id == ownerId)
			continue;
		Object *candidate = logic->findObjectByID(id);
		if (!candidate)
			return false;
		if (candidate->owner == owner)
			continue;
		Overridable *candidateData = candidate->runtime;
		if (candidateData && candidateData->next)
			candidateData = candidateData->next->getFinalOverride();
		if (candidateData->flagsD4 & 0x1000)
			continue;
		return false;
	}
	done:
	return true;
}
