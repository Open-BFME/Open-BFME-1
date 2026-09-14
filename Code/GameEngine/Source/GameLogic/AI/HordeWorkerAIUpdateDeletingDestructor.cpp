// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for HordeWorkerAIUpdate.
// Vtable 0x00CC8790 slots name this class (?getModuleNameKey@HordeWorkerAIUpdate@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x0001E53D to this 30-byte wrapper, whose complete destructor
// route ILT 0x000369AD reaches cleanup body 0x002C4980.

class HordeWorkerAIUpdate
{
protected:
	virtual ~HordeWorkerAIUpdate();
private:
	friend void forceHordeWorkerAIUpdateDeletingDestructor();
};

void forceHordeWorkerAIUpdateDeletingDestructor()
{
	HordeWorkerAIUpdate value;
}
