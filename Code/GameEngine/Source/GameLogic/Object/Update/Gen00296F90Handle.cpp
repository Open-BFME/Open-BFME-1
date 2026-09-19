// cl: /O2 /Ob2 /GR- /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// BFME LargeGroupAudioUpdate helper at retail 0x00296F90.

#include <string.h>

struct Coord3D
{
	int x;
	int y;
	int z;
};

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_position;
	char m_pad44[0x94 - 0x44];
	unsigned int m_statusFlags;
	char m_pad98[0x110 - 0x98];
	unsigned int m_conditionFlags[10];
};

class LargeGroupAudioUpdateModuleData
{
public:
	char m_pad00[0x14];
	int m_b;
	int m_a;
};

class Gen00296F90;

class Rva004A66AOwner
{
public:
	void registerUpdate(Gen00296F90 *update);
};

class UpdateModule
{
public:
	void setWakeFrame(Object *object, int wakeDelay);
};

extern char g_bfmeFmt1029[];

int GetGameLogicRandomValue(int low, int high, char *file, int line);

class Gen00296F90 : public UpdateModule
{
public:
	void handle();

private:
	char m_pad00[4];
	LargeGroupAudioUpdateModuleData *m_moduleData;
	Object *m_object;
	char m_pad0c[0x24 - 0x0c];
	Coord3D m_position;
	unsigned int m_conditionFlags[10];
	char m_pad58[0x65 - 0x58];
	unsigned char m_initialized;
};

void Gen00296F90::handle()
{
	if (m_initialized != 0)
		return;

	if ((m_object->m_statusFlags & 0x80000) != 0)
		return;

	m_initialized = 1;
	(*reinterpret_cast<Rva004A66AOwner **>(0x012F1044))->registerUpdate(this);

	Object *object = m_object;
	LargeGroupAudioUpdateModuleData *moduleData = m_moduleData;
	int wakeDelay = GetGameLogicRandomValue(0, moduleData->m_a, g_bfmeFmt1029, 0x54) +
		moduleData->m_b + 1;
	setWakeFrame(object, wakeDelay);

	m_position = m_object->m_position;
	memcpy(m_conditionFlags, m_object->m_conditionFlags, sizeof(m_conditionFlags));
}
