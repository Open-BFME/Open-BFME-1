// cl: /DNDEBUG /MD /EHsc
//
// AITNGuardMachine uses MEMORY_POOL_GLUE_WITHOUT_GCMP, which makes its
// virtual destructor protected. The exact constructor at 0x0018AFB0 installs
// vtable 0x0109B4B0; slot-zero ILT 0x0000889B reaches the retail wrapper at
// 0x00189E10, which calls complete-destructor ILT 0x0003D4C9.

class AITNGuardMachine
{
protected:
	virtual ~AITNGuardMachine();

private:
	friend void forceAITNGuardMachineDeletingDestructor();
};

void forceAITNGuardMachineDeletingDestructor()
{
	AITNGuardMachine value;
}
