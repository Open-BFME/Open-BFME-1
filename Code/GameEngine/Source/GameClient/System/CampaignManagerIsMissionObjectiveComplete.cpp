// ?isMissionObjectiveComplete@CampaignManager@@QAEEH@Z
// BFME's second mission-objective span stores completion bytes alongside the
// objective records.  The ILT at 0x0000DFDA names this body.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Gen003C0350Owner
{
public:
	void *probe(void *key);
};

struct CampaignObjectiveRecord
{
	unsigned char m_indexed;
	volatile unsigned char m_complete;
};

struct CampaignObjectiveSpan
{
	CampaignObjectiveRecord *m_begin;
	CampaignObjectiveRecord *m_end;
	int byteDistance() const
	{
		return (int)((const unsigned char *)m_end - (const unsigned char *)m_begin);
	}
	CampaignObjectiveRecord &operator[](unsigned index) const { return m_begin[index]; }
};

static __forceinline int isComplete(int count, const CampaignObjectiveSpan &span, unsigned index)
{
	if (index < (unsigned)count)
	{
		unsigned char value = span[index].m_complete;
		_ReadWriteBarrier();
		if (value)
		{
			_ReadWriteBarrier();
			return 1;
		}
		_ReadWriteBarrier();
		return 0;
	}
	_ReadWriteBarrier();
	return 0;
}

class CampaignManager
{
public:
	unsigned char isMissionObjectiveComplete(int index);

private:
	char m_pad00[0x28];
	Gen003C0350Owner *m_resolver;
	char m_pad2C[0x4];
	char m_key;
	char m_pad31[0x53];
	CampaignObjectiveSpan m_objectives;
};

unsigned char CampaignManager::isMissionObjectiveComplete(int index)
{
	Gen003C0350Owner *resolver = m_resolver;
	if (resolver)
	{
		int idx = index;
		if (idx >= 0)
		{
			if (resolver->probe(&m_key))
			{
				int count = m_objectives.byteDistance();
				count >>= 1;
				return isComplete(count, m_objectives, (unsigned)idx);
			}
		}
	}
	return 0;
}
