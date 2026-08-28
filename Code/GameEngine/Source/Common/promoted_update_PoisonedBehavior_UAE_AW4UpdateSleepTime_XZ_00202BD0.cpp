// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?update@PoisonedBehavior@@UAE?AW4UpdateSleepTime@@XZ: Code/GameEngine/Source/GameLogic/Object/Behavior/PoisonedBehavior.cpp
// Grok promote from masm_dumps — retail 0x00202BD0 size 48
// was: Code/masm_dumps/update_PoisonedBehavior_00202BD0_packet301.asm

enum UpdateSleepTime { UPDATE_SLEEP_NONE=0 };
class PoisonedBehaviorOwnerShim {
public:
	UpdateSleepTime helper(int, void *, int, int);
};

class PoisonedBehavior { public: virtual UpdateSleepTime update(void); };

// ?update@PoisonedBehavior@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime PoisonedBehavior::update(void)
{
	void *object = *(void **)((unsigned char *)this + 0x18);
	PoisonedBehaviorOwnerShim *owner = (PoisonedBehaviorOwnerShim *)this;
	owner = (PoisonedBehaviorOwnerShim *)((unsigned char *)owner - 0x10);
	if (object && object != *(void **)((unsigned char *)(*(void **)0x012F0898) + 0x3C))
		return owner->helper(*(int *)((unsigned char *)owner + 0x24), object,
			0x3FFFFFFF, 0x3FFFFFFF);
	return (UpdateSleepTime)0x3FFFFFFF;
}

