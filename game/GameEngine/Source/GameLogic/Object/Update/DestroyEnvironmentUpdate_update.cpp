// cl: /DNDEBUG /MD /EHsc
// DestroyEnvironmentUpdate::update, retail 0x0028D2D0, 155 bytes.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// Constructor 0x0028CD70 installs vtable 0x010BDAB0 at primary+0x10; slot 0
// routes here. `this` is that UpdateModuleInterface address.

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(int id);

	unsigned char m_pad[0x3C];
	unsigned int m_frame;
};

extern GameLogic *TheBfmeGameLogic;
extern const float BfmeShadowScale;

class DestroyEnvironmentUpdateModuleData
{
public:
	void *m_vtable;
	unsigned int m_gap4;
	unsigned int m_startDelay;
	unsigned int m_duration;
};

class BfmeDestroyable
{
public:
	virtual void slot0(int);
	virtual void apply(float value);
};

BfmeDestroyable *bfmeFindModule();
int rva0028D0C0();

class Gen_0028CF50
{
public:
	void bfmeRelease();
};

class DestroyEnvironmentUpdate
{
public:
	virtual UpdateSleepTime update();
};

#pragma comment(linker, "/alternatename:?TheBfmeGameLogic@@3PAVGameLogic@@A=?TheBfmeGameLogic@@3PAURva00367E30Logic@@A")
#pragma comment(linker, "/alternatename:?bfmeFindModule@@YAPAVBfmeDestroyable@@XZ=?d_0028ccd0@@YAXXZ")

// ?update@DestroyEnvironmentUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime DestroyEnvironmentUpdate::update()
{
	unsigned char *self = (unsigned char *)this;
	DestroyEnvironmentUpdateModuleData *data =
		*(DestroyEnvironmentUpdateModuleData **)(self - 0x0C);
	if (data == 0)
	{
		_ReadWriteBarrier();
		return UPDATE_SLEEP_FOREVER;
	}

	unsigned int *objectId = (unsigned int *)(self + 0x14);
	if (*objectId == 0)
	{
		unsigned int spawned = (unsigned int)rva0028D0C0();
		*objectId = spawned;
		if (spawned == 0)
			return UPDATE_SLEEP_FOREVER;
	}

	GameLogic *logic = TheBfmeGameLogic;
	unsigned int elapsed = logic->m_frame - *(unsigned int *)(self + 0x10);
	unsigned int startDelay = data->m_startDelay;
	if (elapsed < startDelay)
		return (UpdateSleepTime)(startDelay - elapsed);

	if (elapsed - startDelay >= data->m_duration)
	{
		((Gen_0028CF50 *)(self - 0x10))->bfmeRelease();
		return UPDATE_SLEEP_NONE;
	}

	Object *object = logic->findObjectByID((int)*objectId);
	if (object != 0)
	{
		BfmeDestroyable *module = bfmeFindModule();
		if (module != 0)
			module->apply(BfmeShadowScale / (float)(unsigned int)data->m_duration);
	}
	return UPDATE_SLEEP_NONE;
}
