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

// ILT 0x4A66A -> 0x003D0FA0, the matched 45-byte Rva003D0FA0::run
// (Y1MemberVectorForEach.cpp), called on TheLargeGroupAudio with this update.
class Y1ForEachArg;
class Rva003D0FA0
{
public:
	void run(Y1ForEachArg *arg);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class UpdateModule
{
protected:
	void setWakeFrame(Object *object, UpdateSleepTime wakeDelay);
};


class LargeGroupAudio;
extern LargeGroupAudio *TheLargeGroupAudio;

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
	reinterpret_cast<Rva003D0FA0 *>(TheLargeGroupAudio)->run(reinterpret_cast<Y1ForEachArg *>(this));

	Object *object = m_object;
	LargeGroupAudioUpdateModuleData *moduleData = m_moduleData;
	int wakeDelay = GetGameLogicRandomValue(0, moduleData->m_a, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\LargeGroupAudioUpdate.cpp", 0x54) +
		moduleData->m_b + 1;
	setWakeFrame(object, static_cast<UpdateSleepTime>(wakeDelay));

	m_position = m_object->m_position;
	memcpy(m_conditionFlags, m_object->m_conditionFlags, sizeof(m_conditionFlags));
}
