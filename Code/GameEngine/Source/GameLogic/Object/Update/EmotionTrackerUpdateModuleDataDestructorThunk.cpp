// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: clean C++ lift of the retail module-data destructor.

#include <vector>

class EmotionTrackerUpdateName
{
public:
	~EmotionTrackerUpdateName();

private:
	char *m_data;
};

class EmotionTrackerUpdateEntry
{
public:
	~EmotionTrackerUpdateEntry();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleData
{
public:
	virtual ~UpdateModuleData() {}

private:
	unsigned char m_data[12];
};

class EmotionTrackerUpdateModuleData : public UpdateModuleData
{
public:
	virtual ~EmotionTrackerUpdateModuleData();

private:
	EmotionTrackerUpdateName m_name0;
	EmotionTrackerUpdateName m_name1;
	EmotionTrackerUpdateName m_name2;
	EmotionTrackerUpdateName m_name3;
	unsigned char m_data[16];
	std::vector<EmotionTrackerUpdateEntry *> m_entries;
};

// ??1EmotionTrackerUpdateModuleData@@UAE@XZ
EmotionTrackerUpdateModuleData::~EmotionTrackerUpdateModuleData()
{
	for (std::vector<EmotionTrackerUpdateEntry *>::iterator it = m_entries.begin(); it != m_entries.end(); ++it) {
		delete *it;
	}
}
