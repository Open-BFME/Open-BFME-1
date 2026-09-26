// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for SubObjectsUpgrade.
// Vtable 0x00CCDFC4 slots name this class (?getClassMemoryPool@SubObjectsUpgrade@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x0002C1E2 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0000A466 reaches cleanup body 0x002D81F0.

class SubObjectsUpgrade
{
protected:
	virtual ~SubObjectsUpgrade();
private:
	friend void forceSubObjectsUpgradeDeletingDestructor();
};

void forceSubObjectsUpgradeDeletingDestructor()
{
	SubObjectsUpgrade value;
}
