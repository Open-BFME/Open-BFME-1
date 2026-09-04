// ?applyTopplingForce@ToppleUpdate@@QAEXPBUCoord3D@@MI@Z
// partial score=0.94 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
// Object.cpp reloc-named callee: applyTopplingForce@ToppleUpdate
// Identity: ILT 0x0003FC97 thunks here; Object.cpp REL32; ZH ToppleUpdate.cpp twin;
// landed ctor at ToppleUpdateCtorThunk.cpp pins the same instance/module layout.
extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" double __cdecl atan2(double, double);

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef int NameKeyType;
typedef unsigned int ObjectID;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum DamageType
{
	DAMAGE_EXPLOSION = 0,
	DAMAGE_UNRESISTABLE = 8
};

enum DeathType
{
	DEATH_NORMAL = 0
};

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))

static const Real PI = 3.14159265359f;
static const Real ANGULAR_LIMIT = PI / 2 - PI / 64;

class Object;
class Thing;
class ModuleData;
class Coord3D;
class Pathfinder;
class ThingTemplate;
class Team;
class Drawable;
class ClientUpdateModule;

struct Coord3D
{
	Real x, y, z;
	void normalize(void);
};

Real normalizeAngle(Real);
Real angleClosestTo(Real, Real, Real);
Real Cos(Real);
Real Sin(Real);

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *);
};

class ScriptEngine
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void adjustToppleDirection(Object *, Coord3D *);
};

class Pathfinder
{
public:
	void removeObjectFromPathfindMap(Object *);
};

class AI
{
public:
	void *m_vptr;
	int m_04;
	int m_08;
	Pathfinder *m_pathfinder;
};

class FXList
{
public:
	bool bfmeIsBlocked(void) const;
	void doFXObj(const Object *primary, const Object *secondary) const;
};

class BfmeRetailAsciiString
{
public:
	char *m_data;
};

class ClientUpdateModule
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual NameKeyType getModuleNameKey(void) const;
	unsigned char m_pad[0x1E];
	unsigned char m_stopSway;
};

class ModelConditionFlags
{
public:
	bool test(int bit) const;
};

class ModelNotifyBits
{
public:
	bool test(int bit) const
	{
		return (m_bits & (1u << bit)) != 0;
	}
	void set(int bit)
	{
		m_bits |= 1u << bit;
	}

private:
	unsigned int m_bits;
};

class Drawable
{
public:
	unsigned char m_pad154[0x154];
	ClientUpdateModule **m_clientUpdateModules;
	unsigned char m_pad250[0xF8];
	ModelConditionFlags m_conditionFlags;
};

class Object
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual Drawable *getDrawable(void);
	void kill(DamageType, DeathType);
	void notifyModelConditionChanged(void);
	void setPosition(const Coord3D *);
	void setOrientation(Real);
	Real getOrientation(void) const { return m_orientation; }
	void setModelConditionState(int bit)
	{
		if (!m_modelNotifyBits.test(bit))
		{
			m_modelNotifyBits.set(bit);
			notifyModelConditionChanged();
		}
	}

	unsigned char m_pad004[0x34];
	Coord3D m_position;
	Real m_orientation;
	unsigned char m_pad048[0x2C];
	ObjectID m_id;
	unsigned char m_pad078[0x98];
	ModelNotifyBits m_modelNotifyBits;
	unsigned char m_pad114[4];
	unsigned int m_stumpModelBits;
	unsigned char m_pad11c[0x228];
	unsigned char m_privateStatus;
};

class ThingTemplate;

template<int NUMBITS>
class BitFlags
{
public:
	BitFlags() { }
	void clear() { m_bits.reset(); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusBits;

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const BfmeRetailAsciiString &);
	Object *newObject(const ThingTemplate *, Team *, const ObjectStatusBits *, int);
};

class ToppleUpdateModuleData
{
public:
	void *m_vptr;
	unsigned int m_04;
	FXList *m_toppleFX;
	FXList *m_bounceFX;
	BfmeRetailAsciiString m_stumpName;
	Real m_initialVelocityPercent;
	Real m_initialAccelPercent;
	Real m_bounceVelocityPercent;
	Real m_minToppleSpeed;
	bool m_killWhenToppled;
	bool m_killWhenStartToppled;
	bool m_killStumpWhenToppled;
	bool m_toppleLeftOrRightOnly;
	bool m_reorientToppledRubble;
};

class TU_DeepBase
{
public:
	TU_DeepBase(Thing *, const ModuleData *);
	virtual ~TU_DeepBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class TU_Iface1 { public: virtual void slot(); };
class TU_Iface2 { public: virtual void slot(); };

class UpdateModule : public TU_DeepBase, public TU_Iface1, public TU_Iface2
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);

