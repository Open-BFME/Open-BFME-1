// ?d_001e9380@@YAXXZ
// partial score=0.91 date=2026-09-24
// ?rva001e9380@WeaponTemplate@@QAEXPBVObject@@PBUCoord3D@@HHPAV2@H1ABUWeaponBonus@@_NPAVWeapon@@PAH@Z
// BFME 1.03 RVA 0x001E9380, 1519 decoded bytes, through ret 0x2c at 0x001E996C.
// Reached by Weapon::privateFireWeapon (001E9FD0) via ILT000425C3.
// This BFME body has eleven slots including source position and victim ID;
// the historical Zero Hour fireWeaponTemplate mangling does NOT describe it.
// Keep the method address-qualified until its original signature is proved.
// The 0x4c frame, all dispatch branches and direct call sites are reconstructed.
// Best measured variant: 1,520 bytes, 139 differing non-relocation bytes, score 0.91.
// getAimPosition/scatter have hidden coordinate returns; scatter additionally
// takes its last coordinate by value. Both callees and caller stack cleanup
// were decoded independently. Drawable FX consumes seven arguments (ret1c),
// not the legacy eight-argument ledger prototype. The new declarations below
// are intentionally unpinned while this caller remains unmatched.
// Coord3D copy/empty-dtor lifetime agrees with the landed TerrainLogic
// getLayerForDestinationObject and BaseUpgrade upgradeImplementation donors.
// Retail calls Object vtable slot +0x28 at +0x196 with EAX and at +0x28B with EDX.
// Separate typed local vtable views reduce relocation drift from nine sites to three.
// The remaining control-flow residue starts at +0x1A3. Retail branches on victimObj
// before loading recoil; this source loads recoil before the branch.

// stlport
// cl: /DNDEBUG /MD /O2 /EHsc
//
// Open-BFME5: anonymous retail body 0x001E9380, 1519 bytes.  The caller at
// 0x001E9FD0 supplies the legacy BFME ABI (eleven stack dwords): source,
// source position, slot, barrel, victim, victim id, aimed position, bonus,
// detonation flag, firing weapon and projectile id.  The address-derived
// method name is intentional: the caller proves this WeaponTemplate-shaped
// body, but does not prove the original source spelling.
//
// The layout witnesses are the matched WeaponTemplate copy/parse bodies.  In
// particular, the retail accesses below prove +0x31, +0x58, +0x74, +0x94,
// +0x4e4, +0x4fd, +0x514, +0x520, +0x524 and the nugget list head at +0x538.
// The final list walk is kept as the witnessed three-pointer STLport node;
// the nugget identity and the 0x00040287 helper remain address-derived.

#include <math.h>
#include <list>
#pragma intrinsic(atan2)
enum KindOfType { KINDOF_INFANTRY=8, KINDOF_BRIDGE=22 };
enum WeaponSlotType { PRIMARY_WEAPON=0 };

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;
typedef int ObjectID;

struct Coord3D
{
    Coord3D() {}
    Coord3D(const Coord3D &p) : x(p.x),y(p.y),z(p.z) {}
    ~Coord3D() {}

    void set(const Coord3D *v) { x=v->x; y=v->y; z=v->z; }

	Real x;
	Real y;
	Real z;
};

struct WeaponBonus
{
	Real fields[6];
};

class Object;
class Weapon;
class WeaponTemplate;
class FXList;
class Drawable;

struct TBridgeAttackInfo
{
	Coord3D attackPoint1;
	Coord3D attackPoint2;
};

struct BfmePt951
{
public:
	Real m_x;
	Real m_y;
};

class BfmeGap951
{
public:
	Real bfmeGapB951(const BfmePt951 *other) const;

private:
	Int m_pad00[14];
	Real m_x;
	Real m_y;
	Int m_pad40[31];
	Real m_radius;
};


#define RVA_VIRTUAL_SLOT(n) virtual void v##n();

