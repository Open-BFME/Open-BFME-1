// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// ?d_0016df90@@YAXXZ, retail RVA 0x0016DF90.
// GetGameLogicRandomValue(1, 2, "AIStates.cpp", 0x3ac4) picks a search order:
// on 1, try findEnemyNear first and fall back to findAllyNear; on 2 (or
// anything else), try findAllyNear first and fall back to findEnemyNear.
// Both searches use the same object as both receiver and target, and the
// same doubled vision range. "this" (ecx) is never read; the sole explicit
// stack argument (ret 4) is the object. No owning class or caller identifies
// this body, so it is placed address-derived per naming policy.

typedef int Int;

class Object;

int __cdecl GetGameLogicRandomValue(int lo, int hi, const char *file, int line);

class AI
{
public:
	Object *findEnemyNear(Object *obj, float range, int a, int b, int c);
	Object *findAllyNear(Object *obj, float range, int a);
};

extern AI *TheAI;

class Object
{
public:
	float getVisionRange(void) const;
};

class Rva0016DF90Owner
{
public:
	Object *rva0016df90(Object *object);
};

// retail RVA 0x0016DF90
Object *Rva0016DF90Owner::rva0016df90(Object *object)
{
	int order = GetGameLogicRandomValue(1, 2,
		"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp", 0x3ac4);

	Object *result;

	if (order == 1)
	{
		result = TheAI->findEnemyNear(object, object->getVisionRange() * 2.0f, 2, 0, 0);
		if (result)
			return result;

		result = TheAI->findAllyNear(object, object->getVisionRange() * 2.0f, 2);
		return result;
	}

	result = TheAI->findAllyNear(object, object->getVisionRange() * 2.0f, 2);
	if (result)
		return result;

	result = TheAI->findEnemyNear(object, object->getVisionRange() * 2.0f, 2, 0, 0);
	return result;
}
