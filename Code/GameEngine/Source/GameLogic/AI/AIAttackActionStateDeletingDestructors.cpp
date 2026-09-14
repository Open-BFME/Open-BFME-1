// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructors for two pool-backed AI attack-action
// states. Exact named constructors install their dedicated vtables and the
// slot-zero ILTs route to these 30-byte wrappers.

class AIAttackAimAtTargetState
{
protected:
	virtual ~AIAttackAimAtTargetState();
private:
	friend void forceAIAttackAimAtTargetStateDeletingDestructor();
};

class AIAttackFireWeaponState
{
protected:
	virtual ~AIAttackFireWeaponState();
private:
	friend void forceAIAttackFireWeaponStateDeletingDestructor();
};

void forceAIAttackAimAtTargetStateDeletingDestructor() { AIAttackAimAtTargetState value; }
void forceAIAttackFireWeaponStateDeletingDestructor() { AIAttackFireWeaponState value; }
