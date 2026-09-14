// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DemoTrapUpdate.
// Vtable 0x00CBD7A4 slots name this class (?getClassMemoryPool@DemoTrapUpdate@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x000330C3 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00010FD7 reaches cleanup body 0x0028C7B0.

class DemoTrapUpdate
{
protected:
	virtual ~DemoTrapUpdate();
private:
	friend void forceDemoTrapUpdateDeletingDestructor();
};

void forceDemoTrapUpdateDeletingDestructor()
{
	DemoTrapUpdate value;
}
