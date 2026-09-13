// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

class BannerCarrierString
{
	void *m_data;
public:
	~BannerCarrierString();
};

class BannerCarrierObjectName
{
	BannerCarrierString m_name;
	unsigned char m_pad[0x2c];
	BannerCarrierString m_templateName;
};

class BannerCarrierUpgrade
{
public:
	~BannerCarrierUpgrade();
};

class BannerCarrierUpdateModuleDataBase
{
public:
	virtual ~BannerCarrierUpdateModuleDataBase() {}
private:
	unsigned char m_pad[0x14];
};

class BannerCarrierUpdateModuleData : public BannerCarrierUpdateModuleDataBase
{
public:
	virtual ~BannerCarrierUpdateModuleData();
private:
	std::vector<BannerCarrierObjectName *> m_objectNames;
	std::vector<BannerCarrierUpgrade *> m_upgrades;
};

// ??1BannerCarrierUpdateModuleData@@UAE@XZ
BannerCarrierUpdateModuleData::~BannerCarrierUpdateModuleData()
{
	for (unsigned int i = 0; i < m_objectNames.size(); ++i)
		delete m_objectNames[i];
	m_objectNames.clear();

	for (unsigned int i = 0; i < m_upgrades.size(); ++i)
		delete m_upgrades[i];
	m_upgrades.clear();
}
