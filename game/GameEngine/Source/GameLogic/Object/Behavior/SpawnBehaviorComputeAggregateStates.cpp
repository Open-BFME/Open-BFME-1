// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// SpawnBehavior::computeAggregateStates, retail 0x0020BAE0. The body is 750
// bytes: the else-branch epilogue ends with the ret at +0x2ED (int3 follows).
// Identity: SpawnBehavior::update (0x0020C750, SpawnBehaviorUpdate.cpp) calls
// it by name; the statements follow the Zero Hour twin in SpawnBehavior.cpp,
// less the veterancy and weapon-bonus propagation BFME does not have, with
// Object::maskObject in place of setStatus(OBJECT_STATUS_MASKED).
//
// Two declarations carry the match:
// - GameLogic::findObjectByID is the header inline (the same hash_map lookup
//   SpawnBehavior_onDamage.cpp inlines). MSVC declines to inline it here and
//   calls the out-of-line copy, but only the inline declaration reproduces
//   retail's register assignment (this in EBP, list cursor in EBX).
// - body-module slot +0x54 takes a second Bool: retail pushes it once before
//   the branch, and StructureBody's slot 21 body (0x00212610) ends in ret 8
//   and tests that argument as a byte.

#include <hash_map>
#include <list>

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef int ObjectID;

struct Rva0020BAE0Coord3D
{
	Real x;
	Real y;
	Real z;

	void set(Real ax, Real ay, Real az)
	{
		x = ax;
		y = ay;
		z = az;
	}

	void add(const Rva0020BAE0Coord3D *a)
	{
		x += a->x;
		y += a->y;
		z += a->z;
	}

	void sub(const Rva0020BAE0Coord3D *a)
	{
		x -= a->x;
		y -= a->y;
		z -= a->z;
	}

	void scale(Real scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;
	}
};

class Object;

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id)
	{
		if (id == 0)
			return 0;
		ObjectPtrHash::iterator it = m_objHash.find(id);
		if (it == m_objHash.end())
			return 0;
		return (*it).second;
	}

private:
	char m_pad000[0xB0];
	ObjectPtrHash m_objHash;
};

extern GameLogic *TheGameLogic;

class GameMessage
{
public:
	void appendBooleanArgument(Bool arg);
	void appendObjectIDArgument(UnsignedInt arg);
};

class MessageStream
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual GameMessage *appendMessage(Int type);
};

extern MessageStream *TheMessageStream;

class Rva0020BAE0Drawable
{
public:
	Bool isSelected() const { return m_unmodelled3AC; }

private:
	unsigned char m_pad000[0x3AC];
	Bool m_unmodelled3AC;
};

class Rva0020BAE0BodyModule
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual Real getHealth();
	virtual void slot5();
	virtual Real getMaxHealth();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void setInitialHealth(Real percent, Bool arg2);
};

class Rva0020BAE0SlavedUpdate
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual Bool isSelfTasking();
};

class Rva0020BAE0ModuleBase
{
	virtual void slot0();
	void *m_moduleData;
	Object *m_object;
};

class Rva0020BAE0BehaviorInterface
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual Rva0020BAE0SlavedUpdate *getSlavedUpdateInterface();
};

class Rva0020BAE0BehaviorModule : public Rva0020BAE0ModuleBase, public Rva0020BAE0BehaviorInterface
{
};

class Object
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual Rva0020BAE0Drawable *getDrawable();

	void maskObject(Bool mask);

	const Rva0020BAE0Coord3D *getPosition() const { return &m_unmodelled038; }
	ObjectID getID() const { return m_id; }
	Rva0020BAE0BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	Rva0020BAE0BodyModule *getBodyModule() const { return m_unmodelled200; }
	void setHealthBoxOffset(const Rva0020BAE0Coord3D &offset) { m_unmodelled24C = offset; }

private:
	unsigned char m_pad004[0x38 - 0x04];
	Rva0020BAE0Coord3D m_unmodelled038;
	unsigned char m_pad044[0x74 - 0x44];
	ObjectID m_id;
	unsigned char m_pad078[0x1F0 - 0x78];
	Rva0020BAE0BehaviorModule **m_behaviors;
	unsigned char m_pad1F4[0x200 - 0x1F4];
	Rva0020BAE0BodyModule *m_unmodelled200;
	unsigned char m_pad204[0x24C - 0x204];
	Rva0020BAE0Coord3D m_unmodelled24C;
};

class InGameUI
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
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
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void selectDrawable(Rva0020BAE0Drawable *draw);
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void slot88();
	virtual void slot89();
	virtual void slot90();
	virtual void slot91();
	virtual void slot92();
	virtual void setDisplayedMaxWarning(Bool selected);
};

