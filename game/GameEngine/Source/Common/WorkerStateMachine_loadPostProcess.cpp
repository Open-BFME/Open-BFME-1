// cl: /DNDEBUG /MD /EHsc
// WorkerStateMachine::loadPostProcess, retail 0x002C8170: slot 1 of WorkerStateMachine's vftable
// 0x010ca1f0, BFME's Snapshot loadPostProcess slot. The retail body is a lone
// ret; Zero Hour declares the method protected.
class WorkerStateMachine
{
protected:
	virtual void loadPostProcess(void);
};

// ?loadPostProcess@WorkerStateMachine@@MAEXXZ
void WorkerStateMachine::loadPostProcess(void)
{
}  // end loadPostProcess
