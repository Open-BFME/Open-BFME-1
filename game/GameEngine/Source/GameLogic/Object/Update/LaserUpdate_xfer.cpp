// cl: /DNDEBUG /MD /EHsc
// LaserUpdate::xfer, retail 0x00603A50 (240 bytes).

typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Bool isSaving();
	virtual void slot03();
	virtual Bool isDoingCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *version);
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
	virtual void xferCoord3D(Coord3D *value);
	virtual void slot25();
	virtual void xferAsciiString(void *value);
	virtual void xferReal(Real *value);
	virtual void slot28();
	virtual void xferUnsignedInt(UnsignedInt *value);
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *value);
};

class BfmeSeedTarget;
void bfmeHandOver_0000240A(BfmeSeedTarget *target, void *item);
void BfmeParticleSystemXferHandle(Xfer &xfer, void *value);

class DrawableModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_base[8];
};

class ClientUpdateModule : public DrawableModule
{
protected:
	virtual void clientUpdate();
};

class LaserUpdate : public ClientUpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	Coord3D m_startPos;
	Coord3D m_endPos;
	Bool m_dirty;
	char m_pad24[3];
	UnsignedInt m_particleSystemID;
	UnsignedInt m_targetParticleSystemID;
	Bool m_widening;
	Bool m_decaying;
	char m_pad32[2];
	UnsignedInt m_widenStartFrame;
	UnsignedInt m_widenFinishFrame;
	Real m_currentWidthScalar;
	UnsignedInt m_decayStartFrame;
	UnsignedInt m_decayFinishFrame;
	UnsignedInt m_parentID;
	UnsignedInt m_targetID;
	UnsignedInt m_parentBoneNameData;
};

// ?xfer@LaserUpdate@@MAEXPAVXfer@@@Z
void LaserUpdate::xfer(Xfer *xfer)
{
	ClientUpdateModule::xfer(xfer);
	if (xfer->isDoingCRC())
		return;

	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 2;
	xfer->xferVersion(&version);
	xfer->xferCoord3D(&m_startPos);
	xfer->xferCoord3D(&m_endPos);
	xfer->xferBool(&m_dirty);
	bfmeHandOver_0000240A((BfmeSeedTarget *)xfer, &m_particleSystemID);
	bfmeHandOver_0000240A((BfmeSeedTarget *)xfer, &m_targetParticleSystemID);
	xfer->xferBool(&m_widening);
	xfer->xferBool(&m_decaying);
	xfer->xferUnsignedInt(&m_widenStartFrame);
	xfer->xferUnsignedInt(&m_widenFinishFrame);
	xfer->xferReal(&m_currentWidthScalar);
	xfer->xferUnsignedInt(&m_decayStartFrame);
	xfer->xferUnsignedInt(&m_decayFinishFrame);
	BfmeParticleSystemXferHandle(*xfer, &m_targetID);
	BfmeParticleSystemXferHandle(*xfer, &m_parentBoneNameData);
	if (version.m_currentVersion >= 2)
		xfer->xferUnsignedInt(&m_parentID);
}
