// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /game/GameEngine/Include/Precompiled /game/Libraries/Source/WWVegas/WWLib
// readable body of ?countVotesForPlayer@DisconnectManager@@IAEHH@Z: game/GameEngine/Source/GameNetwork/DisconnectManager.cpp

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/DisconnectManager.h
class DisconnectManager
{
protected:
    int countVotesForPlayer(int playerIndex);
};

class DisconnectManagerCountVotesShim
{
public:
    int count(int playerIndex);
};

int DisconnectManager::countVotesForPlayer(int playerIndex)
{
    return ((DisconnectManagerCountVotesShim *)this)->count(playerIndex);
}
