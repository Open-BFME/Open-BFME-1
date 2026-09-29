// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include/GameNetwork/GameSpy /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "PreRTS.h"
#include "GameClient/GameText.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetStaticText.h"
#include "MainMenuUtils.h" // Generals overall-stat layout, before the Zero Hour HTTP API.

static OverallStats s_statsUSA, s_statsChina, s_statsGLA;

// calcPercent at 0050B200 uses a reference-returning max and an inline
// StringBase accessor. Keep this static helper with updateOverallStats:
// MSVC uses a private ESI argument convention shared by their exact bodies.
template <class T> inline const T &percentMax(const T &a, const T &b) { return a > b ? a : b; }

static UnicodeString calcPercent(const OverallStats& stats, Int n, UnicodeString sideStr)
{
	Real winPercentUSA   = s_statsUSA.wins[n]*100/INT_TO_REAL(percentMax(1, s_statsUSA.wins[n]+s_statsUSA.losses[n]));
	Real winPercentChina = s_statsChina.wins[n]*100/INT_TO_REAL(percentMax(1, s_statsChina.wins[n]+s_statsChina.losses[n]));
	Real winPercentGLA   = s_statsGLA.wins[n]*100/INT_TO_REAL(percentMax(1, s_statsGLA.wins[n]+s_statsGLA.losses[n]));
	Real thisWinPercent  = stats.wins[n]*100/INT_TO_REAL(percentMax(1, stats.wins[n]+stats.losses[n]));
	Real totalWinPercent = winPercentUSA + winPercentChina + winPercentGLA;
	Real val = thisWinPercent*100/percentMax(1.0f,totalWinPercent);
	UnicodeString s;
	s.format(TheGameText->fetch("GUI:PerSideWinPercentage"), (Int)val, sideStr.str());
	return s;
}

void updateOverallStats(void)
{
	UnicodeString usa, china, gla;
	GameWindow *win;

	usa = calcPercent(s_statsUSA, STATS_LASTWEEK, TheGameText->fetch("SIDE:America"));
	china = calcPercent(s_statsChina, STATS_LASTWEEK, TheGameText->fetch("SIDE:China"));
	gla = calcPercent(s_statsGLA, STATS_LASTWEEK, TheGameText->fetch("SIDE:GLA"));
	win = TheWindowManager->winGetWindowFromId( NULL, NAMEKEY("WOLWelcomeMenu.wnd:StaticTextUSALastWeek") );
	GadgetStaticTextSetText(win, usa);
	win = TheWindowManager->winGetWindowFromId( NULL, NAMEKEY("WOLWelcomeMenu.wnd:StaticTextChinaLastWeek") );
	GadgetStaticTextSetText(win, china);
	win = TheWindowManager->winGetWindowFromId( NULL, NAMEKEY("WOLWelcomeMenu.wnd:StaticTextGLALastWeek") );
	GadgetStaticTextSetText(win, gla);

	usa = calcPercent(s_statsUSA, STATS_TODAY, TheGameText->fetch("SIDE:America"));
	china = calcPercent(s_statsChina, STATS_TODAY, TheGameText->fetch("SIDE:China"));
	gla = calcPercent(s_statsGLA, STATS_TODAY, TheGameText->fetch("SIDE:GLA"));
	win = TheWindowManager->winGetWindowFromId( NULL, NAMEKEY("WOLWelcomeMenu.wnd:StaticTextUSAToday") );
	GadgetStaticTextSetText(win, usa);
	win = TheWindowManager->winGetWindowFromId( NULL, NAMEKEY("WOLWelcomeMenu.wnd:StaticTextChinaToday") );
	GadgetStaticTextSetText(win, china);
	win = TheWindowManager->winGetWindowFromId( NULL, NAMEKEY("WOLWelcomeMenu.wnd:StaticTextGLAToday") );
	GadgetStaticTextSetText(win, gla);
}
