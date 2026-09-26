// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for PartitionFilterRejectByKindOf.
// Vtable 0x00C9686C slots name this class (?allow@PartitionFilterRejectByKindOf@@UAE_NPAVObject@@@Z); its slot zero routes
// through ILT 0x00039FA4 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00034F04 reaches cleanup body 0x00160C60.

class PartitionFilterRejectByKindOf
{
protected:
	virtual ~PartitionFilterRejectByKindOf();
private:
	friend void forcePartitionFilterRejectByKindOfDeletingDestructor();
};

void forcePartitionFilterRejectByKindOfDeletingDestructor()
{
	PartitionFilterRejectByKindOf value;
}
