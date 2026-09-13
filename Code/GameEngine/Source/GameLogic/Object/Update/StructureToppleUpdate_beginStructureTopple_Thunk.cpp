// cl: /DNDEBUG /MD /EHsc

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

class Thing;
class ModuleData;
class Object;

struct Coord2D
{
	Real x;
	Real y;

	Real toAngle() const;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class DamageInfo
{
public:
	unsigned char m_padding[8];
	Int m_sourceID;
};

class BfmeGeometryInfo
{
public:
	Real boxMajorRadius() const;
	Real boxMinorRadius() const;
};

class Object
{
public:
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const unsigned char *)this + 0x38);
	}

	Real getOrientation() const
	{
		return *(const Real *)((const unsigned char *)this + 0x44);
	}

	const BfmeGeometryInfo &getGeometryInfo() const
	{
		return *(const BfmeGeometryInfo *)((const unsigned char *)this + 0xac);
	}
};

class GameLogic
{
public:
	UnsignedInt getFrame() const
	{
		return *(const UnsignedInt *)((const unsigned char *)this + 0x3c);
	}

	Object *findObjectByID(Int objectID);
};

extern GameLogic *TheGameLogic;

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
	virtual void v50();
	virtual void adjustToppleDirection(Object *, Coord2D *);
};

extern ScriptEngine *TheScriptEngine;

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual Real getGroundHeight(Real, Real, Coord3D *) const;
};

extern TerrainLogic *TheTerrainLogic;

class UpdateModuleBase
{
public:
	UpdateModuleBase();
	virtual ~UpdateModuleBase();

protected:
	void *m_moduleData;
	Object *m_object;
};

class UpdateModuleInterface1
{
public:
	virtual void slot();
};

class UpdateModuleInterface2
{
public:
	virtual void slot();
};

class UpdateModule : public UpdateModuleBase,
	public UpdateModuleInterface1,
	public UpdateModuleInterface2
{
public:
	void setWakeFrame(Object *, Int);

	protected:
	Object *getObject() const
	{
		return m_object;
	}

private:
	UnsignedInt m_wakeFrame;
	Int m_wakeDelay;
	Int m_wakeFlags;
};

class StructureToppleUpdateInterface
{
public:
	virtual void slot();
};

class StructureToppleUpdateModuleData
{
public:
	unsigned char m_padding00[0x34];
	Int m_minToppleDelay;
	Int m_maxToppleDelay;
	unsigned char m_padding3c[0x28];
	Int m_minToppleBurstDelay;
	Int m_maxToppleBurstDelay;
	unsigned char m_padding6c[0x48];
	Real m_toppleAngle;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class StructureToppleUpdate : public UpdateModule,
	public StructureToppleUpdateInterface
{
protected:
	const StructureToppleUpdateModuleData *getStructureToppleUpdateModuleData() const
	{
		return (const StructureToppleUpdateModuleData *)m_moduleData;
	}

	void doToppleStartFX(Object *, const DamageInfo *);
	void beginStructureTopple(const DamageInfo *);

	UnsignedInt m_toppleFrame;
	Coord2D m_toppleDirection;
	Int m_toppleState;
	Real m_toppleVelocity;
	Real m_accumulatedAngle;
	Real m_structuralIntegrity;
	Real m_lastCrushedLocation;
	Int m_nextBurstFrame;
	Coord3D m_delayBurstLocation;
	Real m_buildingHeight;
};

extern int GetGameLogicRandomValue(int, int, char *, int);
extern Real GetGameLogicRandomValueReal(Real, Real, char *, int);
extern Real normalizeAngle(Real);
extern Real Cos(Real);
extern Real Sin(Real);
extern const float g_01075954;

#define BFME_SOURCE_FILE "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\StructureToppleUpdate.cpp"

// ?beginStructureTopple@StructureToppleUpdate@@IAEXPBVDamageInfo@@@Z
void StructureToppleUpdate::beginStructureTopple(const DamageInfo *damageInfo)
{
	const StructureToppleUpdateModuleData *d = getStructureToppleUpdateModuleData();

	if (d != 0)
	{
		UnsignedInt now = TheGameLogic->getFrame();
#line 135 BFME_SOURCE_FILE
		m_toppleFrame = now + GetGameLogicRandomValue(
			d->m_minToppleDelay, d->m_maxToppleDelay,
			(char *)BFME_SOURCE_FILE, 135);

		Object *attacker = TheGameLogic->findObjectByID(damageInfo->m_sourceID);
		Object *building = getObject();
		Real toppleAngle;

		if (d->m_toppleAngle != -9.876540184020996f)
		{
			toppleAngle = d->m_toppleAngle;
			toppleAngle *= *(volatile const Real *)&g_01075954;
			toppleAngle += building->getOrientation();
#line 145 BFME_SOURCE_FILE
			if (GetGameLogicRandomValue(0, 2, (char *)BFME_SOURCE_FILE, 145) < 1)
			{
				toppleAngle += 2 * 3.14159265359f;
			}
			toppleAngle = normalizeAngle(toppleAngle);
		}
		else if (attacker == 0)
		{
#line 151 BFME_SOURCE_FILE
			toppleAngle = GetGameLogicRandomValueReal(
				0.0f, 2 * 3.14159265359f, (char *)BFME_SOURCE_FILE, 151);
		}
		else
		{
			const Coord3D *attackerPos = attacker->getPosition();
			const Coord3D *buildingPos = building->getPosition();
			m_toppleDirection.x = buildingPos->x - attackerPos->x;
			m_toppleDirection.y = buildingPos->y - attackerPos->y;
			toppleAngle = m_toppleDirection.toAngle();
#line 164 BFME_SOURCE_FILE
			toppleAngle += GetGameLogicRandomValueReal(
				-3.14159265359f / 8, 3.14159265359f / 8,
				(char *)BFME_SOURCE_FILE, 164);
		}

		m_toppleDirection.x = Cos(toppleAngle);
		m_toppleDirection.y = Sin(toppleAngle);
		TheScriptEngine->adjustToppleDirection(getObject(), &m_toppleDirection);

		Real majorRadius = building->getGeometryInfo().boxMajorRadius();
		Real minorRadius = building->getGeometryInfo().boxMinorRadius();
		Real averageRadius = (majorRadius + minorRadius) / 2;
		Real explosionRadius = averageRadius * *(const double *)0x010af378;
		m_delayBurstLocation.x = building->getPosition()->x +
			explosionRadius * Cos(toppleAngle);
		m_delayBurstLocation.y = building->getPosition()->y +
			explosionRadius * Sin(toppleAngle);
		m_delayBurstLocation.z = TheTerrainLogic->getGroundHeight(
			m_delayBurstLocation.x, m_delayBurstLocation.y, 0);

		doToppleStartFX(building, damageInfo);
#line 181 BFME_SOURCE_FILE
		m_nextBurstFrame = now + GetGameLogicRandomValue(
			d->m_minToppleBurstDelay, d->m_maxToppleBurstDelay,
			(char *)BFME_SOURCE_FILE, 181);

		m_toppleState = 1;
		setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
	}
}
