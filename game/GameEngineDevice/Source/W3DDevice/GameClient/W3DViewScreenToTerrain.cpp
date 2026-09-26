// BFME W3DView::screenToTerrain at retail RVA 0x00746420.
// Vtable slot, ABI, cache record layout, and callee contracts are established by reverse evidence.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/vendor/stlport /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

#include "Common/BuildAssistant.h"
#include "Common/STLTypedefs.h"
#include "GameClient/Drawable.h"
#include "GameClient/View.h"
#include "W3DDevice/GameClient/BaseHeightMap.h"
#include <coltest.h>
#include <lineseg.h>

struct Rva00746420Record
{
	ICoord2D first;
	Coord3D second;
	Bool found;
};

typedef std::vector<Rva00746420Record> Rva00746420Records;

class Bridge;

class TerrainLogic
{
public:
	virtual void _tl_00(void) = 0;
	virtual void _tl_01(void) = 0;
	virtual void _tl_02(void) = 0;
	virtual void _tl_03(void) = 0;
	virtual void _tl_04(void) = 0;
	virtual void _tl_05(void) = 0;
	virtual void _tl_06(void) = 0;
	virtual void _tl_07(void) = 0;
	virtual void _tl_08(void) = 0;
	virtual void _tl_09(void) = 0;
	virtual void _tl_10(void) = 0;
	virtual void _tl_11(void) = 0;
	virtual void _tl_12(void) = 0;
	virtual void _tl_13(void) = 0;
	virtual void _tl_14(void) = 0;
	virtual void _tl_15(void) = 0;
	virtual void _tl_16(void) = 0;
	virtual void _tl_17(void) = 0;
	virtual void _tl_18(void) = 0;
	virtual void _tl_19(void) = 0;
	virtual void _tl_20(void) = 0;
	virtual void _tl_21(void) = 0;
	virtual void _tl_22(void) = 0;
	virtual void _tl_23(void) = 0;
	virtual void _tl_24(void) = 0;
	virtual void _tl_25(void) = 0;
	virtual void _tl_26(void) = 0;
	virtual void _tl_27(void) = 0;
	virtual void _tl_28(void) = 0;
	virtual void _tl_29(void) = 0;
	virtual void _tl_30(void) = 0;
	virtual void _tl_31(void) = 0;
	virtual void _tl_32(void) = 0;
	virtual void _tl_33(void) = 0;
	virtual void _tl_34(void) = 0;
	virtual void _tl_35(void) = 0;
	virtual void _tl_36(void) = 0;
	virtual Bridge *getFirstBridge(void) = 0;
	virtual void _tl_38(void) = 0;
	virtual void _tl_39(void) = 0;
	virtual void _tl_40(void) = 0;
	virtual void _tl_41(void) = 0;
	virtual Bool pickBridge(const Vector3 &from, const Vector3 &to, Vector3 *pos);
	virtual void _tl_43(void) = 0;
	virtual void _tl_44(void) = 0;
	virtual void deleteBridge(Bridge *bridge);
	virtual void updateBridgeDamageStates(void);
};

extern TerrainLogic *TheTerrainLogic;

class W3DView
{
public:
	virtual Bool screenToTerrain(const ICoord2D *screen, Coord3D *world,
		Bool terrainOnly);

	private:
	void getPickRay(const ICoord2D *screen, Vector3 *rayStart, Vector3 *rayEnd);

	unsigned char m_padding04[0x23c8 - 4];
	Bool m_cameraHasMovedSinceRequest;
	Rva00746420Records m_locationRequests;
};

Bool W3DView::screenToTerrain(const ICoord2D *screen, Coord3D *world,
	Bool terrainOnly)
{
	register const ICoord2D *pixel = screen;
	register Coord3D *out = world;

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
				return m_locationRequests[i].found;
			}
		}
	}

	Vector3 rayEnd, rayStart;
	LineSegClass lineseg;
	CastResultStruct castResult;
	Vector3 intersection(0, 0, 0);
	Bool found = FALSE;

	getPickRay(pixel, &rayEnd, &rayStart);
	lineseg.Set(rayEnd, rayStart);
	RayCollisionTestClass raytest(lineseg, &castResult);

	if (TheTerrainRenderObject->Cast_Ray(raytest))
	{
		intersection = castResult.ContactPoint;
		found = TRUE;
	}

	if (!terrainOnly)
	{
		Vector3 bridgePt;
		Bool bridge = TheTerrainLogic->pickBridge(rayEnd, rayStart,
			&bridgePt);
		if (bridge != NULL && (!found || bridgePt.Z > intersection.Z))
		{
			intersection = bridgePt;
			found = TRUE;
		}
	}

	if (found)
	{
		out->x = intersection.X;
		out->y = intersection.Y;
		out->z = intersection.Z;
	}
	else
	{
		out->x = rayStart.X;
		out->y = rayStart.Y;
		out->z = rayStart.Z;
	}

	if (!terrainOnly)
	{
		Rva00746420Record request;
		request.first = *pixel;
		request.second = *out;
		request.found = found;
		m_locationRequests.push_back(request);
	}

	return found;
}

