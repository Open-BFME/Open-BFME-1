// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail's five-byte ILT entry at 0x000205F4 jumps to the real
// FirewallHelperClass::detectionBeginUpdate body at 0x0066EFA0. The entry lives
// in its own unit so FirewallHelper.obj (Generals-header AsciiString inline
// copies) no longer owns a row below retail's StringBase providers and sorts
// ahead of them in link order.

class FirewallHelperClass
{
public:
	bool detectionBeginUpdate();
};

class FirewallHelperDetectionBeginUpdateShim
{
public:
	bool thunk();
};

// ?detectionBeginUpdate@FirewallHelperClass@@QAE_NXZ
bool FirewallHelperDetectionBeginUpdateShim::thunk()
{
	return ((FirewallHelperClass *) this)->detectionBeginUpdate();
}
