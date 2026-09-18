// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpawnUnitBehaviorModuleData scalar-deleting destructor.
// The matched complete destructor is emitted by
// SpawnUnitBehaviorModuleDataDestructor.cpp.  This declaration-only TU
// gives MSVC the retail wrapper shape while binding its direct call to that
// already byte-verified class destructor.

class SpawnUnitBehaviorModuleData
{
public:
	virtual ~SpawnUnitBehaviorModuleData();
};

// ??_GSpawnUnitBehaviorModuleData@@UAEPAXI@Z
void forceSpawnUnitBehaviorModuleDataDeletingDestructor()
{
	SpawnUnitBehaviorModuleData value;
}
