// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ??1RankInfo@@MAE@XZ: Code/GameEngine/Source/GameLogic/System/RankInfo.cpp

// RankInfo has a POD science vector, a UnicodeString, and an Overridable base.
// Keeping the BFME fields in their retail order lets the compiler emit the
// complete SEH destructor, including the inline STLport vector teardown.
#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	~UnicodeString()
	{
		releaseBuffer();
	}

protected:
	void releaseBuffer();
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
protected:
	__forceinline virtual ~Overridable()
	{
		if (m_nextOverride)
			m_nextOverride->deleteInstance();
		m_nextOverride = 0;
	}

	void deleteInstance()
	{
		delete this;
	}

	Overridable *m_nextOverride;
	bool m_isOverride;
};

class __declspec(novtable) RankInfo : public Overridable
{
protected:
	virtual ~RankInfo();

private:
	UnicodeString m_rankName;
	int m_skillPointsNeededDefault;
	int m_skillPointsNeededCampaign;
	int m_skillPointsNeededGondor;
	int m_skillPointsNeededRohan;
	int m_skillPointsNeededMordor;
	int m_skillPointsNeededIsengard;
	int m_sciencePurchasePointsGranted;
	std::vector<int> m_sciencesGranted;
};

// ??1RankInfo@@MAE@XZ
RankInfo::~RankInfo()
{
}
