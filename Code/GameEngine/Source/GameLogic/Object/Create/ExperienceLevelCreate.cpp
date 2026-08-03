// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ExperienceLevelCreateModuleData default ctor.

class ExperienceLevelCreateModuleData
{
public:
	ExperienceLevelCreateModuleData();
	virtual ~ExperienceLevelCreateModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_08;
	unsigned char m_0c;
};

// ??0ExperienceLevelCreateModuleData@@QAE@XZ
ExperienceLevelCreateModuleData::ExperienceLevelCreateModuleData()
{
	m_08 = 0xffffffff;
	m_0c = 0;
}