class AIUpdateInterfaceBase
{
public:
	RVA_VIRTUAL_SLOT(000)
	RVA_VIRTUAL_SLOT(001)
	RVA_VIRTUAL_SLOT(002)
	RVA_VIRTUAL_SLOT(003)
	RVA_VIRTUAL_SLOT(004)
	RVA_VIRTUAL_SLOT(005)
	RVA_VIRTUAL_SLOT(006)
	RVA_VIRTUAL_SLOT(007)
	RVA_VIRTUAL_SLOT(008)
	RVA_VIRTUAL_SLOT(009)
	RVA_VIRTUAL_SLOT(010)
	RVA_VIRTUAL_SLOT(011)
	RVA_VIRTUAL_SLOT(012)
	RVA_VIRTUAL_SLOT(013)
	RVA_VIRTUAL_SLOT(014)
	RVA_VIRTUAL_SLOT(015)
	RVA_VIRTUAL_SLOT(016)
	RVA_VIRTUAL_SLOT(017)
	RVA_VIRTUAL_SLOT(018)
	RVA_VIRTUAL_SLOT(019)
	RVA_VIRTUAL_SLOT(020)
	RVA_VIRTUAL_SLOT(021)
	RVA_VIRTUAL_SLOT(022)
	RVA_VIRTUAL_SLOT(023)
	RVA_VIRTUAL_SLOT(024)
	RVA_VIRTUAL_SLOT(025)
	RVA_VIRTUAL_SLOT(026)
	RVA_VIRTUAL_SLOT(027)
	RVA_VIRTUAL_SLOT(028)
	RVA_VIRTUAL_SLOT(029)
	RVA_VIRTUAL_SLOT(030)
	RVA_VIRTUAL_SLOT(031)
	RVA_VIRTUAL_SLOT(032)
	RVA_VIRTUAL_SLOT(033)
	RVA_VIRTUAL_SLOT(034)
	RVA_VIRTUAL_SLOT(035)
	RVA_VIRTUAL_SLOT(036)
	RVA_VIRTUAL_SLOT(037)
	RVA_VIRTUAL_SLOT(038)
	RVA_VIRTUAL_SLOT(039)
	RVA_VIRTUAL_SLOT(040)
	RVA_VIRTUAL_SLOT(041)
	RVA_VIRTUAL_SLOT(042)
	RVA_VIRTUAL_SLOT(043)
	RVA_VIRTUAL_SLOT(044)
	RVA_VIRTUAL_SLOT(045)
	RVA_VIRTUAL_SLOT(046)
	RVA_VIRTUAL_SLOT(047)
	RVA_VIRTUAL_SLOT(048)
	RVA_VIRTUAL_SLOT(049)
	RVA_VIRTUAL_SLOT(050)
	RVA_VIRTUAL_SLOT(051)
	RVA_VIRTUAL_SLOT(052)
	RVA_VIRTUAL_SLOT(053)
	RVA_VIRTUAL_SLOT(054)
	RVA_VIRTUAL_SLOT(055)
	RVA_VIRTUAL_SLOT(056)
	RVA_VIRTUAL_SLOT(057)
	RVA_VIRTUAL_SLOT(058)
	RVA_VIRTUAL_SLOT(059)
	RVA_VIRTUAL_SLOT(060)
	RVA_VIRTUAL_SLOT(061)
	RVA_VIRTUAL_SLOT(062)
	RVA_VIRTUAL_SLOT(063)
	RVA_VIRTUAL_SLOT(064)
	RVA_VIRTUAL_SLOT(065)
	RVA_VIRTUAL_SLOT(066)
	RVA_VIRTUAL_SLOT(067)
	RVA_VIRTUAL_SLOT(068)
	RVA_VIRTUAL_SLOT(069)
	RVA_VIRTUAL_SLOT(070)
	RVA_VIRTUAL_SLOT(071)
	RVA_VIRTUAL_SLOT(072)
	RVA_VIRTUAL_SLOT(073)
	RVA_VIRTUAL_SLOT(074)
	RVA_VIRTUAL_SLOT(075)
	RVA_VIRTUAL_SLOT(076)
	RVA_VIRTUAL_SLOT(077)
	RVA_VIRTUAL_SLOT(078)
	RVA_VIRTUAL_SLOT(079)
	RVA_VIRTUAL_SLOT(080)
	RVA_VIRTUAL_SLOT(081)
	RVA_VIRTUAL_SLOT(082)
	RVA_VIRTUAL_SLOT(083)
	RVA_VIRTUAL_SLOT(084)
	RVA_VIRTUAL_SLOT(085)
	RVA_VIRTUAL_SLOT(086)
	RVA_VIRTUAL_SLOT(087)
	RVA_VIRTUAL_SLOT(088)
	RVA_VIRTUAL_SLOT(089)
	RVA_VIRTUAL_SLOT(090)
	RVA_VIRTUAL_SLOT(091)
	RVA_VIRTUAL_SLOT(092)
	RVA_VIRTUAL_SLOT(093)
	RVA_VIRTUAL_SLOT(094)
	RVA_VIRTUAL_SLOT(095)
	RVA_VIRTUAL_SLOT(096)
	RVA_VIRTUAL_SLOT(097)
	RVA_VIRTUAL_SLOT(098)
	RVA_VIRTUAL_SLOT(099)
	RVA_VIRTUAL_SLOT(100)
	RVA_VIRTUAL_SLOT(101)
	RVA_VIRTUAL_SLOT(102)
	RVA_VIRTUAL_SLOT(103)
	RVA_VIRTUAL_SLOT(104)
	RVA_VIRTUAL_SLOT(105)
	RVA_VIRTUAL_SLOT(106)
	RVA_VIRTUAL_SLOT(107)
	RVA_VIRTUAL_SLOT(108)
	RVA_VIRTUAL_SLOT(109)
	RVA_VIRTUAL_SLOT(110)
	RVA_VIRTUAL_SLOT(111)
	RVA_VIRTUAL_SLOT(112)
	RVA_VIRTUAL_SLOT(113)
};

