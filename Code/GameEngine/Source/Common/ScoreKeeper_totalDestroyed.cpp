// Aggregate the per-player unit and building destruction counters.

typedef int Int;

class ScoreKeeper
{
public:
	Int getTotalUnitsDestroyed(void);
	Int getTotalBuildingsDestroyed(void);

private:
	void *m_bfmeVtable;
	Int m_totalMoneyEarned;
	Int m_totalMoneySpent;
	Int m_totalUnitsDestroyed[32];			// +0x0C
	Int m_totalUnitsBuilt;
	Int m_totalUnitsLost;
	Int m_totalBuildingsDestroyed[32];		// +0x94
	Int m_totalBuildingsBuilt;
	Int m_totalBuildingsLost;
};

// ?getTotalUnitsDestroyed@ScoreKeeper@@QAEHXZ
Int ScoreKeeper::getTotalUnitsDestroyed(void)
{
	Int total = 0;

	for (Int i = 0; i < 32; ++i)
		total += m_totalUnitsDestroyed[i];

	return total;
}

// ?getTotalBuildingsDestroyed@ScoreKeeper@@QAEHXZ
Int ScoreKeeper::getTotalBuildingsDestroyed(void)
{
	Int total = 0;

	for (Int i = 0; i < 32; ++i)
		total += m_totalBuildingsDestroyed[i];

	return total;
}
