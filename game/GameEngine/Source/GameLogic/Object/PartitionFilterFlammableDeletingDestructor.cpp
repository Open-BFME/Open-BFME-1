// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for PartitionFilterFlammable.
// Vtable 0x00CBE9EC slots name this class (?allow@PartitionFilterFlammable@@UAE_NPAVObject@@@Z); its slot zero routes
// through ILT 0x0003E595 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0000D378 reaches cleanup body 0x00292540.

class PartitionFilterFlammable
{
protected:
	virtual ~PartitionFilterFlammable();
private:
	friend void forcePartitionFilterFlammableDeletingDestructor();
};

void forcePartitionFilterFlammableDeletingDestructor()
{
	PartitionFilterFlammable value;
}
