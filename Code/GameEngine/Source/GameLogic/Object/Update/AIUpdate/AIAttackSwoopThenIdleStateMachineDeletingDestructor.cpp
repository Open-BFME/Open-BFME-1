// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: AIAttackSwoopThenIdleStateMachine scalar-deleting destructor at
// retail RVA 0x002BC920 (30 bytes).  The class identity is established by the
// matched constructor at 0x002BF480, which installs vtable 0x010C7460, and by
// the two independently matched factories at 0x002BFA80 and 0x002C0370,
// whose return type names this exact state-machine class.  Vtable slot zero
// is ILT 0x00030F21 and routes directly to this wrapper.  The wrapper invokes
// the complete destructor through ILT 0x000298D9, whose retail target is the
// matched 11-byte derived dtor body at 0x002BBAC0; that body re-seats its
// vftable before tail-jumping to StateMachine's destructor.

// The complete dtor body is already recovered in VptrTailJumpDestructors.cpp
// under an address-derived name.  This alias keeps the authentic class name
// on the wrapper while routing the declaration-only dtor to that exact body.
#pragma comment(linker, "/alternatename:??1AIAttackSwoopThenIdleStateMachine@@UAE@XZ=??1Rva002BBAC0TailDtor@@UAE@XZ")

class AIAttackSwoopThenIdleStateMachine
{
public:
	virtual ~AIAttackSwoopThenIdleStateMachine();
};

void forceAIAttackSwoopThenIdleStateMachineDeletingDestructor()
{
	AIAttackSwoopThenIdleStateMachine value;
}
