// ?rva00742920@W3DView@@UAEHPAUCoord2D@@@Z
// cl:  /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWDebug
// BFME W3DView virtual at vtable 0x011217A0 slot 23 (+0x5C, ILT 0x00046169),
// retail 0x00742920, 726 bytes, thiscall, ret 4. It is the
// BFME form of Zero Hour's W3DView::scrollBy: the screen delta moves the camera
// along the ground direction of the view's centre pick ray (normalized, z dropped),
// scaled by a zoom-limit virtual and the zoom, then reports which camera
// constraints the new position crosses (1 = below low x, 2 = above high x,
// 4 = below low y, 8 = above high y). The method name is not recovered, so it
// keeps its address.
//
// Shape (probe; prior best 0.938): the pick-ray direction is built in place in the
// ray-end vector (its address went to getPickRay, so it stays in memory with an
// explicit Z = 0 store); centre/ray-start and right/up live in sibling scopes so
// they share frame slots; the camera position is read member-wise and written back
// as one struct copy; `up` is declared before `right`.
typedef int Int;
typedef float Real;

#include "../../../../Libraries/Include/Lib/Coord2D.h"
struct ICoord2D { Int x, y; };
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Source/WWVegas/WWMath/vector2.h"
#include "../../../../Libraries/Source/WWVegas/WWMath/vector3.h"

class CameraClass
{
public:
	void Device_To_World_Space(const Vector2 &device, Vector3 *world);
};

class RvaZoomLimits
{
public:
	virtual void slot000();
	virtual void slot001();
	virtual void slot002();
	virtual void slot003();
	virtual Real slot004();
};

class BfmeSubETH;
class BfmeViewETH
{
public:
	void bfmeApplyETH(BfmeSubETH *pos);
};

class ClientRoot4120
{
	char m_unreconstructed000[0xbc];
public:
	unsigned char cameraChangeBlocked;
};
// Canonical datum ?TheGameClient@@3PAVGameClient@@A (0x012F1464, defined in
// GameClient.cpp); the partial ClientRoot4120 view stays a cast at the use
// site (identity_evidence/012f1464-TheGameClient.md).
class GameClient;
extern GameClient *TheGameClient;

