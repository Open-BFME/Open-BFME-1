// BroadcastStealthUpdate::upgradeImplementation at retail 0x00289830, 15 bytes: slot 9 of the
// UpgradeMux table 0x010BCAF0, reached only through ILT 0x00031101. BroadcastStealthUpdate's
// registered constructor 0x00289880 stores that table at its UpgradeMux subobject
// (+0x20). Evidence:
// targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md
// BroadcastStealthUpdate has no Zero Hour twin; the method name comes from the UpgradeMux
// slot it overrides. The body is the same wake-up the ZH behaviours use.
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

class BroadcastStealthUpdate
{
protected:
	virtual void upgradeImplementation();
};

void BroadcastStealthUpdate::upgradeImplementation()
{
	( (Gen000157DA *)( (char *)this - 0x20 ) )->handle(
		( (Gen000157DA *)( (char *)this - 0x20 ) )->m_field, 1 );
}
