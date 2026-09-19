// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME5: GateProxyBehaviorModuleData scalar-deleting destructor at retail
// RVA 0x001FCE40 (30 bytes). The matched constructor at 0x001FCEC0 installs
// vtable 0x0108A2A0; the complete destructor at 0x001FCB50 tears down the
// seven-member snapshot-derived layout including four ThingRef members and
// two STLport string vectors. GateOpenAndCloseBehaviorModuleData already has
// matched constructor and complete-destructor aliases at the same addresses;
// its identical vtable and scalar wrapper are folded here as well.

class GateProxyBehaviorModuleData
{
public:
	virtual ~GateProxyBehaviorModuleData();
};

void forceGateProxyBehaviorModuleDataDeletingDestructor()
{
	GateProxyBehaviorModuleData value;
}
