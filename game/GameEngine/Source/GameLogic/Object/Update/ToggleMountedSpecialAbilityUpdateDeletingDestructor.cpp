// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ToggleMountedSpecialAbilityUpdate.
// Vtable 0x00CB88E8 slots name this class (?getModuleNameKey@ToggleMountedSpecialAbilityUpdate@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x000301F2 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0003E5E5 reaches cleanup body 0x0026C550.

class ToggleMountedSpecialAbilityUpdate
{
protected:
	virtual ~ToggleMountedSpecialAbilityUpdate();
private:
	friend void forceToggleMountedSpecialAbilityUpdateDeletingDestructor();
};

void forceToggleMountedSpecialAbilityUpdateDeletingDestructor()
{
	ToggleMountedSpecialAbilityUpdate value;
}
