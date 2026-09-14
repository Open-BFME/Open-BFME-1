// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for FireWeaponWhenDeadBehavior.
// Vtable 0x00CA405C slots name this class (?getClassMemoryPool@FireWeaponWhenDeadBehavior@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x00022679 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0002D6FA reaches cleanup body 0x001FBFC0.

class FireWeaponWhenDeadBehavior
{
protected:
	virtual ~FireWeaponWhenDeadBehavior();
private:
	friend void forceFireWeaponWhenDeadBehaviorDeletingDestructor();
};

void forceFireWeaponWhenDeadBehaviorDeletingDestructor()
{
	FireWeaponWhenDeadBehavior value;
}
