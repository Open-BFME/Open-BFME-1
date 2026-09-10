// ?screenToTerrain@W3DView@@UAE_NPBUICoord2D@@PAUCoord3D@@_N@Z
// partial score=0.68 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ivendor/stlport /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// BFME W3DView::screenToTerrain at retail 0x00746420 (full 787 bytes).
//
// The shipped ZH header has the two-argument void method, but BFME's vtable
// slot 89 is a three-argument Bool method.  The extra terrainOnly argument is
// proven by the retail ret 0xc and by the FireWeapon, InGameUI, and Miles
// screen-center shims.  Keep this reconstruction TU-local until the exact
// symbol and cache layout have been independently verified.

#include "Common/BuildAssistant.h"
#include "Common/STLTypedefs.h"
#include "GameClient/Drawable.h"
#include "GameClient/View.h"
#include "GameLogic/TerrainLogic.h"
#include "W3DDevice/GameClient/BaseHeightMap.h"
#include <coltest.h>
#include <lineseg.h>

struct BfmePosRequest
{
	ICoord2D first;
	Coord3D second;
	Int bfmePadding;
};

typedef std::vector<BfmePosRequest> BfmePosRequests;

struct BfmeCastResult
{
	Int bfmePadding;
	CastResultStruct result;
};

class W3DView
{
public:
	virtual Bool screenToTerrain(const ICoord2D *screen, Coord3D *world,
		Bool terrainOnly);

	void getPickRay(const ICoord2D *screen, Vector3 *rayStart, Vector3 *rayEnd);

	private:
	unsigned char m_padding04[0x23c8 - 4];
	Bool m_cameraHasMovedSinceRequest;
	BfmePosRequests m_locationRequests;
};

Bool W3DView::screenToTerrain(const ICoord2D *screen, Coord3D *world,
	Bool terrainOnly)
{
	register Coord3D *out = world;
	register const ICoord2D *pixel = screen;

	if (pixel == NULL || out == NULL || TheTerrainRenderObject == NULL)
		return FALSE;

	if (!terrainOnly)
	{
		if (m_cameraHasMovedSinceRequest)
		{
			m_locationRequests.clear();
			m_cameraHasMovedSinceRequest = false;
		}

		if (m_locationRequests.size() > 40)
			m_locationRequests.erase(m_locationRequests.begin(),
				m_locationRequests.begin() + 10);

		for (int i = m_locationRequests.size() - 1; i >= 0; --i)
		{
			if (m_locationRequests[i].first.x == pixel->x &&
				m_locationRequests[i].first.y == pixel->y)
			{
				*out = m_locationRequests[i].second;
				return TRUE;
			}
		}
	}

	Vector3 rayStart, rayEnd;
	LineSegClass lineseg;
	BfmeCastResult castResult;
	Vector3 intersection(0, 0, 0);
	Bool found = FALSE;

	getPickRay(pixel, &rayStart, &rayEnd);
	lineseg.Set(rayStart, rayEnd);
	RayCollisionTestClass raytest(lineseg, &castResult.result);

	if (TheTerrainRenderObject->Cast_Ray(raytest))
	{
		intersection = castResult.result.ContactPoint;
		found = TRUE;
	}

	if (!terrainOnly)
	{
		Vector3 bridgePt;
		Drawable *bridge = TheTerrainLogic->pickBridge(rayStart, rayEnd,
			&bridgePt);
		if (bridge != NULL && bridgePt.Z > intersection.Z)
		{
			intersection = bridgePt;
			found = TRUE;
		}
	}

	out->x = intersection.X;
	out->y = intersection.Y;
	out->z = intersection.Z;

	if (!terrainOnly)
	{
		BfmePosRequest request;
		request.first = *pixel;
		request.second = *out;
		m_locationRequests.push_back(request);
	}

	return found;
}
