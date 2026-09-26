// ?update@AnimalAIUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.68 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

// BFME-only AnimalAIUpdate::update.  There is no Zero Hour twin; the owning
// file and behavior are identified by the retail CritterDesync literals.

typedef unsigned int ObjectID;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class Object
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
	float distanceSquaredTo(Object *other) const;
};

class AnimalTemplateView
{
public:
	AnimalTemplateView *friend_getFinalOverride();
};

class AIUpdateInterface
{
public:
	virtual UpdateSleepTime update();
	void aiIdle(CommandSourceType source);
	void aiMoveToPosition(const Coord3D *position, CommandSourceType source);
};

class AnimalAIUpdateDestinationLayer
{
public:
	unsigned char isReachableLayer(const Coord3D *position) const;
};

class AnimalAIUpdate
{
public:
	virtual UpdateSleepTime update();
};

struct AnimalAIUpdateModuleDataView
{
	unsigned char m_beforeFleeRange[0x64];
	int m_fleeRange;
	int m_fleeDistance;
	int m_wanderPercentage;
	int m_maxWanderDistance;
	int m_maxWanderRadius;
	unsigned int m_updateTimer;
};

class TerrainLogic
{
public:
	int getLayerForDestination(Object *object, const Coord3D *position);
};

class GameLogicFrameView
{
public:
	unsigned char m_beforeFrame[0x3c];
	unsigned int m_frame;
	Object *findObjectByID(ObjectID id);
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, float range,
		int measureFrom, void *filters);
};

extern TerrainLogic *TheTerrainLogic;
extern GameLogicFrameView *TheGameLogic;
extern PartitionManager *ThePartitionManager;
extern "C" unsigned char bfmeRetailCritterDesyncFlag;
extern "C" void *bfmeRetailCritterDesyncSink;
extern "C" void __cdecl Gen0003A17A(void *sink, const char *format, ...);
extern int __cdecl GetGameLogicRandomValue(int low, int high, char *file, int line);
extern float __cdecl Sin(float radians);
extern float __cdecl Cos(float radians);

// The retail periodic search owns two stack filters.  Keeping their lifetime
// explicit preserves the function's EH frame while the filter predicates are
// reconstructed.
class AnimalPeriodicFilter
{
public:
	AnimalPeriodicFilter(int a, int b, int c, int d, int e);
	~AnimalPeriodicFilter();
private:
	unsigned char m_body[0x2c];
};

class AnimalEmitterFilter
{
public:
	AnimalEmitterFilter(void *moduleName, int key, int value);
	~AnimalEmitterFilter();
private:
	unsigned char m_body[0x24];
};

extern void *TheNameKeyGenerator;

static const char *const kAnimalSource =
	"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\AnimalAIUpdate.cpp";

static __forceinline AnimalAIUpdateModuleDataView *animalData(AnimalAIUpdate *self)
{
	return *(AnimalAIUpdateModuleDataView **)((char *)self - 0x0c);
}

static __forceinline Object *animalObject(AnimalAIUpdate *self)
{
	return *(Object **)((char *)self - 8);
}

static __forceinline Coord3D *animalPosition(Object *object)
{
	return (Coord3D *)((char *)object + 0x38);
}

static __forceinline ObjectID animalID(Object *object)
{
	return *(ObjectID *)((char *)object + 0x74);
}

static __forceinline const char *animalDebugName(Object *object)
{
	AnimalTemplateView *record = *(AnimalTemplateView **)((char *)object + 4);
	if (record != 0 && *(void **)((char *)record + 4) != 0)
		record = record->friend_getFinalOverride();
	if (record == 0)
		return "";
	char *text = *(char **)((char *)record + 0x20);
	return text ? text + 8 : "";
}

static __forceinline Coord3D *originalPosition(AnimalAIUpdate *self)
{
	return (Coord3D *)((char *)self + 0x338);
}

static __forceinline ObjectID &scaringObjectID(AnimalAIUpdate *self)
{
	return *(ObjectID *)((char *)self + 0x334);
}

static __forceinline unsigned char &processedOne(AnimalAIUpdate *self)
{
	return *(unsigned char *)((char *)self + 0x344);
}

static __forceinline unsigned char &returning(AnimalAIUpdate *self)
{
	return *(unsigned char *)((char *)self + 0x345);
}

static __forceinline void animalLog(const char *text)
{
	if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
		Gen0003A17A(bfmeRetailCritterDesyncSink, text);
}

