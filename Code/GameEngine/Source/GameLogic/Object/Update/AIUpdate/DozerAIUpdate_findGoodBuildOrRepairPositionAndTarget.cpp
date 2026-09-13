// cl: /DNDEBUG /DWIN32 /MD /EHs-c-
// TU-local BFME ABI slice for the bridge-repair target helper.

typedef unsigned int UnsignedInt;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled08[0xc0];
	UnsignedInt m_kindOf[3];
};

class AIUpdateInterface
{
public:
	bool isPathAvailable(const Coord3D *destination) const;
};

class Object
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_unmodelled08[0x30];
	Coord3D m_position;
	unsigned char m_unmodelled44[0x1c0];
	AIUpdateInterface *m_ai;
};

enum BridgeTowerType
{
	BRIDGE_TOWER_0 = 0,
	BRIDGE_TOWER_1,
	BRIDGE_TOWER_2,
	BRIDGE_TOWER_3
};

class BridgeBehaviorInterface
{
public:
	virtual int anchor00(BridgeTowerType) = 0;
	virtual int getTowerID(BridgeTowerType) = 0;
};

class BridgeBehavior
{
public:
	static BridgeBehaviorInterface *getBridgeBehaviorInterfaceFromObject(Object *object);
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheBfmeGameLogic;

class Rva002B8890DozerAIUpdate
{
public:
	bool findGoodBuildOrRepairPosition(const Object *me, const Object *target, Coord3D &positionOut);

	// The receiver is the BFME context carried in ECX although the retail
	// spelling of the public helper is the static DozerAIUpdate name.
	Object *findGoodBuildOrRepairPositionAndTarget(Object *me, Object *target,
		Coord3D &positionOut);
};

#pragma comment(linker, "/alternatename:?findGoodBuildOrRepairPosition@Rva002B8890DozerAIUpdate@@QAE_NPBVObject@@0AAUCoord3D@@@Z=?findGoodBuildOrRepairPosition@DozerAIUpdate@@SA_NPBVObject@@0AAUCoord3D@@@Z")

// ?findGoodBuildOrRepairPositionAndTarget@DozerAIUpdate@@SAPAVObject@@PAV2@0AAUCoord3D@@@Z
Object *Rva002B8890DozerAIUpdate::findGoodBuildOrRepairPositionAndTarget(
	Object *me, Object *target, Coord3D &positionOut)
{
	ThingTemplate *thingTemplate = target->m_template;
	if (thingTemplate != 0 && thingTemplate->m_nextOverride != 0)
		thingTemplate = (ThingTemplate *)thingTemplate->m_nextOverride->getFinalOverride();
	if ((thingTemplate->m_kindOf[0] & 0x400000) != 0)
		{
			BridgeBehaviorInterface *bbi = BridgeBehavior::getBridgeBehaviorInterfaceFromObject(target);
			if (bbi)
			{
				AIUpdateInterface *ai = me->m_ai;
				float bestDistSqr = 1e10f;
				Object *bestTower = 0;
				for (int i = 0; i < 4; ++i)
				{
					Object *tower = TheBfmeGameLogic->findObjectByID(bbi->getTowerID((BridgeTowerType)i));
					if (tower)
					{
						Coord3D tmp;
						bool found = findGoodBuildOrRepairPosition(me, tower, tmp);
						if (found && ai->isPathAvailable(&tmp))
						{
						float thisDistSqr = (me->m_position.y - tmp.y) * (me->m_position.y - tmp.y)
							+ (me->m_position.x - tmp.x) * (me->m_position.x - tmp.x);
							if (thisDistSqr < bestDistSqr)
							{
								positionOut = tmp;
								bestDistSqr = thisDistSqr;
								bestTower = tower;
							}
						}
					}
				}
				if (bestTower)
					return bestTower;
				return 0;
			}
	}

	findGoodBuildOrRepairPosition(me, target, positionOut);
	return target;
}
