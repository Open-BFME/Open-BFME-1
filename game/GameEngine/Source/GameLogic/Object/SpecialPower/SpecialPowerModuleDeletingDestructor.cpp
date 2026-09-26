// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for SpecialPowerModule.
// Vtable 0x00CB7C3C slots name this class (?loadPostProcess@SpecialPowerModule@@MAEXXZ); its slot zero routes
// through ILT 0x000138CC to this 30-byte wrapper, whose complete destructor
// route ILT 0x0002041E reaches cleanup body 0x00268F30.

class SpecialPowerModule
{
protected:
	virtual ~SpecialPowerModule();
private:
	friend void forceSpecialPowerModuleDeletingDestructor();
};

void forceSpecialPowerModuleDeletingDestructor()
{
	SpecialPowerModule value;
}
