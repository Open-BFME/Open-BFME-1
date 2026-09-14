// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for HijackerUpdate.
// Vtable 0x00CBF7E4 slots name this class (?getClassMemoryPool@HijackerUpdate@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x0003972A to this 30-byte wrapper, whose complete destructor
// route ILT 0x0000D76F reaches cleanup body 0x00295AC0.

class HijackerUpdate
{
protected:
	virtual ~HijackerUpdate();
private:
	friend void forceHijackerUpdateDeletingDestructor();
};

void forceHijackerUpdateDeletingDestructor()
{
	HijackerUpdate value;
}
