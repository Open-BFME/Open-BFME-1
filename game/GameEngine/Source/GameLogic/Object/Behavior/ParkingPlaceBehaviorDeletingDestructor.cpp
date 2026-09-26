// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ParkingPlaceBehavior.
// The exact constructor at 0x001F59F0 installs dedicated vtable 0x010A2A1C;
// slot zero routes through ILT 0x0002F80B to this 30-byte wrapper, whose
// protected complete destructor is reached through ILT 0x0000DEA9.

class ParkingPlaceBehavior
{
protected:
	virtual ~ParkingPlaceBehavior();
private:
	friend void forceParkingPlaceBehaviorDeletingDestructor();
};

void forceParkingPlaceBehaviorDeletingDestructor()
{
	ParkingPlaceBehavior value;
}
