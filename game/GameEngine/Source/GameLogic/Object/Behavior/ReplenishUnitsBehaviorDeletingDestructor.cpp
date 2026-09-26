// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for ReplenishUnitsBehavior.
// The exact constructor at 0x002044E0 installs dedicated vtable 0x010A5C44;
// slot zero routes through ILT 0x0000CE4B to this 30-byte wrapper, whose
// complete destructor is reached through ILT 0x0002CCB4.

class ReplenishUnitsBehavior
{
public:
	virtual ~ReplenishUnitsBehavior();
};

void forceReplenishUnitsBehaviorDeletingDestructor()
{
	ReplenishUnitsBehavior value;
}
