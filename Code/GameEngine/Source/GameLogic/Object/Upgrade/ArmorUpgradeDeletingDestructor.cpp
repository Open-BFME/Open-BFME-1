// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ArmorUpgrade.
// Vtable 0x00CCBB54 slots name this class (?getClassMemoryPool@ArmorUpgrade@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x00031AC0 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00010118 reaches cleanup body 0x002D2A60.

class ArmorUpgrade
{
protected:
	virtual ~ArmorUpgrade();
private:
	friend void forceArmorUpgradeDeletingDestructor();
};

void forceArmorUpgradeDeletingDestructor()
{
	ArmorUpgrade value;
}
