// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for PartitionFilterPlayerAffiliation.
// Vtable 0x00C9689C slots name this class (?allow@PartitionFilterPlayerAffiliation@@MAE_NPAVObject@@@Z); its slot zero routes
// through ILT 0x000275E8 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0003D659 reaches cleanup body 0x00160D10.

class PartitionFilterPlayerAffiliation
{
protected:
	virtual ~PartitionFilterPlayerAffiliation();
private:
	friend void forcePartitionFilterPlayerAffiliationDeletingDestructor();
};

void forcePartitionFilterPlayerAffiliationDeletingDestructor()
{
	PartitionFilterPlayerAffiliation value;
}
