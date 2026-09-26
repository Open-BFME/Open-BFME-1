// ?update@AnimalAIUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.3344272076372315 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
#include "coord3d.h"
#include "string_base.h"
template<>inline const char*StringBase<char>::str()const{return m_data?m_data->data:"";}
#include "ascii_string.h"
#include <math.h>
inline Coord3D::Coord3D(){}
inline Coord3D::Coord3D(const Coord3D&t){x=t.x;y=t.y;z=t.z;}
inline Coord3D::~Coord3D(){}
inline Coord3DBase&Coord3DBase::operator=(const Coord3DBase&t){struct Raw{unsigned x,y,z;};*(Raw*)this=*(const Raw*)&t;return *this;}
inline Coord3D&Coord3D::operator=(const Coord3D&t){Coord3DBase*b=this;*b=t;return *this;}
__forceinline Coord3D&Coord3D::Scale(float n){x*=n;y*=n;z*=n;return *this;}
inline float Coord3D::GetLengthEstimate2D()const{float ax=(float)fabs(x),ay=(float)fabs(y);if(ax>ay)return ax+0.41421357f*ay;return ay+0.41421357f*ax;}

// BFME-only AnimalAIUpdate::update.  There is no Zero Hour twin; the owning
// secondary update-interface slot is installed by the independently named
// constructor: primary object +0x10, vtable VA 0x010C5590, slot 0.
// Bank only: unresolved frame/register scheduling remains. See the adjacent
// identity_evidence/002B32A0-animal-update.md receipt before resuming.

typedef unsigned int ObjectID;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class Overridable{public:virtual ~Overridable();const Overridable*getFinalOverride()const;Overridable*m_nextOverride;};
class ThingTemplate:public Overridable{public:char m_08[0x18];AsciiString m_name;const AsciiString&getName()const{return m_name;}};
class Thing{public:virtual ~Thing();const ThingTemplate*m_template;const ThingTemplate*getTemplate()const{const ThingTemplate*t=m_template;if(!t)return 0;if(t->m_nextOverride)t=(const ThingTemplate*)t->m_nextOverride->getFinalOverride();return t;}const Coord3D*getUnitDirectionVector2D()const;};
class Object:public Thing{};
class BfmeSpotCN;class Gen_0016E370{public:float bfmeDistanceSquared(const BfmeSpotCN*)const;};
class AICommandInterface{public:void aiIdle(CommandSourceType);void aiMoveToPosition(const Coord3D*,CommandSourceType);void aiBfmeCommand2E(Object*,CommandSourceType);};
template<int N>class RvaAnimalSlots:public RvaAnimalSlots<N-1>{public:virtual void slot(char(*)[N]);};template<>class RvaAnimalSlots<0>{};
class RvaAnimalPrimary:public RvaAnimalSlots<127>{public:virtual void rva1fc(int);};
class AIUpdateInterface
{
public:
	virtual UpdateSleepTime update();
	unsigned getCurrentStateID()const;
	void aiIdle(CommandSourceType source);
	void aiMoveToPosition(const Coord3D *position, CommandSourceType source);
};

class AnimalAIUpdateDestinationLayer
{
public:
	bool isReachableLayer(const Coord3D *position) const;
	char m_00[8];Object*m_object;
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

class GameLogic
{
public:
	unsigned char m_beforeFrame[0x3c];
	unsigned int m_frame;
	Object *findObjectByID(int id);
};

class PartitionFilter;
class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, float range,
		int measureFrom, PartitionFilter *filters);
};

extern TerrainLogic *TheTerrainLogic;
extern GameLogic *TheGameLogic;
extern PartitionManager *ThePartitionManager;
extern "C" unsigned char bfmeRetailCritterDesyncFlag;extern bool g_012F0239;
class CRCParameterCheck{public:void __cdecl rva00065C80(const char*,...);};
extern CRCParameterCheck *bfmeRetailCritterDesyncSink;
extern int __cdecl GetGameLogicRandomValue(int low, int high, char *file, int line);
extern float __cdecl Sin(float radians);
extern float __cdecl Cos(float radians);

template<int N>class BitFlags{public:enum BogusInitType{kInit=0};BitFlags(BogusInitType,int);BitFlags(BogusInitType,int,int,int,int);unsigned m_bits[(N+31)/32];};

