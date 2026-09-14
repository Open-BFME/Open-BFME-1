// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DestroyDie.
// Vtable 0x00CB2DD4 slots name this class (?getClassMemoryPool@DestroyDie@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x0002D6F0 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00039A13 reaches cleanup body 0x00254F50.

class DestroyDie
{
protected:
	virtual ~DestroyDie();
private:
	friend void forceDestroyDieDeletingDestructor();
};

void forceDestroyDieDeletingDestructor()
{
	DestroyDie value;
}
