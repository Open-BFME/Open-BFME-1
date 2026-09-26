// cl: /DNDEBUG /MD /EHsc /O2
// GarrisonContain::xfer, retail RVA 0x0021DAA0, 403 bytes (ret 4 at +0x190).
// Identity: constructor 0x0021D820 (??0GarrisonContain) installs vtable
// 0x010AB818 and slot 3 reaches this body through ILT 0x0000EAA7.
// ZH twin: GarrisonContain.cpp GarrisonContain::xfer. BFME runs the base
// transfer first (ILT 0x000489DC -> 0x002298B0), returns early on a
// light-CRC pass, scopes the version record, and throws the RTTI-proven
// eight-byte XferException (ThrowInfo VA 0x011DFE5C, variadic constructor
// 0x009D6220). The version block and the unbraced throw give retail's
// frame: $T exception and version on esp+0, teamID on esp+8.
// 0x0000C9B4 is the ObjectID hand-over helper and 0x00008CA1 the separate
// particle-system handle helper.

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct BfmeGarrisonXferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
	UnsignedByte m_padding[2];
};

class XferException
{
public:
	XferException(Int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	Int tag;
};

class Team
{
public:
	UnsignedInt getID() const { return m_id; }

private:
	UnsignedByte m_beforeId[8];
	UnsignedInt m_id;
};

class TeamFactory
{
public:
	Team *findTeamByID(UnsignedInt id);
};

extern TeamFactory *TheTeamFactory;

class Xfer;

class BfmeSeedTarget
{
public:
	virtual void slot00();
	virtual Bool isLoading();
	virtual void slot02();
	virtual void slot03();
	virtual Bool isLightCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(BfmeGarrisonXferVersion *version);
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
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void xferUnsignedInt(UnsignedInt *value);
	virtual void xferInt(Int *value);
	virtual void xferUnsignedShort(UnsignedShort *value);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *value);
};

typedef BfmeSeedTarget BfmeGarrisonXferTarget;

class BfmeBase002298B0
{
	friend class GarrisonContain;
	void xferBase2298B0(Xfer *target);
};

struct BfmeGarrisonPointData
{
	void *object;
	UnsignedInt targetID;
	UnsignedInt placeFrame;
	UnsignedInt lastEffectFrame;
	void *effect;
};

class BfmeGarrisonXferView
{
public:
	UnsignedByte m_beforeOriginalTeam[0xd4];
	Team *m_originalTeam;
	BfmeGarrisonPointData m_garrisonPointData[40];
	Int m_garrisonPointsInUse;
	Coord3D m_garrisonPoint[3][40];
	UnsignedByte m_unmodelled_99c[0xc];
	Coord3D m_exitRallyPoint;
	Bool m_garrisonPointsInitialized;
	Bool m_hideGarrisonedStateFromNonallies;
	Bool m_rallyValid;
};

enum { MAX_GARRISON_POINTS = 40 };

class GarrisonContain
{
protected:
	virtual void xfer(Xfer *xfer);
};

extern void bfmeHandOver_0000C9B4(BfmeSeedTarget *target, void *item);
extern void BfmeParticleSystemXferHandle(Xfer &target, void *item);
void GarrisonContain::xfer(Xfer *xfer)
{
	BfmeGarrisonXferTarget *target =
		reinterpret_cast<BfmeGarrisonXferTarget *>(xfer);
	BfmeGarrisonXferView *self =
		reinterpret_cast<BfmeGarrisonXferView *>(this);
	Int i;

	reinterpret_cast<BfmeBase002298B0 *>(this)->xferBase2298B0(xfer);
	if (target->isLightCRC())
		return;

	{
		BfmeGarrisonXferVersion version;
		version.m_version = 1;
		version.m_currentVersion = 1;
		target->xferVersion(&version);
	}

	UnsignedInt teamID = self->m_originalTeam ? self->m_originalTeam->getID() : 0;
	target->xferUnsignedInt(&teamID);
	if (target->isLoading())
	{
		if (teamID)
		{
			self->m_originalTeam = TheTeamFactory->findTeamByID(teamID);
			if (self->m_originalTeam == 0)
				throw XferException(5, 0);
		}
		else
			self->m_originalTeam = 0;
	}

	target->xferBool(&self->m_hideGarrisonedStateFromNonallies);
	UnsignedShort pointDataCount = MAX_GARRISON_POINTS;
	target->xferUnsignedShort(&pointDataCount);
	for (i = 0; i < pointDataCount; ++i)
	{
		bfmeHandOver_0000C9B4(target, &self->m_garrisonPointData[i].object);
		bfmeHandOver_0000C9B4(target, &self->m_garrisonPointData[i].targetID);
		target->xferUnsignedInt(&self->m_garrisonPointData[i].placeFrame);
		target->xferUnsignedInt(&self->m_garrisonPointData[i].lastEffectFrame);
		BfmeParticleSystemXferHandle(*xfer, &self->m_garrisonPointData[i].effect);
	}

	target->xferInt(&self->m_garrisonPointsInUse);
	for (i = 0; i < 3; ++i)
	{
		for (Int j = 0; j < MAX_GARRISON_POINTS; ++j)
			target->xferCoord3D(&self->m_garrisonPoint[i][j]);
	}
	target->xferBool(&self->m_garrisonPointsInitialized);
	target->xferBool(&self->m_rallyValid);
	target->xferCoord3D(&self->m_exitRallyPoint);
}
