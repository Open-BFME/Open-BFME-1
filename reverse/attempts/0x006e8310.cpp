// ?d_006e8310@@YAXXZ
// partial score=0.35 date=2026-09-10
// Research reconstruction for retail RVA 0x006E8310.
// The owner is the W3DDisplay update slot's hidden transition state at
// W3DDisplay + 0x278.  The public source headers do not expose this BFME
// state or the two display virtual signatures used by the retail body.

struct Rva006E8310Rgb
{
	float red;
	float green;
	float blue;
};

struct Rva006E8310TerrainLighting
{
	Rva006E8310Rgb ambient;
	Rva006E8310Rgb diffuse;
	Rva006E8310Rgb lightPos;
};

struct Rva006E8310TransitionState
{
	int mode;
	int startFrame;
	float duration;
	float red;
	float green;
	float blue;
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
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot2a(); virtual void slot2b(); virtual void slot2c();
	virtual void slot2d(); virtual void slot2e(); virtual void slot2f();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39();
	virtual void setLighting(int channel, float red, float green, float blue);
	virtual void setObjectLighting(int channel, float red, float green, float blue);
};

class Rva006E8310TerrainRenderObject
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
	virtual void slot0a();
	virtual void slot0b();
	virtual void slot0c();
	virtual void slot0d();
	virtual void slot0e();
	virtual void slot0f();
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
	virtual void slot1a();
	virtual void slot1b();
	virtual void slot1c();
	virtual void slot1d();
	virtual void slot1e();
	virtual void slot1f();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot2a();
	virtual void slot2b();
	virtual void slot2c();
	virtual void slot2d();
	virtual void slot2e();
	virtual void slot2f();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot3a();
	virtual void slot3b();
	virtual void slot3c();
	virtual void slot3d();
	virtual void slot3e();
	virtual void slot3f();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot4a();
	virtual void slot4b();
	virtual void slot4c();
	virtual void slot4d();
	virtual void slot4e();
	virtual void slot4f();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot5a();
	virtual void slot5b();
	virtual void slot5c();
	virtual void slot5d();
	virtual void slot5e();
	virtual void slot5f();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot6a();
	virtual void slot6b();
	virtual void slot6c();
	virtual void slot6d();
	virtual void slot6e();
	virtual void slot6f();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot7a();
	virtual void slot7b();
	virtual void slot7c();
	virtual void slot7d();
	virtual void slot7e();
	virtual void slot7f();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void slot88();
	virtual void slot89();
	virtual void slot8a();
	virtual void slot8b();
	virtual void slot8c();
	virtual void slot8d();
	virtual void slot8e();
	virtual void slot8f();
	virtual void slot90();
	virtual void slot91();
	virtual void slot92();
	virtual void slot93();
	virtual void slot94();
	virtual void slot95();
	virtual void slot96();
	virtual void slot97();
	virtual void slot98();
	virtual void slot99();
	virtual void slot9a();
	virtual void slot9b();
	virtual void slot9c();
	virtual void slot9d();
	virtual void slot9e();
	virtual void slot9f();
	virtual void slota0();
	virtual void slota1();
	virtual void slota2();
	virtual void slota3();
	virtual void slota4();
	virtual void slota5();
	virtual void slota6();
	virtual void slota7();
	virtual void slota8();
	virtual void slota9();
	virtual void slotaa();
	virtual void slotab();
	virtual void slotac();
	virtual void slotad();
	virtual void slotae();
	virtual void slotaf();
	virtual void slotb0();
	virtual void slotb1();
	virtual void slotb2();
	virtual void slotb3();
	virtual void slotb4();
	virtual void slotb5();
	virtual void slotb6();
	virtual void slotb7();
	virtual void slotb8();
	virtual void slotb9();
	virtual void slotba();
	virtual void slotbb();
	virtual void slotbc();
	virtual void slotbd();
	virtual void slotbe();
	virtual void slotbf();
	virtual void slotc0();
	virtual void slotc1();
	virtual void slotc2();
	virtual void slotc3();
	virtual void slotc4();
	virtual void slotc5();
	virtual void slotc6();
	virtual void slotc7();
	virtual void slotc8();
	virtual void slotc9();
	virtual void slotca();
	virtual void slotcb();
	virtual void slotcc();
	virtual void slotcd();
	virtual void slotce();
	virtual void slotcf();
	virtual void slotd0();
	virtual void slotd1();
	virtual void slotd2();
	virtual void slotd3();
	virtual void slotd4();
	virtual void slotd5();
	virtual void slotd6();
	virtual void slotd7();
	virtual void slotd8();
	virtual void slotd9();
	virtual void slotda();
	virtual void slotdb();
	virtual void slotdc();
	virtual void slotdd();
	virtual void slotde();
	virtual void slotdf();
	virtual void slote0();
	virtual void slote1();
	virtual void slote2();
	virtual void slote3();
	virtual void slote4();
	virtual void slote5();
	virtual void slote6();
	virtual void slote7();
	virtual void slote8();
	virtual void slote9();
	virtual void slot ea();
	virtual void slot eb();
	virtual void slot ec();
	virtual void slot ed();
	virtual void slot ee();
	virtual void slot ef();
	virtual void slot f0();
	virtual void slot f1();
	virtual void slot f2();
	virtual void slot f3();
	virtual void slot f4();
	virtual void slot f5();
	virtual void slot f6();
	virtual void slot f7();
	virtual void slot f8();
	virtual void slot f9();
	virtual void slot fa();
	virtual void slot fb();
	virtual void slot fc();
	virtual void slot fd();
	virtual void slot fe();
	virtual void slot ff();
	virtual void setTimeOfDay(int value);
};

