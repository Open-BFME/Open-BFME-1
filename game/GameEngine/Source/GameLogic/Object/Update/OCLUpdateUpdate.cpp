// ?update@OCLUpdate@@UAE?AW4UpdateSleepTime@@XZ
// Open-BFME5: OCLUpdate::update, retail 0x00298BB0, 239 bytes.
//
// The landed OCLUpdate constructor at 0x00298960 installs the secondary
// UpdateModuleInterface vtable 0x010C02A0 at this+0x10. Its first slot is ILT
// 0x00035B2A, which routes to this body. This independently fixes both the
// OCLUpdate owner and the virtual update signature.
//
// BFME's body is the pre-faction-update implementation: it gates on the next
// creation frame and under-construction status, schedules the next interval,
// optionally clips the creation point to the terrain edge, then dispatches the
// OCL. The two inlined scheduling sites need different alias visibility. The
// ordinary first-use helper lets the caller cleanup precede the timer store;
// the continuing path uses volatile stores so the following module-data load
// remains after both stores. Both helpers are zero-overhead real C++.
// cl: /DNDEBUG /MD

typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class GameLogic
{
public:
	char m_pad[0x3c];
	UnsignedInt m_frame;
	UnsignedInt getFrame() const { return m_frame; }
};

extern GameLogic *TheBfmeGameLogic;
extern char g_bfmeFmt1051B[];
int GetGameLogicRandomValue(int, int, char *, int);

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
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual Coord3D findClosestEdgePoint(const Coord3D *) const;
};

extern TerrainLogic *TheTerrainLogic;

class BfmeThingFB
{
public:
	// Existing byte-matched facade for BFME's OCL-nugget traversal at
	// 0x001D67C0. Its four-argument ABI is the one this retail caller uses.
	void bfmeTellFB(void *, void *, void *, void *);
};

class OCLUpdateModuleData
{
public:
	char m_pad00[8];
	BfmeThingFB *m_ocl;
	UnsignedInt m_minDelay;
	UnsignedInt m_maxDelay;
	unsigned char m_isCreateAtEdge;
};

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_position;
	char m_pad44[0x4c];
	unsigned char m_statusBits;

	Coord3D *getPosition() { return &m_position; }
};

class OCLUpdate
{
public:
	virtual UpdateSleepTime update();

protected:
	__forceinline void setNextCreationFrame(char *);
	__forceinline void setNextCreationFrameOrdered(char *);
	__forceinline unsigned char shouldCreate();
	__forceinline OCLUpdateModuleData *getOCLUpdateModuleData();
	__forceinline Object *getObject();

private:
	char m_pad04[0xc];
	UnsignedInt m_nextCreationFrame;
	UnsignedInt m_timerStartedFrame;
};

__forceinline void OCLUpdate::setNextCreationFrame(char *file)
{
	UnsignedInt delay = GetGameLogicRandomValue(getOCLUpdateModuleData()->m_minDelay,
		getOCLUpdateModuleData()->m_maxDelay,
		file, 0x6a);
	GameLogic *logic = TheBfmeGameLogic;
	UnsignedInt frame = logic->m_frame;
	m_timerStartedFrame = frame;
	m_nextCreationFrame = frame + delay;
}

// ?setNextCreationFrameOrdered@OCLUpdate@@ absent-from-retail
__forceinline void OCLUpdate::setNextCreationFrameOrdered(char *file)
{
	UnsignedInt delay = GetGameLogicRandomValue(getOCLUpdateModuleData()->m_minDelay,
		getOCLUpdateModuleData()->m_maxDelay,
		file, 0x6a);
	GameLogic *logic = TheBfmeGameLogic;
	UnsignedInt frame = logic->m_frame;
	*(volatile UnsignedInt *)((char *)this + 0x14) = frame;
	*(volatile UnsignedInt *)((char *)this + 0x10) = frame + delay;
}

// ?getOCLUpdateModuleData@OCLUpdate@@ absent-from-retail
__forceinline OCLUpdateModuleData *OCLUpdate::getOCLUpdateModuleData()
{
	return *(OCLUpdateModuleData **)((const char *)this - 0xc);
}

// ?getObject@OCLUpdate@@ absent-from-retail
__forceinline Object *OCLUpdate::getObject()
{
	return *(Object **)((const char *)this - 8);
}

__forceinline unsigned char OCLUpdate::shouldCreate()
{
	return TheBfmeGameLogic->getFrame() >= m_nextCreationFrame;
}

UpdateSleepTime OCLUpdate::update()
{
	Coord3D creationCoord;
	if (!shouldCreate())
		return UPDATE_SLEEP_NONE;
	if ((getObject()->m_statusBits & 4) != 0)
		return UPDATE_SLEEP_NONE;
	if (*(volatile UnsignedInt *)((const char *)this + 0x10) == 0)
	{
		setNextCreationFrame(g_bfmeFmt1051B);
		return UPDATE_SLEEP_NONE;
	}
	setNextCreationFrameOrdered(g_bfmeFmt1051B);
	if ((*(OCLUpdateModuleData *volatile *)((const char *)this - 0xc))->m_isCreateAtEdge)
		creationCoord = TheTerrainLogic->findClosestEdgePoint(getObject()->getPosition());
	else
		creationCoord = *getObject()->getPosition();

	if (getOCLUpdateModuleData()->m_ocl != 0)
	{
		Object *obj = getObject();
		getOCLUpdateModuleData()->m_ocl->bfmeTellFB(obj, &creationCoord, obj->getPosition(), 0);
	}

	return UPDATE_SLEEP_NONE;
}
