// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: bounds-centre effect point helper at retail 0x00259CD0 (near-twin of 0x0025D6E0, constant 1 vs 2).

typedef float Real;

struct Coord3D_259CD0
{
	Real x;
	Real y;
	Real z;
};

struct Region3D_259CD0
{
	Coord3D_259CD0 lo;
	Coord3D_259CD0 hi;
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

class TerrainLogic_259CD0
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
	virtual void getExtentIncludingBorder(Region3D_259CD0 *extent);
};

extern TerrainLogic_259CD0 *TheTerrainLogic;

class Rva00259CD0Dispatch
{
public:
	void apply(Coord3D_259CD0 *subject);

private:
	unsigned char pad[4];
	BfmeThingCOF *thing;
};

// ?apply@Rva00259CD0Dispatch@@QAEXPAUCoord3D_259CD0@@@Z
void Rva00259CD0Dispatch::apply(Coord3D_259CD0 *subject)
{
	if (g_bfmeModeAZC->mode == 1)
		return;

	BfmeThingCOF *object = thing;
	g_bfmeModeAZC->bfmeStopAZC(1);
	if (object->containedBy != 0)
	{
		Region3D_259CD0 extent;
		TheTerrainLogic->getExtentIncludingBorder(&extent);
		Coord3D_259CD0 point;
		point.x = (extent.lo.x + extent.hi.x) * g_bfmeK1253;
		point.y = (extent.lo.y + extent.hi.y) * g_bfmeK1253;
		point.z = subject->z;
		BfmeThingCOF *containedBy = object->containedBy;
		if (containedBy != 0 && !containedBy->bfmeAskCOF())
			containedBy->bfmeRunCOF(&point, 0, 0, 0);
	}
}
