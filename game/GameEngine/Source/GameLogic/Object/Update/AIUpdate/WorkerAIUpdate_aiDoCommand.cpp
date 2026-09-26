// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2
// BFME's WorkerAIUpdate::aiDoCommand is emitted through the secondary
// AICommandInterface view.  The method receiver is full WorkerAIUpdate + 0x20.

typedef bool Bool;
typedef int Int;

class Object;
class Drawable;

struct AICommandParms
{
	Int m_cmd;
	Int m_cmdSource;
	unsigned char m_pad08[0x0c];
	Object *m_obj;
};

enum
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 2,
	AICMD_REPAIR = 0x13,
	AICMD_RESUME_CONSTRUCTION = 0x14,
	DOZER_TASK_INVALID = -1
};

class Object
{
public:
	void notifyModelConditionChanged();
};

class Drawable
{
public:
	void updateDrawableSupplyStatus(Int maxBoxes, Int currentBoxes);
};

class AIUpdateInterface
{
public:
	void aiDoCommand(const AICommandParms *parms);
};

class AICommandInterface
{
public:
	void aiIdle(Int source);
};

class WorkerAIUpdate
{
public:
	void createMachines();
	virtual void aiDoCommand(const AICommandParms *parms);
};

void j_00024d70();
void j_0003fa53();
void j_000409b2();

template <Int N>
class BfmeWorkerSlots : public BfmeWorkerSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeWorkerSlots<0>
{
};

class BfmeWorkerRepairView : public BfmeWorkerSlots<40>
{
public:
	virtual void privateRepair(Object *, Int source) = 0;
	virtual void privateResumeConstruction(Object *, Int source) = 0;
};

class BfmeWorkerMinesView : public BfmeWorkerSlots<98>
{
public:
	virtual Bool isClearingMines() const = 0;
};

class BfmeWorkerAllowedView : public BfmeWorkerSlots<132>
{
public:
	virtual Bool isAllowedToRespondToAiCommands(const AICommandParms *) const = 0;
};

class BfmeDozerInterfaceView : public BfmeWorkerSlots<9>
{
public:
	virtual Int getCurrentTask() const = 0;
	virtual void unusedSlot10() = 0;
	virtual void unusedSlot11() = 0;
	virtual void unusedSlot12() = 0;
	virtual void cancelTask(Int task) = 0;
};

class BfmeDozerStateMachineView : public BfmeWorkerSlots<6>
{
public:
	virtual void resetToDefaultState() = 0;
};

class BfmeObjectDrawableView : public BfmeWorkerSlots<10>
{
public:
	virtual Drawable *getDrawable() = 0;
};

static __forceinline Object *bfmeWorkerObject(const char *self)
{
	return *reinterpret_cast<Object *const *>(self - 0x18);
}

static __forceinline void clearModelCondition100(Object *object)
{
	unsigned int &flags = *reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(object) + 0x118);
	if ((flags & 0x100) != 0)
	{
		flags &= 0xfffffeff;
		object->notifyModelConditionChanged();
	}
}

static __forceinline void clearModelCondition200000(Object *object)
{
	unsigned int &flags = *reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(object) + 0x12c);
	if ((flags & 0x200000) != 0)
	{
		flags &= 0xffdfffff;
		object->notifyModelConditionChanged();
	}
}

static __forceinline void clearModelCondition400000(Object *object)
{
	unsigned int &flags = *reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(object) + 0x12c);
	if ((flags & 0x400000) != 0)
	{
		flags &= 0xffbfffff;
		object->notifyModelConditionChanged();
	}
}

class BfmeWorkerCreateMachinesCall
{
public:
	void invoke();
};

class BfmeWorkerAiIdleCall
{
public:
	void invoke(Int source);
};

class BfmeWorkerBaseAiDoCommandCall
{
public:
	void invoke(const AICommandParms *parms);
};

static __forceinline void bfmeWorkerCreateMachines(WorkerAIUpdate *worker)
{
	typedef void (BfmeWorkerCreateMachinesCall::*Call)();
	union
	{
		void (*asFunction)();
		Call asMember;
	} thunk;
	thunk.asFunction = j_0003fa53;
	(reinterpret_cast<BfmeWorkerCreateMachinesCall *>(worker)->*thunk.asMember)();
}

