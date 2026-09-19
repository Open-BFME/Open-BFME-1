// cl: /DNDEBUG /MD /EHsc

// Retail @0x001244A0: WanderAIUpdateModuleData scalar-deleting destructor.
// The named complete destructor is matched at 0x0027E4E0; this declaration
// gives MSVC the authentic class name while emitting the small retail wrapper.
//
// The 0x0011BEE0 friend_newModuleData factory allocates this exact type, and
// its companion TU installs the dedicated vtable at 0x0108A5A8.  Slot zero's
// ILT 0x00022E76 routes to this wrapper.  The complete-destructor call is ILT
// 0x0004A2B9, which jumps through 0x001244D0 and 0x00029D02 to 0x0027E4E0.
class WanderAIUpdateModuleData
{
public:
	virtual ~WanderAIUpdateModuleData();
};

void forceWanderAIUpdateModuleDataDeletingDestructor()
{
	WanderAIUpdateModuleData value;
}