class AIUpdateInterface : public AIUpdateInterfaceBase
{
public:
	virtual Bool getSneakyTargetingOffset(Coord3D *offset);
};

class Rva001E9380Query1fcBase
{
public:
	RVA_VIRTUAL_SLOT(000)
	RVA_VIRTUAL_SLOT(001)
	RVA_VIRTUAL_SLOT(002)
	RVA_VIRTUAL_SLOT(003)
	RVA_VIRTUAL_SLOT(004)
	RVA_VIRTUAL_SLOT(005)
	RVA_VIRTUAL_SLOT(006)
	RVA_VIRTUAL_SLOT(007)
	RVA_VIRTUAL_SLOT(008)
	RVA_VIRTUAL_SLOT(009)
	RVA_VIRTUAL_SLOT(010)
	RVA_VIRTUAL_SLOT(011)
	RVA_VIRTUAL_SLOT(012)
	RVA_VIRTUAL_SLOT(013)
	RVA_VIRTUAL_SLOT(014)
	RVA_VIRTUAL_SLOT(015)
	RVA_VIRTUAL_SLOT(016)
	RVA_VIRTUAL_SLOT(017)
	RVA_VIRTUAL_SLOT(018)
	RVA_VIRTUAL_SLOT(019)
	RVA_VIRTUAL_SLOT(020)
	RVA_VIRTUAL_SLOT(021)
	RVA_VIRTUAL_SLOT(022)
	RVA_VIRTUAL_SLOT(023)
	RVA_VIRTUAL_SLOT(024)
	RVA_VIRTUAL_SLOT(025)
	virtual void *slot68();
	virtual void slot1b();
	virtual void slot1c();
	virtual void slot1d();
	virtual void slot1e();
	virtual void slot1f();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot2a();
	virtual void slot2b();
	virtual void slot2c();
	virtual void slot2d();
	virtual void slot2e();
	virtual void slot2f();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual Object *slotE0(const Coord3D *);
};

class Rva001E9380Query200Base
{
public:
	RVA_VIRTUAL_SLOT(000)
	RVA_VIRTUAL_SLOT(001)
	RVA_VIRTUAL_SLOT(002)
	RVA_VIRTUAL_SLOT(003)
	RVA_VIRTUAL_SLOT(004)
	RVA_VIRTUAL_SLOT(005)
	RVA_VIRTUAL_SLOT(006)
	RVA_VIRTUAL_SLOT(007)
	RVA_VIRTUAL_SLOT(008)
	RVA_VIRTUAL_SLOT(009)
	RVA_VIRTUAL_SLOT(010)
	RVA_VIRTUAL_SLOT(011)
	RVA_VIRTUAL_SLOT(012)
	RVA_VIRTUAL_SLOT(013)
	RVA_VIRTUAL_SLOT(014)
	RVA_VIRTUAL_SLOT(015)
	RVA_VIRTUAL_SLOT(016)
	RVA_VIRTUAL_SLOT(017)
	RVA_VIRTUAL_SLOT(018)
	RVA_VIRTUAL_SLOT(019)
	RVA_VIRTUAL_SLOT(020)
	RVA_VIRTUAL_SLOT(021)
	RVA_VIRTUAL_SLOT(022)
	RVA_VIRTUAL_SLOT(023)
	RVA_VIRTUAL_SLOT(024)
	RVA_VIRTUAL_SLOT(025)
	RVA_VIRTUAL_SLOT(026)
	RVA_VIRTUAL_SLOT(027)
	RVA_VIRTUAL_SLOT(028)
	RVA_VIRTUAL_SLOT(029)
	RVA_VIRTUAL_SLOT(030)
	RVA_VIRTUAL_SLOT(031)
	RVA_VIRTUAL_SLOT(032)
	RVA_VIRTUAL_SLOT(033)
	RVA_VIRTUAL_SLOT(034)
	virtual Real slot8C();
};

