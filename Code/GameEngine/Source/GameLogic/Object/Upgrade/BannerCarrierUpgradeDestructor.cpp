// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

class BannerCarrierString
{
public:
	~BannerCarrierString();
};

class BannerCarrierUpgrade
{
public:
	~BannerCarrierUpgrade();

private:
	unsigned int m_unknown;
	std::vector<BannerCarrierString *> m_strings;
};

// ??1BannerCarrierUpgrade@@QAE@XZ
BannerCarrierUpgrade::~BannerCarrierUpgrade()
{
	for (unsigned int i = 0; i < m_strings.size(); ++i)
		delete m_strings[i];
	m_strings.clear();
}
