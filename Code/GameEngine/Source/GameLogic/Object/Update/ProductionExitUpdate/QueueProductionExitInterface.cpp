// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /O2 /Ob2
//
// Open-BFME: three of QueueProductionExitUpdate's ExitInterface slots.
//
//   ?isExitBusy@           0x002D04B0,   3 bytes, slot 0
//   ?unreserveDoorForExit@ 0x002D04E0,   3 bytes, slot 1
//   ?exitObjectByBudding@  0x002D0E40, 148 bytes, slot 2
//
// All three are entered through the ExitInterface subobject at module+0x20, not
// through the module itself, and that is the single fact three separate files
// each had to work around privately. `this` points at the interface, so the
// module's own fields are BEHIND it: the object is at [this-0x18] and the module
// data at [this-0x1C]. exitObjectByBudding reaches both with raw casts, and the
// two stubs never needed to know -- which is exactly why nothing in either of
// them said so.
//
// Declared together, the slot numbers stop being prose. Each file recorded its
// own ("ExitInterface vtable slot 0", "slot 4", "the slot after
// unreserveDoorForExit"), which is three ways of saying the ordering that the
// declaration order below now enforces, and the second of those was written in
// bytes where the other two were written in indices.
//
// The module's fields also only appear once here: the delay at +0x04 -- the
// first word past the vptr -- the rally point at +0x08, its flag at +0x14, the
// clearance distance at +0x18 and the burst count at +0x1C. Only
// exitObjectByBudding reads any of them.

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 0
};

enum ExitDoorType
{
	DOOR_1 = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class Thing
{
public:
	unsigned char m_pad[0x38];
	Coord3D m_cachedPos;						// +0x38
	float m_cachedAngle;					// +0x44

	void setOrientation(float angle);
};

class AICommandInterface
{
public:
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType source);
};

class AIUpdateInterface
{
public:
	unsigned char m_pad[0x20];
	AICommandInterface m_command;				// AI+0x20
};

class Object : public Thing
{
public:
	unsigned char m_padObj[0x204 - 0x48];
	AIUpdateInterface *m_ai;				// +0x204

	int getLayer() const;
	void setPosition(const Coord3D *pos);
	void setLayer(PathfindLayerEnum layer);
};

class QueueProductionExitUpdateModuleData
{
public:
	unsigned char m_pad[0x20];
	unsigned m_exitDelayData;				// +0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/QueueProductionExitUpdate.h
class QueueProductionExitUpdate
{
public:
	virtual bool isExitBusy() const;			// ExitInterface slot 0
	virtual void unreserveDoorForExit(ExitDoorType exitDoor);	// slot 1
	virtual void exitObjectByBudding(Object *newObj, Object *budHost);	// slot 2

	unsigned m_currentDelay;				// +0x04
	Coord3D m_rallyPoint;					// +0x08
	bool m_rallyPointExists;				// +0x14
	float m_creationClearDistance;				// +0x18
	unsigned m_currentBurstCount;				// +0x1C
};

// ?isExitBusy@QueueProductionExitUpdate@@UBE_NXZ
// Zero Hour returns FALSE inline; retail is the same three bytes.
bool QueueProductionExitUpdate::isExitBusy() const
{
	return false;
}

// ?unreserveDoorForExit@QueueProductionExitUpdate@@UAEXW4ExitDoorType@@@Z
// Zero Hour's empty body; ret 4.
void QueueProductionExitUpdate::unreserveDoorForExit(ExitDoorType)
{
}

// ?exitObjectByBudding@QueueProductionExitUpdate@@UAEXPAVObject@@0@Z
// The Zero Hour budding sequence: getLayer / setPosition / setOrientation /
// setLayer, then aiMoveToPosition. With no bud host it falls back to the
// module's own object at [this-0x18].
void QueueProductionExitUpdate::exitObjectByBudding(Object *newObj, Object *budHost)
{
	if (budHost)
	{
		float newAngle = budHost->m_cachedAngle;
		int newLayer = budHost->getLayer();
		newObj->setPosition(&budHost->m_cachedPos);
		newObj->setOrientation(newAngle);
		newObj->setLayer((PathfindLayerEnum)newLayer);
	}
	else
	{
		newObj->setPosition(&(*reinterpret_cast<Object **>(
			reinterpret_cast<char *>(this) - 0x18))->m_cachedPos);
		newObj->setOrientation((*reinterpret_cast<Object **>(
			reinterpret_cast<char *>(this) - 0x18))->m_cachedAngle);
	}

	AIUpdateInterface *ai = newObj->m_ai;
	if (ai)
		ai->m_command.aiMoveToPosition(&newObj->m_cachedPos, CMD_FROM_AI);

	const QueueProductionExitUpdateModuleData *data =
		*reinterpret_cast<const QueueProductionExitUpdateModuleData *const *>(
			reinterpret_cast<char *>(this) - 0x1C);
	m_currentDelay = data->m_exitDelayData;
	if (m_currentBurstCount)
		m_currentBurstCount--;
}
