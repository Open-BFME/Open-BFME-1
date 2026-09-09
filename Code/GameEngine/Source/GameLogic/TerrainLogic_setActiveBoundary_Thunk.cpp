// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME5: clean C++ reconstruction of TerrainLogic::setActiveBoundary.
//
// Retail's BFME body differs from the ZH source donor after the boundary
// guards: it builds one Region3D, refreshes Radar and the two existing facade
// entry points, notifies every Object, and finally recalculates the camera.
// The member-pointer unions below preserve those already-ledgered facade
// addresses while giving their forwarded arguments their real ABI types.

#include <vector>

typedef float Real;
typedef int Int;

struct ICoord2D
{
	Int x;
	Int y;
};

struct Region3D
{
	Real lo[3];
	Real hi[3];
};

typedef _STL::vector<ICoord2D> BoundaryVector;

class Object;

// BFME's TerrainLogic vtable puts getExtent at slot 8 (+0x20).  The first
// vptr is sufficient here; the unmodelled secondary base is covered by the
// padding before the boundary vector at +0x24.
class __declspec(novtable) TerrainLogic
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void getExtent(Region3D *extent) const = 0;

	void setActiveBoundary(Int newActiveBoundary);

private:
	char m_unmodelled04[0x20];
	BoundaryVector m_boundaries;
	Int m_activeBoundary;
};

// The target calls Radar::newMap through vtable slot 6 (+0x18).
class __declspec(novtable) Radar
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void newMap(TerrainLogic *) = 0;
};

class PartitionManager
{
};

// Existing generated facade rows.  Their bodies are the only known owners of
// these two retail entry points; their forwarded signatures are established
// by this caller's stack arguments and the downstream Region3D setter.
struct Gen_009f2640
{
	void m();
};

struct Gen_008f7390
{
	void m();
};

class GameLogic
{
public:
	Object *getFirstObject();
};

class GameLogic40D9
{
};

class Object
{
public:
	void friend_notifyOfNewMapBoundary();
};

