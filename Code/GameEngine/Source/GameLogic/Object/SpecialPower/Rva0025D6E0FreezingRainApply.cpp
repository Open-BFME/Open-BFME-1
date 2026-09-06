// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FreezingRain effect point helper at retail 0x0025D6E0.

typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Region3D
{
	Coord3D lo;
	Coord3D hi;
};

struct BfmeModeAZC
{
	unsigned char pad[0x0c];
	int mode;
	void bfmeStopAZC(int value);
};

extern BfmeModeAZC *g_bfmeModeAZC;
extern const Real g_bfmeK1253;

class BfmeThingCOF
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	bool bfmeAskCOF();
	void bfmeRunCOF(void *, void *, void *, void *);

	private:
		unsigned char pad[0x214 - 0x04];

	public:
		BfmeThingCOF *containedBy;
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void getExtentIncludingBorder(Region3D *extent);
};

extern TerrainLogic *TheTerrainLogic;

class Rva0025D7E0FreezingRainDispatch
{
public:
	void apply(Coord3D *subject);

private:
	unsigned char pad[4];
	BfmeThingCOF *thing;
};

// ?apply@Rva0025D7E0FreezingRainDispatch@@QAEXPAUCoord3D@@@Z
void Rva0025D7E0FreezingRainDispatch::apply(Coord3D *subject)
{
	if (g_bfmeModeAZC->mode == 2)
		return;

	BfmeThingCOF *object = thing;
	g_bfmeModeAZC->bfmeStopAZC(2);
	if (object->containedBy != 0)
	{
		Region3D extent;
		TheTerrainLogic->getExtentIncludingBorder(&extent);
		Coord3D point;
		point.x = (extent.lo.x + extent.hi.x) * g_bfmeK1253;
		point.y = (extent.lo.y + extent.hi.y) * g_bfmeK1253;
		point.z = subject->z;
		BfmeThingCOF *containedBy = object->containedBy;
		if (containedBy != 0 && !containedBy->bfmeAskCOF())
			containedBy->bfmeRunCOF(&point, 0, 0, 0);
	}
}