extern InGameUI *TheInGameUI;

class Rva0020BAE0SpawnBehaviorModuleData
{
	unsigned char m_pad00[0x08];

public:
	Int m_spawnNumberData;
};

class SpawnBehavior
{
public:
	void computeAggregateStates();

private:
	Object *getObject() const { return m_object; }
	const Rva0020BAE0SpawnBehaviorModuleData *getSpawnBehaviorModuleData() const { return m_moduleData; }

	void *m_vtable;
	const Rva0020BAE0SpawnBehaviorModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x48 - 0x0C];
	_STL::list<ObjectID> m_spawnIDs;
	unsigned char m_pad4C;
	Bool m_aggregateHealth;
	unsigned char m_pad4E[0x54 - 0x4E];
	UnsignedInt m_selfTaskingSpawnCount;
};

// ?computeAggregateStates@SpawnBehavior@@QAEXXZ
void SpawnBehavior::computeAggregateStates()
{
	if (!m_aggregateHealth)
		return;

	const Rva0020BAE0SpawnBehaviorModuleData *md = getSpawnBehaviorModuleData();
	Object *obj = getObject();

	Int spawnCount = 0;
	Int spawnCountMax = md->m_spawnNumberData;
	Rva0020BAE0Coord3D avgSpawnPos;
	avgSpawnPos.set(0.0f, 0.0f, 0.0f);
	Real acrHealth = 0.0f;
	Real avgHealthMax = 0.0f;

	Bool SomebodyIsSelected = false;
	Bool SomebodyIsNotSelected = false;
	Rva0020BAE0Drawable *spawnDraw = 0;
	Object *currentSpawn = 0;

	m_selfTaskingSpawnCount = 0;

	for (_STL::list<ObjectID>::iterator iter = m_spawnIDs.begin(); iter != m_spawnIDs.end(); iter++)
	{
		currentSpawn = TheGameLogic->findObjectByID(*iter);

		if (currentSpawn)
		{
			for (Rva0020BAE0BehaviorModule **update = currentSpawn->getBehaviorModules(); *update; ++update)
			{
				Rva0020BAE0SlavedUpdate *sdu = (*update)->getSlavedUpdateInterface();
				if (sdu != 0)
				{
					m_selfTaskingSpawnCount += sdu->isSelfTasking();
					break;
				}
			}

			avgSpawnPos.add(currentSpawn->getPosition());

			Rva0020BAE0BodyModule *body = currentSpawn->getBodyModule();
			acrHealth += body->getHealth();
			avgHealthMax += body->getMaxHealth();

			spawnDraw = currentSpawn->getDrawable();
			if (spawnDraw->isSelected())
				SomebodyIsSelected = true;
			else
				SomebodyIsNotSelected = true;

			++spawnCount;
		}
	}

	if (SomebodyIsSelected && (!obj->getDrawable()->isSelected() || SomebodyIsNotSelected))
	{
		GameMessage *teamMsg = TheMessageStream->appendMessage(0x3E9);
		teamMsg->appendBooleanArgument(false);

		if (SomebodyIsNotSelected)
		{
			for (_STL::list<ObjectID>::iterator iter = m_spawnIDs.begin(); iter != m_spawnIDs.end(); iter++)
			{
				currentSpawn = TheGameLogic->findObjectByID(*iter);
				if (currentSpawn)
				{
					spawnDraw = currentSpawn->getDrawable();
					if (!spawnDraw->isSelected())
					{
						TheInGameUI->selectDrawable(spawnDraw);
						TheInGameUI->setDisplayedMaxWarning(false);
						teamMsg->appendBooleanArgument(false);
						teamMsg->appendObjectIDArgument(currentSpawn->getID());
					}
				}
			}
		}

		if (!obj->getDrawable()->isSelected())
		{
			TheInGameUI->selectDrawable(obj->getDrawable());
			TheInGameUI->setDisplayedMaxWarning(false);
			teamMsg->appendBooleanArgument(false);
			teamMsg->appendObjectIDArgument(obj->getID());
		}
	}

	avgSpawnPos.scale(1.0f / spawnCount);
	avgSpawnPos.sub(obj->getPosition());
	obj->setHealthBoxOffset(avgSpawnPos);

	if (spawnCount)
	{
		avgHealthMax /= spawnCount;
		Real perfectTotalHealth = avgHealthMax * spawnCountMax;
		Real actualHealth = acrHealth / perfectTotalHealth;
		obj->getBodyModule()->setInitialHealth(100.0f * actualHealth, false);
	}
	else
	{
		obj->getBodyModule()->setInitialHealth(0.0f, false);
	}

	obj->maskObject(true);
}
