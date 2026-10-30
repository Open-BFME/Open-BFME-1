// cl: /DNDEBUG /MD /EHsc
//
// SquishCollide::onCollide, retail 0x00216D90 (1138 bytes, ret 0xC).
// BFME 1 target evidence: the matched constructor 0x00216BA0 installs vtable
// VA 0x010A9F94 at +0x10, whose slot 0 reaches this body, and ilt_oracle
// confirms ?onCollide@SquishCollide@@UAEXPAVObject@@PBVCoord3D@@1@Z
// (class-keyed Coord3D; the struct-keyed spelling is contradicted). `this`
// is the CollideModuleInterface subobject, the Object sits at -8. The
// HijackerUpdate key is a function static (guard 0x012EF9E4, unwind state 0);
// the local GeometryInfo copy is state 1.
// Donor (open-bfme-2 20a0cb6173, Code/GameEngine/Source/GameLogic/Object/
// Collide/SquishCollide.cpp, retail 0x004BBA65 there, 1144 B) supplies the
// control flow; BFME 1 differs in the kind tests (KindOf 0x6C), the
// friendly-crush test (relationship 2 returns) and the crush weapons at
// +0x2B8/+0x2BC. Callee names are the ledger's; several are address-derived.
// Scratch-register choice follows two source details: the experience
// pointer is a named local and object IDs are read through getID().

typedef float Real;
typedef bool Bool;

enum KindOfType
{
	KINDOF_6C = 0x6c
};
enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};
enum Relationship
{
	ALLIES = 2
};
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};
enum SpecialPowerType
{
	SPECIAL_POWER_19 = 0x19
};

// class-gate: allow Coord3D ilt_oracle confirms the class-keyed (PBV) decoration for this body; the canonical header is struct-keyed.
class Coord3D
{
public:
	Coord3D() {}
	Coord3D(const Coord3D &o) : x(o.x), y(o.y), z(o.z) {}
	Real x, y, z;
	void normalize();
	void sub(const Coord3D *a) { x -= a->x; y -= a->y; z -= a->z; }
};

class Module;
class Weapon;
class Object;
class SpecialAbilityUpdate;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class StateMachine
{
public:
	Object *getGoalObject();
};

template<int N> class Rva00216D90Slots : public Rva00216D90Slots<N - 1>
{
public:
	virtual void slot(char (*)[N]);
};
template<> class Rva00216D90Slots<0>
{
};

class Rva00216D90AI : public Rva00216D90Slots<84>
{
public:
	virtual Object *v150();				// slot 84
	unsigned char m_pad04[0x30 - 4];
	StateMachine *m_stateMachine;			// +0x30
};

class Rva00216D90Body : public Rva00216D90Slots<38>
{
public:
	virtual Bool v98(Object *other);		// slot 38
};

class Rva00216D90Experience
{
public:
	unsigned char m_pad00[0x5c];
	Bool m_flag5C;					// +0x5C
};

class Rva00216D90AbilityIface : public Rva00216D90Slots<2>
{
public:
	virtual Bool v08();				// slot 2
};

class Rva00216D90Ability
{
public:
	unsigned char m_pad00[0x20];
	Rva00216D90AbilityIface m_iface20;		// +0x20
};

// ??1Rva000FFCA0 is the ledger's name for GeometryInfo's destructor.
class Rva000FFCA0
{
public:
	~Rva000FFCA0();
};

class GeometryInfo : public Rva000FFCA0
{
public:
	GeometryInfo(const GeometryInfo &other);
	unsigned char m_data[0x5c];
};

class Thing : public Rva00216D90Slots<13>
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class DamageInfo
{
public:
	DamageInfo();
	unsigned int m_vtbl00;
	unsigned int m_inVtbl04;
	unsigned int m_sourceID;			// +0x08
	unsigned char m_pad0c[4];
	int m_damageType;				// +0x10
	unsigned char m_pad14[4];
	int m_deathType;				// +0x18
	Real m_amount;					// +0x1C
	unsigned char m_pad20[0x10];
	Coord3D m_direction;				// +0x30
	Real m_field3C;					// +0x3C
	Real m_field40;					// +0x40
	Real m_field44;					// +0x44
	Real m_field48;					// +0x48
	unsigned char m_pad4c[0x10];
};

