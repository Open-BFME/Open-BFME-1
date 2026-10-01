// ?Rva0052AE20@@YAHH@Z
// partial score=0.9221 date=2026-10-01
// cl: /DNDEBUG /MD /EHsc
// The caller at 0x0052AE80 proves the int __cdecl(int) ABI. The helper keeps its RVA name.
// Retail returns at +0x4C and starts padding at +0x4D. The draft still copies cursor early.

class CampaignManager
{
public:
	int getMissionObjectiveCount();
	bool isMissionObjectiveEligible(int index);
};

typedef CampaignManager Glo012F1028Type;
extern Glo012F1028Type *Glo012F1028;

int Rva0052AE20(int n)
{
	int remain = n;
	if (Glo012F1028 == 0)
		return -1;

	bool more = true;
	int count = Glo012F1028->getMissionObjectiveCount();
	int cursor = 0;
	int current;

	while (more)
	{
		current = cursor;
		if (cursor >= count)
			return -1;
		++cursor;
		if (!Glo012F1028->isMissionObjectiveEligible(current))
			continue;
		if (remain <= 0)
			return current;
		--remain;
	}
}
