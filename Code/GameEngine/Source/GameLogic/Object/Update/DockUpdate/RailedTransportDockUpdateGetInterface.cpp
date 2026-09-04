class DockUpdateStorage
{
public:
	virtual void dockUpdateAnchor();

private:
	char m_storage[0x84];
};

class RailedTransportDockUpdateInterface
{
public:
	virtual void railedTransportDockAnchor();
};

class RailedTransportDockUpdate : public DockUpdateStorage,
	public RailedTransportDockUpdateInterface
{
public:
	virtual RailedTransportDockUpdateInterface *getRailedTransportDockUpdateInterface();
};

RailedTransportDockUpdateInterface *RailedTransportDockUpdate::getRailedTransportDockUpdateInterface()
{
	return this;
}