protected:
	void setWakeFrame(Object *, UpdateSleepTime);
	Object *getObject() const { return m_object; }
	const ToppleUpdateModuleData *getToppleUpdateModuleData() const
	{
		return (const ToppleUpdateModuleData *)m_moduleData;
	}

private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

class BfmeToppleCollideModuleInterface { public: virtual void slot(); };

class ToppleUpdate : public UpdateModule, public BfmeToppleCollideModuleInterface
{
public:
	void applyTopplingForce(const Coord3D *toppleDirection, Real toppleSpeed, UnsignedInt options);

private:
	Real m_angularVelocity;
	Real m_angularAcceleration;
	Coord3D m_toppleDirection;
	int m_toppleState;
	Real m_angularAccumulation;
	Real m_angleDeltaX;
	Int m_numAngleDeltaX;
	bool m_doBounceFX;
	UnsignedInt m_options;
	ObjectID m_stumpID;
	unsigned int m_bfmeState;
};

extern ScriptEngine *TheScriptEngine;
extern NameKeyGenerator *TheNameKeyGenerator;
extern AI *TheAI;
extern ThingFactory *TheThingFactory;

// ?applyTopplingForce@ToppleUpdate@@QAEXPBUCoord3D@@MI@Z
void ToppleUpdate::applyTopplingForce(const Coord3D *toppleDirection, Real toppleSpeed, UnsignedInt options)
{
	ObjectStatusBits bits;
	if (getObject()->m_privateStatus & 1)
		return;

	const ToppleUpdateModuleData *d = getToppleUpdateModuleData();
	if (toppleSpeed < d->m_minToppleSpeed)
		toppleSpeed = d->m_minToppleSpeed;

	Drawable *draw = getObject()->getDrawable();
	setWakeFrame(getObject(), UPDATE_SLEEP_NONE);

	if (d->m_killWhenStartToppled)
	{
		setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
		getObject()->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
		return;
	}

	m_toppleDirection = *toppleDirection;
	m_toppleDirection.normalize();
	TheScriptEngine->adjustToppleDirection(getObject(), &m_toppleDirection);

	m_angularVelocity = toppleSpeed * d->m_initialVelocityPercent;
	m_angularAcceleration = toppleSpeed * d->m_initialAccelPercent;
	m_toppleState = 1;
	m_options = options;

	static NameKeyType nameKeySwayUpdate = TheNameKeyGenerator->nameToKey("SwayClientUpdate");
	ClientUpdateModule **clientModules = draw->m_clientUpdateModules;
	if (clientModules)
	{
		while (*clientModules)
		{
			if ((*clientModules)->getModuleNameKey() == nameKeySwayUpdate)
				(*clientModules)->m_stopSway = 0;
			++clientModules;
		}
	}

	Real curAngleX = normalizeAngle(getObject()->getOrientation());
	Real toppleAngle = normalizeAngle((Real)atan2(m_toppleDirection.y, m_toppleDirection.x));
	if (d->m_toppleLeftOrRightOnly)
	{
		toppleAngle = angleClosestTo(curAngleX + PI / 2, curAngleX - PI / 2, toppleAngle);
		m_toppleDirection.x = Cos(toppleAngle);
		m_toppleDirection.y = Sin(toppleAngle);
		TheAI->m_pathfinder->removeObjectFromPathfindMap(getObject());
	}

	Real desiredAngleX = angleClosestTo(toppleAngle + PI / 2, toppleAngle - PI / 2, curAngleX);
	m_numAngleDeltaX = REAL_TO_INT_FLOOR(ANGULAR_LIMIT / (m_angularVelocity * (Real)2));
	if (m_numAngleDeltaX < 1)
		m_numAngleDeltaX = 1;
	m_angleDeltaX = (desiredAngleX - curAngleX) / m_numAngleDeltaX;

	getObject()->setModelConditionState(0);

	{
		FXList *toppleFX = d->m_toppleFX;
		Object *obj = getObject();
		if (toppleFX && !toppleFX->bfmeIsBlocked())
			toppleFX->doFXObj(obj, 0);
	}

	if (d->m_stumpName.m_data && *(unsigned short *)(d->m_stumpName.m_data + 4) != 0)
	{
		const ThingTemplate *ttn = TheThingFactory->findTemplate(d->m_stumpName);
		bits.clear();
		Object *stump = TheThingFactory->newObject(ttn, 0, &bits, 0);
		if (stump)
		{
			stump->setPosition(&getObject()->m_position);
			stump->setOrientation(getObject()->m_orientation);
			m_stumpID = stump->m_id;

			Drawable *ownerDraw = getObject()->getDrawable();
			if (ownerDraw && ownerDraw->m_conditionFlags.test(0x4f) == true)
			{
				if ((stump->m_stumpModelBits & 0x8000) == 0)
				{
					stump->m_stumpModelBits |= 0x8000;
					stump->notifyModelConditionChanged();
				}
			}
		}
	}
}
