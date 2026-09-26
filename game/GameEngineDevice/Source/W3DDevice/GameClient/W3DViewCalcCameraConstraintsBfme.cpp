// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// BFME W3DView::calcCameraConstraints, retail 0x00740CF0 / 496 bytes.
// Identity: the matched W3DView::setCameraTransform (0x007423B0) calls it
// through ILT 0x00014934, which jumps here; the body is the Zero Hour
// W3DView.cpp routine plus BFME's _isnan and quarter-map-width clamps.
// Retail's 0x50 frame packs the Coord3D bottom onto the dead screen pair:
// VC7.1 overlaps the two only when screen is scoped to the pick-ray block.

#include "Lib/BaseType.h"
#include "vector3.h"

class GlobalData
{
public:
	unsigned char m_padding[0xA88];
	Int m_debugAI;
};

class TerrainLogic
{
public:
	virtual void terrainSlot00() = 0;
	virtual void terrainSlot04() = 0;
	virtual void terrainSlot08() = 0;
	virtual void terrainSlot0C() = 0;
	virtual void terrainSlot10() = 0;
	virtual void terrainSlot14() = 0;
	virtual void terrainSlot18() = 0;
	virtual void terrainSlot1C() = 0;
	virtual void getExtent(Region3D *extent) const = 0;
};

class W3DView
{
public:
	virtual void viewSlot00() = 0;
	virtual void viewSlot04() = 0;
	virtual void viewSlot08() = 0;
	virtual void viewSlot0C() = 0;
	virtual void viewSlot10() = 0;
	virtual void viewSlot14() = 0;
	virtual void viewSlot18() = 0;
	virtual void viewSlot1C() = 0;
	virtual void viewSlot20() = 0;
	virtual void viewSlot24() = 0;
	virtual void viewSlot28() = 0;
	virtual void viewSlot2C() = 0;
	virtual void viewSlot30() = 0;
	virtual void viewSlot34() = 0;
	virtual void viewSlot38() = 0;
	virtual Int getWidth() = 0;
	virtual void viewSlot40() = 0;
	virtual Int getHeight() = 0;

private:
	void calcCameraConstraints();
	void getPickRay(const ICoord2D *screen, Vector3 *rayStart, Vector3 *rayEnd);

	unsigned char m_padding0004[0x1C];
	Int m_originX;
	Int m_originY;
	unsigned char m_padding0028[0x23F8 - 0x28];
	Real m_groundLevel;
	Region2D m_cameraConstraint;
	Bool m_cameraConstraintValid;
};

extern GlobalData *TheWritableGlobalData;
#define TheGlobalData TheWritableGlobalData
extern TerrainLogic *TheTerrainLogic;
extern const Real BfmeZeroRange;
extern "C" __declspec(dllimport) int __cdecl _isnan(double value);

void W3DView::calcCameraConstraints()
{
	if (TheTerrainLogic)
	{
		Region3D mapRegion;
		TheTerrainLogic->getExtent(&mapRegion);

		Real maxEdgeZ = m_groundLevel;
		Coord3D center, bottom;
		Vector3 rayStart, rayEnd;
		{
			ICoord2D screen;

			//Pick at the center
			screen.x = 0.5f * getWidth() + m_originX;
			screen.y = 0.5f * getHeight() + m_originY;
			getPickRay(&screen, &rayStart, &rayEnd);

			center.x = Vector3::Find_X_At_Z(maxEdgeZ, rayStart, rayEnd);
			center.y = Vector3::Find_Y_At_Z(maxEdgeZ, rayStart, rayEnd);
			center.z = maxEdgeZ;

			screen.y = m_originY + 0.95f * getHeight();
			getPickRay(&screen, &rayStart, &rayEnd);
		}
		bottom.x = Vector3::Find_X_At_Z(maxEdgeZ, rayStart, rayEnd);
		bottom.y = Vector3::Find_Y_At_Z(maxEdgeZ, rayStart, rayEnd);
		bottom.z = maxEdgeZ;
		center.x -= bottom.x;
		center.y -= bottom.y;
		center.z = BfmeZeroRange;

		Real offset = center.length();
		if (_isnan(offset))
			offset = BfmeZeroRange;
		if (offset > mapRegion.hi.x * 0.25f)
			offset = BfmeZeroRange;

		if (TheGlobalData->m_debugAI)
			offset = -1000; // push out the constraints so we can look at staging areas.

		m_cameraConstraint.lo.x = mapRegion.lo.x + offset;
		m_cameraConstraint.hi.x = mapRegion.hi.x - offset;
		// this looks inverted, but is correct
		m_cameraConstraint.lo.y = mapRegion.lo.y + offset;
		m_cameraConstraint.hi.y = mapRegion.hi.y - offset;
		m_cameraConstraintValid = true;
	}
}
