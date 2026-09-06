typedef float Real;

Real GetGameClientRandomValueReal(Real low, Real high, char *file, int line);

extern "C" void *bfmeVtERHa[];
extern "C" void *bfmeVtERHb[];

class BfmeThingERH;
class BfmeModuleDataERH;

class BfmeDrawBaseERH
{
public:
	BfmeDrawBaseERH(BfmeThingERH *thing, const BfmeModuleDataERH *data);
	~BfmeDrawBaseERH(void);

	void *m_bfmeVtAERH;
	unsigned char m_bfmeHeadERH[8];
	void *m_bfmeVtBERH;
	unsigned char m_bfmeMidERH[0x3dc];
};

class BfmeDrawERH : public BfmeDrawBaseERH
{
public:
	BfmeDrawERH(BfmeThingERH *thing, const BfmeModuleDataERH *data);

	int m_bfmeCountERH;
	Real m_bfmeValueERH;
};

BfmeDrawERH::BfmeDrawERH(BfmeThingERH *thing, const BfmeModuleDataERH *data)
	: BfmeDrawBaseERH(thing, data)
{
	m_bfmeVtAERH = bfmeVtERHa;
	m_bfmeVtBERH = bfmeVtERHb;
	m_bfmeCountERH = 0;
	m_bfmeValueERH = GetGameClientRandomValueReal(0.0f, 10.0f,
		"F:\\bfme\\Code\\gameenginedevice\\Source\\W3DDevice\\GameClient\\Drawable\\W3DPoliceCarDraw.cpp", 62);
}