#undef RVA_VIRTUAL_SLOT

class Thing
{
public:
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08();
    virtual void v09(); virtual Drawable *getDrawable() const;
    Bool isKindOf(KindOfType) const;
    char m_pad04[0x34];
    Coord3D m_position;
};
class Player;
struct Rva001E9380ThingVtable
{
    void *slots00[10];
    union
    {
        Drawable *(__fastcall *getDrawableEax)(Thing *);
        Drawable *(__fastcall *getDrawableEdx)(Thing *, Rva001E9380ThingVtable *);
    };
};

class Object : public Thing
{
public:
    Bool isLocallyControlled() const;
    Bool queryRva001CAEE0(const Player *) const;
    Real getDistanceSquared(const Object *) const;
    char m_pad44[0x1b8];
    Rva001E9380Query1fcBase *m_query1fc;
    Rva001E9380Query200Base *m_query200;
    AIUpdateInterface *m_ai;
    AIUpdateInterface *getAI() const { return m_ai; }
    Rva001E9380Query1fcBase *getContain() const { return m_query1fc; }
};

class Drawable
{
public:
	Bool handleWeaponFireFX(WeaponSlotType wslot, Int barrel, const FXList *fx,
		Real weaponSpeed, Real recoilAmount, Real recoilAngle,
		const Coord3D *victimPos);
};

class TerrainLogic
{
public:
	void getBridgeAttackPoints(const Object *victim, TBridgeAttackInfo *info);
};

class Weapon
{
public:
	Real getAttackRange(const Object *source, Real heightDifference) const;
	Bool isGoalPosWithinAttackRange(const Object *source,
		const Coord3D *goalPos, const Object *target,
		const Coord3D *targetPos, Real extra) const;

	char m_pad00[0x30];
	UnsignedInt m_suspendFXFrame;
	char m_pad34[0x1c];
	UnsignedInt m_rangeFrame;
};

class Pathfinder
{
public:
    Bool bfmeGroundCellThreshold(const Coord3D *, Bool);
};
class BFMEObjectLocalQuery
{
public:
    char m_00[12];
    Pathfinder *m_pathfinder;
};
class BFMEObjectStealthQuery
{
public:
    char m_00[0x3c];
    UnsignedInt m_frame;
};
extern TerrainLogic *TheTerrainLogic;
extern BFMEObjectStealthQuery *TheBfmeGameLogic;
extern BFMEObjectLocalQuery *TheAI;
extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;
extern Real GetGameLogicRandomValueReal(Real low, Real high, char *file, Int line);
class FXList
{
public:
    static void doFXObj(const FXList *, const Object *, const Object *);
};
#define BFME_GAME_LOGIC_FRAME (TheBfmeGameLogic->m_frame)
#define BFME_RANDOM_FILE "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Weapon.cpp"
#define BFME_ZERO_RANGE BfmeZeroRange
#define BFME_DEFAULT_BU g_bfmeDefaultBU
static Real distanceToPoint(const Object *source, const Coord3D *point)
{
    return reinterpret_cast<const BfmeGap951 *>(source)->bfmeGapB951(reinterpret_cast<const BfmePt951 *>(point));
}


class Rva001E9380Nugget
{
public:
	virtual void v00();
	virtual Bool v01(Weapon *weapon, Object *victim);
	virtual Bool v02(Weapon *weapon, const Coord3D *position);
	virtual void v03();
	virtual void v04();
	virtual void v05(Weapon *weapon, Object *victim);
	virtual void v06(Weapon *weapon, const Coord3D *position);
};

