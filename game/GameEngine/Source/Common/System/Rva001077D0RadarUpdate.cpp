// ?update@Rva001077D0Radar@@QAEXXZ
// Byte-exact BFME Radar update view for retail 0x001077D0.
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
	__forceinline Rva001077D0Reference *get() const
	{
		return pointer;
	}

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

class GameLogic;
extern GameLogic *TheGameLogic;

// TU-local field view of the retail global at 0x012F0898; the global itself is
// declared with its real type (GameLogic *) so the linked build has one symbol.
static inline Rva001077D0GameLogic *g_rva001077D0GameLogic()
{
	return (Rva001077D0GameLogic *)TheGameLogic;
}

// Retail 0x012F1464 is EA's GameClient *TheGameClient, defined once in
// game/GameEngine/Source/GameClient/GameClient.cpp.  Rva001077D0FrameSource is
// a TU-local view of that object reached through the canonical global.
class GameClient;
extern GameClient *TheGameClient;
static inline Rva001077D0FrameSource *rva001077D0FrameSource( void )
{
	return (Rva001077D0FrameSource *)TheGameClient;
}
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

void Rva001077D0Radar::update()
{
	unsigned currentFrame =
		rva001077D0FrameSource()->getFrame();
	dirty = 1;

	for (int i = 0; i < 64; ++i)
	{
		Rva001077D0RadarEvent &event = events[i];
		if (event.active == 1 && event.createFrame != 0
			&& currentFrame > event.dieFrame)
		{
			Rva001077D0Reference *reference = event.reference.get();
			event.active = 0;
			if (reference)
				event.reference.clear();
		}
	}

	if (terrainRefreshFrame != 0
		&& (float)(g_rva001077D0GameLogic()->frame - terrainRefreshFrame)
			> 15.0f) // Retail 0x010888F0: __real@41700000.
	{
		Rva001077D0RadarPrimary *primary =
			(Rva001077D0RadarPrimary *)((char *)this - 4);
		primary->refreshTerrain(
			reinterpret_cast<Rva001077D0TerrainLogic *>(TheTerrainLogic));
	}
}
