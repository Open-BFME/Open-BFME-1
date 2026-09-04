// ??0LivingWorldCampaignManager@@QAE@XZ
// partial score=0.93 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// PARTIAL 0x003B7C70 LivingWorldCampaignManager default ctor 144B score~0.93
// Wall: flag stores vs EH-state-3/mov ecx,edi scheduling. Volatile global
// barrier keeps flags ahead of EH but inserts an extra store; member field
// stores want to sit before EH. Size 144 exact with near-miss orderings.
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class AsciiString {
public:
	static const AsciiString TheEmptyString;
	__forceinline AsciiString(void) : m_data(0) {}
	__forceinline AsciiString(const AsciiString &other) {
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&other);
	}
	void clear(void);
	~AsciiString();
private:
	char *m_data;
};

class LivingWorldCampaignManager {
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
	char m_flag1C;
	char m_flag1D;
	int m_field20;
	int m_field24;
};

LivingWorldCampaignManager::LivingWorldCampaignManager(void) :
	m_name04(AsciiString::TheEmptyString),
	m_field10(0),
	m_field14(0),
	m_name18(AsciiString::TheEmptyString)
{
	m_flag1C = 0;
	m_flag1D = 0;
	volatile int *p20 = &m_field20;
	*p20 = 0;
	m_field24 = 0;
	m_name08.clear();
	m_name0C.clear();
}

LivingWorldCampaignManager::~LivingWorldCampaignManager() {}
