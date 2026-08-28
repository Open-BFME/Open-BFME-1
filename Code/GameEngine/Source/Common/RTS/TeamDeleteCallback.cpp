// cl: /DNDEBUG /MD /EHsc

class Team;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamFactory
{
public:
	void teamAboutToBeDeleted(Team *team);
};

extern TeamFactory *TheTeamFactory;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	virtual ~Team();
};

void deleteTeamCallback(Team *team)
{
	if (team)
	{
		TheTeamFactory->teamAboutToBeDeleted(team);
		delete team;
	}
}
