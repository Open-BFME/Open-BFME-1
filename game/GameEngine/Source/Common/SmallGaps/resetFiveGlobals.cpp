// ?resetFiveGlobals@@YAXXZ
extern int g_bfmeFirstEB;
extern int g_bfmeSecondEB;
extern int g_bfmeThirdEB;
extern int g_bfmeFourthEB;
extern int g_bfmeFifthEB;
void resetFiveGlobals()
{
	g_bfmeSecondEB = 0;
	g_bfmeFirstEB = 1;
	g_bfmeThirdEB = 7;
	g_bfmeFourthEB = 0;
	g_bfmeFifthEB = 1;
}
// ?Rva00933710ResetGlobals@@YAXXZ
void Rva00933710ResetGlobals()
{
	g_bfmeSecondEB = 0;
	g_bfmeFirstEB = 0;
	g_bfmeThirdEB = 3;
	g_bfmeFourthEB = 2;
	g_bfmeFifthEB = 5;
}
// ?Rva009337A0ResetGlobals@@YAXXZ
void Rva009337A0ResetGlobals()
{
	g_bfmeSecondEB = 1;
	g_bfmeFirstEB = 0;
	g_bfmeThirdEB = 7;
	g_bfmeFourthEB = 2;
	g_bfmeFifthEB = 5;
}
