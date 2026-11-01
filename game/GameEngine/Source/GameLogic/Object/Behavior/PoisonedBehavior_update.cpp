// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?update@PoisonedBehavior@@UAE?AW4UpdateSleepTime@@XZ: game/GameEngine/Source/GameLogic/Object/Behavior/PoisonedBehavior.cpp
// Grok promote from masm_dumps — retail 0x00202BD0 size 48
// was: game/masm_dumps/update_PoisonedBehavior_00202BD0_packet301.asm

enum UpdateSleepTime { UPDATE_SLEEP_NONE=0 };
// The callee (ILT 0x000202A7 -> 0x002B1FD0) is the matched protected
// UpdateModule::frameToSleepTime; call it by that defined name.
class UpdateModule {
	friend class PoisonedBehavior;
protected:
	UpdateSleepTime frameToSleepTime(unsigned int, unsigned int, unsigned int, unsigned int);
};
typedef UpdateModule PoisonedBehaviorOwnerShim;

class GameLogic;
extern GameLogic *TheGameLogic;

class PoisonedBehavior { public: virtual UpdateSleepTime update(void); };

// ?update@PoisonedBehavior@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime PoisonedBehavior::update(void)
{
	void *object = *(void **)((unsigned char *)this + 0x18);
	PoisonedBehaviorOwnerShim *owner = (PoisonedBehaviorOwnerShim *)this;
	owner = (PoisonedBehaviorOwnerShim *)((unsigned char *)owner - 0x10);
	if (object && object != *(void **)((unsigned char *)TheGameLogic + 0x3C))
		return owner->frameToSleepTime(*(unsigned int *)((unsigned char *)owner + 0x24),
			(unsigned int)object, 0x3FFFFFFF, 0x3FFFFFFF);
	return (UpdateSleepTime)0x3FFFFFFF;
}

