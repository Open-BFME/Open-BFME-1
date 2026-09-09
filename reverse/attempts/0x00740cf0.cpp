// ?calcCameraConstraints@W3DView@@AAEXXZ
// partial score=0.96 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/Generals/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/Generals/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// ?calcCameraConstraints@W3DView@@AAEXXZ

#include "Lib/BaseType.h"
#include "vector3.h"

class GlobalData
{
public:
	unsigned char m_padding[0xA88];
	int m_debugAI;
};

class TerrainLogic
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0C() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual void unused18() = 0;
	virtual void unused1C() = 0;
	virtual void getExtent(Region3D *extent) const = 0;
};

class W3DView
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0C() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual void unused18() = 0;
	virtual void unused1C() = 0;
	virtual void unused20() = 0;
	virtual void unused24() = 0;
	virtual void unused28() = 0;
	virtual void unused2C() = 0;
	virtual void unused30() = 0;
	virtual void unused34() = 0;
	virtual void unused38() = 0;
	virtual Int getWidth() = 0;
	virtual void unused40() = 0;
	virtual Int getHeight() = 0;

private:
	void calcCameraConstraints();
	unsigned char m_padding0004[0x1C];
	Int m_originX;
	Int m_originY;
	unsigned char m_padding0028[0x23D0];
	Real m_groundLevel;
	Region2D m_cameraConstraint;
	bool m_cameraConstraintValid;

	void getPickRay(const ICoord2D *screen, Vector3 *rayStart, Vector3 *rayEnd);
};

extern GlobalData *TheGlobalData;
extern TerrainLogic *TheTerrainLogic;
extern const Real BfmeZeroRange;
extern "C" __declspec(dllimport) int __cdecl _isnan(double value);

void W3DView::calcCameraConstraints()
{
	if (TheTerrainLogic)
	{
		Region3D mapRegion;
		TheTerrainLogic->getExtent(&mapRegion);

		const Real maxEdgeZ = m_groundLevel;
		Coord3D center;
		Coord2D bottom;
		ICoord2D screen;
		Vector3 rayStart, rayEnd;

		screen.x = 0.5f * getWidth() + m_originX;
		screen.y = 0.5f * getHeight() + m_originY;
		getPickRay(&screen, &rayStart, &rayEnd);

		center.x = Vector3::Find_X_At_Z(maxEdgeZ, rayStart, rayEnd);
		center.y = Vector3::Find_Y_At_Z(maxEdgeZ, rayStart, rayEnd);

		screen.y = m_originY + 0.95f * getHeight();
		getPickRay(&screen, &rayStart, &rayEnd);
		bottom.x = Vector3::Find_X_At_Z(maxEdgeZ, rayStart, rayEnd);
		bottom.y = Vector3::Find_Y_At_Z(maxEdgeZ, rayStart, rayEnd);
		center.x -= bottom.x;
		center.y -= bottom.y;
		center.z = BfmeZeroRange;
		Real offset = center.length();
		if (_isnan(offset))
			offset = BfmeZeroRange;
		if (offset > mapRegion.hi.x * 0.25f)
			offset = BfmeZeroRange;

		if (TheGlobalData->m_debugAI)
			offset = -1000;

		m_cameraConstraint.lo.x = mapRegion.lo.x + offset;
		m_cameraConstraint.hi.x = mapRegion.hi.x - offset;
		m_cameraConstraint.lo.y = mapRegion.lo.y + offset;
		m_cameraConstraint.hi.y = mapRegion.hi.y - offset;
		m_cameraConstraintValid = true;
	}
}