class WeaponTemplate
{
public:
	Coord3D rva001E7C30(const Object *source, const Object *victim, Coord3D position);
	Coord3D rva001E65C0(const Object *source, const Object *victim, Bool);
	Real getMinimumAttackRange() const;
    Real getWeaponSpeed() const { return m_weaponSpeed; }
    Real getWeaponRecoilAmount() const { return m_weaponRecoil; }

	void rva001e9380(const Object *sourceObj, const Coord3D *sourcePos,
		Int wslot, Int specificBarrelToUse, Object *victimObj,
		ObjectID victimID, const Coord3D *victimPos,
		const WeaponBonus &bonus, Bool isProjectileDetonation,
		Weapon *firingWeapon, ObjectID *projectileID);

	UnsignedInt m_dword00;
	unsigned char m_pad04[0x2c];
	unsigned char m_byte30;
	unsigned char m_disableScatterForTargetsOnWall;
	unsigned char m_pad32[0x26];
	Real m_weaponSpeed;
	unsigned char m_pad5c[9];
	Bool m_byte65;
	unsigned char m_pad66[0x0e];
	Real m_weaponRecoil;
	unsigned char m_pad78[0x1c];
	const FXList *m_fireFXs[8];
	unsigned char m_padB4[0x4e4 - 0xb4];
	unsigned char m_damageDealtAtSelfPosition;
	unsigned char m_pad4e5[0x4fd - 0x4e5];
	unsigned char m_playFXWhenStealthed;
	unsigned char m_pad4fe[0x514 - 0x4fe];
	Real m_infantryInaccuracyDist;
	unsigned char m_pad518[0x520 - 0x518];
	Real m_hitPercentage;
	Real m_hitPassengerPercentage;
	unsigned char m_pad528[0x538 - 0x528];
	std::list<Rva001E9380Nugget *> m_nuggetList;
};


