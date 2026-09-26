// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: EmotionTrackerUpdate module-data constructor. The exact named
// friend_newModuleData factory and destructor establish the class identity;
// the destructor fixes four owned handles at +10..+1C and a pointer vector at
// +30.

#include <bitset>
#include <vector>

class EmotionTrackerUpdateEntry;

class KindOfMask
{
public:
	KindOfMask() {}
private:
	std::bitset<181> m_bits;
};

extern const KindOfMask KINDOFMASK_NONE;

class EmotionTrackerUpdateName
{
public:
	EmotionTrackerUpdateName();
	~EmotionTrackerUpdateName();
	void setPolicies(KindOfMask required, KindOfMask excluded);
private:
	int m_handle;
};

class __declspec(novtable) UpdateModuleData
{
public:
	virtual ~UpdateModuleData();
private:
	unsigned int m_value04;
};

class EmotionTrackerUpdateModuleData : public UpdateModuleData
{
public:
	EmotionTrackerUpdateModuleData();
	virtual ~EmotionTrackerUpdateModuleData();
private:
	unsigned int m_value08;
	unsigned int m_value0C;
	EmotionTrackerUpdateName m_name0;
	EmotionTrackerUpdateName m_name1;
	EmotionTrackerUpdateName m_name2;
	EmotionTrackerUpdateName m_name3;
	unsigned int m_value20;
	unsigned int m_value24;
	unsigned int m_value28;
	unsigned char m_flag2C;
	unsigned char m_pad2D[3];
	std::vector<EmotionTrackerUpdateEntry *> m_entries;
};

// ??0EmotionTrackerUpdateModuleData@@QAE@XZ
EmotionTrackerUpdateModuleData::EmotionTrackerUpdateModuleData()
	: m_value08(0),
	  m_value0C(0),
	  m_value20(0),
	  m_value24(0),
	  m_value28(0),
	  m_flag2C(0)
{
	m_name0.setPolicies(KINDOFMASK_NONE, KINDOFMASK_NONE);
	m_name1.setPolicies(KINDOFMASK_NONE, KINDOFMASK_NONE);
	m_name2.setPolicies(KINDOFMASK_NONE, KINDOFMASK_NONE);
	m_name3.setPolicies(KINDOFMASK_NONE, KINDOFMASK_NONE);
}
