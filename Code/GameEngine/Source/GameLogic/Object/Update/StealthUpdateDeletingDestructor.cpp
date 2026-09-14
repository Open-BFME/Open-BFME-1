// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for StealthUpdate.
// Vtable 0x00CC457C slots name this class (?xfer@StealthUpdate@@MAEXPAVXfer@@@Z); its slot zero routes
// through ILT 0x00035B7A to this 30-byte wrapper, whose complete destructor
// route ILT 0x0003EFC7 reaches cleanup body 0x002AC070.

class StealthUpdate
{
protected:
	virtual ~StealthUpdate();
private:
	friend void forceStealthUpdateDeletingDestructor();
};

void forceStealthUpdateDeletingDestructor()
{
	StealthUpdate value;
}