UpdateSleepTime AnimalAIUpdate::update()
{
	AnimalAIUpdate *self = this;
	AnimalAIUpdateModuleDataView *data = animalData(self);
	char *machine = *(char **)((char *)self + 0x20);
	char *state = *(char **)(machine + 0x1c);
	int stateID = state ? *(int *)(state + 4) : 999999;
	Object *animal = animalObject(self);

	((AIUpdateInterface *)self)->AIUpdateInterface::update();

	if (!processedOne(self))
	{
		*originalPosition(self) = *animalPosition(animal);
		if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
			Gen0003A17A(bfmeRetailCritterDesyncSink,
				"CritterDesync:  m_processedOne false - setting m_originalPos to %g,%g,%g",
				originalPosition(self)->x, originalPosition(self)->y,
				originalPosition(self)->z);
		processedOne(self) = 1;
	}

	Coord3D *position = animalPosition(animal);
	if (TheTerrainLogic->getLayerForDestination(animal, position) > 1)
	{
		if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
			Gen0003A17A(bfmeRetailCritterDesyncSink,
				"CritterDesync:  animal %s is in a bad area, return to origin %g,%g,%g.",
				animalDebugName(animal), originalPosition(self)->x, originalPosition(self)->y,
				originalPosition(self)->z);
		((AIUpdateInterface *)self)->aiIdle(CMD_FROM_AI);
		((AIUpdateInterface *)self)->aiMoveToPosition(originalPosition(self), CMD_FROM_AI);
		returning(self) = 1;
		return UPDATE_SLEEP_NONE;
	}

	if (returning(self))
	{
		if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
			Gen0003A17A(bfmeRetailCritterDesyncSink,
				"CritterDesync:  m_returning is true - animal %s is checking if we are near origin %g,%g,%g to stop.",
				animalDebugName(animal), originalPosition(self)->x, originalPosition(self)->y,
				originalPosition(self)->z);

		float dx = originalPosition(self)->x - position->x;
		float dy = originalPosition(self)->y - position->y;
		if (dx < 0.0f) dx = -dx;
		if (dy < 0.0f) dy = -dy;
		float minPart;
		float maxPart;
		if (dx < dy)
		{
			minPart = dx;
			maxPart = dy;
		}
		else
		{
			minPart = dy;
			maxPart = dx;
		}
		if (maxPart + minPart * 0.41421357f <= 10.0f)
		{
			if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
				Gen0003A17A(bfmeRetailCritterDesyncSink,
					"CritterDesync:  animal %s is finished returning to origin.",
					animalDebugName(animal));
			returning(self) = 0;
		}
		else
		{
			if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
				Gen0003A17A(bfmeRetailCritterDesyncSink,
					"CritterDesync:  animal %s is NOT finished returning to origin.",
					animalDebugName(animal));
			return UPDATE_SLEEP_NONE;
		}
	}

	if (TheGameLogic->m_frame % data->m_updateTimer == 0)
	{
		if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
			Gen0003A17A(bfmeRetailCritterDesyncSink,
				"CritterDesync:  animal %s is doing periodic search for enemies.",
				animalDebugName(animal));
		Object *enemy;
		{
			AnimalPeriodicFilter enemyFilter(0, 8, 9, 10, 11);
			enemy = ThePartitionManager->getClosestObject(position,
				(float)data->m_fleeRange, 0, &enemyFilter);
		}
		if (enemy && !(*(unsigned int *)((char *)enemy + 0x344) & 1))
		{
			ObjectID enemyID = animalID(enemy);
			if (enemyID == scaringObjectID(self) &&
				(stateID == 20 || stateID == 19))
			{
				if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
					Gen0003A17A(bfmeRetailCritterDesyncSink,
						"CritterDesync:  animal %s(%d) sees SAME enemy %s(%d) to be scared of.",
						animalDebugName(animal), animalID(animal), animalDebugName(enemy), enemyID);
				return UPDATE_SLEEP_NONE;
			}

			if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
				Gen0003A17A(bfmeRetailCritterDesyncSink,
					"CritterDesync:  animal %s(%d) found NEW enemy %s(%d) to be scared of RUNAWAYPANIC.",
					animalDebugName(animal), animalID(animal), animalDebugName(enemy), enemyID);
			*(float *)((char *)animal + 0x18c) = (float)data->m_fleeDistance;
			Object *goal = TheGameLogic->findObjectByID(enemyID);
			((AIUpdateInterface *)self)->aiMoveToPosition(animalPosition(goal), CMD_FROM_AI);
			scaringObjectID(self) = enemyID;
			if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
				Gen0003A17A(bfmeRetailCritterDesyncSink,
					"CritterDesync:  animal %s(%d) blah-1",
					animalDebugName(animal), animalID(animal));
			return UPDATE_SLEEP_NONE;
		}

		if (stateID != 0)
		{
			if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
				Gen0003A17A(bfmeRetailCritterDesyncSink,
					"CritterDesync:  animal %s(%d) is not idle, sleep.",
					animalDebugName(animal), animalID(animal));
			return UPDATE_SLEEP_NONE;
		}
		scaringObjectID(self) = 0;
		if (GetGameLogicRandomValue(0, 100, (char *)kAnimalSource, 0x98)
			< data->m_wanderPercentage)
		{
			if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
				Gen0003A17A(bfmeRetailCritterDesyncSink,
					"CritterDesync:  animal %s(%d) dice roll suceeded for wanderpercentage",
					animalDebugName(animal), animalID(animal));
			AnimalEmitterFilter emitterFilter(TheNameKeyGenerator, 0x91, 0);
			Object *emitter = ThePartitionManager->getClosestObject(position,
				(float)data->m_fleeRange, 1, &emitterFilter);
			if (emitter)
			{
				if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
					Gen0003A17A(bfmeRetailCritterDesyncSink,
						"CritterDesync:  animal %s(%d) EMITTER CASE",
						animalDebugName(animal), animalID(animal));
				float radius = (float)data->m_maxWanderRadius;
				if (animal->distanceSquaredTo(emitter) <= radius * radius)
				{
					if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
						Gen0003A17A(bfmeRetailCritterDesyncSink,
							"CritterDesync:  animal %s(%d) moving to emitter at %g,%g,%g",
							animalDebugName(animal), animalID(animal),
							animalPosition(emitter)->x, animalPosition(emitter)->y,
							animalPosition(emitter)->z);
					((AIUpdateInterface *)self)->aiMoveToPosition(animalPosition(emitter), CMD_FROM_AI);
				}
				else
				{
					if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
						Gen0003A17A(bfmeRetailCritterDesyncSink,
							"CritterDesync:  animal %s(%d) wander to random location",
							animalDebugName(animal), animalID(animal));
					Coord3D destination = *animal->getUnitDirectionVector2D();
					int angle = GetGameLogicRandomValue(-15, 15, (char *)kAnimalSource, 0xba);
					float distance = (float)GetGameLogicRandomValue(0,
						data->m_maxWanderDistance, (char *)kAnimalSource, 0xbd);
					destination.x = position->x + Cos((float)angle) * distance;
					destination.y = position->y + Sin((float)angle) * distance;
					if (((AnimalAIUpdateDestinationLayer *)((char *)self - 0x10))->isReachableLayer(&destination))
					{
						if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
							Gen0003A17A(bfmeRetailCritterDesyncSink,
								"CritterDesync:  animal %s(%d) wandering to dest %g,%g,%g",
								animalDebugName(animal), animalID(animal),
								destination.x, destination.y, destination.z);
						((AIUpdateInterface *)self)->aiMoveToPosition(&destination, CMD_FROM_AI);
					}
					else
					{
						if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
							Gen0003A17A(bfmeRetailCritterDesyncSink,
								"CritterDesync:  animal %s(%d) CANNOT wander to dest %g,%g,%g",
								animalDebugName(animal), animalID(animal),
								destination.x, destination.y, destination.z);
					}
				}
			}
			else
			{
				if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
					Gen0003A17A(bfmeRetailCritterDesyncSink,
						"CritterDesync:  animal %s(%d) NO EMITTER CASE",
						animalDebugName(animal), animalID(animal));
				float dx = originalPosition(self)->x - position->x;
				float dy = originalPosition(self)->y - position->y;
				float dz = originalPosition(self)->z - position->z;
				float range2 = dx * dx + dy * dy + dz * dz;
				float radius = (float)data->m_maxWanderRadius;
				if (range2 > radius * radius)
				{
					if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
						Gen0003A17A(bfmeRetailCritterDesyncSink,
							"CritterDesync:  animal %s(%d) returning to m_originalPos %g,%g,%g",
							animalDebugName(animal), animalID(animal),
							originalPosition(self)->x, originalPosition(self)->y,
							originalPosition(self)->z);
					((AIUpdateInterface *)self)->aiMoveToPosition(originalPosition(self), CMD_FROM_AI);
				}
				else
				{
					if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
						Gen0003A17A(bfmeRetailCritterDesyncSink,
							"CritterDesync:  animal %s(%d) wandering to random spot",
							animalDebugName(animal), animalID(animal));
					Coord3D destination = *animal->getUnitDirectionVector2D();
					int angle = GetGameLogicRandomValue(-15, 15, (char *)kAnimalSource, 0xf2);
					float distance = (float)GetGameLogicRandomValue(0,
						data->m_maxWanderDistance, (char *)kAnimalSource, 0xf5);
					destination.x = position->x + Cos((float)angle) * distance;
					destination.y = position->y + Sin((float)angle) * distance;
					if (((AnimalAIUpdateDestinationLayer *)((char *)self - 0x10))->isReachableLayer(&destination))
					{
						if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
							Gen0003A17A(bfmeRetailCritterDesyncSink,
								"CritterDesync:  animal %s(%d) wandering to %g,%g,%g",
								animalDebugName(animal), animalID(animal),
								destination.x, destination.y, destination.z);
						((AIUpdateInterface *)self)->aiMoveToPosition(&destination, CMD_FROM_AI);
					}
					else
					{
						if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
							Gen0003A17A(bfmeRetailCritterDesyncSink,
								"CritterDesync:  animal %s(%d) CANNOT wander to %g,%g,%g",
								animalDebugName(animal), animalID(animal),
								destination.x, destination.y, destination.z);
					}
				}
			}
		}
		else
		{
			if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
				Gen0003A17A(bfmeRetailCritterDesyncSink,
					"CritterDesync:  animal %s(%d) dice roll failed.",
					animalDebugName(animal), animalID(animal));
		}
	}

	if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
		Gen0003A17A(bfmeRetailCritterDesyncSink,
			"CritterDesync:  animal %s(%d) finished update.", animalDebugName(animal), animalID(animal));

	return UPDATE_SLEEP_NONE;
}
