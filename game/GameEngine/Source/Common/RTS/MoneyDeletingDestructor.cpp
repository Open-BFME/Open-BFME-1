// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for Money.
// Constructor 0x000E1540 installs dedicated vtable 0x00C83D18; its slot
// zero routes through ILT 0x00042B27 to this 30-byte wrapper, whose complete
// destructor route ILT 0x000424BA reaches cleanup body 0x000CBAE0.

class Money
{
protected:
	virtual ~Money();
private:
	friend void forceMoneyDeletingDestructor();
};

void forceMoneyDeletingDestructor()
{
	Money value;
}