class Object : public Thing
{
	friend class SquishCollide;
public:
	virtual void v34(DamageInfo *info);		// slot 13
	unsigned char getCrushableLevel() const;
	unsigned char getCrusherLevel() const;
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	Relationship getRelationship(const Object *that) const;
	SpecialAbilityUpdate *findSpecialAbilityUpdate(SpecialPowerType type) const;
	Bool rva001c7530();
	void rva001CC660(Object *other);
	void rva001CC250(Object *other);
	void friend_setUndetectedDefector(Bool set);
	const Coord3D *getPosition() const { return &m_position; }
	unsigned int getID() const { return m_id; }
	unsigned char m_pad004[0x38 - 4];
	Coord3D m_position;				// +0x38
	Real m_orientation;				// +0x44
	unsigned char m_pad048[0x74 - 0x48];
	unsigned int m_id;				// +0x74
	unsigned char m_pad078[0xac - 0x78];
	GeometryInfo m_geometryInfo;			// +0xAC
	unsigned char m_pad108[0x200 - 0x108];
	Rva00216D90Body *m_body;			// +0x200
	Rva00216D90AI *m_ai;				// +0x204
	Rva00216D90Experience *m_experience;		// +0x208
	unsigned char m_pad20c[0x2b8 - 0x20c];
	Weapon *m_crushWeapon;				// +0x2B8
	Weapon *m_crushedWeapon;			// +0x2BC
	unsigned char m_pad2c0[0x344 - 0x2c0];
	unsigned char m_status344;			// +0x344
protected:
	Module *findModule(NameKeyType key) const;
};

class Weapon
{
public:
	Bool rva001EA5F0(const Object *source, int victimID, const Object *victim, int *projectileID);
};

class BfmeVec3EP
{
public:
	Real x, y, z;
};
class Gen_001C1D60
{
public:
	BfmeVec3EP bfmeGetRow() const;
};

struct BfmeOtherMG;
class BfmeThingMG
{
public:
	unsigned char bfmeTellMG(BfmeOtherMG *other, void *what);
};

class BFMEActionObject
{
public:
	Bool testStatus(int bit) const;
};

class Rva00216D20
{
public:
	Bool field() const;
};
class Rva00216CC0
{
public:
	Real field() const;
};
class Rva00216CF0
{
public:
	Real field() const;
};

// Callees whose ledger decorations use the struct-keyed Coord3D, or whose
// ledger signature disagrees with the retail call (int result tested as AL,
// float pushed for a void* parameter): reached through their ILT rows.
extern void j_00005ee3();	// Thing::getUnitDirectionVector2D 0x00132190
extern void j_0003ab20();	// Rva000D3F10::test 0x000D3F10
extern void j_000424b5();	// GeometryInfo radius setter 0x000FD030
extern void j_0002ca2f();	// GeometryInfo radius setter 0x000FD070
class Rva00216D90Call
{
public:
	void method();
};
static __forceinline void rva00132190(const Object *o, Coord3D &dir)
{
	union { void (*raw)(); void (Rva00216D90Call::*fn)(Coord3D &) const; } c;
	c.raw = j_00005ee3;
	(((const Rva00216D90Call *)o)->*c.fn)(dir);
}
static __forceinline Bool rva000D3F10(Object *o, unsigned int bit)
{
	union { void (*raw)(); Bool (Rva00216D90Call::*fn)(unsigned int); } c;
	c.raw = j_0003ab20;
	return (((Rva00216D90Call *)o)->*c.fn)(bit);
}
static __forceinline void rva000FD030(GeometryInfo *g, Real value)
{
	union { void (*raw)(); void (Rva00216D90Call::*fn)(Real); } c;
	c.raw = j_000424b5;
	(((Rva00216D90Call *)g)->*c.fn)(value);
}
static __forceinline void rva000FD070(GeometryInfo *g, Real value)
{
	union { void (*raw)(); void (Rva00216D90Call::*fn)(Real); } c;
	c.raw = j_0002ca2f;
	(((Rva00216D90Call *)g)->*c.fn)(value);
}
// Direct call (no ILT) to the struct-keyed GeometryInfo intersection test.
extern "C" void __identifier("?bfmeIntersects@GeometryInfo@@QBE_NABUCoord3D@@MABV1@0M@Z")();
static __forceinline Bool rva0087F2F0(const GeometryInfo *g, const Coord3D &pos, Real angle,
	const GeometryInfo &other, const Coord3D &otherPos, Real otherAngle)
{
	union { void (*raw)(); Bool (Rva00216D90Call::*fn)(const Coord3D &, Real, const GeometryInfo &, const Coord3D &, Real) const; } c;
	c.raw = __identifier("?bfmeIntersects@GeometryInfo@@QBE_NABUCoord3D@@MABV1@0M@Z");
	return (((const Rva00216D90Call *)g)->*c.fn)(pos, angle, other, otherPos, otherAngle);
}

class SquishCollide
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
	Object *getObject() const { return *(Object **)((char *)this - 8); }
};

