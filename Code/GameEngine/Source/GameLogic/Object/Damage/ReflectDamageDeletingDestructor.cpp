// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ReflectDamage.
// Vtable 0x00CB240C slots name this class (?getModuleNameKey@ReflectDamage@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x00010992 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00007C57 reaches cleanup body 0x00251690.

class ReflectDamage
{
protected:
	virtual ~ReflectDamage();
private:
	friend void forceReflectDamageDeletingDestructor();
};

void forceReflectDamageDeletingDestructor()
{
	ReflectDamage value;
}
