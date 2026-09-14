// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for BaseUpgrade.
// Vtable 0x00CCC0EC slots name this class (?getModuleNameKey@BaseUpgrade@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x0000DEF9 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0001A785 reaches cleanup body 0x002D3770.

class BaseUpgrade
{
protected:
	virtual ~BaseUpgrade();
private:
	friend void forceBaseUpgradeDeletingDestructor();
};

void forceBaseUpgradeDeletingDestructor()
{
	BaseUpgrade value;
}
