// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ModelConditionUpgrade.
// Vtable 0x00CCD48C slots name this class (?getClassMemoryPool@ModelConditionUpgrade@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x0003C1E1 to this 30-byte wrapper, whose complete destructor
// route ILT 0x000387F3 reaches cleanup body 0x002D6650.

class ModelConditionUpgrade
{
protected:
	virtual ~ModelConditionUpgrade();
private:
	friend void forceModelConditionUpgradeDeletingDestructor();
};

void forceModelConditionUpgradeDeletingDestructor()
{
	ModelConditionUpgrade value;
}
