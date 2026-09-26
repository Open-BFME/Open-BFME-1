// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: HitReactionBehaviorModuleData scalar-deleting destructor at
// retail RVA 0x00291E80 (30 bytes).  The matched constructor at 0x00291950
// fixes the 0x30-byte module-data layout, while the complete destructor at
// 0x00291EB0 and the friend allocator establish the same class identity.

class HitReactionBehaviorModuleData
{
public:
	virtual ~HitReactionBehaviorModuleData();
};

void forceHitReactionBehaviorModuleDataDeletingDestructor()
{
	HitReactionBehaviorModuleData value;
}
