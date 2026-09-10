// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug

#include "Lib/BaseType.h"
#include "GameClient/DrawableInfo.h"
#include "WW3D2/coltest.h"
#include "sphere.h"

extern "C" void __cdecl _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern const Real BfmeZeroRange;

// The BFME RenderObjClass vtable has moved slots relative to the imported ZH
// header.  This mirror names only the five slots witnessed by this body.
class Rva007129F0RenderObjPrefix
{
public:
	virtual void slot000() = 0;
	virtual void slot001() = 0;
	virtual void slot002() = 0;
	virtual void slot003() = 0;
	virtual void slot004() = 0;
	virtual void slot005() = 0;
	virtual void slot006() = 0;
	virtual void slot007() = 0;
	virtual void slot008() = 0;
	virtual void slot009() = 0;
	virtual void slot010() = 0;
	virtual void slot011() = 0;
	virtual void slot012() = 0;
	virtual void slot013() = 0;
	virtual void slot014() = 0;
	virtual void slot015() = 0;
	virtual void slot016() = 0;
	virtual void slot017() = 0;
	virtual void slot018() = 0;
	virtual void slot019() = 0;
	virtual void slot020() = 0;
	virtual void slot021() = 0;
	virtual void slot022() = 0;
	virtual void slot023() = 0;
	virtual void slot024() = 0;
	virtual void slot025() = 0;
	virtual void slot026() = 0;
	virtual void slot027() = 0;
	virtual void slot028() = 0;
	virtual void slot029() = 0;
	virtual void slot030() = 0;
	virtual void slot031() = 0;
	virtual void slot032() = 0;
	virtual void slot033() = 0;
	virtual void slot034() = 0;
	virtual void slot035() = 0;
	virtual void slot036() = 0;
	virtual void slot037() = 0;
	virtual void slot038() = 0;
	virtual void slot039() = 0;
	virtual void slot040() = 0;
	virtual void slot041() = 0;
	virtual void slot042() = 0;
	virtual void slot043() = 0;
	virtual void slot044() = 0;
	virtual void slot045() = 0;
	virtual void slot046() = 0;
	virtual void slot047() = 0;
	virtual void slot048() = 0;
	virtual void slot049() = 0;
	virtual void slot050() = 0;
	virtual void slot051() = 0;
	virtual void slot052() = 0;
	virtual void slot053() = 0;
	virtual void slot054() = 0;
	virtual void slot055() = 0;
	virtual void slot056() = 0;
	virtual void slot057() = 0;
	virtual void slot058() = 0;
};

class Rva007129F0RenderObjClass : public Rva007129F0RenderObjPrefix
{
public:
	virtual bool Cast_Ray(RayCollisionTestClass &raytest) = 0;
	virtual void slot060() = 0;
	virtual void slot061() = 0;
	virtual void slot062() = 0;
	virtual void slot063() = 0;
	virtual const SphereClass &Get_Bounding_Sphere() const = 0;
	virtual void slot065() = 0;
	virtual void slot066() = 0;
	virtual void slot067() = 0;
	virtual void slot068() = 0;
	virtual void slot069() = 0;
	virtual void slot070() = 0;
	virtual void slot071() = 0;
	virtual void slot072() = 0;
	virtual void slot073() = 0;
	virtual void slot074() = 0;
	virtual void slot075() = 0;
	virtual void slot076() = 0;
	virtual void slot077() = 0;
	virtual void slot078() = 0;
	virtual void slot079() = 0;
	virtual void slot080() = 0;
	virtual void slot081() = 0;
	virtual void slot082() = 0;
	virtual void slot083() = 0;
	virtual void slot084() = 0;
	virtual void slot085() = 0;
	virtual void *Get_User_Data() = 0;
	virtual void slot087() = 0;
	virtual void slot088() = 0;
	virtual void slot089() = 0;
	virtual void slot090() = 0;
	virtual void slot091() = 0;
	virtual void slot092() = 0;
	virtual void slot093() = 0;
	virtual void slot094() = 0;
	virtual int Is_Really_Visible() = 0;
	virtual void slot096() = 0;
	virtual void slot097() = 0;
	virtual void slot098() = 0;
	virtual void slot099() = 0;
	virtual void slot100() = 0;
	virtual void slot101() = 0;
	virtual void slot102() = 0;
	virtual void slot103() = 0;
	virtual void slot104() = 0;
	virtual void slot105() = 0;
	virtual void slot106() = 0;
	virtual void slot107() = 0;
	virtual void slot108() = 0;
	virtual void slot109() = 0;
	virtual void slot110() = 0;
	virtual void slot111() = 0;
	virtual void slot112() = 0;
	virtual void slot113() = 0;
	virtual void slot114() = 0;
	virtual void slot115() = 0;
	virtual void slot116() = 0;
	virtual void slot117() = 0;
	virtual void slot118() = 0;
	virtual int Get_Collision_Type() const = 0;
};

