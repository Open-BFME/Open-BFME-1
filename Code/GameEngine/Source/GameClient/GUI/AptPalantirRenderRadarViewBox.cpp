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
	virtual void renderRadarViewBox();
};

extern AptPalantir *TheAptPalantir;

// ?aptPalantirRenderRadarViewBox@@YAXXZ
void aptPalantirRenderRadarViewBox()
{
	TheAptPalantir->renderRadarViewBox();
}
