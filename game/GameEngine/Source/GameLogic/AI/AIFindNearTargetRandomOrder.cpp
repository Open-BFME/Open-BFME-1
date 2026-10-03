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

// Retail reaches GetGameLogicRandomValue through the ILT at 0x00001BAE; the
// only body the tree defines is the one random_value.cpp compiles from the
// `char *file` parameter, so the reference is spelled that way.
int __cdecl GetGameLogicRandomValue(int lo, int hi, char *file, int line);

// Retail reaches AI::findEnemyNear through the five-byte ILT thunk at
// 0x0003F990.  The only ledger owner of that address is the address-claimed
// thunk ?j_0003f990@@YAXXZ (game/gen_small/thunks_030.cpp, matched); nothing
// anywhere defines the member name, so the reference never resolved.  Routing
// the call through the thunk fixes that and changes no byte: the
// pointer-to-member type still supplies __thiscall's ecx receiver and the same
// five pushed arguments, which is exactly retail's shape here
// (`mov ecx,TheAI` / `fstp dword ptr [esp]` / `push esi` / `call 0x0003F990`).
// This is the same union route MemberAttack00242270.cpp already uses for this
// very thunk.
extern void j_0003f990();

class AI
{
public:
	Object *findAllyNear(Object *object, float range, int a);
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
	Object *rva0016df90(Object *referenceObject);
};

// retail RVA 0x0016DF90
Object *Rva0016DF90Owner::rva0016df90(Object *referenceObject)
{
	int searchOrder = GetGameLogicRandomValue(1, 2,
		"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp", 0x3ac4);

	typedef Object *(AI::*FindEnemyNear)(Object *object, float range, int a, int b, int c);
	union
	{
		void (*fn)();
		FindEnemyNear call;
	} findEnemyNear = { j_0003f990 };

	Object *nearbyObject;

	if (searchOrder == 1)
	{
		nearbyObject = (TheAI->*findEnemyNear.call)(referenceObject,
			referenceObject->getVisionRange() * 2.0f, 2, 0, 0);
		if (nearbyObject)
			return nearbyObject;

		nearbyObject = TheAI->findAllyNear(referenceObject,
			referenceObject->getVisionRange() * 2.0f, 2);
		return nearbyObject;
	}

	nearbyObject = TheAI->findAllyNear(referenceObject,
		referenceObject->getVisionRange() * 2.0f, 2);
	if (nearbyObject)
		return nearbyObject;

	nearbyObject = (TheAI->*findEnemyNear.call)(referenceObject,
		referenceObject->getVisionRange() * 2.0f, 2, 0, 0);
	return nearbyObject;
}
