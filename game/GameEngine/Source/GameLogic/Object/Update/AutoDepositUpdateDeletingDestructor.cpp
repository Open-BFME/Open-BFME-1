// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AutoDepositUpdate.
// Vtable 0x00CBB1D4 slots name this class (?getClassMemoryPool@AutoDepositUpdate@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x000468B7 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0003C06F reaches cleanup body 0x00280CD0.

class AutoDepositUpdate
{
protected:
	virtual ~AutoDepositUpdate();
private:
	friend void forceAutoDepositUpdateDeletingDestructor();
};

void forceAutoDepositUpdateDeletingDestructor()
{
	AutoDepositUpdate value;
}