class BaseHeightMapRenderObjClass
{
public:
	virtual void slot000();
	virtual void slot001();
	virtual void slot002();
	virtual void slot003();
	virtual void slot004();
	virtual void slot005();
	virtual void slot006();
	virtual void slot007();
	virtual void slot008();
	virtual void slot009();
	virtual void slot010();
	virtual void slot011();
	virtual void slot012();
	virtual void slot013();
	virtual void slot014();
	virtual void slot015();
	virtual void slot016();
	virtual void slot017();
	virtual void slot018();
	virtual void slot019();
	virtual void slot020();
	virtual void slot021();
	virtual void slot022();
	virtual void slot023();
	virtual void slot024();
	virtual void slot025();
	virtual void slot026();
	virtual void slot027();
	virtual void slot028();
	virtual void slot029();
	virtual void slot030();
	virtual void slot031();
	virtual void slot032();
	virtual void slot033();
	virtual void slot034();
	virtual void slot035();
	virtual void slot036();
	virtual void slot037();
	virtual void slot038();
	virtual void slot039();
	virtual void slot040();
	virtual void slot041();
	virtual void slot042();
	virtual void slot043();
	virtual void slot044();
	virtual void slot045();
	virtual void slot046();
	virtual void slot047();
	virtual void slot048();
	virtual void slot049();
	virtual void slot050();
	virtual void slot051();
	virtual void slot052();
	virtual void slot053();
	virtual void slot054();
	virtual void slot055();
	virtual void slot056();
	virtual void slot057();
	virtual void slot058();
	virtual void slot059();
	virtual void slot060();
	virtual void slot061();
	virtual void slot062();
	virtual void slot063();
	virtual void slot064();
	virtual void slot065();
	virtual void slot066();
	virtual void slot067();
	virtual void slot068();
	virtual void slot069();
	virtual void slot070();
	virtual void slot071();
	virtual void slot072();
	virtual void slot073();
	virtual void slot074();
	virtual void slot075();
	virtual void slot076();
	virtual void slot077();
	virtual void slot078();
	virtual void slot079();
	virtual void slot080();
	virtual void slot081();
	virtual void slot082();
	virtual void slot083();
	virtual void slot084();
	virtual void slot085();
	virtual void slot086();
	virtual void slot087();
	virtual void slot088();
	virtual void slot089();
	virtual void slot090();
	virtual void slot091();
	virtual void slot092();
	virtual void slot093();
	virtual void slot094();
	virtual void slot095();
	virtual void slot096();
	virtual void slot097();
	virtual void slot098();
	virtual void slot099();
	virtual void slot100();
	virtual void slot101();
	virtual void slot102();
	virtual void slot103();
	virtual void slot104();
	virtual void slot105();
	virtual void slot106();
	virtual void slot107();
	virtual void slot108();
	virtual void slot109();
	virtual void slot110();
	virtual void slot111();
	virtual void slot112();
	virtual void slot113();
	virtual void slot114();
	virtual void slot115();
	virtual void slot116();
	virtual void slot117();
	virtual void slot118();
	virtual void slot119();
	virtual void slot120();
	virtual void slot121();
	virtual void slot122();
	virtual void slot123();
	virtual void slot124();
	virtual void slot125();
	virtual void slot126();
	virtual void slot127();
	virtual void slot128();
	virtual void slot129();
	virtual void slot130();
	virtual void slot131();
	virtual void slot132();
	virtual void slot133();
	virtual void slot134();
	virtual void slot135();
	virtual void slot136();
	virtual void slot137();
	virtual void slot138();
	virtual void slot139();
	virtual void slot140();
	virtual void slot141(Int value);
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class W3DView
{
public:
	virtual void slot000();
	virtual void slot001();
	virtual void slot002();
	virtual void slot003();
	virtual void slot004();
	virtual void slot005();
	virtual void slot006();
	virtual void slot007();
	virtual void slot008();
	virtual void slot009();
	virtual void slot010();
	virtual void slot011();
	virtual void slot012();
	virtual void slot013();
	virtual void slot014();
	virtual Int getWidth();
	virtual void slot016();
	virtual Int getHeight();
	virtual void slot018();
	virtual void slot019();
	virtual void slot020();
	virtual void slot021();
	virtual void slot022();
	virtual void slot023();
	virtual Int rva00742920(Coord2D *delta);

private:
	void getPickRay(const ICoord2D *screen, Vector3 *rayStart, Vector3 *rayEnd);
	void setCameraTransform();

	char m_unreconstructed0004[0x0c - 4];
	Coord3D m_pos;
	char m_unreconstructed018[0x3c - 0x18];
	Real m_zoom;
	char m_unreconstructed040[0x44 - 0x40];
	unsigned char opaque0044;
	char m_unreconstructed045[0x104 - 0x45];
	CameraClass *m_3DCamera;
	char m_unreconstructed108[0x1dc - 0x108];
	unsigned char cameraMovementFlag;
	char m_unreconstructed1DD[0x23ec - 0x1dd];
	Coord2D m_scrollAmount;
	char m_unreconstructed23F4[0x23fc - 0x23f4];
	Coord2D m_constraintLo;
	Coord2D m_constraintHi;
	char m_unreconstructed240C[0x24b8 - 0x240c];
	RvaZoomLimits m_zoomSource;
};

// ?rva00742920@W3DView@@UAEHPAUCoord2D@@@Z
Int W3DView::rva00742920(Coord2D *delta)
{
	if (((ClientRoot4120 *)TheGameClient)->cameraChangeBlocked && opaque0044)
		return 0;

	Int flags = 0;
	if (delta && (delta->x != 0 || delta->y != 0))
	{
		const Real SCROLL_RESOLUTION = 250.0f;

		m_scrollAmount = *delta;

		Vector2 start, end;
		start.X = getWidth() / 2;
		start.Y = getHeight() / 2;
		Real aspect = getWidth() / getHeight();
		end.X = start.X + delta->x * SCROLL_RESOLUTION;
		end.Y = start.Y + aspect * delta->y * SCROLL_RESOLUTION;

		Vector3 dir;
		{
			ICoord2D center;
			center.x = start.X;
			center.y = start.Y;
			Vector3 rayStart;
			getPickRay(&center, &rayStart, &dir);
			dir.X -= rayStart.X;
			dir.Y -= rayStart.Y;
			dir.Z = 0;
		}
		dir.Normalize();

		Vector3 worldStart, worldEnd;
		m_3DCamera->Device_To_World_Space(start, &worldStart);
		m_3DCamera->Device_To_World_Space(end, &worldEnd);

		Coord3D pos;
		pos.x = m_pos.x;
		pos.y = m_pos.y;
		pos.z = m_pos.z;
		{
			Vector2 up(-dir.X, -dir.Y);
			Vector2 right(dir.Y, -dir.X);
			Real scale = m_zoomSource.slot004() * (m_zoom * 0.25f);
			pos.x += (right.X * delta->x + up.X * delta->y) * scale;
			pos.y += (right.Y * delta->x * aspect + up.Y * delta->y) * scale;
		}
		if (opaque0044)
			((BfmeViewETH *)this)->bfmeApplyETH((BfmeSubETH *)&pos);
		m_pos = pos;

		if (pos.x < m_constraintLo.x)
			flags = 1;
		if (pos.x > m_constraintHi.x)
			flags |= 2;
		if (pos.y < m_constraintLo.y)
			flags |= 4;
		if (pos.y > m_constraintHi.y)
			flags |= 8;

		cameraMovementFlag = 0;
		setCameraTransform();
		if (TheTerrainRenderObject)
			TheTerrainRenderObject->slot141(1);
	}
	return flags;
}
