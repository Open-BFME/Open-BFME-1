// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: SpawnPointProductionExitUpdate scalar-deleting destructor at
// retail RVA 0x002D18C0 (30 bytes). Its exact constructor at 0x002D1480,
// complete destructor at 0x002D17A0, factories, pool, and landed exit methods
// establish the class. The destructor ILT is 0x0003FF58.

class SpawnPointProductionExitUpdate
{
public:
	virtual ~SpawnPointProductionExitUpdate();
};

void forceSpawnPointProductionExitUpdateDeletingDestructor()
{
	SpawnPointProductionExitUpdate value;
}
