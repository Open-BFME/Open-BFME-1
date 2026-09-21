// ?calcPercent@@YA?AVUnicodeString@@ABUOverallStats@@HV1@@Z
// partial score=0.27 date=2026-09-18
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringbaseunicode /ICode/Libraries/Source/WWVegas/WWLib
// Zero Hour Generals twin: WOLWelcomeMenu.cpp calcPercent.
// The BFME static OverallStats objects are the three retail blocks at
// 0x012F48CC, 0x012F48EC and 0x012F490C.

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned short wchar_t;

#include "Common/UnicodeString.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define INT_TO_REAL(x) ((Real)(x))
#define REAL_TO_INT(x) ((Int)(x))

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
};

#define TheGameText (*(GameTextInterface **)0x012F147C)

enum OverallStatsPeriod
{
	STATS_TODAY = 0,
	STATS_YESTERDAY,
	STATS_ALLTIME,
	STATS_LASTWEEK,
	STATS_MAX
};

struct OverallStats
{
	Int wins[STATS_MAX];
	Int losses[STATS_MAX];
};

#define s_statsUSA (*(const OverallStats *)0x012F48CC)
#define s_statsChina (*(const OverallStats *)0x012F48EC)
#define s_statsGLA (*(const OverallStats *)0x012F490C)

static UnicodeString calcPercent(const OverallStats &stats, Int n, UnicodeString sideStr)
{
	Real winPercentUSA = s_statsUSA.wins[n] * 100 /
		INT_TO_REAL(max(1, s_statsUSA.wins[n] + s_statsUSA.losses[n]));
	Real winPercentChina = s_statsChina.wins[n] * 100 /
		INT_TO_REAL(max(1, s_statsChina.wins[n] + s_statsChina.losses[n]));
	Real winPercentGLA = s_statsGLA.wins[n] * 100 /
		INT_TO_REAL(max(1, s_statsGLA.wins[n] + s_statsGLA.losses[n]));
	Real thisWinPercent = stats.wins[n] * 100 /
		INT_TO_REAL(max(1, stats.wins[n] + stats.losses[n]));
	Real totalWinPercent = winPercentUSA + winPercentChina + winPercentGLA;
	Real val = thisWinPercent * 100 / max(1.0f, totalWinPercent);

	UnicodeString s;
	s.format(TheGameText->fetch("GUI:PerSideWinPercentage"), REAL_TO_INT(val), sideStr.str());
	return s;
}

extern "C" __declspec(noinline) void calcPercentAnchor()
{
	UnicodeString usa, china, gla;
	usa = calcPercent(s_statsUSA, STATS_LASTWEEK, TheGameText->fetch("SIDE:America"));
	china = calcPercent(s_statsChina, STATS_LASTWEEK, TheGameText->fetch("SIDE:China"));
	gla = calcPercent(s_statsGLA, STATS_LASTWEEK, TheGameText->fetch("SIDE:GLA"));
	usa = calcPercent(s_statsUSA, STATS_TODAY, TheGameText->fetch("SIDE:America"));
	china = calcPercent(s_statsChina, STATS_TODAY, TheGameText->fetch("SIDE:China"));
	gla = calcPercent(s_statsGLA, STATS_TODAY, TheGameText->fetch("SIDE:GLA"));
}
