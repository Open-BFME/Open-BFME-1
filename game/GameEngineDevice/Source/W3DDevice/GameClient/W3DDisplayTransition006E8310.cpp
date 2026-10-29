// cl: /DNDEBUG /MD /EHsc
// Observed transition state at W3DDisplay +0x278.
// Evidence: targets/game/reverse/identity_evidence/006e8310-transition.md

typedef float Real;

struct Rva006E8310Rgb
{
	Real red;
	Real green;
	Real blue;
};

struct Rva006E8310TerrainLighting
{
	Rva006E8310Rgb ambient;
	Rva006E8310Rgb diffuse;
	Rva006E8310Rgb lightPos;
};

class Rva006E8310GlobalDataLayout
{
public:
	unsigned char pad000[0x218];
	int timeOfDay;
	unsigned char pad21c[0x224 - 0x21c];
	Rva006E8310TerrainLighting terrain[18];
	Rva006E8310TerrainLighting objects[18];
	Rva006E8310TerrainLighting active[18];
	unsigned char pad9bc[0x9e0 - 0x9bc];
	Rva006E8310Rgb current[3];
};

class Rva006E8310GameClient
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot0a(); virtual void slot0b();
	virtual void slot0c(); virtual void slot0d(); virtual void slot0e();
	virtual void slot0f(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19();
	virtual unsigned int getFrame();
};

class Rva006E8310Display
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot0a(); virtual void slot0b();
	virtual void slot0c(); virtual void slot0d(); virtual void slot0e();
	virtual void slot0f(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1a();
	virtual void slot1b(); virtual void slot1c(); virtual void slot1d();
	virtual void slot1e(); virtual void slot1f(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27();
	virtual void setLighting(int channel, Real red, Real green, Real blue);
	virtual void setObjectLighting(int channel, Real red, Real green, Real blue);
};

class Rva006C8E00Dispatch
{
public:
	void invoke(int value);
};

class Rva006E8310TransitionState
{
public:
	void update();

	int mode;
	unsigned int startFrame;
	Real duration;
	Real red;
	Real green;
	Real blue;
};

class GameClient;
class Display;
class GlobalData;
class BaseHeightMapRenderObjClass;

extern GameClient *TheGameClient;
extern Display *TheDisplay;
extern GlobalData *TheWritableGlobalData;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern const Real g_bfmeZeroCY;
extern Real g_bfmeDefaultBU;
Real g_Va012BAA30 = 0.033333335f;

static Rva006E8310TerrainLighting *lightingAt(unsigned char *base,
	int timeOfDay, unsigned int offset)
{
	return reinterpret_cast<Rva006E8310TerrainLighting *>(
		base + offset + static_cast<unsigned int>(timeOfDay) * 0x6c);
}

// ?update@Rva006E8310TransitionState@@QAEXXZ
void Rva006E8310TransitionState::update()
{
	if (duration != g_bfmeZeroCY)
	{
		unsigned int elapsed = reinterpret_cast<Rva006E8310GameClient *>(TheGameClient)->getFrame() - startFrame;
		Real seconds = static_cast<Real>(elapsed) * g_Va012BAA30;
		Real from = seconds / duration;
		if (from > 1.0f)
		{
			duration = 0.0f;
			return;
		}

		Real to = g_bfmeDefaultBU - from;
		if (mode == 1)
		{
			Real swap = to;
			to = from;
			from = swap;
		}

		unsigned char *global = reinterpret_cast<unsigned char *>(TheWritableGlobalData);
		int timeOfDay = *reinterpret_cast<int *>(global + 0x218);
		Rva006E8310TerrainLighting *terrain = lightingAt(global, timeOfDay, 0x224);
		Rva006E8310TerrainLighting *objects = lightingAt(global, timeOfDay, 0x4ac);
		Rva006E8310TerrainLighting *active = lightingAt(global, timeOfDay, 0x734);

		for (int i = 0; i < 3; ++i)
		{
			const Rva006E8310TerrainLighting &a = terrain[i];
			const Rva006E8310TerrainLighting &b = objects[i];
			const Rva006E8310TerrainLighting &c = active[i];
			Rva006E8310Rgb color;
			color.blue = from * a.diffuse.blue + to * blue;
			color.red = from * a.diffuse.red + to * red;
			color.green = from * a.diffuse.green + to * green;
			Rva006E8310Rgb objectColor;
			objectColor.blue = from * b.diffuse.blue + to * blue;
			objectColor.red = from * b.diffuse.red + to * red;
			objectColor.green = from * b.diffuse.green + to * green;
			Rva006E8310Rgb activeColor;
			activeColor.blue = from * c.diffuse.blue + to * blue;
			activeColor.red = from * c.diffuse.red + to * red;
			activeColor.green = from * c.diffuse.green + to * green;
			reinterpret_cast<Rva006E8310Display *>(TheDisplay)->setLighting(i, objectColor.red, objectColor.green, objectColor.blue);
			reinterpret_cast<Rva006E8310Display *>(TheDisplay)->setObjectLighting(i, activeColor.red, activeColor.green, activeColor.blue);
			reinterpret_cast<Rva006E8310GlobalDataLayout *>(TheWritableGlobalData)->current[i] = color;
		}

		if (TheTerrainRenderObject != 0)
			reinterpret_cast<Rva006C8E00Dispatch *>(TheTerrainRenderObject)->invoke(timeOfDay);
	}
}
