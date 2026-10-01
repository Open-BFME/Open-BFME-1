// ?resetFiveGlobalsB@@YAXXZ
// Open-BFME7: twins of the five-global reset at 0x009336E0 with other values.
extern int g_bfmeFirstEB;
extern int g_bfmeSecondEB;
extern int g_bfmeThirdEB;
extern int g_bfmeFourthEB;
extern int g_bfmeFifthEB;
void resetFiveGlobalsB()
{
	g_bfmeSecondEB = 0;
	g_bfmeFirstEB = 0;
	g_bfmeThirdEB = 7;
	g_bfmeFourthEB = 2;
	g_bfmeFifthEB = 5;
}
// ?resetFiveGlobalsC@@YAXXZ
void resetFiveGlobalsC()
{
	g_bfmeSecondEB = 2;
	g_bfmeFirstEB = 0;
	g_bfmeThirdEB = 7;
	g_bfmeFourthEB = 0;
	g_bfmeFifthEB = 1;
}
