// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DelayedUpgrade.
// Vtable 0x00CCC814 slots name this class (?getModuleNameKey@DelayedUpgrade@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x0000F7CC to this 30-byte wrapper, whose complete destructor
// route ILT 0x00014C04 reaches cleanup body 0x002D4CC0.

class DelayedUpgrade
{
protected:
	virtual ~DelayedUpgrade();
private:
	friend void forceDelayedUpgradeDeletingDestructor();
};

void forceDelayedUpgradeDeletingDestructor()
{
	DelayedUpgrade value;
}
