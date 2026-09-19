// cl: /DNDEBUG /MD /EHsc

// DrawModule slot 14 at retail RVA 0x0074FF90 is an empty setHidden method.
// W3DLightDrawDestructor.cpp records the vtable slot and the bool ABI.

typedef bool Bool;

class DrawModule
{
public:
	virtual void setHidden(Bool hidden);
};

// ?setHidden@DrawModule@@UAEX_N@Z
void DrawModule::setHidden(Bool hidden)
{
}
