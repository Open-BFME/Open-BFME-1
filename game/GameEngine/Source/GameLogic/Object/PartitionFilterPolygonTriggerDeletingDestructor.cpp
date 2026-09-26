// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for PartitionFilterPolygonTrigger.
// Vtable 0x00C95714 slots name this class (?allow@PartitionFilterPolygonTrigger@@MAE_NPAVObject@@@Z); its slot zero routes
// through ILT 0x000432AC to this 30-byte wrapper, whose complete destructor
// route ILT 0x0000C5F9 reaches cleanup body 0x00149FE0.

class PartitionFilterPolygonTrigger
{
protected:
	virtual ~PartitionFilterPolygonTrigger();
private:
	friend void forcePartitionFilterPolygonTriggerDeletingDestructor();
};

void forcePartitionFilterPolygonTriggerDeletingDestructor()
{
	PartitionFilterPolygonTrigger value;
}
