// readable body of ?initializeBonePositions@SpawnPointProductionExitUpdate@@AAEXXZ: Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SpawnPointProductionExitUpdate.cpp
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpawnPointProductionExitUpdate.h
class SpawnPointProductionExitUpdate
{
    void initializeBonePositions();
};

class SpawnPointInitializeBonePositionsShim
{
public:
    void init();
};

void SpawnPointProductionExitUpdate::initializeBonePositions()
{
    ((SpawnPointInitializeBonePositionsShim *)this)->init();
}
