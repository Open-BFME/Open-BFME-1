// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ??0Campaign@@QAE@XZ: game/GameEngine/Source/GameClient/System/CampaignManager.cpp

#include <list>

typedef int Int;

#include "ascii_string.h"

class Mission;
typedef _STL::list<Mission *> MissionList;

class Mission
{
public:
	void deleteInstance(void);
};

class Campaign
{
public:
	Campaign(void);
	virtual ~Campaign() {}

private:
	AsciiString m_name;
	AsciiString m_firstMission;
	AsciiString m_campaignNameLabel;
	MissionList m_missions;
	AsciiString m_finalMovieName;
};

Campaign::Campaign(void)
{
	m_missions.clear();
	m_firstMission.clear();
	m_name.clear();
	m_finalMovieName.clear();
}