void SquishCollide::onCollide(Object *other, const Coord3D *loc, const Coord3D *normal)
{
	// Note that other == null means "collide with ground"
	if (other == 0 || (other->m_status344 & 1))
		return;
	if (other->isKindOf(KINDOF_6C))
		return;
	Object *self = getObject();
	if (self->m_status344 & 1)
		return;
	Rva00216D90Experience *experience = self->m_experience;
	if (experience->m_flag5C)
		return;
	if (!((char)other->getCrusherLevel() > (char)self->getCrushableLevel()))
		return;
	Rva00216D90AI *otherAI = other->m_ai;
	if (otherAI)
	{
		Object *target = otherAI->v150();
		if (target)
		{
			if (*(unsigned int *)((char *)target + 0x3f8) == self->getID())
				return;
		}
		else if (otherAI->m_stateMachine->getGoalObject() == self && other->getCurrentWeapon(0)
			&& ((BfmeThingMG *)other->getCurrentWeapon(0))->bfmeTellMG((BfmeOtherMG *)other, self))
			return;
	}
	// only squish if tank is moving toward victim
	Coord3D dir;
	rva00132190(other, dir);
	const Coord3D *otherPos = other->getPosition();
	BfmeVec3EP actualPos = ((const Gen_001C1D60 *)other)->bfmeGetRow();
	Object *me = getObject();
	Coord3D to(*me->getPosition());
	to.sub(otherPos);
	if (to.x * dir.x + to.y * dir.y < 0.0f)
	{
		to = *me->getPosition();
		to.sub((const Coord3D *)&actualPos);
		if (to.x * dir.x + to.y * dir.y < 0.0f)
			return;
	}
	// order matters: we want to know if IT considers ME to be an ally
	if (!((BFMEActionObject *)other)->testStatus(0x38) && !((BFMEActionObject *)other)->testStatus(0x31)
		&& !rva000D3F10(other, 0x7c) && !((Rva00216D20 *)other)->field()
		&& other->getRelationship(me) == ALLIES)
		return;
	Rva00216D90AI *ai = self->m_ai;
	if (ai && ai->m_stateMachine->getGoalObject() == other)
	{
		// Hijacking!
		static NameKeyType key_HijackerUpdate = TheNameKeyGenerator->nameToKey("HijackerUpdate");
		if (self->findModule(key_HijackerUpdate))
			return;
		// TNT hunter placing a charge!
		Rva00216D90Ability *ability = (Rva00216D90Ability *)self->findSpecialAbilityUpdate(SPECIAL_POWER_19);
		if (ability && ability->m_iface20.v08())
			return;
	}
	GeometryInfo myGeom(self->m_geometryInfo);
	rva000FD030(&myGeom, 5.0f);
	rva000FD070(&myGeom, 5.0f);
	if (!rva0087F2F0(&other->m_geometryInfo, *other->getPosition(), other->m_orientation, myGeom,
			*self->getPosition(), self->m_orientation))
		return;
	if (!other->rva001c7530())
	{
		other->rva001CC660(getObject());
		return;
	}
	Rva00216D90Body *body = getObject()->m_body;
	if (body && !body->v98(other))
		return;
	DamageInfo damageInfo;
	other->rva001CC250(getObject());
	if (((Rva00216CC0 *)other)->field() > 0.0f)
	{
		Coord3D v(*self->getPosition());
		v.sub(other->getPosition());
		v.normalize();
		damageInfo.m_direction = v;
		damageInfo.m_field3C = ((Rva00216CC0 *)other)->field();
		damageInfo.m_field48 = ((Rva00216CF0 *)other)->field();
		damageInfo.m_field40 = 10.0f;
		damageInfo.m_field44 = 1.0f;
		damageInfo.m_damageType = 1;
		damageInfo.m_deathType = 0;
		damageInfo.m_sourceID = other->getID();
		damageInfo.m_amount = 0.0f;
		self->v34(&damageInfo);
	}
	if (!other->isKindOf(KINDOF_6C))
	{
		Weapon *crushWeapon = other->m_crushWeapon;
		if (crushWeapon)
			crushWeapon->rva001EA5F0(other, self->getID(), self, 0);
		else
		{
			damageInfo.m_damageType = 1;
			damageInfo.m_deathType = 2;
			damageInfo.m_sourceID = other->getID();
			damageInfo.m_amount = 999999.0f; // make sure they die
			self->v34(&damageInfo);
		}
		Weapon *crushedWeapon = self->m_crushedWeapon;
		if (crushedWeapon)
			crushedWeapon->rva001EA5F0(self, other->getID(), other, 0);
	}
	other->friend_setUndetectedDefector(false);
}
