// ?resetFiveGlobals@@YAXXZ
extern "C" int g_bfmeFirstEB;
extern "C" int g_bfmeSecondEB;
extern "C" int g_bfmeThirdEB;
extern "C" int g_bfmeFourthEB;
extern "C" int g_bfmeFifthEB;
void resetFiveGlobals()
{
	g_bfmeSecondEB = 0;
	g_bfmeFirstEB = 1;
	g_bfmeThirdEB = 7;
	g_bfmeFourthEB = 0;
	g_bfmeFifthEB = 1;
}