// The BFME visible-list member is the witnessed SimpleSceneClass list at
// +0xec.  Its embedded sentinel starts at +0xf0 and its next link at +0xf4.
// Each node's object link points eight bytes into the RenderObjClass object.
struct BfmeSceneListNode
{
	BfmeSceneListNode *previous;
	BfmeSceneListNode *next;
	BfmeSceneListNode *nextInList;
	unsigned char *objectLink;
	void *list;
};

struct BfmeSceneList
{
	void *vtable;
	BfmeSceneListNode head;
};

class BFMERopeDrawableGetPositionShim
{
public:
	const Coord3D *get() const;
};

struct Rva007129F0DrawableInfo
{
	int m_unused_id;
	void *m_drawable;
	void *getDrawable() { return m_drawable; }
};

static __forceinline const Coord3D *Rva007129F0GetPosition(void *draw)
{
	return ((BFMERopeDrawableGetPositionShim *)draw)->get();
}

class Rva007129F0RTS3DScene
{
public:
	Bool castRay(RayCollisionTestClass &raytest, Bool testAll, Int collisionType);

private:
	unsigned char m_unreconstructed_000[0xec];
	BfmeSceneList m_visibleList;
};

// ?castRay@RTS3DScene@@QAE_NAAVRayCollisionTestClass@@_NH@Z
Bool Rva007129F0RTS3DScene::castRay(RayCollisionTestClass &raytest,
	Bool testAll, Int collisionType)
{
	CastResultStruct result;
	RayCollisionTestClass tempRayTest(raytest.Ray, &result);
	Vector3 newEndPoint;
	*(volatile int *)&tempRayTest.CollisionType = COLL_TYPE_ALL;
	*(volatile bool *)&tempRayTest.CheckTranslucent = true;
	_ReadWriteBarrier();

	Bool hit = FALSE;
	BfmeSceneListNode *head = &m_visibleList.head;
	BfmeSceneListNode *node = head->next;
	while (node != head)
	{
		Rva007129F0RenderObjClass *robj;
		if (node->objectLink)
			robj = reinterpret_cast<Rva007129F0RenderObjClass *>(node->objectLink - 8);
		else
			robj = NULL;
		node = node->next;

		Bool collisionTypePass;
		if (testAll)
			collisionTypePass =
				(robj->Get_Collision_Type() & collisionType) == collisionType;
		else
			collisionTypePass =
				(robj->Get_Collision_Type() & collisionType) != 0;
		if (!collisionTypePass)
			continue;
		if (!robj->Is_Really_Visible())
			continue;

		const SphereClass *sphere = &robj->Get_Bounding_Sphere();
		Vector3 sphereVector(sphere->Center - tempRayTest.Ray.Get_P0());
		Real alpha = Vector3::Dot_Product(sphereVector,
			tempRayTest.Ray.Get_Dir());
		Real beta = sphere->Radius * sphere->Radius -
			(Vector3::Dot_Product(sphereVector, sphereVector) -
			 alpha * alpha);
		if (beta < BfmeZeroRange)
		{
			Rva007129F0DrawableInfo *drawInfo =
				(Rva007129F0DrawableInfo *)robj->Get_User_Data();
			if (!drawInfo)
				continue;

			SphereClass recenteredSphere;
			BFMERopeDrawableGetPositionShim *draw =
				(BFMERopeDrawableGetPositionShim *)drawInfo->getDrawable();
			if (!draw)
				continue;

			recenteredSphere = *sphere;
			recenteredSphere.Re_Center(
				*(const Vector3 *)Rva007129F0GetPosition((void *)draw));
			Vector3 recenteredSphereVector(
				recenteredSphere.Center - tempRayTest.Ray.Get_P0());
			Real recenteredAlpha = Vector3::Dot_Product(
				recenteredSphereVector, tempRayTest.Ray.Get_Dir());
			beta = recenteredSphere.Radius * recenteredSphere.Radius -
				(Vector3::Dot_Product(recenteredSphereVector,
					recenteredSphereVector) -
				 recenteredAlpha * recenteredAlpha);
			if (beta < BfmeZeroRange)
				continue;
		}

		if (robj->Cast_Ray(tempRayTest))
		{
			raytest.CollidedRenderObj = reinterpret_cast<RenderObjClass *>(robj);
			hit = TRUE;
			tempRayTest.Ray.Compute_Point(tempRayTest.Result->Fraction,
				&newEndPoint);
			tempRayTest.Ray.Set(raytest.Ray.Get_P0(), newEndPoint);
			tempRayTest.Result->Fraction = 1.0f;
		}
	}

	raytest.Ray = tempRayTest.Ray;
	return hit;
}
