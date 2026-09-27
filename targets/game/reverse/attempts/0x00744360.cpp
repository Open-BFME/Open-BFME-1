// ?d_00744360@@YAXXZ
// partial score=0.81 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc
// Retail 0x00744360 (358 B). Draft 2: TU-local ABI adapters for the four ILT
// callees, so the call sites compile through the real ledger thunks.
typedef int Int;
typedef bool Bool;

struct Rva00744360Vec
{
	float x;
	float y;
	float z;
};

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
};

class GameLogic
{
public:
	typedef Object *(GameLogic::*FindCall)(int id);
	Object *findObjectByID(int id);
};

extern void j_0001f253(void);
extern void j_0004935a(void);
extern void j_0001b757(void);
extern void j_00019cc2(void);

static __forceinline Object *Rva00744360Find(GameLogic *logic, int id)
{
	union { void (*raw)(void); GameLogic::FindCall member; } route;
	route.raw = j_0001f253;
	return (logic->*route.member)(id);
}

struct Rva00744360Vec3
{
	float x;
	float y;
	float z;
};

class Rva00744360Seg
{
public:
	void set(const struct Rva00744360Vec3 &a, const struct Rva00744360Vec3 &b);

	Rva00744360Vec3 m_p0;
	Rva00744360Vec3 m_p1;
	Rva00744360Vec3 m_dp;
	Rva00744360Vec3 m_dir;
	float m_length;
};

struct Rva00744360RayResult
{
	Bool m_startBad;
	float m_fraction;
	Rva00744360Vec3 m_normal;
	unsigned int m_surfaceType;
	Bool m_computeContact;
	Rva00744360Vec3 m_contact;
};

class Rva00744360Ray
{
public:
	typedef void (Rva00744360Ray::*BuildCall)(const Rva00744360Seg &seg,
		Rva00744360RayResult *res, int type, Bool translucent, Bool hidden);

	Rva00744360RayResult *m_result;
	int m_collisionType;
	void *m_hit;
	Rva00744360Seg m_seg;
	Bool m_checkTranslucent;
	Bool m_checkHidden;
};

class Rva00744360Scene
{
public:
	typedef Bool (Rva00744360Scene::*CastCall)(Rva00744360Ray &raytest,
		Bool testAll, Int collisionType);
	Bool castRay(Rva00744360Ray &raytest, Bool testAll, Int collisionType);
};

class Rva00744360DrawLink
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
	virtual void *renderLink00744360();
};

struct Rva00744360RenderLink
{
	void *m_vtable;
	void *m_drawable;
};

struct Rva00744360OwnerLink
{
	unsigned char m_pad[0xfc];
	void *m_owner;
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define g_bfmeGlobPB (*(Rva00744360Scene **)0x012F8058)

static __forceinline void Rva00744360SetSeg(Rva00744360Seg *seg,
	const Rva00744360Vec3 *a, const Rva00744360Vec3 *b)
{
	union { void (*raw)(void); void (Rva00744360Seg::*member)(const struct Rva00744360Vec3 &, const struct Rva00744360Vec3 &); } route;
	route.raw = j_0004935a;
	(seg->*route.member)(*a, *b);
}

static __forceinline void Rva00744360BuildRay(Rva00744360Ray *ray,
	const Rva00744360Seg &seg, Rva00744360RayResult *res)
{
	union { void (*raw)(void); Rva00744360Ray::BuildCall member; } route;
	route.raw = j_0001b757;
	(ray->*route.member)(seg, res, 1, false, false);
}

static __forceinline Bool Rva00744360Cast(Rva00744360Scene *scene,
	Rva00744360Ray &ray, Bool all, Int type)
{
	union { void (*raw)(void); Rva00744360Scene::CastCall member; } route;
	route.raw = j_00019cc2;
	return (scene->*route.member)(ray, all, type);
}

Bool __stdcall rva00744360HasClearShot(int firstID, int secondID, void *extra)
{
	GameLogic *logic = TheBfmeGameLogic;
	Object *first = Rva00744360Find(logic, firstID);
	Object *second = Rva00744360Find(logic, secondID);
	if (first == 0 || !first->rva00744360Able() || second == 0 || !second->rva00744360Able())
		return false;

	const Rva00744360Vec *firstVec = (const Rva00744360Vec *)((const char *)first + 0x38);
	const Rva00744360Vec *secondVec = (const Rva00744360Vec *)((const char *)second + 0x38);
	Rva00744360Vec3 firstPos;
	firstPos.x = firstVec->x;
	firstPos.y = firstVec->y;
	firstPos.z = firstVec->z;
	Rva00744360Vec3 secondPos;
	secondPos.x = secondVec->x;
	secondPos.y = secondVec->y;
	secondPos.z = secondVec->z;

	Rva00744360Seg seg;
	Rva00744360SetSeg(&seg, &firstPos, &secondPos);

	Rva00744360RayResult result;
	result.m_startBad = false;
	result.m_fraction = 1.0f;
	result.m_normal.x = 0.0f;
	result.m_normal.y = 0.0f;
	result.m_normal.z = 0.0f;
	result.m_surfaceType = 0;
	result.m_contact.x = 0.0f;
	result.m_contact.y = 0.0f;
	result.m_contact.z = 0.0f;
	result.m_computeContact = true;

	Rva00744360Ray ray;
	Rva00744360BuildRay(&ray, seg, &result);

	if (!Rva00744360Cast(g_bfmeGlobPB, ray, false, (Int)extra))
		return false;

	Rva00744360DrawLink *link = (Rva00744360DrawLink *)ray.m_hit;
	if (link == 0)
		return false;
	Rva00744360RenderLink *robj = (Rva00744360RenderLink *)link->renderLink00744360();
	if (robj == 0)
		return false;
	void *draw = robj->m_drawable;
	if (draw == 0)
		return false;
	void *owner = ((Rva00744360OwnerLink *)draw)->m_owner;
	if (owner == 0)
		return false;
	if (*(int *)((char *)owner + 0x74) != secondID)
		return false;
	return true;
}
