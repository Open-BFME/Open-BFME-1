// cl: /DNDEBUG /MD /EHsc
//
// WorkerStateMachine is declared in WorkerAIUpdate.h with a protected virtual
// destructor.  A friend force function keeps that access shape while asking
// MSVC to emit the retail scalar deleting destructor.

class WorkerStateMachine;
void Force_WorkerStateMachine_Deleting_Destructor(WorkerStateMachine *machine);

class WorkerStateMachine
{
	friend void Force_WorkerStateMachine_Deleting_Destructor(WorkerStateMachine *machine);

protected:
	virtual ~WorkerStateMachine();
};

__declspec(noinline) WorkerStateMachine::~WorkerStateMachine() {}

void Force_WorkerStateMachine_Deleting_Destructor(WorkerStateMachine *machine)
{
	delete machine;
}
