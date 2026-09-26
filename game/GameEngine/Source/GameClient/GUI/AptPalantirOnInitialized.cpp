class AptPalantir
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual void unused3();
	virtual void unused4();
	virtual void unused5();
	virtual void unused6();
	virtual void unused7();
	virtual void unused8();
	virtual void unused9();
	virtual void unused10();
	virtual void initialize();

	unsigned char m_unmodelled04[ 0x50 ];
	int m_jewelMode;
};

class WindowManager
{
public:
	void add( void *window, const char *name, int type, void *value,
		int unused0, int unused1, int unused2, int unused3 );
};

extern AptPalantir *TheAptPalantir;
extern WindowManager *g_theWindowManager;
extern unsigned char g_aptPalantirInitialized;
extern unsigned char g_aptPalantirJewelBrightened;
extern int g_aptPalantirWindow;
extern char g_aptPalantirJewelName[];
extern char g_aptPalantirBrightJewel[];
extern char g_aptPalantirNormalJewel[];

// ?aptPalantirOnInitialized@@YAXXZ
void aptPalantirOnInitialized()
{
	g_aptPalantirInitialized = 0;
	g_aptPalantirJewelBrightened = 0;
	if( TheAptPalantir )
		TheAptPalantir->initialize();

	const char *jewel;
	switch( TheAptPalantir->m_jewelMode )
	{
		case 1:
			jewel = g_aptPalantirBrightJewel;
			break;
		default:
			jewel = g_aptPalantirNormalJewel;
			break;
	}
	g_theWindowManager->add( (void *)g_aptPalantirWindow,
		g_aptPalantirJewelName, 1, (void *)jewel, 0, 0, 0, 0 );
}
