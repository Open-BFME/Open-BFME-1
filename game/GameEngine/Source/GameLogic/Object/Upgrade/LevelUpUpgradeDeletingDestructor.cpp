// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for LevelUpUpgrade.
// Vtable 0x00CCCF64 slots name this class (?getModuleNameKey@LevelUpUpgrade@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x000482DE to this 30-byte wrapper, whose complete destructor
// route ILT 0x0002AA13 reaches cleanup body 0x002D5E90.

class LevelUpUpgrade
{
protected:
	virtual ~LevelUpUpgrade();
private:
	friend void forceLevelUpUpgradeDeletingDestructor();
};

void forceLevelUpUpgradeDeletingDestructor()
{
	LevelUpUpgrade value;
}
