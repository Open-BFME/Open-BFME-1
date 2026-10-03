// ?isMissionObjectiveEligible@CampaignManager@@QAEEH@Z
// cl: /Igame/Libraries/Source/WWVegas/WWLib
//
// The CampaignManager identity is established by the matched sibling
// objective methods and ScoreKeeper's named caller.  This method uses the
// same resolver/key layout, while its first objective span stores the
// eligibility byte in each two-byte record.

#include "ascii_string.h"

class LivingWorldRegion;

class LivingWorldRegionManager
{
public:
	LivingWorldRegion *rva003C8A50(const AsciiString &key);
};

struct CampaignObjectiveEligibleRecord
{
	unsigned char m_eligible;
	unsigned char m_complete;
};

struct CampaignObjectiveEligibleSpan
{
	CampaignObjectiveEligibleRecord *m_begin;
	CampaignObjectiveEligibleRecord *m_end;

	unsigned int size() const
	{
		return (unsigned int)(m_end - m_begin);
	}
};

struct CampaignObjectiveEligibleFoundSpan
{
	void **m_begin;
	void **m_end;
};

struct CampaignObjectiveEligibleFound
{
	char m_pad00[0x54];
	CampaignObjectiveEligibleFoundSpan m_first;
	char m_pad5c[4];
	CampaignObjectiveEligibleFoundSpan m_second;
};

static __forceinline int campaignObjectiveEligibleFlag(unsigned int index,
	unsigned int total)
{
	return index < total;
}

class CampaignManager
{
public:
	unsigned char isMissionObjectiveEligible(int index);

private:
	char m_pad00[0x28];
	LivingWorldRegionManager *m_resolver;
	char m_pad2C[0x4];
	AsciiString m_key;
	char m_pad34[0x50];
	CampaignObjectiveEligibleSpan m_objectives;
};

unsigned char CampaignManager::isMissionObjectiveEligible(int index)
{
	LivingWorldRegionManager *resolver = m_resolver;
	if (resolver)
	{
		int idx = index;
		if (idx >= 0)
		{
			CampaignObjectiveEligibleFound *found =
				(CampaignObjectiveEligibleFound *)resolver->rva003C8A50(m_key);
			if (found)
			{
				unsigned int count = m_objectives.size();
				if ((unsigned int)idx >= count)
				{
					int second = (int)(found->m_second.m_end -
						found->m_second.m_begin);
					int first = (int)(found->m_first.m_end -
						found->m_first.m_begin);
					int total = second + first;
					return (unsigned char)campaignObjectiveEligibleFlag(
						(unsigned int)idx, (unsigned int)total);
				}
				return m_objectives.m_begin[idx].m_eligible;
			}
		}
	}
	return 0;
}
