// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for PartitionFilterPlayer.
// Vtable 0x00C9688C slots name this class (?allow@PartitionFilterPlayer@@MAE_NPAVObject@@@Z); its slot zero routes
// through ILT 0x00003EB8 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00016D5B reaches cleanup body 0x00160CD0.

class PartitionFilterPlayer
{
protected:
	virtual ~PartitionFilterPlayer();
private:
	friend void forcePartitionFilterPlayerDeletingDestructor();
};

void forcePartitionFilterPlayerDeletingDestructor()
{
	PartitionFilterPlayer value;
}
