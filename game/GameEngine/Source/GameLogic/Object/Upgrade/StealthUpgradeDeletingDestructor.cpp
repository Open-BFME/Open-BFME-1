// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for StealthUpgrade.
// Vtable 0x00CCDE6C slots name this class (?getClassMemoryPool@StealthUpgrade@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x0003B19C to this 30-byte wrapper, whose complete destructor
// route ILT 0x00012823 reaches cleanup body 0x002D7FC0.

class StealthUpgrade
{
protected:
	virtual ~StealthUpgrade();
private:
	friend void forceStealthUpgradeDeletingDestructor();
};

void forceStealthUpgradeDeletingDestructor()
{
	StealthUpgrade value;
}
