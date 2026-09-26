// cl: /DNDEBUG /MD /EHsc
// LargeGroupAudioUpdate::update, retail 0x002968C0 (274 bytes).
//
// Identity: slot 0 of the update-interface table 0x010BF94C (ILT 0x00037DF8)
// of the class whose matched constructor is 0x00296C80, and the random sleep
// is drawn with LargeGroupAudioUpdate.cpp as its __FILE__.  The interface sits
// at owner+0x10, so the module data and object are this-0x0C and this-0x08.
// While enabled, the module re-registers its owner with the large-group audio
// manager (g_bfmeJ1023) whenever the object's position, model condition flags,
// the 12-byte block at Object+0x90 or its stealthed-and-undetected state
// changed since the last pass, and remembers the new values.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
class Coord3D
{
public:
	Bool IsExactlyEqualTo(const Coord3D &other) const;

	float x;
	float y;
	float z;
};

class ModelConditionFlags
{
public:
	Bool operator!=(const ModelConditionFlags &other) const;

	UnsignedInt m_bits[10];
};

struct Rva001C2920Vec3
{
	Bool notEquals(const Rva001C2920Vec3 *other) const;

	UnsignedInt m_words[3];
};

class Object;

class BFMEObjectStealthQuery
{
public:
	Bool isStealthedAndUndetected(const Object *viewer) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	const ModelConditionFlags &getModelConditionFlags() const { return m_modelConditionFlags; }
	const Rva001C2920Vec3 &getBlock90() const { return m_block90; }

	Bool isStealthedAndUndetected(const Object *viewer) const
	{
		return ((const BFMEObjectStealthQuery *)this)->isStealthedAndUndetected(viewer);
	}

private:
	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0x90 - 0x44];
	Rva001C2920Vec3 m_block90;
	unsigned char m_pad9c[0x110 - 0x9c];
	ModelConditionFlags m_modelConditionFlags;
};

class Y1ForEachArg;

class Rva003D0F60
{
public:
	void run(Y1ForEachArg *arg);
};

class BfmeJ1023;

extern BfmeJ1023 *g_bfmeJ1023;

class ModuleData
{
public:
	virtual ~ModuleData();
};

class LargeGroupAudioUpdateModuleData : public ModuleData
{
public:
	unsigned char m_pad04[0x14 - 0x04];
	Int m_minSleepFrames;
	Int m_sleepVariance;
};

class LGAU_DeepBase
{
public:
	virtual ~LGAU_DeepBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class LGAU_Iface1 { public: virtual void slot(); };

class LGAU_UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class LGAU_UpdateModule : public LGAU_DeepBase,
                          public LGAU_Iface1,
                          public LGAU_UpdateModuleInterface
{
private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class LGAU_Interface { public: virtual void slot(); };

class LargeGroupAudioUpdate : public LGAU_UpdateModule,
                              public LGAU_Interface
{
public:
	virtual UpdateSleepTime update();

private:
	const LargeGroupAudioUpdateModuleData *getLargeGroupAudioUpdateModuleData() const
	{
		return (const LargeGroupAudioUpdateModuleData *)m_moduleData;
	}

	UpdateSleepTime nextSleep(const LargeGroupAudioUpdateModuleData *data) const
	{
		return (UpdateSleepTime)(GetGameLogicRandomValue(0, data->m_sleepVariance,
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\LargeGroupAudioUpdate.cpp",
			0x54) + data->m_minSleepFrames + 1);
	}

	Coord3D m_lastPosition;
	ModelConditionFlags m_lastModelConditionFlags;
	Rva001C2920Vec3 m_lastBlock90;
	Bool m_lastStealthed;
	Bool m_enabled;
};

// ?update@LargeGroupAudioUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime LargeGroupAudioUpdate::update()
{
	const LargeGroupAudioUpdateModuleData *data = getLargeGroupAudioUpdateModuleData();
	if (!m_enabled)
		return nextSleep(data);

	Object *object = m_object;
	if (object == 0)
		return nextSleep(data);

	const Coord3D *position = object->getPosition();
	const ModelConditionFlags &flags = object->getModelConditionFlags();
	const Rva001C2920Vec3 &block90 = object->getBlock90();
	Bool stealthed = object->isStealthedAndUndetected(0);

	if (!position->IsExactlyEqualTo(m_lastPosition)
		|| flags != m_lastModelConditionFlags
		|| block90.notEquals(&m_lastBlock90)
		|| stealthed != m_lastStealthed)
	{
		((Rva003D0F60 *)g_bfmeJ1023)->run((Y1ForEachArg *)this);
		m_lastPosition = *position;
		m_lastModelConditionFlags = flags;
		m_lastBlock90 = block90;
		m_lastStealthed = stealthed;
	}

	return nextSleep(data);
}
