// ?update@Rva001077D0Radar@@QAEXXZ
// partial score=0.96 date=2026-08-31
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva001077D0FrameSource
{
public:
	virtual void unused00(); virtual void unused01();
	virtual void unused02(); virtual void unused03();
	virtual void unused04(); virtual void unused05();
	virtual void unused06(); virtual void unused07();
	virtual void unused08(); virtual void unused09();
	virtual void unused10(); virtual void unused11();
	virtual void unused12(); virtual void unused13();
	virtual void unused14(); virtual void unused15();
	virtual void unused16(); virtual void unused17();
	virtual void unused18(); virtual void unused19();
	virtual void unused20(); virtual void unused21();
	virtual void unused22(); virtual void unused23();
	virtual void unused24(); virtual void unused25();
	virtual unsigned getFrame();
};

struct Rva001077D0GameLogic
{
	char padding00[0x3c];
	unsigned frame;
};

class Rva001077D0TerrainLogic;

class Rva001077D0Reference
{
public:
	virtual ~Rva001077D0Reference();

	__forceinline void release()
	{
		if (--referenceCount <= 0)
			delete this;
	}

	int referenceCount;
};

class Rva001077D0ReferencePointer
{
public:
	__forceinline void clear()
	{
		if (pointer)
		{
			pointer->release();
			pointer = 0;
		}
	}


private:
	Rva001077D0Reference *pointer;
};

class Rva001077D0RadarPrimary
{
public:
	virtual void unused0(); virtual void unused1();
	virtual void unused2(); virtual void unused3();
	virtual void refreshTerrain(Rva001077D0TerrainLogic *terrain);
};

struct Rva001077D0RadarEvent
{
	unsigned char active;
	char padding01[3];
	unsigned createFrame;
	unsigned dieFrame;
	char padding0c[0x3c];
	Rva001077D0ReferencePointer reference;
	unsigned tail4c;
};

class Rva001077D0Radar
{
public:
	void update();

private:
	char padding00[9];
	unsigned char dirty;
	char padding0a[0x1e];
	Rva001077D0RadarEvent events[64];
	char padding1428[0x3c];
	unsigned terrainRefreshFrame;
};

extern Rva001077D0FrameSource *g_rva001077D0FrameSource;
extern Rva001077D0GameLogic *g_rva001077D0GameLogic;
extern Rva001077D0TerrainLogic *g_rva001077D0TerrainLogic;
extern float g_rva001077D0RefreshDelay;

void Rva001077D0Radar::update()
{
	unsigned currentFrame =
		g_rva001077D0FrameSource->getFrame();
	dirty = 1;

	for (int i = 0; i < 64; ++i)
	{
		Rva001077D0RadarEvent &event = events[i];
		if (event.active == 1 && event.createFrame != 0
			&& currentFrame > event.dieFrame)
		{
			event.active = 0;
			event.reference.clear();
		}
	}

	if (terrainRefreshFrame != 0
		&& (float)(g_rva001077D0GameLogic->frame - terrainRefreshFrame)
			> g_rva001077D0RefreshDelay)
	{
		Rva001077D0RadarPrimary *primary =
			(Rva001077D0RadarPrimary *)((char *)this - 4);
		primary->refreshTerrain(g_rva001077D0TerrainLogic);
	}
}
