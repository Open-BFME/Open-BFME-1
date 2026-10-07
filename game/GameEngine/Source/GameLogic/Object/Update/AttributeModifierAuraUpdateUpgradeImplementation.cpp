// AttributeModifierAuraUpdate::upgradeImplementation at retail 0x002802D0, 15 bytes: slot 9 of the
// UpgradeMux table 0x010BAD08, reached only through ILT 0x0001B734. AttributeModifierAuraUpdate's
// registered constructor 0x002800D0 stores that table at its UpgradeMux subobject
// (+0x20). Evidence:
// targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md
// AttributeModifierAuraUpdate has no Zero Hour twin; the method name comes from the UpgradeMux
// slot it overrides. The body is the same wake-up the ZH behaviours use.
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
	friend class AttributeModifierAuraUpdate;
protected:
	void setWakeFrame( Object *obj, UpdateSleepTime wakeDelay );
	void *m_vtable;
	void *m_moduleData;
	Object *m_object;
};

class AttributeModifierAuraUpdate
{
protected:
	virtual void upgradeImplementation();
};

void AttributeModifierAuraUpdate::upgradeImplementation()
{
	( (UpdateModule *)( (char *)this - 0x20 ) )->setWakeFrame(
		( (UpdateModule *)( (char *)this - 0x20 ) )->m_object, UPDATE_SLEEP_NONE );
}
