// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for CaveContain.
// Vtable 0x00CAB000 slots name this class (?getClassMemoryPool@CaveContain@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x0001B35B to this 30-byte wrapper, whose complete destructor
// route ILT 0x0002748F reaches cleanup body 0x00219290.

class CaveContain
{
protected:
	virtual ~CaveContain();
private:
	friend void forceCaveContainDeletingDestructor();
};

void forceCaveContainDeletingDestructor()
{
	CaveContain value;
}
