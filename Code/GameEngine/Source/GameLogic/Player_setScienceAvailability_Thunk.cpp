// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ivendor/stlport
#include <vector>

enum ScienceType {};

enum ScienceAvailabilityType
{
	SCIENCE_AVAILABILITY_INVALID = -1,
	SCIENCE_AVAILABLE,
	SCIENCE_DISABLED,
	SCIENCE_HIDDEN
};

typedef std::vector<ScienceType> ScienceVec;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void setScienceAvailability(ScienceType science,
		ScienceAvailabilityType type);

private:
	// BFME inserts player state absent from Zero Hour before these vectors.
	char m_retailPrefix[0x240];
	ScienceVec m_sciencesDisabled;
	ScienceVec m_sciencesHidden;
};

void Player::setScienceAvailability(ScienceType science,
	ScienceAvailabilityType type)
{
	ScienceVec::iterator it;
	bool found = false;

	for (it = m_sciencesDisabled.begin(); it != m_sciencesDisabled.end(); ++it)
	{
		if (*it == science)
		{
			m_sciencesDisabled.erase(it);
			found = true;
			break;
		}
	}

	if (!found)
	{
		for (it = m_sciencesHidden.begin(); it != m_sciencesHidden.end(); ++it)
		{
			if (*it == science)
			{
				m_sciencesHidden.erase(it);
				break;
			}
		}
	}

	if (type == SCIENCE_DISABLED)
	{
		m_sciencesDisabled.push_back(science);
	}
	else if (type == SCIENCE_HIDDEN)
	{
		m_sciencesHidden.push_back(science);
	}
}
