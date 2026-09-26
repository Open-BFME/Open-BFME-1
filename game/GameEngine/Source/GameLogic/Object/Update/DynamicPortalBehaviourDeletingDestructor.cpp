// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructor for DynamicPortalBehaviour.
// Its primary vtable (0x010A397C) routes slot zero through ILT 0x0001946B
// to this 30-byte wrapper; the complete destructor is the exact ICF-shared
// body at 0x001F8D10.

class DynamicPortalBehaviour
{
	public:
	virtual ~DynamicPortalBehaviour();

private:
	friend void forceDynamicPortalBehaviourDeletingDestructor();
};

// QueueProductionExitUpdate has the same empty-derived destructor shape and
// folds onto the same retail body; retain both authentic class spellings.
class QueueProductionExitUpdate
{
	public:
	virtual ~QueueProductionExitUpdate();

	private:
	friend void forceQueueProductionExitUpdateDeletingDestructor();
};

void forceDynamicPortalBehaviourDeletingDestructor()
{
	DynamicPortalBehaviour value;
}

void forceQueueProductionExitUpdateDeletingDestructor()
{
	QueueProductionExitUpdate value;
}