// BFME View vtable slot +0x1b4 is forceCameraConstraintRecalc.  The 109
// preceding entries are deliberately unnamed: only this slot is consumed.
#define BFME_VIEW_SLOT(n) virtual void slot##n() = 0;
class __declspec(novtable) View
{
public:
	BFME_VIEW_SLOT(000) BFME_VIEW_SLOT(001) BFME_VIEW_SLOT(002) BFME_VIEW_SLOT(003)
	BFME_VIEW_SLOT(004) BFME_VIEW_SLOT(005) BFME_VIEW_SLOT(006) BFME_VIEW_SLOT(007)
	BFME_VIEW_SLOT(008) BFME_VIEW_SLOT(009) BFME_VIEW_SLOT(010) BFME_VIEW_SLOT(011)
	BFME_VIEW_SLOT(012) BFME_VIEW_SLOT(013) BFME_VIEW_SLOT(014) BFME_VIEW_SLOT(015)
	BFME_VIEW_SLOT(016) BFME_VIEW_SLOT(017) BFME_VIEW_SLOT(018) BFME_VIEW_SLOT(019)
	BFME_VIEW_SLOT(020) BFME_VIEW_SLOT(021) BFME_VIEW_SLOT(022) BFME_VIEW_SLOT(023)
	BFME_VIEW_SLOT(024) BFME_VIEW_SLOT(025) BFME_VIEW_SLOT(026) BFME_VIEW_SLOT(027)
	BFME_VIEW_SLOT(028) BFME_VIEW_SLOT(029) BFME_VIEW_SLOT(030) BFME_VIEW_SLOT(031)
	BFME_VIEW_SLOT(032) BFME_VIEW_SLOT(033) BFME_VIEW_SLOT(034) BFME_VIEW_SLOT(035)
	BFME_VIEW_SLOT(036) BFME_VIEW_SLOT(037) BFME_VIEW_SLOT(038) BFME_VIEW_SLOT(039)
	BFME_VIEW_SLOT(040) BFME_VIEW_SLOT(041) BFME_VIEW_SLOT(042) BFME_VIEW_SLOT(043)
	BFME_VIEW_SLOT(044) BFME_VIEW_SLOT(045) BFME_VIEW_SLOT(046) BFME_VIEW_SLOT(047)
	BFME_VIEW_SLOT(048) BFME_VIEW_SLOT(049) BFME_VIEW_SLOT(050) BFME_VIEW_SLOT(051)
	BFME_VIEW_SLOT(052) BFME_VIEW_SLOT(053) BFME_VIEW_SLOT(054) BFME_VIEW_SLOT(055)
	BFME_VIEW_SLOT(056) BFME_VIEW_SLOT(057) BFME_VIEW_SLOT(058) BFME_VIEW_SLOT(059)
	BFME_VIEW_SLOT(060) BFME_VIEW_SLOT(061) BFME_VIEW_SLOT(062) BFME_VIEW_SLOT(063)
	BFME_VIEW_SLOT(064) BFME_VIEW_SLOT(065) BFME_VIEW_SLOT(066) BFME_VIEW_SLOT(067)
	BFME_VIEW_SLOT(068) BFME_VIEW_SLOT(069) BFME_VIEW_SLOT(070) BFME_VIEW_SLOT(071)
	BFME_VIEW_SLOT(072) BFME_VIEW_SLOT(073) BFME_VIEW_SLOT(074) BFME_VIEW_SLOT(075)
	BFME_VIEW_SLOT(076) BFME_VIEW_SLOT(077) BFME_VIEW_SLOT(078) BFME_VIEW_SLOT(079)
	BFME_VIEW_SLOT(080) BFME_VIEW_SLOT(081) BFME_VIEW_SLOT(082) BFME_VIEW_SLOT(083)
	BFME_VIEW_SLOT(084) BFME_VIEW_SLOT(085) BFME_VIEW_SLOT(086) BFME_VIEW_SLOT(087)
	BFME_VIEW_SLOT(088) BFME_VIEW_SLOT(089) BFME_VIEW_SLOT(090) BFME_VIEW_SLOT(091)
	BFME_VIEW_SLOT(092) BFME_VIEW_SLOT(093) BFME_VIEW_SLOT(094) BFME_VIEW_SLOT(095)
	BFME_VIEW_SLOT(096) BFME_VIEW_SLOT(097) BFME_VIEW_SLOT(098) BFME_VIEW_SLOT(099)
	BFME_VIEW_SLOT(100) BFME_VIEW_SLOT(101) BFME_VIEW_SLOT(102) BFME_VIEW_SLOT(103)
	BFME_VIEW_SLOT(104) BFME_VIEW_SLOT(105) BFME_VIEW_SLOT(106) BFME_VIEW_SLOT(107)
	BFME_VIEW_SLOT(108)
	virtual void forceCameraConstraintRecalc() = 0;
};
#undef BFME_VIEW_SLOT

extern TerrainLogic *TheTerrainLogic;
extern Radar *TheRadar;
extern PartitionManager *ThePartitionManager;
extern PartitionManager *TheShroudManager;
extern GameLogic40D9 *TheGameLogic40D9;
extern View *TheTacticalView;

void TerrainLogic::setActiveBoundary(Int newActiveBoundary)
{
	if (newActiveBoundary < 0 ||
		newActiveBoundary >= m_boundaries.size())
		return;

	if (newActiveBoundary == m_activeBoundary)
		return;

	if (m_boundaries[newActiveBoundary].x == 0 ||
		m_boundaries[newActiveBoundary].y == 0)
		return;

	Region3D region;
	m_activeBoundary = newActiveBoundary;
	getExtent(&region);
	TheRadar->newMap(TheTerrainLogic);

	typedef void (PartitionManager::*PartitionRegionCall)(Region3D *);
	union
	{
		void (Gen_009f2640::*generic)();
		PartitionRegionCall typed;
	} partitionCall;
	partitionCall.generic = &Gen_009f2640::m;
	(ThePartitionManager->*partitionCall.typed)(&region);

	typedef void (PartitionManager::*ShroudRegionCall)(const Region3D *, Real);
	union
	{
		void (Gen_008f7390::*generic)();
		ShroudRegionCall typed;
	} shroudCall;
	shroudCall.generic = &Gen_008f7390::m;
	(TheShroudManager->*shroudCall.typed)(&region, 0.0f);

	Object *object = reinterpret_cast<GameLogic *>(TheGameLogic40D9)->getFirstObject();
	while (object != 0)
	{
		object->friend_notifyOfNewMapBoundary();
		object = *(Object **)((char *)object + 0x88);
	}

	TheTacticalView->forceCameraConstraintRecalc();
}
