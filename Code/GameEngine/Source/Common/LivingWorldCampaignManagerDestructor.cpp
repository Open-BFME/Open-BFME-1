// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LivingWorldCampaignManager's virtual destructor, retail
// 0x003B7D30, 109 bytes. Four AsciiString members and the eight-byte gap
// between the third and fourth member reproduce the retail unwind states.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
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
	char m_bfmePad10[8];
	AsciiString m_name18;
};

// ??1LivingWorldCampaignManager@@UAE@XZ
LivingWorldCampaignManager::~LivingWorldCampaignManager()
{
}
