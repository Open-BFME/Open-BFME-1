// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for LocomotorSetUpgrade.
// Vtable 0x00CCD0BC slots name this class (?getClassMemoryPool@LocomotorSetUpgrade@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x0001E975 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00020BE4 reaches cleanup body 0x002D6110.

class LocomotorSetUpgrade
{
protected:
	virtual ~LocomotorSetUpgrade();
private:
	friend void forceLocomotorSetUpgradeDeletingDestructor();
};

void forceLocomotorSetUpgradeDeletingDestructor()
{
	LocomotorSetUpgrade value;
}
