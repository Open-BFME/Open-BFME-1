// cl: /DNDEBUG /MD /EHsc
// DozerAIUpdateView::internalTaskComplete, retail 0x002B6910.
// Standalone view: m_task at +4 (after the interface vptr) and m_dockPoint at
// +0x98 so the 16-byte dock-point stride lands on retail's lea [ecx+esi+0x98]
// without moving the matched getBuildSubTask / getMostRecentCommand offsets
// in the real DozerAIUpdate.cpp TU.

enum DozerTask
{
	DOZER_TASK_BUILD = 0,
	DOZER_TASK_REPAIR = 1,
	DOZER_TASK_FORTIFY = 2,
	DOZER_NUM_TASKS = 3
};

enum { DOZER_NUM_DOCK_POINTS = 3 };

struct Coord3D
{
	float x, y, z;
};

struct DozerTaskInfo
{
	int m_targetObjectID;
	unsigned int m_taskOrderFrame;
};

struct DozerDockPointInfo
{
	bool valid;
	unsigned char pad[3];
	Coord3D location;
};

class DozerAIUpdateView
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
	virtual void internalTaskCompleteOrCancelled(DozerTask task);	///< vtable +0x40
	virtual void internalTaskComplete(DozerTask task);

private:
	DozerTaskInfo m_task[DOZER_NUM_TASKS];							// +0x04
	unsigned char m_pad[0x98 - 0x1C];								// +0x1C
	DozerDockPointInfo m_dockPoint[DOZER_NUM_TASKS][DOZER_NUM_DOCK_POINTS];	// +0x98
};

// ?internalTaskComplete@DozerAIUpdate@@UAEXW4DozerTask@@@Z
void DozerAIUpdateView::internalTaskComplete(DozerTask task)
{
	internalTaskCompleteOrCancelled(task);

	m_task[task].m_targetObjectID = 0;
	m_task[task].m_taskOrderFrame = 0;

	for (int i = 0; i < DOZER_NUM_DOCK_POINTS; i++)
		m_dockPoint[task][i].valid = false;
}
