// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for RiderChangeContain.
// The exact constructor at 0x00229FB0 installs dedicated vtable 0x010ACAF0;
// slot zero routes through ILT 0x000310AC to this 30-byte wrapper, whose
// protected complete destructor is reached through ILT 0x0001CA80.

class RiderChangeContain
{
protected:
	virtual ~RiderChangeContain();
private:
	friend void forceRiderChangeContainDeletingDestructor();
};

void forceRiderChangeContainDeletingDestructor()
{
	RiderChangeContain value;
}
