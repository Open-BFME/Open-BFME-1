// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00297F10: LifetimeUpdate helper that re-rolls min/max lifetime from
// module data, stores birth/die frames, and wakes the object. CastleBehavior
// at 0x00372BD0 is the sole caller after findModule("LifetimeUpdate").

typedef unsigned int UnsignedInt;

enum UpdateSleepTime { UPDATE_SLEEP_DUMMY };

int GetGameLogicRandomValue(int, int, char *, int);

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class Object;
class ModuleData;

class UpdateModule
{
protected:
	void setWakeFrame(Object *, UpdateSleepTime);

	void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x14];
};

class LifetimeUpdate : public UpdateModule
{
public:
	void resetLifetimeFromModuleData();

private:
	UnsignedInt m_dieFrame;
	UnsignedInt m_birthFrame;
};

class LifetimeUpdateModuleData
{
private:
	unsigned char m_pad00[8];

public:
	UnsignedInt m_minFrames;
	UnsignedInt m_maxFrames;
};

// ?resetLifetimeFromModuleData@LifetimeUpdate@@QAEXXZ
void LifetimeUpdate::resetLifetimeFromModuleData()
{
	const LifetimeUpdateModuleData *data =
		(const LifetimeUpdateModuleData *)m_moduleData;
	UnsignedInt maxFrames = data->m_maxFrames;
	UnsignedInt minFrames = data->m_minFrames;
	UnsignedInt delay = GetGameLogicRandomValue(
		minFrames, maxFrames,
		"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\LifetimeUpdate.cpp",
		116);
	if (delay < 1)
		delay = 1;

	UnsignedInt frame = TheGameLogic->getFrame();
	m_birthFrame = frame;
	m_dieFrame = frame + delay;
	setWakeFrame(m_object, (UpdateSleepTime)delay);
}
