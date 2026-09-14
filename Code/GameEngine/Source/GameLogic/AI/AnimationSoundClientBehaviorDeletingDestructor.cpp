// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: AnimationSoundClientBehavior scalar-deleting destructor at
// retail RVA 0x00604E60 (30 bytes). The matched constructor at 0x00605380,
// the existing multiple-inheritance complete destructor at 0x00604B40, and
// the AnimationSoundClientBehavior module/factory family establish the class
// identity. The scalar wrapper's ILT target is the complete destructor.

class AnimationSoundClientBehavior
{
public:
	virtual ~AnimationSoundClientBehavior();
};

void forceAnimationSoundClientBehaviorDeletingDestructor()
{
	AnimationSoundClientBehavior value;
}
