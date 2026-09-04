class PalantirAptWindow
{
public:
	void close( int window );
};

extern PalantirAptWindow *g_bfmeLog1020;
extern int g_bfmeMsg1020;
extern char g_bfmeC1020;
extern char g_bfmeD1020;

// ?aptPalantirOnClosed@@YAXXZ
void aptPalantirOnClosed()
{
	g_bfmeLog1020->close( g_bfmeMsg1020 );
	g_bfmeC1020 = 1;
	g_bfmeD1020 = 0;
}
