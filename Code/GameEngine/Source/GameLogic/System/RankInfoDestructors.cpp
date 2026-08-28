// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ??1RankInfo@@MAE@XZ: Code/GameEngine/Source/GameLogic/System/RankInfo.cpp
// readable body of ??1RankInfoStore@@UAE@XZ: Code/GameEngine/Source/GameLogic/System/RankInfo.cpp

// The store's destructor and the element's destructor are one pair: the store
// deletes every RankInfo it owns, so the two bodies only agree if they agree on
// what a RankInfo is. They sat in two files, one carrying the real layout and
// the other a bare stand-in with a public destructor, and nothing checked that
// the stand-in matched.
//
// RankInfo has a POD science vector, a UnicodeString, and an Overridable base.
// Keeping the BFME fields in their retail order lets the compiler emit the
// complete SEH destructor, including the inline STLport vector teardown.
//
// RankInfoStore::~RankInfoStore deletes every element, clears the vector, then
// lets the member and the base tear themselves down.
//
// The same shape as SpecialPowerStore with one difference visible in a single
// instruction: the comparisons here are jle and jl rather than jbe and jb, so
// the loop is signed and the size is compared as an int. The first test is the
// compiler's signed form of dividing the byte span by four -- test against
// 0xFFFFFFFC masks the low two bits off before checking the sign.
//
// The clear() is the degenerate erase(begin(), end()) again: comparing finish
// with itself, and a branch that can never be taken.
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

class RankInfoStore;

class __declspec(novtable) RankInfo : public Overridable
{
	// The M in ??1RankInfo@@MAE@XZ is protected-virtual, so the store cannot
	// reach this destructor by name -- yet its retail body deletes RankInfo
	// instances through it. Upstream reaches it through MemoryPoolObject's
	// public deleteInstance(); the shim grants the one access that call needs.
	friend class RankInfoStore;

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	int m_04;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/RankInfo.h
class RankInfoStore : public SubsystemInterface
{
public:
	virtual ~RankInfoStore();

private:
	std::vector<RankInfo *> m_ranks;
};

// ??1RankInfo@@MAE@XZ
RankInfo::~RankInfo()
{
}

// ??1RankInfoStore@@UAE@XZ
RankInfoStore::~RankInfoStore()
{
	for (int i = 0; i < (int)m_ranks.size(); i++) {
		delete m_ranks[i];
	}

	m_ranks.clear();
}
