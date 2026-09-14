// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AttributeModifierUpgrade.
// Vtable 0x00CCBCD4 slots name this class (?getModuleNameKey@AttributeModifierUpgrade@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x000287E0 to this 30-byte wrapper, whose complete destructor
// route ILT 0x000446E3 reaches cleanup body 0x002D2E30.

class AttributeModifierUpgrade
{
protected:
	virtual ~AttributeModifierUpgrade();
private:
	friend void forceAttributeModifierUpgradeDeletingDestructor();
};

void forceAttributeModifierUpgradeDeletingDestructor()
{
	AttributeModifierUpgrade value;
}
