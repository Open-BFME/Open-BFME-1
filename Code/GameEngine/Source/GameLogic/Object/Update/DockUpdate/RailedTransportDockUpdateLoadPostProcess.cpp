class DockUpdate
{
protected:
	virtual void loadPostProcess();
};

class RailedTransportDockUpdate : public DockUpdate
{
protected:
	virtual void loadPostProcess();
};

void RailedTransportDockUpdate::loadPostProcess()
{
	DockUpdate::loadPostProcess();
}
