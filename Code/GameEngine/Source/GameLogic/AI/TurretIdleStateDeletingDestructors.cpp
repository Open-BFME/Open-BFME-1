// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructors for two pool-backed turret states.
// Exact named constructors install their dedicated vtables and the slot-zero
// ILTs route to these 30-byte wrappers.

class TurretAIIdleState
{
protected:
	virtual ~TurretAIIdleState();
private:
	friend void forceTurretAIIdleStateDeletingDestructor();
};

class TurretAIIdleScanState
{
protected:
	virtual ~TurretAIIdleScanState();
private:
	friend void forceTurretAIIdleScanStateDeletingDestructor();
};

void forceTurretAIIdleStateDeletingDestructor() { TurretAIIdleState value; }
void forceTurretAIIdleScanStateDeletingDestructor() { TurretAIIdleScanState value; }
