// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for MaxHealthUpgrade.
// Vtable 0x00CCD26C slots name this class (?getClassMemoryPool@MaxHealthUpgrade@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x00033681 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0001F8E8 reaches cleanup body 0x002D6320.

class MaxHealthUpgrade
{
protected:
	virtual ~MaxHealthUpgrade();
private:
	friend void forceMaxHealthUpgradeDeletingDestructor();
};

void forceMaxHealthUpgradeDeletingDestructor()
{
	MaxHealthUpgrade value;
}
