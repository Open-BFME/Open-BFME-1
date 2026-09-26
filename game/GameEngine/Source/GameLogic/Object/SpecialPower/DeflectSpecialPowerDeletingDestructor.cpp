// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DeflectSpecialPower.
// Vtable 0x00CB44EC slots name this class (?getModuleNameKey@DeflectSpecialPower@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x000358A0 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00007180 reaches cleanup body 0x0025A390.

class DeflectSpecialPower
{
protected:
	virtual ~DeflectSpecialPower();
private:
	friend void forceDeflectSpecialPowerDeletingDestructor();
};

void forceDeflectSpecialPowerDeletingDestructor()
{
	DeflectSpecialPower value;
}