static __forceinline void bfmeWorkerAiIdle(AICommandInterface *self, Int source)
{
	typedef void (BfmeWorkerAiIdleCall::*Call)(Int);
	union
	{
		void (*asFunction)();
		Call asMember;
	} thunk;
	thunk.asFunction = j_00024d70;
	(reinterpret_cast<BfmeWorkerAiIdleCall *>(self)->*thunk.asMember)(source);
}

static __forceinline void bfmeWorkerBaseAiDoCommand(AIUpdateInterface *self, const AICommandParms *parms)
{
	typedef void (BfmeWorkerBaseAiDoCommandCall::*Call)(const AICommandParms *);
	union
	{
		void (*asFunction)();
		Call asMember;
	} thunk;
	thunk.asFunction = j_000409b2;
	(reinterpret_cast<BfmeWorkerBaseAiDoCommandCall *>(self)->*thunk.asMember)(parms);
}

// ?aiDoCommand@WorkerAIUpdate@@UAEXPBUAICommandParms@@@Z
void WorkerAIUpdate::aiDoCommand(const AICommandParms *parms)
{
	char *self = reinterpret_cast<char *>(this);
	clearModelCondition100(bfmeWorkerObject(self));
	clearModelCondition200000(bfmeWorkerObject(self));
	clearModelCondition400000(bfmeWorkerObject(self));

	WorkerAIUpdate *worker = reinterpret_cast<WorkerAIUpdate *>(self - 0x20);
	if (!reinterpret_cast<const BfmeWorkerAllowedView *>(worker)->isAllowedToRespondToAiCommands(parms))
		return;

	bfmeWorkerCreateMachines(worker);

	switch (parms->m_cmd)
	{
	case AICMD_REPAIR:
		{
			BfmeDozerInterfaceView *dozer = reinterpret_cast<BfmeDozerInterfaceView *>(self + 0x320);
			if (dozer->getCurrentTask() == DOZER_TASK_INVALID)
				bfmeWorkerAiIdle(reinterpret_cast<AICommandInterface *>(self), CMD_FROM_AI);
			reinterpret_cast<BfmeWorkerRepairView *>(worker)->privateRepair(parms->m_obj, parms->m_cmdSource);
			break;
		}

	case AICMD_RESUME_CONSTRUCTION:
		{
			BfmeDozerInterfaceView *dozer = reinterpret_cast<BfmeDozerInterfaceView *>(self + 0x320);
			if (dozer->getCurrentTask() == DOZER_TASK_INVALID)
				bfmeWorkerAiIdle(reinterpret_cast<AICommandInterface *>(self), CMD_FROM_AI);
			reinterpret_cast<BfmeWorkerRepairView *>(worker)->privateResumeConstruction(parms->m_obj, parms->m_cmdSource);
			break;
		}

	default:
		{
			if (parms->m_cmdSource == CMD_FROM_PLAYER)
			{
				BfmeDozerInterfaceView *dozer = reinterpret_cast<BfmeDozerInterfaceView *>(self + 0x320);
				if (dozer->getCurrentTask() != DOZER_TASK_INVALID)
					dozer->cancelTask(dozer->getCurrentTask());
			}

		bfmeWorkerBaseAiDoCommand(reinterpret_cast<AIUpdateInterface *>(self), parms);

			if (parms->m_cmdSource == CMD_FROM_PLAYER)
				reinterpret_cast<BfmeDozerStateMachineView *>(*reinterpret_cast<void **>(self + 0x400))->resetToDefaultState();
			break;
		}
	}

	if (reinterpret_cast<const BfmeWorkerMinesView *>(worker)->isClearingMines())
	{
		Int &numberBoxes = *reinterpret_cast<Int *>(self + 0x3dc);
		if (numberBoxes > 0)
		{
			Object *object = bfmeWorkerObject(self);
			numberBoxes = 0;
			Drawable *draw = reinterpret_cast<BfmeObjectDrawableView *>(object)->getDrawable();
			if (draw)
			{
				Int maxBoxes = *reinterpret_cast<const Int *>(
				reinterpret_cast<const char *>(*reinterpret_cast<void *const *>(self - 0x1c)) + 0x64);
				draw->updateDrawableSupplyStatus(maxBoxes, numberBoxes);
			}
		}
	}
}
