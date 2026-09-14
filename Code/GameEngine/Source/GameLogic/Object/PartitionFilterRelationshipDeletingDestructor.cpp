// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for PartitionFilterRelationship.
// Vtable 0x00C85DC0 slots name this class (?allow@PartitionFilterRelationship@@UAE_NPAVObject@@@Z); its slot zero routes
// through ILT 0x000080B7 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00004C87 reaches cleanup body 0x000EC7A0.

class PartitionFilterRelationship
{
protected:
	virtual ~PartitionFilterRelationship();
private:
	friend void forcePartitionFilterRelationshipDeletingDestructor();
};

void forcePartitionFilterRelationshipDeletingDestructor()
{
	PartitionFilterRelationship value;
}
