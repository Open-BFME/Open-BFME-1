// cl: /DNDEBUG /MD /EHsc

#include <new>
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// Open-BFME5: LivingWorldCampaignManager's copy constructor and virtual
// destructor. Four AsciiString members and the eight-byte gap between the
// third and fourth member reproduce the retail unwind states.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	__forceinline AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString();

private:
	char *m_data;
};

class LivingWorldCampaignManager
{
public:
	virtual ~LivingWorldCampaignManager();

private:
	AsciiString m_name04;
	AsciiString m_name08;
	AsciiString m_name0C;
	int m_field10;
	int m_field14;
	AsciiString m_name18;
	bool m_flag1C;
	bool m_flag1D;
	int m_field20;
	int m_field24;
};

void bfmeEmitLivingWorldCampaignManagerCopy(
		void *storage, const LivingWorldCampaignManager &other)
{
	new (storage) LivingWorldCampaignManager(other);
}

// ??1LivingWorldCampaignManager@@UAE@XZ
LivingWorldCampaignManager::~LivingWorldCampaignManager()
{
}
