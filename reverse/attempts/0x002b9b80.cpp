// ?aiDoCommand@DozerAIUpdate@@UAEXPBUAICommandParms@@@Z
// partial score=0.99 date=2026-09-10
// ?aiDoCommand@DozerAIUpdate@@UAEXPBUAICommandParms@@@Z
class BfmeDozerAiCommandView : public BfmeDozerSlots<40>
{
public:
	virtual void privateRepair(Object *, CommandSourceType) = 0;
	virtual void privateResumeConstruction(Object *, CommandSourceType) = 0;
};

class BfmeObjectModelCondition
{
public:
	void clearModelConditionState()
	{
		if ((m_conditionFlags & 0x100) != 0)
		{
			m_conditionFlags &= 0xfffffeff;
			notifyModelConditionChanged();
		}
	}

	void notifyModelConditionChanged();

private:
	char m_padding[0x118];
	UnsignedInt m_conditionFlags;
};

class BfmeDozerTaskView : public BfmeDozerSlots<9>
{
public:
	virtual DozerTask getCurrentTask() const = 0;
	virtual void unusedSlot10() = 0;
	virtual void unusedSlot11() = 0;
	virtual void unusedSlot12() = 0;
	virtual void cancelTask(DozerTask) = 0;
};

class BfmeDozerStateMachineView : public BfmeDozerSlots<6>
{
public:
	virtual void resetToDefaultState() = 0;
};

class BfmeDozerAiUpdateView : public BfmeDozerSlots<132>
{
public:
	virtual Bool isAllowedToRespondToAiCommands(const AICommandParms *) const = 0;
};

void DozerAIUpdate::aiDoCommand(const AICommandParms* parms)
{
	BfmeObjectModelCondition *object = *reinterpret_cast<BfmeObjectModelCondition **>((char *)this + 0x8);
	object->clearModelConditionState();
	if (!reinterpret_cast<BfmeDozerAiUpdateView *>(this)->isAllowedToRespondToAiCommands(parms))
		return;

	createMachines();

	switch( parms->m_cmd )
	{
		case static_cast<AICommandType>(0x34):
		{
			Object *otherObj = parms->m_obj;
			Bool otherIsDozer = false;
			if (otherObj)
				otherIsDozer = otherObj->isKindOf(static_cast<KindOfType>(0xe));
			if (!otherIsDozer && reinterpret_cast<BfmeDozerTaskView *>((char *)this + 0x340)->getCurrentTask() != DOZER_TASK_INVALID)
				return;
			AIUpdateInterface::aiDoCommand(parms);
			break;
		}
		case AICMD_REPAIR:
		{
			if (reinterpret_cast<BfmeDozerTaskView *>((char *)this + 0x340)->getCurrentTask() == DOZER_TASK_INVALID)
				aiIdle(CMD_FROM_AI);
			reinterpret_cast<BfmeDozerAiCommandView *>(this)->privateRepair(parms->m_obj, parms->m_cmdSource);
			break;
		}
		case AICMD_RESUME_CONSTRUCTION:
		{
			if (reinterpret_cast<BfmeDozerTaskView *>((char *)this + 0x340)->getCurrentTask() == DOZER_TASK_INVALID)
				reinterpret_cast<AICommandInterface *>(this)->aiIdle(CMD_FROM_AI);
			reinterpret_cast<BfmeDozerAiCommandView *>(this)->privateResumeConstruction(parms->m_obj, parms->m_cmdSource);
			break;
		}
		default:
		{
			if (parms->m_cmdSource == CMD_FROM_PLAYER)
			{
				BfmeDozerTaskView *dozerAI = reinterpret_cast<BfmeDozerTaskView *>((char *)this + 0x340);
				if (dozerAI->getCurrentTask() != DOZER_TASK_INVALID)
					dozerAI->cancelTask(dozerAI->getCurrentTask());
			}
			AIUpdateInterface::aiDoCommand(parms);
			if (parms->m_cmdSource == CMD_FROM_PLAYER)
				reinterpret_cast<BfmeDozerStateMachineView *>(*(void **)((char *)this + 0x35c))->resetToDefaultState();
			break;
		}
	}
}
