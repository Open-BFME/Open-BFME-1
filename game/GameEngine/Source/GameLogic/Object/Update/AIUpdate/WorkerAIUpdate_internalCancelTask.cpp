// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2
// WorkerAIUpdate::internalCancelTask, retail 0x002CA510.

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum DozerTask
{
	DOZER_TASK_INVALID = -1
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiMoveToPosition(const Coord3D *position, CommandSourceType source);
};

class AIUpdateInterface
{
public:
	char m_pad00[0x20];
	AICommandInterface m_command;
};

class Object
{
public:
	char m_pad00[0x204];
	AIUpdateInterface *m_ai;

	AIUpdateInterface *getAIUpdateInterface() const
	{
		return m_ai;
	}

	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(
			reinterpret_cast<const char *>(this) + 0x38);
	}
};

class DozerTaskInterface
{
public:
	virtual void onDelete() = 0;
	virtual float getRepairHealthPerSecond() const = 0;
	virtual float getBoredTime() const = 0;
	virtual float getBoredRange() const = 0;
	virtual Object *construct(void *, const void *, float, void *, bool) = 0;
	virtual DozerTask getMostRecentCommand() = 0;
	virtual bool isTaskPending(DozerTask task) = 0;
	virtual unsigned int getTaskTarget(DozerTask task) = 0;
	virtual bool isAnyTaskPending() = 0;
	virtual DozerTask getCurrentTask() const = 0;
	virtual void setCurrentTask(DozerTask task) = 0;
	virtual bool getIsRebuild() = 0;
	virtual void newTask(DozerTask task, Object *target) = 0;
	virtual void cancelTask(DozerTask task) = 0;
	virtual void internalTaskComplete(DozerTask task) = 0;
	virtual void internalCancelTask(DozerTask task) = 0;
	virtual void internalTaskCompleteOrCancelled(DozerTask task) = 0;
};

struct DozerTaskInfo
{
	unsigned int m_targetObjectID;
	unsigned int m_taskOrderFrame;
};

struct DozerDockPointInfo
{
	unsigned char m_valid;
	unsigned char m_padding[3];
	Coord3D m_location;
};

class WorkerAIUpdate : public DozerTaskInterface
{
public:
	virtual void internalCancelTask(DozerTask task);

	Object *getObject() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const char *>(this) - 0x338);
	}

private:
	char m_pad00[8];
	DozerTaskInfo m_task[3];
	char m_pad24[4];
	DozerDockPointInfo m_dockPoint[3][3];
};

void WorkerAIUpdate::internalCancelTask(DozerTask task)
{
	internalTaskCompleteOrCancelled(task);

	m_task[task].m_targetObjectID = 0;
	m_task[task].m_taskOrderFrame = 0;
	for (int i = 0; i < 3; ++i)
		m_dockPoint[task][i].m_valid = 0;

	Object *object = getObject();
	AIUpdateInterface *ai = object->getAIUpdateInterface();
	if (ai != 0)
		ai->m_command.aiMoveToPosition(object->getPosition(), CMD_FROM_AI);
}
