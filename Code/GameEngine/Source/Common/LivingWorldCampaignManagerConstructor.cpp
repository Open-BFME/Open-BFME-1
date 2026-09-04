// cl: /DNDEBUG /MD /EHsc
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class AsciiString
{
public:
	static const AsciiString TheEmptyString;
	__forceinline AsciiString(void) : m_data(0) {}
	__forceinline AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&other);
	}
	void clear(void);
	~AsciiString();

private:
	char *m_data;
};

class LivingWorldFlags
{
public:
	__forceinline LivingWorldFlags(void) : m_flag1C(0), m_flag1D(0) {}

private:
	char m_flag1C;
	char m_flag1D;
};

class LivingWorldCampaignManager
{
public:
	LivingWorldCampaignManager(void);
	virtual ~LivingWorldCampaignManager();

private:
	AsciiString m_name04;
	AsciiString m_name08;
	AsciiString m_name0C;
	int m_field10;
	int m_field14;
	AsciiString m_name18;
	LivingWorldFlags m_flags1C;
	int m_field20;
	int m_field24;
};

LivingWorldCampaignManager::LivingWorldCampaignManager(void) :
	m_name04(AsciiString::TheEmptyString),
	m_field10(0),
	m_field14(0),
	m_name18(AsciiString::TheEmptyString)
{
	m_field24 = m_field20 = 0;
	m_name08.clear();
	m_name0C.clear();
}

LivingWorldCampaignManager::~LivingWorldCampaignManager() {}
