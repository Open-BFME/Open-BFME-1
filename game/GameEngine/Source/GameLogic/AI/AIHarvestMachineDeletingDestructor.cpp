// cl: /DNDEBUG /MD /EHsc
//
// AIHarvestMachine is allocated through the state-machine pool-glue path,
// which gives it a protected virtual destructor. Its exact constructor at
// 0x0015FE90 installs vtable 0x01096650; slot-zero ILT 0x00014EC5 reaches
// wrapper 0x0015FA60, which calls complete-dtor ILT 0x000289FC.

class AIHarvestMachine
{
protected:
	virtual ~AIHarvestMachine();

private:
	friend void forceAIHarvestMachineDeletingDestructor();
};

void forceAIHarvestMachineDeletingDestructor()
{
	AIHarvestMachine value;
}
