class AsciiString
{
public:
	int bfmeCompare1294(const char *text) const;
};

class BfmeGameLogic1294
{
public:
	bool bfmeUsePrimaryRank1294();
};

extern BfmeGameLogic1294 *g_bfmeGameLogic1294;
extern char g_bfmeSideNameA1294[];
extern char g_bfmeSideNameB1294[];
extern char g_bfmeSideNameC1294[];
extern char g_bfmeSideNameD1294[];

class RankInfo
{
public:
	int getSkillPointsNeeded(const AsciiString &side) const;

private:
	char m_padding00[0x10];
	int m_default10;
	int m_primary14;
	int m_sideA18;
	int m_sideB1c;
	int m_sideC20;
	int m_sideD24;
};

int RankInfo::getSkillPointsNeeded(const AsciiString &side) const
{
	if (g_bfmeGameLogic1294 != 0 && g_bfmeGameLogic1294->bfmeUsePrimaryRank1294()) {
		if (m_primary14 != -1)
			return m_primary14;
	} else {
		if (side.bfmeCompare1294(g_bfmeSideNameA1294) == 0 && m_sideA18 != -1)
			return m_sideA18;
		if (side.bfmeCompare1294(g_bfmeSideNameB1294) == 0 && m_sideB1c != -1)
			return m_sideB1c;
		if (side.bfmeCompare1294(g_bfmeSideNameC1294) == 0 && m_sideC20 != -1)
			return m_sideC20;
		if (side.bfmeCompare1294(g_bfmeSideNameD1294) == 0 && m_sideD24 != -1)
			return m_sideD24;
	}
	return m_default10;
}
