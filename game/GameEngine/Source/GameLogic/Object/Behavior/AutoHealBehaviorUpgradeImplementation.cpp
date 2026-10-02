// AutoHealBehavior::upgradeImplementation at retail 0x001EE8D0, 15 bytes: slot 9 of the
// UpgradeMux table 0x010A1C20, reached only through ILT 0x0000524F. AutoHealBehavior's
// registered constructor 0x001EE950 stores that table at its UpgradeMux subobject
// (+0x20). Evidence:
// targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md
// The body is the inline override in ZH AutoHealBehavior.h:
//     setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
//
// The bytes are `mov eax,[ecx-0x18] / push 1 / push eax / add ecx,-0x20 /
// call / ret`: the owner (this-0x20) is spelled inline in the call so ecx is
// adjusted after both pushes, and as raw pointer arithmetic because a C++
// base cast would add a null test. 0x000157DA is pinned as the ILT thunk to
// UpdateModule::setWakeFrame; this TU keeps the address-derived view of it.

class Gen000157DA
{
public:
	void handle( int a, int b );
	char m_lead[ 8 ];
	int m_field;
};

class AutoHealBehavior
{
protected:
	virtual void upgradeImplementation();
};

void AutoHealBehavior::upgradeImplementation()
{
	( (Gen000157DA *)( (char *)this - 0x20 ) )->handle(
		( (Gen000157DA *)( (char *)this - 0x20 ) )->m_field, 1 );
}
