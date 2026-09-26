// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: AIGuardMachine scalar-deleting destructor at retail RVA
// 0x0015C030 (30 bytes). The matched constructor at 0x0015D1D0 installs
// vtable 0x01095FE0, and the adjacent literal-name getter independently
// identifies the class. This wrapper calls the pinned complete destructor
// through ILT 0x00035D46 before conditionally invoking scalar operator delete.

class AIGuardMachine
{
public:
	virtual ~AIGuardMachine();
};

void forceAIGuardMachineDeletingDestructor()
{
	AIGuardMachine value;
}
