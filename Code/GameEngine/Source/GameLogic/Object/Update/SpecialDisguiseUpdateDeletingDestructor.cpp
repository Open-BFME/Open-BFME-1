// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for SpecialDisguiseUpdate.
// Vtable 0x00CB7708 slots name this class (?getModuleNameKey@SpecialDisguiseUpdate@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x0001A5D2 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00008AE4 reaches cleanup body 0x002675F0.

class SpecialDisguiseUpdate
{
protected:
	virtual ~SpecialDisguiseUpdate();
private:
	friend void forceSpecialDisguiseUpdateDeletingDestructor();
};

void forceSpecialDisguiseUpdateDeletingDestructor()
{
	SpecialDisguiseUpdate value;
}
