// cl: /DNDEBUG /MD /EHsc

typedef unsigned char UnsignedByte;

class XferVersion
{
public:
	XferVersion(UnsignedByte major, UnsignedByte minor) :
		m_major(major), m_minor(minor) {}

	UnsignedByte m_major;
	UnsignedByte m_minor;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual bool isLightCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion &value);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual Xfer &xferInt(int &value);
};

// BFME keeps statistics for 32 player slots.  The Snapshot base vptr occupies
// the first word, so the two arrays and their scalar fields land at +0x04,
// +0x84, +0x88 and +0x108 respectively.
class Rva000C84F0MissionStats
{
public:
	void xfer(Xfer *xfer);

private:
	void *m_vtbl;
	int m_unitsKilled[32];
	int m_unitsLost;
	int m_buildingsKilled[32];
	int m_buildingsLost;
};

void Rva000C84F0MissionStats::xfer(Xfer *xfer)
{
	if (!xfer->isLightCRC())
	{
		XferVersion version(1, 1);
		xfer->xferVersion(version);
		xfer->xferInt(m_unitsLost);

		for (int i = 0; i < 32; ++i)
		{
			xfer->xferInt(m_unitsKilled[i]);
			xfer->xferInt(m_buildingsKilled[i]);
		}

		xfer->xferInt(m_buildingsLost);
	}
}
