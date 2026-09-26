// cl: /DNDEBUG /MD /EHsc

enum ObjectID {};
typedef float Real;

struct XferVersionInfo
{
	unsigned char currentVersion;
	unsigned char version;
};

class Xfer
{
public:
	virtual void reserved00();
	virtual void reserved01();
	virtual void reserved02();
	virtual void reserved03();
	virtual void reserved04();
	virtual void reserved05();
	virtual void reserved06();
	virtual void reserved07();
	virtual void reserved08();
	virtual void reserved09();
	virtual void xferVersion(XferVersionInfo *version);
	virtual void reserved11();
	virtual void reserved12();
	virtual void reserved13();
	virtual void reserved14();
	virtual void reserved15();
	virtual void reserved16();
	virtual void reserved17();
	virtual void reserved18();
	virtual void reserved19();
	virtual void reserved20();
	virtual void reserved21();
	virtual void reserved22();
	virtual void reserved23();
	virtual void reserved24();
	virtual void reserved25();
	virtual void reserved26();
	virtual void xferReal(Real *value);
	virtual void reserved28();
	virtual void reserved29();
	virtual void xferInt(int *value);
};

void friend_xferObjectID(Xfer *xfer, ObjectID *value);

class DockUpdate
{
public:
	virtual void dockUpdateAnchor();

protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_storage[0x88];
};

class RailedTransportDockUpdate : public DockUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_dockingObjectID;
	Real m_pullInsideDistancePerFrame;
	ObjectID m_unloadingObjectID;
	Real m_pushOutsideDistancePerFrame;
	int m_unloadCount;
};

void RailedTransportDockUpdate::xfer(Xfer *xfer)
{
	XferVersionInfo version = { 1, 1 };
	xfer->xferVersion(&version);
	DockUpdate::xfer(xfer);
	friend_xferObjectID(xfer, &m_dockingObjectID);
	xfer->xferReal(&m_pullInsideDistancePerFrame);
	friend_xferObjectID(xfer, &m_unloadingObjectID);
	xfer->xferReal(&m_pushOutsideDistancePerFrame);
	xfer->xferInt(&m_unloadCount);
}
