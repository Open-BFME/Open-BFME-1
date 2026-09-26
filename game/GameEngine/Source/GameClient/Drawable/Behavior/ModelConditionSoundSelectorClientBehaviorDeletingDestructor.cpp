// cl: /DNDEBUG /MD /EHsc

// Retail @0x00124AF0: ModelConditionSoundSelectorClientBehavior
// scalar-deleting destructor.  The complete-destructor tail at 0x00124B20
// reseats the class's vtables before chaining to its base destructor; this
// declaration supplies the authentic class name while emitting the retail
// wrapper.
//
// The dedicated constructor at 0x00124A10 stores the primary and secondary
// vtables 0x0108E53C and 0x0108E52C after the ClientUpdateModule base call.
// The 0x00126190 friend_newModuleInstance factory allocates this exact type.
// The wrapper's complete-destructor ILT 0x00042758 jumps to 0x00124B20.
class ModelConditionSoundSelectorClientBehavior
{
public:
	virtual ~ModelConditionSoundSelectorClientBehavior();
};

void forceModelConditionSoundSelectorClientBehaviorDeletingDestructor()
{
	ModelConditionSoundSelectorClientBehavior value;
}
