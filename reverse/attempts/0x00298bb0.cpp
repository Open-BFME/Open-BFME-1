// ?d_00298bb0@@YAXXZ
// partial score=0.95 date=2026-09-06
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

class GameLogicFrame
{
public:
	char m_pad[0x3c];
	UnsignedInt m_frame;
	UnsignedInt getFrame() const { return m_frame; }
};

extern GameLogicFrame *TheBfmeGameLogic;
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
	void bfmeTellFB(void *, void *, void *, void *);
};

class OCLModuleData
{
public:
	char m_pad00[8];
	BfmeThingFB *m_ocl;
	UnsignedInt m_minDelay;
	UnsignedInt m_maxDelay;
	unsigned char m_isCreateAtEdge;
};

class OCLInitialData
{
public:
	char m_pad00[8];
	BfmeThingFB *m_ocl;
	UnsignedInt m_minDelay;
	UnsignedInt m_maxDelay;
	unsigned char m_isCreateAtEdge;
};

class OCLLaterData
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
	__forceinline unsigned char shouldCreate();
	__forceinline OCLModuleData *getOCLUpdateModuleData();
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
	GameLogicFrame *logic = TheBfmeGameLogic;
	UnsignedInt frame = logic->m_frame;
	m_timerStartedFrame = frame;
	m_nextCreationFrame = frame + delay;
}

__forceinline OCLModuleData *OCLUpdate::getOCLUpdateModuleData()
{
	return *(OCLModuleData **)((const char *)this - 0xc);
}

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
	setNextCreationFrame(g_bfmeFmt1051B);
	if (getOCLUpdateModuleData()->m_isCreateAtEdge)
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
