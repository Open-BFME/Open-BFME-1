// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for StealthDetectorUpdate.
// Vtable 0x00CC3B2C slots name this class (?getClassMemoryPool@StealthDetectorUpdate@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x000064BF to this 30-byte wrapper, whose complete destructor
// route ILT 0x000056C3 reaches cleanup body 0x002AB3B0.

class StealthDetectorUpdate
{
protected:
	virtual ~StealthDetectorUpdate();
private:
	friend void forceStealthDetectorUpdateDeletingDestructor();
};

void forceStealthDetectorUpdateDeletingDestructor()
{
	StealthDetectorUpdate value;
}
