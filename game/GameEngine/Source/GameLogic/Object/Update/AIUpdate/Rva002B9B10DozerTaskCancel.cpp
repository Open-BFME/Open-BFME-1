// cl: /DNDEBUG /MD /EHsc
// Neutral C++ reconstruction of retail RVA 0x002B9B10 (83 bytes).
//
// Retail proves the Dozer-task ABI here: the callback is virtual slot 16,
// task records begin after the interface vptr, and the three 16-byte dock
// records begin at +0x98.  The enclosing owner and its AI pointer are read
// from the proven BFME object offsets.  No named caller reaches this dump,
// so the translation-unit class remains address-derived until an owner is
// independently established.

struct Coord3D
{
	float x, y, z;
};

enum DozerTask
{
	DOZER_TASK_BUILD = 0,
	DOZER_TASK_REPAIR = 1,
	DOZER_TASK_FORTIFY = 2,
	DOZER_NUM_TASKS = 3
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	unsigned char m_pad[0x20];
	AICommandInterface m_command;
};

class Object
{
public:
	unsigned char m_pad[0x204];
	AIUpdateInterface *m_ai;

	AIUpdateInterface *getAIUpdateInterface() const
	{
		return m_ai;
	}
};

struct DozerTaskInfo
{
	unsigned int m_targetObjectID;
	unsigned int m_taskOrderFrame;
};

struct DozerDockPointInfo
{
	bool valid;
	unsigned char pad[3];
	Coord3D location;
};

class Rva002B9B10DozerTaskView
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void internalTaskCompleteOrCancelled(DozerTask task);
	virtual void internalCancelTask(DozerTask task);

	Object *getObject() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const char *>(this) - 0x338);
	}

private:
	DozerTaskInfo m_task[DOZER_NUM_TASKS];
	unsigned char m_pad[0x98 - 0x1c];
	DozerDockPointInfo m_dockPoint[DOZER_NUM_TASKS][DOZER_NUM_TASKS];
};

// ?internalCancelTask@Rva002B9B10DozerTaskView@@UAEXW4DozerTask@@@Z
void Rva002B9B10DozerTaskView::internalCancelTask(DozerTask task)
{
	internalTaskCompleteOrCancelled(task);

	m_task[task].m_targetObjectID = 0;
	m_task[task].m_taskOrderFrame = 0;
	for (int i = 0; i < DOZER_NUM_TASKS; ++i)
		m_dockPoint[task][i].valid = false;

	Object *object = getObject();
	AIUpdateInterface *ai = object->getAIUpdateInterface();
	ai->m_command.aiIdle(CMD_FROM_AI);
}
