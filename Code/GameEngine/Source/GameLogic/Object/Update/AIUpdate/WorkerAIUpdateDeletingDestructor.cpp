// cl: /DNDEBUG /MD /EHsc
//
// The module memory-pool declaration gives WorkerAIUpdate a protected virtual
// destructor.  The friend force function preserves that access and asks MSVC
// to emit the retail scalar deleting wrapper.

class WorkerAIUpdate;
void Force_WorkerAIUpdate_Deleting_Destructor(WorkerAIUpdate *update);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/WorkerAIUpdate.h
class WorkerAIUpdate
{
	friend void Force_WorkerAIUpdate_Deleting_Destructor(WorkerAIUpdate *update);

protected:
	virtual ~WorkerAIUpdate();
};

__declspec(noinline) WorkerAIUpdate::~WorkerAIUpdate() {}

void Force_WorkerAIUpdate_Deleting_Destructor(WorkerAIUpdate *update)
{
	delete update;
}
