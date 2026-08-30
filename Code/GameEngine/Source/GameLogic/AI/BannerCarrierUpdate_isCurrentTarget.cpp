// cl: /DNDEBUG /MD /EHsc

class BfmeTargetObject;

class BfmeStateMachine
{
public:
	BfmeTargetObject *getGoalObject();
};

#define BFME_EIGHT_SLOTS(prefix) \
	virtual void prefix##0(); virtual void prefix##1(); \
	virtual void prefix##2(); virtual void prefix##3(); \
	virtual void prefix##4(); virtual void prefix##5(); \
	virtual void prefix##6(); virtual void prefix##7()

class BfmeTargetObject
{
public:
	BFME_EIGHT_SLOTS(a);
	BFME_EIGHT_SLOTS(b);
	BFME_EIGHT_SLOTS(c);
	BFME_EIGHT_SLOTS(d);
	BFME_EIGHT_SLOTS(e);
	BFME_EIGHT_SLOTS(f);
	BFME_EIGHT_SLOTS(g);
	BFME_EIGHT_SLOTS(h);
	BFME_EIGHT_SLOTS(i);
	BFME_EIGHT_SLOTS(j);
	BFME_EIGHT_SLOTS(k);
	BFME_EIGHT_SLOTS(l);
	virtual void m0();
	virtual char hasCurrentTarget();

	BfmeTargetObject *resolveMeleeTarget(char includeContained);

	unsigned char m_pad04[0x2c];
	BfmeStateMachine *m_stateMachine;
};

#undef BFME_EIGHT_SLOTS

char __stdcall bfmeIsCurrentTarget(BfmeTargetObject *source, BfmeTargetObject *candidate)
{
	if (source == 0 || candidate == 0)
		return false;

	char matches = false;
	BfmeTargetObject *resolvedCandidate = candidate->resolveMeleeTarget(false);
	if (source->hasCurrentTarget())
	{
		BfmeTargetObject *goal = source->m_stateMachine->getGoalObject();
		if (goal != 0)
		{
			if (candidate == goal)
				matches = true;
			else
			{
				BfmeTargetObject *resolvedGoal = goal->resolveMeleeTarget(false);
				if (resolvedGoal != 0 && resolvedCandidate == resolvedGoal)
					matches = true;
			}
		}
	}
	return matches;
}
