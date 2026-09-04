// ?bfmeFindNthPred@@YAHH@Z
// partial score=0.9 date=2026-09-04
// ?bfmeFindNthPred@@YAHH@Z
// stlport
// cl: /EHs-c-

class CampaignManager
{
public:
	int getMissionObjectiveCount();
	bool isMissionObjectiveEligible( int index );
};

extern CampaignManager *TheCampaignManager;

// Return the index of the n-th eligible mission objective, or -1 when the
// campaign manager is absent or fewer than n eligible objectives exist.
int bfmeFindNthPred( int n )
{
	int remain = n;

	if ( TheCampaignManager == 0 )
		return -1;

	int count = TheCampaignManager->getMissionObjectiveCount();
	int i = 0;
	int current;

loop:
	if ( i >= count )
		goto failed;
	current = i++;
	if ( !TheCampaignManager->isMissionObjectiveEligible( current ) )
		goto loop;
	if ( remain <= 0 )
		goto succeeded;
	--remain;
	goto loop;

failed:
	return -1;
succeeded:
	return current;
}
