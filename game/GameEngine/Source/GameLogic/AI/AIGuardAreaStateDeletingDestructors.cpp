// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructors for two pool-backed guard/area AI
// states. Exact named constructors install the dedicated vtables whose
// slot-zero ILTs route to these 30-byte wrappers.

class AITunnelNetworkGuardState
{
protected:
	virtual ~AITunnelNetworkGuardState();
private:
	friend void forceAITunnelNetworkGuardStateDeletingDestructor();
};

class AIAttackAreaState
{
protected:
	virtual ~AIAttackAreaState();
private:
	friend void forceAIAttackAreaStateDeletingDestructor();
};

void forceAITunnelNetworkGuardStateDeletingDestructor() { AITunnelNetworkGuardState value; }
void forceAIAttackAreaStateDeletingDestructor() { AIAttackAreaState value; }
