// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ReflectDamageModuleData.
// Constructor 0x002516D0 installs dedicated vtable 0x00CB22E0; its slot
// zero routes through ILT 0x0002F7B1 to this 30-byte wrapper, whose complete
// destructor route ILT 0x000393B0 reaches cleanup body 0x002518A0.

class ReflectDamageModuleData
{
protected:
	virtual ~ReflectDamageModuleData();
private:
	friend void forceReflectDamageModuleDataDeletingDestructor();
};

void forceReflectDamageModuleDataDeletingDestructor()
{
	ReflectDamageModuleData value;
}
