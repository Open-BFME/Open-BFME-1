// FireWeaponWhenDamagedBehavior::upgradeImplementation at retail 0x001FB550, 15 bytes: slot 9 of the
// UpgradeMux table 0x010A3DE8, reached only through ILT 0x0000E98A. FireWeaponWhenDamagedBehavior's
// registered constructor 0x001FB5D0 stores that table at its UpgradeMux subobject
// (+0x20). Evidence:
// targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md
// The body is the inline override in ZH FireWeaponWhenDamagedBehavior.h:
//     setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
//
// The bytes are `mov eax,[ecx-0x18] / push 1 / push eax / add ecx,-0x20 /
// call / ret`: the owner (this-0x20) is spelled inline in the call so ecx is
// adjusted after both pushes, and as raw pointer arithmetic because a C++
// base cast would add a null test. 0x000157DA is pinned as the ILT thunk to
// UpdateModule::setWakeFrame; this TU keeps the address-derived view of it.

// ILT 0x000157DA jumps to the matched UpdateModule::setWakeFrame (0x002B2040).
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class UpdateModule
{
	friend class FireWeaponWhenDamagedBehavior;
protected:
	void setWakeFrame( Object *obj, UpdateSleepTime wakeDelay );
	void *m_vtable;
	void *m_moduleData;
	Object *m_object;
};

class FireWeaponWhenDamagedBehavior
{
protected:
	virtual void upgradeImplementation();
};

void FireWeaponWhenDamagedBehavior::upgradeImplementation()
{
	( (UpdateModule *)( (char *)this - 0x20 ) )->setWakeFrame(
		( (UpdateModule *)( (char *)this - 0x20 ) )->m_object, UPDATE_SLEEP_NONE );
}
