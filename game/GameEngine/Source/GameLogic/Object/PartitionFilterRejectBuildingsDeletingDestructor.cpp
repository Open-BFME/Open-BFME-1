// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for PartitionFilterRejectBuildings.
// Vtable 0x00C9FB64 slots name this class (?allow@PartitionFilterRejectBuildings@@MAE_NPAVObject@@@Z); its slot zero routes
// through ILT 0x000058E9 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0002C9AD reaches cleanup body 0x0014A610.

class PartitionFilterRejectBuildings
{
protected:
	virtual ~PartitionFilterRejectBuildings();
private:
	friend void forcePartitionFilterRejectBuildingsDeletingDestructor();
};

void forcePartitionFilterRejectBuildingsDeletingDestructor()
{
	PartitionFilterRejectBuildings value;
}
