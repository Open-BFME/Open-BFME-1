// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ProneUpdate.
// Vtable 0x00CC13F4 slots name this class (?getClassMemoryPool@ProneUpdate@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x00012C2E to this 30-byte wrapper, whose complete destructor
// route ILT 0x00019AA1 reaches cleanup body 0x0029FDF0.

class ProneUpdate
{
protected:
	virtual ~ProneUpdate();
private:
	friend void forceProneUpdateDeletingDestructor();
};

void forceProneUpdateDeletingDestructor()
{
	ProneUpdate value;
}
