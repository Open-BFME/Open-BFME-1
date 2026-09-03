// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /O2 /Ob2
// Retail 0x002D0E40, 148 bytes: QueueProductionExitUpdate::exitObjectByBudding.
// ExitInterface this (module+0x20): object at [this-0x18], moduleData at
// [this-0x1C]. m_currentDelay at +4, m_currentBurstCount at +0x1C.
// md->m_exitDelayData at md+0x20. Object pos +0x38, orient +0x44, AI +0x204.
// AICommandInterface at AI+0x20. ExitInterface vtable slot after
// unreserveDoorForExit. ret 8.
// Identity: call order is getLayer / setPosition / setOrientation / setLayer
// then aiMoveToPosition; same ZH budding sequence as the landed Queue siblings.

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
	Coord3D m_pos;
	float m_orientation;

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
	AICommandInterface m_command;
};

class Object : public Thing
{
public:
	unsigned char m_padObj[0x204 - 0x48];
	AIUpdateInterface *m_ai;

	int getLayer() const;
	void setPosition(const Coord3D *pos);
	void setLayer(PathfindLayerEnum layer);
};

class QueueProductionExitUpdateModuleData
{
public:
	unsigned char m_pad[0x20];
	unsigned m_exitDelayData;
};

class QueueProductionExitUpdate
{
public:
	virtual void exitObjectByBudding(Object *newObj, Object *budHost);

	unsigned m_currentDelay;
	Coord3D m_rallyPoint;
	bool m_rallyPointExists;
	float m_creationClearDistance;
	unsigned m_currentBurstCount;
};

void QueueProductionExitUpdate::exitObjectByBudding(Object *newObj, Object *budHost)
{
	if (budHost)
	{
		float newAngle = budHost->m_orientation;
		int newLayer = budHost->getLayer();
		newObj->setPosition(&budHost->m_pos);
		newObj->setOrientation(newAngle);
		newObj->setLayer((PathfindLayerEnum)newLayer);
	}
	else
	{
		newObj->setPosition(&(*reinterpret_cast<Object **>(
			reinterpret_cast<char *>(this) - 0x18))->m_pos);
		newObj->setOrientation((*reinterpret_cast<Object **>(
			reinterpret_cast<char *>(this) - 0x18))->m_orientation);
	}

	AIUpdateInterface *ai = newObj->m_ai;
	if (ai)
		ai->m_command.aiMoveToPosition(&newObj->m_pos, CMD_FROM_AI);

	const QueueProductionExitUpdateModuleData *data =
		*reinterpret_cast<const QueueProductionExitUpdateModuleData *const *>(
			reinterpret_cast<char *>(this) - 0x1C);
	m_currentDelay = data->m_exitDelayData;
	if (m_currentBurstCount)
		m_currentBurstCount--;
}
