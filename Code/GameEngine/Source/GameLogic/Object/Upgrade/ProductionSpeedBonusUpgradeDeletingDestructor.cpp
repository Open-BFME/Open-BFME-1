// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ProductionSpeedBonusUpgrade.
// Vtable 0x00CCD95C slots name this class (?getModuleNameKey@ProductionSpeedBonusUpgrade@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x0002D466 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00027A6B reaches cleanup body 0x002D76F0.

class ProductionSpeedBonusUpgrade
{
protected:
	virtual ~ProductionSpeedBonusUpgrade();
private:
	friend void forceProductionSpeedBonusUpgradeDeletingDestructor();
};

void forceProductionSpeedBonusUpgradeDeletingDestructor()
{
	ProductionSpeedBonusUpgrade value;
}
