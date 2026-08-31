// cl: /DNDEBUG /MD /EHsc

typedef float Real;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Xfer
{
public:
	struct Version
	{
		unsigned char minimum;
		unsigned char current;
	};

	virtual void reserved00(); virtual void reserved01();
	virtual void reserved02(); virtual void reserved03();
	virtual bool skipsSlavedState();
	virtual void reserved05(); virtual void reserved06();
	virtual void reserved07(); virtual void reserved08();
	virtual void xferUser(void *value, int size);
	virtual void xferVersion(Version *version);
	virtual void reserved11(); virtual void reserved12();
	virtual void reserved13(); virtual void reserved14();
	virtual void reserved15(); virtual void reserved16();
	virtual void reserved17(); virtual void reserved18();
	virtual void reserved19(); virtual void reserved20();
	virtual void reserved21(); virtual void reserved22();
	virtual void reserved23();
	virtual void xferCoord3D(Coord3D *value);
	virtual void reserved25(); virtual void reserved26();
	virtual void reserved27(); virtual void reserved28();
	virtual void reserved29();
	virtual void xferInt(int *value);
	virtual void reserved31(); virtual void reserved32();
	virtual void reserved33(); virtual void reserved34();
	virtual void xferBool(bool *value);
};

void friend_xferObjectID(Xfer *xfer, ObjectID *id);

class UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_baseState[0x20];
};

class SlavedUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_slaver;
	Coord3D m_guardPointOffset;
	int m_framesToWait;
	int m_repairState;
	bool m_repairing;
	unsigned char m_padding3D[3];
	ObjectID m_version2ObjectID;
};

// ?xfer@SlavedUpdate@@MAEXPAVXfer@@@Z
void SlavedUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->skipsSlavedState())
		return;

	Xfer::Version version;
	version.minimum = 1;
	version.current = 2;
	xfer->xferVersion(&version);
	friend_xferObjectID(xfer, &m_slaver);
	xfer->xferCoord3D(&m_guardPointOffset);
	xfer->xferInt(&m_framesToWait);
	xfer->xferUser(&m_repairState, sizeof(m_repairState));
	xfer->xferBool(&m_repairing);
	if (version.current >= 2)
		friend_xferObjectID(xfer, &m_version2ObjectID);
}