extern "C" void*__cdecl memset(void*,int,unsigned);
template<int N> __declspec(noinline) BitFlags<N>::BitFlags(BogusInitType,int a){memset(m_bits,0,sizeof(m_bits));m_bits[(unsigned)a>>5]|=1u<<((unsigned)a&31);}
template<int N> __declspec(noinline) BitFlags<N>::BitFlags(BogusInitType,int a,int b,int c,int d){memset(m_bits,0,sizeof(m_bits));m_bits[(unsigned)a>>5]|=1u<<((unsigned)a&31);m_bits[(unsigned)b>>5]|=1u<<((unsigned)b&31);m_bits[(unsigned)c>>5]|=1u<<((unsigned)c&31);m_bits[(unsigned)d>>5]|=1u<<((unsigned)d&31);}
typedef BitFlags<192> KindOfMaskType;extern const KindOfMaskType KINDOFMASK_NONE;
class PartitionFilter{public:PartitionFilter():m_next(0){}virtual ~PartitionFilter(){}virtual bool allow(Object*)=0;virtual int getPlayerMask();PartitionFilter*link(PartitionFilter*);PartitionFilter*m_next;};
class Rva0025F2D0KindOfAnyFilter:public PartitionFilter{public:__forceinline Rva0025F2D0KindOfAnyFilter(const KindOfMaskType&m):m_mask(m){}virtual ~Rva0025F2D0KindOfAnyFilter(){}virtual bool allow(Object*);KindOfMaskType m_mask;};
class PartitionFilterRelationship:public PartitionFilter{public:PartitionFilterRelationship(Object*o,int f,bool b):m_object(o),m_flags(f),m_match(b){}virtual ~PartitionFilterRelationship(){}virtual bool allow(Object*);virtual int getPlayerMask();Object*m_object;int m_flags;bool m_match;};
class PartitionFilterAcceptByKindOf:public PartitionFilter{public:PartitionFilterAcceptByKindOf(const KindOfMaskType&,const KindOfMaskType&);virtual ~PartitionFilterAcceptByKindOf(){}virtual bool allow(Object*);KindOfMaskType m_mustBeSet,m_mustBeClear;};

inline bool AnimalAIUpdateDestinationLayer::isReachableLayer(const Coord3D*p)const{if(!p)return false;return TheTerrainLogic->getLayerForDestination(m_object,p)<=1;}
static const char *const kAnimalSource =
	"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\AnimalAIUpdate.cpp";

static __forceinline const AnimalAIUpdateModuleDataView *animalData(AnimalAIUpdate *self)
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

static __forceinline const char *animalDebugName(Object*object){return object->getTemplate()->getName().str();}
static __forceinline AICommandInterface*animalCommands(AnimalAIUpdate*self){return (AICommandInterface*)((char*)self+0x10);}
static __forceinline RvaAnimalPrimary*animalPrimary(AnimalAIUpdate*self){return (RvaAnimalPrimary*)((char*)self-0x10);}
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
		bfmeRetailCritterDesyncSink->rva00065C80( text);
}

