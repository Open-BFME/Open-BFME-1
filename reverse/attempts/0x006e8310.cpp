// ?d_006e8310@@YAXXZ
// partial score=0.38 date=2026-09-22
// ?update@Rva006E8310TransitionState@@QAEXXZ
// cl: /DNDEBUG /MD /EHsc

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
	virtual int getFrame();
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
	int startFrame;
	Real duration;
	Real red;
	Real green;
	Real blue;
};

#define TheGameClient (*(Rva006E8310GameClient **)0x012F1464)
#define TheDisplay (*(Rva006E8310Display **)0x012F1270)
#define Rva006E8310GlobalDataPtr (*(Rva006E8310GlobalDataLayout **)0x012ED5C8)
#define TheTerrainRenderObject (*(Rva006C8E00Dispatch **)0x012F7FE0)
#define Rva006E8310Zero (*(const Real *)0x01075350)
#define g_bfmeDefaultBU (*(const Real *)0x01075334)
#define Rva006E8310Uint32Scale (*(const Real *)0x01075358)
#define Rva006E8310FrameScale (*(const Real *)0x012BAA30)

static Rva006E8310TerrainLighting *lightingAt(unsigned char *base,
	int timeOfDay, unsigned int offset)
{
	return reinterpret_cast<Rva006E8310TerrainLighting *>(
		base + offset + static_cast<unsigned int>(timeOfDay) * 0x6c);
}

void Rva006E8310TransitionState::update()
{
	if (Rva006E8310Zero < duration)
	{

	int elapsed = TheGameClient->getFrame() - startFrame;
	Real fraction = static_cast<Real>(elapsed);
	if (elapsed < 0)
		fraction += Rva006E8310Uint32Scale;
	fraction *= Rva006E8310FrameScale;
	fraction /= duration;
	if (fraction >= g_bfmeDefaultBU)
	{
		duration = Rva006E8310Zero;
		return;
	}

	Real from = g_bfmeDefaultBU - fraction;
	Real to = fraction;
	if (mode == 1)
	{
		Real swap = from;
		from = to;
		to = swap;
	}

	unsigned char *global = reinterpret_cast<unsigned char *>(Rva006E8310GlobalDataPtr);
	int timeOfDay = *reinterpret_cast<int *>(global + 0x218);
	Rva006E8310TerrainLighting *terrain = lightingAt(global, timeOfDay, 0x224);
	Rva006E8310TerrainLighting *objects = lightingAt(global, timeOfDay, 0x4ac);
	Rva006E8310TerrainLighting *active = lightingAt(global, timeOfDay, 0x734);

	for (int i = 0; i < 3; ++i)
	{
		const Rva006E8310TerrainLighting &a = terrain[i];
		const Rva006E8310TerrainLighting &b = objects[i];
		const Rva006E8310TerrainLighting &c = active[i];
		const Real redValue = from * red + to * a.diffuse.red;
		const Real greenValue = from * green + to * a.diffuse.green;
		const Real blueValue = from * blue + to * a.diffuse.blue;

		TheDisplay->setLighting(0,
			from * a.diffuse.red + to * b.diffuse.red,
			from * a.diffuse.green + to * b.diffuse.green,
			from * a.diffuse.blue + to * b.diffuse.blue);
		TheDisplay->setObjectLighting(0,
			from * a.diffuse.red + to * c.diffuse.red,
			from * a.diffuse.green + to * c.diffuse.green,
			from * a.diffuse.blue + to * c.diffuse.blue);

		Rva006E8310Rgb *current = reinterpret_cast<Rva006E8310Rgb *>(global + 0x9e0);
		current[i].red = redValue;
		current[i].green = greenValue;
		current[i].blue = blueValue;
	}

	if (TheTerrainRenderObject != 0)
		TheTerrainRenderObject->invoke(timeOfDay);
	}
}
