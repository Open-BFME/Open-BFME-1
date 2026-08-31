// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;
typedef float Real;

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
	virtual bool skipsRubbleState();
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
	virtual void xferReal(Real *value);
	virtual void reserved28();
	virtual void xferUnsignedInt(UnsignedInt *value);
};

class UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_baseState[0x20];
};

class RubbleRiseUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	UnsignedInt m_phaseFrame;
	UnsignedInt m_nextRiseFrame;
	UnsignedInt m_riseState;
	Real m_riseVelocity;
	Real m_currentHeight;
	Real m_rubbleHeight;
	Coord3D m_risePosition;
};

// ?xfer@RubbleRiseUpdate@@MAEXPAVXfer@@@Z
void RubbleRiseUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->skipsRubbleState())
		return;

	Xfer::Version version;
	version.minimum = 1;
	version.current = 2;
	xfer->xferVersion(&version);
	xfer->xferUnsignedInt(&m_phaseFrame);
	xfer->xferUnsignedInt(&m_nextRiseFrame);
	xfer->xferUser(&m_riseState, sizeof(m_riseState));
	xfer->xferReal(&m_riseVelocity);
	xfer->xferReal(&m_currentHeight);
	xfer->xferCoord3D(&m_risePosition);
	if (version.current >= 2)
		xfer->xferReal(&m_rubbleHeight);
}
