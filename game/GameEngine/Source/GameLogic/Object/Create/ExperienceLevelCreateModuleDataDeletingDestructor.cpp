// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ExperienceLevelCreateModuleData.
// Constructor 0x0024F7A0 installs dedicated vtable 0x00CB15F8; its slot
// zero routes through ILT 0x0003179B to this 30-byte wrapper, whose complete
// destructor route ILT 0x0003FFF8 reaches cleanup body 0x0024F800.

class ExperienceLevelCreateModuleData
{
protected:
	virtual ~ExperienceLevelCreateModuleData();
private:
	friend void forceExperienceLevelCreateModuleDataDeletingDestructor();
};

void forceExperienceLevelCreateModuleDataDeletingDestructor()
{
	ExperienceLevelCreateModuleData value;
}
