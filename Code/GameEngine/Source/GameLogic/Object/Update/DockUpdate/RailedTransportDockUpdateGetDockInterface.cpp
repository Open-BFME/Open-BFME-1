class DockUpdateInterface;

class RailedTransportDockUpdate
{
public:
	virtual DockUpdateInterface *getDockUpdateInterface();
};

DockUpdateInterface *RailedTransportDockUpdate::getDockUpdateInterface()
{
	// This vtable entry receives the BehaviorModuleInterface subobject at +0x0C.
	RailedTransportDockUpdate *self =
		(RailedTransportDockUpdate *)((char *)this - 0x0C);
	if (self)
		return (DockUpdateInterface *)((char *)this + 0x14);

	return 0;
}
