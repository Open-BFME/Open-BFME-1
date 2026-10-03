// ?rva00744360HasClearShot@W3DView@@UAE_NW4ObjectID@@0H@Z
// cl: /I. /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWDebug
// BFME W3DView virtual at vtable 0x011217A0 slot 155 (ILT 0x000217E7), retail 0x00744360.
// Casts a ray between two objects; false when a different object's drawable blocks it.
// Evidence: targets/game/reverse/identity_evidence/00744360-vector-evaluation.md
typedef int Int;
typedef bool Bool;
typedef float Real;

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7FFFFFFF
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

#include "game/Libraries/Source/WWVegas/WWMath/vector3.h"
#include "game/Libraries/Source/WWVegas/WWMath/castres.h"
// Retail calls LineSegClass::Set and RayCollisionTestClass construction out of line.
#pragma auto_inline(off)
#include "game/Libraries/Source/WWVegas/WW3D2/coltest.h"
#pragma auto_inline(on)

#define BFME_HAVE_OBJECTID
#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS const Coord3D *getPosition() const { return &m_cachedPos; }
#define OBJECT_TU_MEMBERS ObjectID getID() const { return m_id; }
#include "game/GameEngine/Source/GameLogic/Object/object.h"
#undef THING_TU_MEMBERS
#undef OBJECT_TU_MEMBERS

// The existing lookup header uses an int ObjectID ABI; this caller uses the
// independently pinned enum spelling. No GameLogic storage is accessed here.
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

// Reconstruction adapter, not an asserted original method name. VC7.1 builds
// call temporaries right to left. Accepting end before start retains retail's
// first-position copy before the second while Set still receives (start, end).
static __forceinline void rva00744360SetEndStart(LineSegClass &line,
    const Vector3 &p1, const Vector3 &p0) { line.Set(p0, p1); }

#include "game/Libraries/Source/WWVegas/WW3D2/rendobj.h"

class RTS3DScene
{
public:
	Bool castRay(RayCollisionTestClass &raytest, Bool testAll, Int collisionType);
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

class Drawable
{
public:
	Object *getObject() { return m_object; }

private:
	char m_unreconstructed_000[0xfc];
	Object *m_object;
};

struct DrawableInfo
{
	void *m_vtable;
	Drawable *m_drawable;
};

class W3DView
{
public:
	virtual Bool rva00744360HasClearShot(ObjectID firstID, ObjectID secondID, Int pickType);
};

Bool W3DView::rva00744360HasClearShot(ObjectID firstID, ObjectID secondID, Int pickType)
{
	GameLogic *logic = TheGameLogic;
	Object *first = logic->findObjectByID(firstID);
	Object *second = logic->findObjectByID(secondID);
	if (first == 0 || !first->getDrawable() || second == 0 || !second->getDrawable())
		return false;

	const Coord3D *firstPos = first->getPosition();
	const Coord3D *secondPos = second->getPosition();

	LineSegClass lineseg;
	rva00744360SetEndStart(lineseg, Vector3(secondPos->x, secondPos->y, secondPos->z), Vector3(firstPos->x, firstPos->y, firstPos->z));

	CastResultStruct result;
	result.ComputeContactPoint = true;
	RayCollisionTestClass raytest(lineseg, &result, 1, false, false);

	if (W3DDisplay::m_3DScene->castRay(raytest, false, pickType))
	{
		RenderObjClass *renderObj = raytest.CollidedRenderObj;
		if (renderObj)
		{
			DrawableInfo *info = (DrawableInfo *)renderObj->Get_User_Data();
			if (info)
			{
				Drawable *draw = info->m_drawable;
				if (draw)
				{
					Object *obj = draw->getObject();
					if (obj && obj->getID() != secondID)
						return false;
				}
			}
		}
	}
	return true;
}
