// cl: /DNDEBUG /MD /EHsc
//
// AIDockMachine's pool glue makes the virtual destructor protected. The
// exact constructor at 0x0014F7C0 installs vtable 0x01095A38; slot-zero ILT
// 0x00041BA5 reaches the retail wrapper at 0x0014F120, which calls complete-
// destructor ILT 0x0000B7C6.

class AIDockMachine
{
protected:
	virtual ~AIDockMachine();

private:
	friend void forceAIDockMachineDeletingDestructor();
};

void forceAIDockMachineDeletingDestructor()
{
	AIDockMachine value;
}
