// cl: /DNDEBUG /MD /EHsc
//
// RadarUpdate::extendRadar, retail 0x002A03E0. BFME inlines Object's
// setModelConditionState against the flags dword at +0x118 (bit 10) then
// stamps the done-frame as unsigned-int + module-data Real, via __ftol2.

typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum ModelConditionFlagType
{
	MODELCONDITION_RADAR_EXTENDING = 10
};

class ModelConditionFlags
{
public:
	Bool test(ModelConditionFlagType condition) const
	{
		return (m_bits & (1u << condition)) != 0;
	}

	void set(ModelConditionFlagType condition)
	{
		m_bits |= 1u << condition;
	}

private:
	UnsignedInt m_bits;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setModelConditionState(ModelConditionFlagType condition)
	{
		if (!m_modelConditionFlags.test(condition))
		{
			m_modelConditionFlags.set(condition);
			notifyModelConditionChanged();
		}
	}

	void notifyModelConditionChanged();

private:
	unsigned char m_unreconstructed000[0x118];
	ModelConditionFlags m_modelConditionFlags;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

	unsigned char m_pad[0x3C];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadarUpdate.h
struct RadarUpdateModuleData
{
	unsigned char m_unmodelled_00[8];
	Real m_radarExtendTime;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadarUpdate.h
class RadarUpdate
{
public:
	void extendRadar();

private:
	const RadarUpdateModuleData *getRadarUpdateModuleData() const
	{
		return m_moduleData;
	}

	Object *getObject() const { return m_object; }

	unsigned int m_unmodelled_00;
	const RadarUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_unmodelled_0c[0x20 - 0x0c];
	UnsignedInt m_extendDoneFrame;
	Bool m_extendComplete;
	Bool m_radarActive;
};

// ?extendRadar@RadarUpdate@@QAEXXZ
void RadarUpdate::extendRadar()
{
	Object *obj = getObject();
	const RadarUpdateModuleData *modData = getRadarUpdateModuleData();

	obj->setModelConditionState(MODELCONDITION_RADAR_EXTENDING);

	m_extendDoneFrame = TheGameLogic->getFrame() + modData->m_radarExtendTime;
	m_radarActive = true;
}
