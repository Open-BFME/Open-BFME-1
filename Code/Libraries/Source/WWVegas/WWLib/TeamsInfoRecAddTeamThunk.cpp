// readable body of ?addTeam@TeamsInfoRec@@QAEXPBVDict@@@Z: Code/GameEngine/Source/GameLogic/Map/SidesList.cpp
// readable body of ?removeTeam@TeamsInfoRec@@QAEXH@Z: Code/GameEngine/Source/GameLogic/Map/SidesList.cpp
class Dict;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/SidesList.h
class TeamsInfoRec
{
public:
    void addTeam(const Dict *);
};

class TeamsInfoRecAddTeamShim
{
public:
    void add(const Dict *dict);
};

void TeamsInfoRec::addTeam(const Dict *dict)
{
    ((TeamsInfoRecAddTeamShim *)this)->add(dict);
}
