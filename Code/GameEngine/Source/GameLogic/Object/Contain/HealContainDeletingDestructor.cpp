// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for HealContain.
// Vtable 0x00CABC78 slots name this class (?getClassMemoryPool@HealContain@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x0000F867 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0003A41D reaches cleanup body 0x00220240.

class HealContain
{
protected:
	virtual ~HealContain();
private:
	friend void forceHealContainDeletingDestructor();
};

void forceHealContainDeletingDestructor()
{
	HealContain value;
}
