// ?onUpgradeCompleted@Player@@QAEXPBVUpgradeTemplate@@@Z
// partial score=0.68 date=2026-08-31
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#define Player ZHPlayer
#include "PreRTS.h"
#include "Common/Team.h"
#include "GameLogic/Object.h"
#undef Player

#include <list>

class UpgradeTemplate;

class BfmeTeamInstanceLink
{
public:
	Team *_bfme_nextInInstanceList();
};

struct BfmeTeamPrototypeInstances
{
	unsigned char m_unmodelled[0x274];
	Team *m_head;
};

struct BfmeTeamMembers
{
	unsigned char m_unmodelled[0x0C];
	Object *m_head;
};

typedef _STL::list<TeamPrototype *> BfmePlayerTeamList;

class Player
{
public:
	void onUpgradeCompleted(const UpgradeTemplate *upgradeTemplate);

private:
	unsigned char m_unmodelled[0x288];
	BfmePlayerTeamList m_playerTeamPrototypes;
};

void Player::onUpgradeCompleted(const UpgradeTemplate *)
{
	for (BfmePlayerTeamList::iterator it = m_playerTeamPrototypes.begin();
		it != m_playerTeamPrototypes.end(); ++it)
	{
		Team *team = ((BfmeTeamPrototypeInstances *)*it)->m_head;
		while (team)
		{
			DLINK_ITERATOR<Object> objects(
				((BfmeTeamMembers *)team)->m_head, Object::dlink_next_TeamMemberList);
			while (!objects.done())
			{
				objects.cur()->updateUpgradeModules();
				objects.advance();
			}
			team = ((BfmeTeamInstanceLink *)team)->_bfme_nextInInstanceList();
		}
	}
}
