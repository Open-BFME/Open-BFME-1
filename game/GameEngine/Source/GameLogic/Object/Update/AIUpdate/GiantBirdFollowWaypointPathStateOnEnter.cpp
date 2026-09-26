// cl: /DNDEBUG /MD
//
// GiantBirdFollowWaypointPathState::onEnter, retail RVA 0x002BF050.  The
// constructor at 0x002BEFA0 installs vtable 0x010C79E0; slot 4 reaches this
// body alongside the matched onExit, update, and updateWaypointGoal methods.

typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class GiantBirdFollowWaypointPathState
{
public:
	virtual StateReturnType onEnter();
	bool updateWaypointGoal();

private:
	char m_gap04[0x18];
	unsigned char *m_machine;
	char m_gap20[4];
	int m_counter;
};

StateReturnType GiantBirdFollowWaypointPathState::onEnter()
{
	m_counter = 0;
	unsigned char *object = *(unsigned char **)(m_machine + 0x10);
	unsigned char *ai = *(unsigned char **)(object + 0x204);
	if (ai == 0)
		goto failure;
	if ((*(unsigned char *)(object + 0x344) & 1) != 0)
		goto failure;
	if (!updateWaypointGoal())
		return STATE_SUCCESS;
	goto checkByte;

failure:
	return STATE_FAILURE;

checkByte:
	if (*(unsigned char *)(ai + 0x424) == 0)
		goto failure;
	*(UnsignedInt *)(ai + 0x3f0) |= 0x80;
	return STATE_CONTINUE;
}
