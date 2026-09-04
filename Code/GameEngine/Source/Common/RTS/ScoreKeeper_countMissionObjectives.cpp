// cl: /DNDEBUG /MD /Gy /O2 /Ob1
// ScoreKeeper::countMissionObjectives at 0x000E8930 (106B).

typedef int Int;

class CampaignManager
{
public:
	Int getMissionObjectiveCount(void);
	unsigned char isMissionObjectiveEligible(Int index);
	unsigned char isMissionObjectiveIndexed(Int index);
	unsigned char isMissionObjectiveComplete(Int index);
};

extern CampaignManager *TheCampaignManager;	// 0x012F1028

class ScoreKeeper
{
public:
	Int countMissionObjectives(Int *outTotal);
};

Int ScoreKeeper::countMissionObjectives(Int *outTotal)
{
	Int completed = 0;
	Int total = 0;
	CampaignManager *mgr = TheCampaignManager;

	if (mgr)
	{
		Int n = mgr->getMissionObjectiveCount();
		Int i = 0;
		if (n > 0)
		{
			do
			{
				if (TheCampaignManager->isMissionObjectiveEligible(i))
				{
					if (TheCampaignManager->isMissionObjectiveIndexed(i))
					{
						++total;
						if (TheCampaignManager->isMissionObjectiveComplete(i))
							++completed;
					}
				}
				++i;
			} while (i < n);
		}
	}

	if (outTotal)
		*outTotal = total;
	return completed;
}
