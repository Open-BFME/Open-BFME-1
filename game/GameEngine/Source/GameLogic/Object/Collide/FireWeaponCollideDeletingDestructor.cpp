// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FireWeaponCollide scalar-deleting destructor.
// The matched complete destructor is emitted by
// FireWeaponCollideDestructorThunk.cpp.  This declaration-only TU makes MSVC
// emit the exact retail scalar wrapper and binds its direct call to that
// named class destructor.

class FireWeaponCollide
{
public:
	virtual ~FireWeaponCollide();
};

// ??_GFireWeaponCollide@@UAEPAXI@Z
void forceFireWeaponCollideDeletingDestructor()
{
	FireWeaponCollide value;
}
