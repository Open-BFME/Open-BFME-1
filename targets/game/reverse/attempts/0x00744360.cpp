// ?rva00744360HasClearShot@W3DView@@UAE_NW4ObjectID@@0H@Z
// partial score=0.9665 date=2026-09-30
// cl: /DNDEBUG /MD /EHsc
// BFME W3DView virtual at vtable 0x011217A0 slot 155 (ILT 0x000217E7), retail 0x00744360.
// Casts a ray between two objects; false when a different object's drawable blocks it.
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

class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	void Set(float x, float y, float z) { X = x; Y = y; Z = z; }

	float X;
	float Y;
	float Z;
};

// Only the Thing position (+0x38), the id (+0x74) and virtual slot 10 are used.
class Object
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Int rva00744360Able() const;

	const Coord3D *getPosition() const { return &m_cachedPos; }
	ObjectID getID() const { return m_id; }

private:
	char m_unreconstructed_004[0x34];
	Coord3D m_cachedPos;
	char m_unreconstructed_044[0x30];
	ObjectID m_id;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

// Retail calls the out-of-line Set at 0x003FEB40 through ILT 0x0004935A.
class LineSegClass
{
public:
	LineSegClass() {}
	void Set(const Vector3 &p0, const Vector3 &p1);

	Vector3 m_p0;
	Vector3 m_p1;
	Vector3 m_dp;
	Vector3 m_dir;
	float m_length;
};

struct CastResultStruct
{
	CastResultStruct() { Reset(); }
	void Reset()
	{
		m_startBad = false;
		m_fraction = 1.0f;
		m_normal.Set(0, 0, 0);
		m_surfaceType = 0;
		m_computeContact = false;
		m_contact.Set(0, 0, 0);
	}

	Bool m_startBad;
	float m_fraction;
	Vector3 m_normal;
	unsigned int m_surfaceType;
	Bool m_computeContact;
	Vector3 m_contact;
};

// Get_User_Data is RenderObjClass vtable slot 86 (+0x158).
class RenderObjClass
{
public:
	virtual void d60slot00(); virtual void d60slot01(); virtual void d60slot02(); virtual void d60slot03();
	virtual void d60slot04(); virtual void d60slot05(); virtual void d60slot06(); virtual void d60slot07();
	virtual void d60slot08(); virtual void d60slot09(); virtual void d60slot10(); virtual void d60slot11();
	virtual void d60slot12(); virtual void d60slot13(); virtual void d60slot14(); virtual void d60slot15();
	virtual void d60slot16(); virtual void d60slot17(); virtual void d60slot18(); virtual void d60slot19();
	virtual void d60slot20(); virtual void d60slot21(); virtual void d60slot22(); virtual void d60slot23();
	virtual void d60slot24(); virtual void d60slot25(); virtual void d60slot26(); virtual void d60slot27();
	virtual void d60slot28(); virtual void d60slot29(); virtual void d60slot30(); virtual void d60slot31();
	virtual void d60slot32(); virtual void d60slot33(); virtual void d60slot34(); virtual void d60slot35();
	virtual void d60slot36(); virtual void d60slot37(); virtual void d60slot38(); virtual void d60slot39();
	virtual void d60slot40(); virtual void d60slot41(); virtual void d60slot42(); virtual void d60slot43();
	virtual void d60slot44(); virtual void d60slot45(); virtual void d60slot46(); virtual void d60slot47();
	virtual void d60slot48(); virtual void d60slot49(); virtual void d60slot50(); virtual void d60slot51();
	virtual void d60slot52(); virtual void d60slot53(); virtual void d60slot54(); virtual void d60slot55();
	virtual void d60slot56(); virtual void d60slot57(); virtual void d60slot58(); virtual void d60slot59();
	virtual void d60slot60(); virtual void d60slot61(); virtual void d60slot62(); virtual void d60slot63();
	virtual void d60slot64(); virtual void d60slot65(); virtual void d60slot66(); virtual void d60slot67();
	virtual void d60slot68(); virtual void d60slot69(); virtual void d60slot70(); virtual void d60slot71();
	virtual void d60slot72(); virtual void d60slot73(); virtual void d60slot74(); virtual void d60slot75();
	virtual void d60slot76(); virtual void d60slot77(); virtual void d60slot78(); virtual void d60slot79();
	virtual void d60slot80(); virtual void d60slot81(); virtual void d60slot82(); virtual void d60slot83();
	virtual void d60slot84(); virtual void d60slot85();
	virtual void *Get_User_Data();
};

// Out-of-line constructor at 0x00609A20, called through ILT 0x0001B757.
class RayCollisionTestClass
{
public:
	RayCollisionTestClass(const LineSegClass &ray, CastResultStruct *res, int collision_type,
		bool check_translucent, bool check_hidden);

	CastResultStruct *m_result;
	int m_collisionType;
	RenderObjClass *m_hit;
	LineSegClass m_seg;
	Bool m_checkTranslucent;
	Bool m_checkHidden;
};

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
	if (first == 0 || !first->rva00744360Able() || second == 0 || !second->rva00744360Able())
		return false;

	const Coord3D *firstPos = first->getPosition();
	const Coord3D *secondPos = second->getPosition();

	LineSegClass lineseg;
	lineseg.Set(Vector3(firstPos->x, firstPos->y, firstPos->z), Vector3(secondPos->x, secondPos->y, secondPos->z));

	CastResultStruct result;
	result.m_computeContact = true;
	RayCollisionTestClass raytest(lineseg, &result, 1, false, false);

	if (W3DDisplay::m_3DScene->castRay(raytest, false, pickType))
	{
		RenderObjClass *renderObj = raytest.m_hit;
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