UpdateSleepTime AnimalAIUpdate::update()
{
	AnimalAIUpdate *self = this;
	CRCParameterCheck*log;
	const AnimalAIUpdateModuleDataView *data = animalData(self);
	char *machine = *(char **)((char *)self + 0x20);
	char *state = *(char **)(machine + 0x1c);
	int stateID = state ? *(int *)(state + 4) : 999999;
	Object *animal = animalObject(self);

	((AIUpdateInterface *)self)->AIUpdateInterface::update();

	if (!processedOne(self))
	{
		*originalPosition(self) = *animalPosition(animal);
		if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
			log->rva00065C80(
				"CritterDesync:  m_processedOne false - setting m_originalPos to %g,%g,%g",
				originalPosition(self)->x, originalPosition(self)->y,
				originalPosition(self)->z);
		processedOne(self) = 1;
	}

	Coord3D *position = animalPosition(animal);
	if (!((AnimalAIUpdateDestinationLayer*)((char*)self-0x10))->isReachableLayer(position))
	{
		if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
			log->rva00065C80(
				"CritterDesync:  animal %s is in a bad area, return to origin %g,%g,%g.",
				animal->getTemplate()->getName().str(), originalPosition(self)->x, originalPosition(self)->y,
				originalPosition(self)->z);
		animalCommands(self)->aiIdle(CMD_FROM_AI);
		animalCommands(self)->aiMoveToPosition(originalPosition(self), CMD_FROM_AI);
		animalPrimary(self)->rva1fc(0);
		returning(self) = 1;
		return UPDATE_SLEEP_NONE;
	}

	if (returning(self))
	{
		if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
			log->rva00065C80(
				"CritterDesync:  m_returning is true - animal %s is checking if we are near origin %g,%g,%g to stop.",
				animal->getTemplate()->getName().str(), originalPosition(self)->x, originalPosition(self)->y,
				originalPosition(self)->z);

		Coord3D delta=*originalPosition(self);delta.x-=position->x;delta.y-=position->y;
		if(delta.GetLengthEstimate2D() < 10.0f)
		{
			if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
				log->rva00065C80(
					"CritterDesync:  animal %s is finished returning to origin.",
					animal->getTemplate()->getName().str());
			returning(self) = 0;
		}
		else
		{
			if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
				log->rva00065C80(
					"CritterDesync:  animal %s is NOT finished returning to origin.",
					animal->getTemplate()->getName().str());
			return UPDATE_SLEEP_NONE;
		}
	}

	if (TheGameLogic->m_frame % data->m_updateTimer == 0)
	{
		if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
			log->rva00065C80(
				"CritterDesync:  animal %s is doing periodic search for enemies.",
				animal->getTemplate()->getName().str());
		Object *enemy;
		{
			Rva0025F2D0KindOfAnyFilter kindFilter(KindOfMaskType(KindOfMaskType::kInit, 8, 9, 10, 11));
			PartitionFilterRelationship enemyFilter(animal,3,false);
			enemy = ThePartitionManager->getClosestObject(animalPosition(animal),
				(float)data->m_fleeRange, 0, enemyFilter.link(&kindFilter));
		}
		if (enemy && !(*(unsigned int *)((char *)enemy + 0x344) & 1))
		{
			ObjectID enemyID = animalID(enemy);
			if (enemyID == scaringObjectID(self) &&
				(((const AIUpdateInterface*)((char*)self-0x10))->getCurrentStateID() == 20 || ((const AIUpdateInterface*)((char*)self-0x10))->getCurrentStateID() == 19))
			{
				if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
					log->rva00065C80(
						"CritterDesync:  animal %s(%d) sees SAME enemy %s(%d) to be scared of.",
						animal->getTemplate()->getName().str(), animalID(animal), enemy->getTemplate()->getName().str(), enemyID);
				return UPDATE_SLEEP_NONE;
			}

			if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
				log->rva00065C80(
					"CritterDesync:  animal %s(%d) found NEW enemy %s(%d) to be scared of RUNAWAYPANIC.",
					animal->getTemplate()->getName().str(), animalID(animal), enemy->getTemplate()->getName().str(), enemyID);
			*(float *)((char *)animal + 0x18c) = (float)data->m_fleeDistance;
			Object *goal = TheGameLogic->findObjectByID(enemyID);
			animalCommands(self)->aiBfmeCommand2E(goal, (CommandSourceType)1);
			scaringObjectID(self) = enemyID;
			if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
				log->rva00065C80(
					"CritterDesync:  animal %s(%d) blah-1",
					animal->getTemplate()->getName().str(), animalID(animal));
			return UPDATE_SLEEP_NONE;
		}

	}

		if (stateID != 0)
		{
			if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
				log->rva00065C80(
					"CritterDesync:  animal %s(%d) is not idle, sleep.",
					animal->getTemplate()->getName().str(), animalID(animal));
			return UPDATE_SLEEP_NONE;
		}
		scaringObjectID(self) = 0;
		if (GetGameLogicRandomValue(0, 100, (char *)kAnimalSource, 0x98)
			< data->m_wanderPercentage)
		{
			if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
				log->rva00065C80(
					"CritterDesync:  animal %s(%d) dice roll suceeded for wanderpercentage",
					animal->getTemplate()->getName().str(), animalID(animal));
			Object*emitter;{PartitionFilterAcceptByKindOf emitterFilter(KindOfMaskType(KindOfMaskType::kInit,0x91),KINDOFMASK_NONE);
			emitter = ThePartitionManager->getClosestObject(animalPosition(animal),
				(float)data->m_fleeRange, 1, &emitterFilter);}
			animalPrimary(self)->rva1fc(0);
			if (emitter)
			{
				if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
					log->rva00065C80(
						"CritterDesync:  animal %s(%d) EMITTER CASE",
						animal->getTemplate()->getName().str(), animalID(animal));
				int radius = data->m_maxWanderRadius;
				if (((const Gen_0016E370*)animal)->bfmeDistanceSquared((const BfmeSpotCN*)emitter) > (float)(radius * radius))
				{
					if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
						log->rva00065C80(
							"CritterDesync:  animal %s(%d) moving to emitter at %g,%g,%g",
							animal->getTemplate()->getName().str(), animalID(animal),
							animalPosition(emitter)->x, animalPosition(emitter)->y,
							animalPosition(emitter)->z);
					animalCommands(self)->aiMoveToPosition(animalPosition(emitter), CMD_FROM_AI);
				}
				else
				{
					if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
						log->rva00065C80(
							"CritterDesync:  animal %s(%d) wander to random location",
							animal->getTemplate()->getName().str(), animalID(animal));
					animal->getUnitDirectionVector2D();
					Coord3D destination = *animal->getUnitDirectionVector2D();
					float angle = (float)GetGameLogicRandomValue(-15, 15, (char *)kAnimalSource, 0xba);
					destination.x += Cos(angle);destination.y += Sin(angle);
					float distance = (float)GetGameLogicRandomValue(0,
						data->m_maxWanderDistance, (char *)kAnimalSource, 0xbd);
					destination.Scale(distance);
					destination.x += position->x;destination.y += position->y;
					if (((AnimalAIUpdateDestinationLayer *)((char *)self - 0x10))->isReachableLayer(&destination))
					{
						if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
							log->rva00065C80(
								"CritterDesync:  animal %s(%d) wandering to dest %g,%g,%g",
								animal->getTemplate()->getName().str(), animalID(animal),
								destination.x, destination.y, destination.z);
						g_012F0239=true;animalCommands(self)->aiMoveToPosition(&destination, CMD_FROM_AI);g_012F0239=false;
					}
					else
					{
						if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
							log->rva00065C80(
								"CritterDesync:  animal %s(%d) CANNOT wander to dest %g,%g,%g",
								animal->getTemplate()->getName().str(), animalID(animal),
								destination.x, destination.y, destination.z);
					}
				}
			}
			else
			{
				if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
					log->rva00065C80(
						"CritterDesync:  animal %s(%d) NO EMITTER CASE",
						animal->getTemplate()->getName().str(), animalID(animal));
				Coord3D delta=*originalPosition(self);delta.x-=position->x;delta.y-=position->y;delta.z-=position->z;
				if(delta.GetLengthEstimate() > (float)data->m_maxWanderRadius)
				{
					if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
						log->rva00065C80(
							"CritterDesync:  animal %s(%d) returning to m_originalPos %g,%g,%g",
							animal->getTemplate()->getName().str(), animalID(animal),
							originalPosition(self)->x, originalPosition(self)->y,
							originalPosition(self)->z);
					animalCommands(self)->aiMoveToPosition(originalPosition(self), CMD_FROM_AI);
				}
				else
				{
					if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
						log->rva00065C80(
							"CritterDesync:  animal %s(%d) wandering to random spot",
							animal->getTemplate()->getName().str(), animalID(animal));
					animal->getUnitDirectionVector2D();
					Coord3D destination = *animal->getUnitDirectionVector2D();
					float angle = (float)GetGameLogicRandomValue(-15, 15, (char *)kAnimalSource, 0xf2);
					destination.x += Cos(angle);destination.y += Sin(angle);
					float distance = (float)GetGameLogicRandomValue(0,
						data->m_maxWanderDistance, (char *)kAnimalSource, 0xf5);
					destination.Scale(distance);
					destination.x += position->x;destination.y += position->y;
					if (((AnimalAIUpdateDestinationLayer *)((char *)self - 0x10))->isReachableLayer(&destination))
					{
						if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
							log->rva00065C80(
								"CritterDesync:  animal %s(%d) wandering to %g,%g,%g",
								animal->getTemplate()->getName().str(), animalID(animal),
								destination.x, destination.y, destination.z);
						animalCommands(self)->aiMoveToPosition(&destination, CMD_FROM_AI);
					}
					else
					{
						if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
							log->rva00065C80(
								"CritterDesync:  animal %s(%d) CANNOT wander to %g,%g,%g",
								animal->getTemplate()->getName().str(), animalID(animal),
								destination.x, destination.y, destination.z);
					}
				}
			}
		}
		else
		{
			if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
				log->rva00065C80(
					"CritterDesync:  animal %s(%d) dice roll failed.",
					animal->getTemplate()->getName().str(), animalID(animal));
		}

	if (bfmeRetailCritterDesyncFlag && (log=bfmeRetailCritterDesyncSink))
		log->rva00065C80(
			"CritterDesync:  animal %s(%d) finished update.", animal->getTemplate()->getName().str(), animalID(animal));

	return UPDATE_SLEEP_NONE;
}
