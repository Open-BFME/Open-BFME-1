// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for PartitionFilterPossibleToAttack.
// Constructor 0x004C12B0 installs dedicated vtable 0x00CFD964; its slot
// zero routes through ILT 0x00009B7E to this 30-byte wrapper, whose complete
// destructor route ILT 0x0002C935 reaches cleanup body 0x004C1150.

class PartitionFilterPossibleToAttack
{
protected:
	virtual ~PartitionFilterPossibleToAttack();
private:
	friend void forcePartitionFilterPossibleToAttackDeletingDestructor();
};

void forcePartitionFilterPossibleToAttackDeletingDestructor()
{
	PartitionFilterPossibleToAttack value;
}
