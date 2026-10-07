// cl: /DNDEBUG /MD /EHsc
//
// Retail's thunk table orders this class's destructors as public (UAE):
// tools/ilt_oracle.py confirms ??_G/??1 UAE and contradicts MAE. The exact constructor at 0x0018AFB0 installs
// vtable 0x0109B4B0; slot-zero ILT 0x0000889B reaches the retail wrapper at
// 0x00189E10, which calls complete-destructor ILT 0x0003D4C9.

class AITNGuardMachine
{
public:
	virtual ~AITNGuardMachine();

private:
	friend void forceAITNGuardMachineDeletingDestructor();
};

void forceAITNGuardMachineDeletingDestructor()
{
	AITNGuardMachine value;
}
