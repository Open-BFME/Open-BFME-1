// ?xfer@GarrisonContain@@MAEXPAVXfer@@@Z
// partial score=0.99007 date=2026-09-23
// Partial clean C++ reconstruction for retail RVA 0x0021DAA0.
// The owner is GarrisonContain::xfer: constructor 0x0021D820 installs
// vtable 0x010AB818 and slot 3 reaches this RVA.  The surrounding source
// file carries the TU-local BFME Xfer ABI and field view used to compile it.

// The banked body was missing its detached-TU declarations.  These views are
// the witnessed BFME ABI: 0x489DC is the reviewed base transfer helper,
// 0x0000C9B4 is the two ObjectID hand-overs, and 0x00008CA1 is the separate
// particle-system handle helper.
// cl: /DNDEBUG /MD /EHsc /O2

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

struct XferException
{
	char *text;
	Int tag;
};

union BfmeGarrisonXferWorking
{
	XferException error;
	struct
	{
		Int loopCount;
		UnsignedInt teamID;
	} values;
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
public:
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
extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, Int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern int g_guardTargetTypeThrowInfo;

void GarrisonContain::xfer(Xfer *xfer)
{
	BfmeGarrisonXferTarget *target =
		reinterpret_cast<BfmeGarrisonXferTarget *>(xfer);
	BfmeGarrisonXferView *self =
		reinterpret_cast<BfmeGarrisonXferView *>(this);

	reinterpret_cast<BfmeBase002298B0 *>(this)->xferBase2298B0(xfer);
	if (target->isLightCRC())
		return;

	BfmeGarrisonXferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	target->xferVersion(&version);

	{
		BfmeGarrisonXferWorking working;
		working.values.teamID = self->m_originalTeam ? self->m_originalTeam->getID() : 0;
		target->xferUnsignedInt(&working.values.teamID);
		if (target->isLoading())
		{
			if (working.values.teamID)
			{
				self->m_originalTeam = TheTeamFactory->findTeamByID(working.values.teamID);
				if (self->m_originalTeam == 0)
				{
					bfmeFormatText(&working.error, 5, 0);
					_CxxThrowException(&working.error, &g_guardTargetTypeThrowInfo);
				}
			}
			else
				self->m_originalTeam = 0;
		}
	}

	Int i;
	target->xferBool(&self->m_hideGarrisonedStateFromNonallies);
	UnsignedShort pointDataCount = MAX_GARRISON_POINTS;
	target->xferUnsignedShort(&pointDataCount);
	i = 0;
	if (pointDataCount <= i)
		goto garrison_point_done;
	{
		UnsignedInt *point = &self->m_garrisonPointData[0].targetID;
		do
		{
			bfmeHandOver_0000C9B4(target, point - 1);
			bfmeHandOver_0000C9B4(target, point);
			target->xferUnsignedInt(point + 1);
			target->xferUnsignedInt(point + 2);
			BfmeParticleSystemXferHandle(*xfer, point + 3);
			++i;
			point += 5;
		} while (i < pointDataCount);
	}
garrison_point_done:

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
