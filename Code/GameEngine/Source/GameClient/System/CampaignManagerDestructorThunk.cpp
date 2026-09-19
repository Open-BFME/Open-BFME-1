// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ??1CampaignManager@@QAE@XZ: Code/GameEngine/Source/GameClient/System/CampaignManager.cpp
// Open-BFME5: CampaignManager destructor converted from the retail SEH body.

#include <list>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/CampaignManager.h
class Campaign
{
public:
	virtual ~Campaign();
	void deleteInstance() { delete this; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	~Snapshot() { }

protected:
	virtual void crc() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/CampaignManager.h
class CampaignManager : public Snapshot
{
public:
	~CampaignManager();

private:
	std::list<Campaign *> m_campaignList;
	Campaign *m_currentCampaign;
	Campaign *m_currentMission;

protected:
	virtual void crc() { }
};

// ??1CampaignManager@@QAE@XZ
CampaignManager::~CampaignManager()
{
	m_currentCampaign = NULL;
	m_currentMission = NULL;

	std::list<Campaign *>::iterator it = m_campaignList.begin();
	while (it != m_campaignList.end())
	{
		Campaign *campaign = *it;
		it = m_campaignList.erase(it);
		if (campaign)
			campaign->deleteInstance();
	}
}