extern Rva006E8310GameClient *TheGameClient;
extern Rva006E8310Display *TheDisplay;
extern Rva006E8310TerrainRenderObject *TheTerrainRenderObject;
extern unsigned char *TheWritableGlobalData;
extern const float BfmeZeroRange;
extern const float g_bfmeDefaultBU;
extern const float g_bfmeUint32Scale;
extern const float g_rva006E8310FrameScale;

static Rva006E8310TerrainLighting *lightingAt(unsigned char *base,
	int timeOfDay, unsigned int offset)
{
	return reinterpret_cast<Rva006E8310TerrainLighting *>(
		base + offset + static_cast<unsigned int>(timeOfDay) * 0x6c);
}

void Rva006E8310TransitionState::update(float frameScale)
{
	if (duration <= BfmeZeroRange)
		return;

	int elapsed = TheGameClient->getFrame() - startFrame;
	float fraction = static_cast<float>(elapsed < 0 ?
		elapsed + 0x100000000UL : elapsed) * g_rva006E8310FrameScale / duration;
	if (fraction >= g_bfmeDefaultBU)
	{
		duration = 0.0f;
		return;
	}

	float from = g_bfmeDefaultBU - fraction;
	float to = fraction;
	if (mode == 1)
	{
		float swap = from;
		from = to;
		to = swap;
	}

	unsigned char *global = TheWritableGlobalData;
	const int timeOfDay = *reinterpret_cast<int *>(global + 0x218);
	Rva006E8310TerrainLighting *terrain = lightingAt(global, timeOfDay, 0x224);
	Rva006E8310TerrainLighting *objects = lightingAt(global, timeOfDay, 0x4ac);
	Rva006E8310TerrainLighting *active = lightingAt(global, timeOfDay, 0x734);

	for (int i = 0; i < 3; ++i)
	{
		const Rva006E8310TerrainLighting &a = terrain[i];
		const Rva006E8310TerrainLighting &b = objects[i];
		const Rva006E8310TerrainLighting &c = active[i];
		const float red = from * this->red + to * a.diffuse.red;
		const float green = from * this->green + to * a.diffuse.green;
		const float blue = from * this->blue + to * a.diffuse.blue;

		// Retail sends both interpolated terrain/object channels through the
		// adjacent display virtuals (+0xa0 and +0xa4), then stores the third
		// channel in GlobalData's active light-position block.
		TheDisplay->setLighting(0,
			from * a.diffuse.red + to * b.diffuse.red,
			from * a.diffuse.green + to * b.diffuse.green,
			from * a.diffuse.blue + to * b.diffuse.blue);
		TheDisplay->setObjectLighting(0,
			from * a.diffuse.red + to * c.diffuse.red,
			from * a.diffuse.green + to * c.diffuse.green,
			from * a.diffuse.blue + to * c.diffuse.blue);

		Rva006E8310Rgb *current = reinterpret_cast<Rva006E8310Rgb *>(global + 0x9e0);
		current[i].red = red;
		current[i].green = green;
		current[i].blue = blue;
	}

	if (TheTerrainRenderObject != 0)
		TheTerrainRenderObject->setTimeOfDay(*reinterpret_cast<int *>(global + 0x218));
}