void WeaponTemplate::rva001e9380(const Object *sourceObj,
    const Coord3D *sourcePos, Int wslot, Int specificBarrelToUse,
    Object *victimObj, ObjectID victimID, const Coord3D *victimPos,
    const WeaponBonus &, Bool isProjectileDetonation,
    Weapon *firingWeapon, ObjectID *)
{
    if (sourceObj == 0 || (victimObj == 0 && victimPos == 0))
        return;
    const Coord3D *targetPosition = victimPos;
    Real distanceSquared;
    TBridgeAttackInfo bridge;
    Coord3D victimPosStorage;
    if (victimObj)
    {
        targetPosition = &victimObj->m_position;
        Coord3D sneakyOffset;
        AIUpdateInterface *ai = victimObj->getAI();
        if (ai && ai->getSneakyTargetingOffset(&sneakyOffset))
        {
            victimPosStorage = *targetPosition;
            victimPosStorage.x += sneakyOffset.x;
            victimPosStorage.y += sneakyOffset.y;
            victimPosStorage.z += sneakyOffset.z;
            targetPosition = &victimPosStorage;
            victimObj = 0;
            distanceSquared = distanceToPoint(sourceObj, targetPosition);
        }
        else if (victimObj->isKindOf(KINDOF_BRIDGE))
        {
            TheTerrainLogic->getBridgeAttackPoints(victimObj, &bridge);
            distanceSquared = distanceToPoint(sourceObj, &bridge.attackPoint1);
            Real second = distanceToPoint(sourceObj, &bridge.attackPoint2);
            if (distanceSquared > second)
            {
                distanceSquared = second;
                targetPosition = &bridge.attackPoint2;
            }
        }
        else
            distanceSquared = sourceObj->getDistanceSquared(victimObj);
    }
    else
        distanceSquared = distanceToPoint(sourceObj, targetPosition);

    if (!isProjectileDetonation && firingWeapon->m_rangeFrame <= BFME_GAME_LOGIC_FRAME)
    {
        Real attackRange = firingWeapon->getAttackRange(sourceObj, targetPosition->z-sourceObj->m_position.z);
        if (distanceSquared > attackRange * attackRange &&
            !firingWeapon->isGoalPosWithinAttackRange(sourceObj, &sourceObj->m_position, victimObj, targetPosition, 0.0f))
            return;
        Real minimumRange = getMinimumAttackRange();
        if (distanceSquared < minimumRange * minimumRange)
            return;
    }
    Rva001E9380ThingVtable *initialDrawableVtable = *(Rva001E9380ThingVtable **)sourceObj;
    if (initialDrawableVtable->getDrawableEax((Thing *)sourceObj))
    {
        Real recoilAngle = getWeaponRecoilAmount();
        Coord3D aimPosition;
        if (victimObj)
        {
            aimPosition = rva001E65C0(sourceObj, victimObj, true);
        }
        else
            aimPosition.set(targetPosition);
        Real direction = recoilAngle != 0.0f ? (Real)atan2(targetPosition->y-sourceObj->m_position.y, targetPosition->x-sourceObj->m_position.x) : 0.0f;
        const FXList *fx = m_fireFXs[0];
        if (BFME_GAME_LOGIC_FRAME < firingWeapon->m_suspendFXFrame)
            fx = 0;
        Bool handled;
        if (!sourceObj->isLocallyControlled() && sourceObj->queryRva001CAEE0(0) && !m_playFXWhenStealthed)
            handled = true;
        else
        {
            Rva001E9380ThingVtable *effectDrawableVtable = *(Rva001E9380ThingVtable **)sourceObj;
            handled = effectDrawableVtable->getDrawableEdx((Thing *)sourceObj, effectDrawableVtable)->handleWeaponFireFX((WeaponSlotType)wslot, specificBarrelToUse, fx, getWeaponSpeed(), recoilAngle, direction, &aimPosition);
        }
        if (!handled && fx)
            FXList::doFXObj(fx,sourceObj,victimObj);
    }
    if (m_damageDealtAtSelfPosition)
    {
        targetPosition = &sourceObj->m_position;
        victimObj = 0;
    }
    if (!targetPosition)
        targetPosition = &victimObj->m_position;
    Coord3D damagePosition = *targetPosition;
    Bool scatter = false;
    if (m_infantryInaccuracyDist > 0.0f && victimObj && victimObj->isKindOf(KINDOF_INFANTRY) &&
        (!m_disableScatterForTargetsOnWall || !TheAI->m_pathfinder->bfmeGroundCellThreshold(&victimObj->m_position,false)))
        scatter = true;
    if (m_hitPercentage < 1.0f)
    {
        Real percentage=m_hitPercentage;
        if (GetGameLogicRandomValueReal(0.0f,1.0f,BFME_RANDOM_FILE,0x536) >= percentage)
            scatter=true;
    }
    if (m_byte65 && victimObj && victimObj->m_query200->slot8C() > 0.0f &&
        GetGameLogicRandomValueReal(0.0f,1.0f,BFME_RANDOM_FILE,0x53c) <= victimObj->m_query200->slot8C())
        scatter = true;
    Bool passenger = false;
    if (!scatter && victimObj && victimObj->getContain() && !victimObj->getContain()->slot68() &&
        m_hitPassengerPercentage > 0.0f)
    {
        Real percentage=m_hitPassengerPercentage;
        if (GetGameLogicRandomValueReal(0.0f,1.0f,BFME_RANDOM_FILE,0x546) <= percentage)
        {
            passenger = true;
            scatter = false;
        }
    }
    if (m_byte30)
    {
        for (std::list<Rva001E9380Nugget *>::iterator node=m_nuggetList.begin(); node!=m_nuggetList.end(); ++node)
        {
            Rva001E9380Nugget *nugget=*node;
            if (scatter)
            {
                damagePosition = rva001E7C30(sourceObj, victimObj, damagePosition);
                victimObj = 0;
            }
            if (nugget->v02(firingWeapon,&damagePosition))
                nugget->v06(firingWeapon,&damagePosition);
        }
    }
    else
    {
        if (scatter)
        {
            damagePosition = rva001E7C30(sourceObj,victimObj,damagePosition);
            victimObj=0;
        }
        else if (passenger == true && victimObj->getContain())
        {
            Object *selected = victimObj->getContain()->slotE0(&victimObj->m_position);
            if (selected)
                victimObj=selected;
        }
        for (std::list<Rva001E9380Nugget *>::iterator node=m_nuggetList.begin(); node!=m_nuggetList.end(); ++node)
        {
            Rva001E9380Nugget *nugget=*node;
            if (victimObj)
            {
                if (nugget->v01(firingWeapon,victimObj))
                    nugget->v05(firingWeapon,victimObj);
            }
            else
            {
                if (nugget->v02(firingWeapon,&damagePosition))
                    nugget->v06(firingWeapon,&damagePosition);
            }
        }
    }
}
