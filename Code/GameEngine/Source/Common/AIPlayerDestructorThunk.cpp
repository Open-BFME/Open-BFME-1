// cl: /DNDEBUG /MD /EHsc
// readable body of ??1AIPlayer@@MAE@XZ: Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp

class PlayerController
{
protected:
	virtual ~PlayerController() {}
};

class TeamInQueue;
static void deleteQueue(TeamInQueue *) {}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer : public PlayerController
{
protected:
	virtual ~AIPlayer();
	void removeAll_TeamBuildQueue(void (*)(TeamInQueue *));
	void removeAll_TeamReadyQueue(void (*)(TeamInQueue *));
};

// ??1AIPlayer@@MAE@XZ
AIPlayer::~AIPlayer()
{
	removeAll_TeamBuildQueue(deleteQueue);
	removeAll_TeamReadyQueue(deleteQueue);
}
