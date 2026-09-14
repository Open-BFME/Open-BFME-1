// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ExperienceScalarUpgrade.
// Vtable 0x00CCC9A4 slots name this class (?getClassMemoryPool@ExperienceScalarUpgrade@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x0003976B to this 30-byte wrapper, whose complete destructor
// route ILT 0x000423E3 reaches cleanup body 0x002D4F50.

class ExperienceScalarUpgrade
{
protected:
	virtual ~ExperienceScalarUpgrade();
private:
	friend void forceExperienceScalarUpgradeDeletingDestructor();
};

void forceExperienceScalarUpgradeDeletingDestructor()
{
	ExperienceScalarUpgrade value;
}
