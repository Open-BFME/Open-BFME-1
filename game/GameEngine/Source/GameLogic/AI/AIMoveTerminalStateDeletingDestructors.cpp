// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructors for the two pool-backed terminal
// movement states. Their exact constructors install dedicated vtables and
// each slot-zero ILT selects the corresponding 30-byte wrapper.

class AIMoveAndEvacuateState
{
protected:
	virtual ~AIMoveAndEvacuateState();
private:
	friend void forceAIMoveAndEvacuateStateDeletingDestructor();
};

class AIMoveAndDeleteState
{
protected:
	virtual ~AIMoveAndDeleteState();
private:
	friend void forceAIMoveAndDeleteStateDeletingDestructor();
};

void forceAIMoveAndEvacuateStateDeletingDestructor() { AIMoveAndEvacuateState value; }
void forceAIMoveAndDeleteStateDeletingDestructor() { AIMoveAndDeleteState value; }
