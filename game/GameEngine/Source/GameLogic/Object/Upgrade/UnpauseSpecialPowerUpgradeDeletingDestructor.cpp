// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for UnpauseSpecialPowerUpgrade.
// Vtable 0x00CCE464 slots name this class (?getClassMemoryPool@UnpauseSpecialPowerUpgrade@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x0002CF93 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0003C6C8 reaches cleanup body 0x002D96E0.

class UnpauseSpecialPowerUpgrade
{
protected:
	virtual ~UnpauseSpecialPowerUpgrade();
private:
	friend void forceUnpauseSpecialPowerUpgradeDeletingDestructor();
};

void forceUnpauseSpecialPowerUpgradeDeletingDestructor()
{
	UnpauseSpecialPowerUpgrade value;
}
