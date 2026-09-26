// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for KeepObjectDie.
// Vtable 0x00CB3224 slots name this class (?getClassMemoryPool@KeepObjectDie@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x000098EA to this 30-byte wrapper, whose complete destructor
// route ILT 0x00029A8C reaches cleanup body 0x00255840.

class KeepObjectDie
{
protected:
	virtual ~KeepObjectDie();
private:
	friend void forceKeepObjectDieDeletingDestructor();
};

void forceKeepObjectDieDeletingDestructor()
{
	KeepObjectDie value;
}
