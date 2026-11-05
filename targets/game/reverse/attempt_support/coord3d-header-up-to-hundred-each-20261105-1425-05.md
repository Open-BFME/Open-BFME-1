# Adopt the registered Coord3D header in 20 units

Base: `66a1ef0c3b7cbba1623b58a20abc056e9bdad6ca`. Native scope: 25 existing rows and 265 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngine/Source/GameLogic/Object/Rva00189E80ObjectVisionQuery.cpp` | 1 | 8 |
| `game/GameEngine/Source/GameLogic/AI/PathfinderGetLayerHeight.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/QueueProductionExitUpdateQueryRallyOverride.cpp` | 1 | 18 |
| `game/GameEngine/Source/GameLogic/Object/Update/Rva00265DF0Neutral.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp` | 2 | 2 |
| `game/GameEngine/Source/Common/Rva006187D0MoveArmyToPosition.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameClient/MessageStream/CommandTranslator_issueCombatDropCommand.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/Object/Update/AssistedTargetingUpdate_makeFeedbackLaser.cpp` | 1 | 2 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DStreakDrawBody.cpp` | 1 | 2 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMapValidateName.cpp` | 2 | 15 |
| `game/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDamagedBehavior_onDamage.cpp` | 3 | 4 |
| `game/GameEngine/Source/GameLogic/Object/Contain/HordeContain/Rva002435F0Formation.cpp` | 1 | 50 |
| `game/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/HealCrateCollide_executeCrateBehavior.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_isWithinAbilityAbortRange.cpp` | 1 | 4 |
| `game/GameEngine/Source/GameClient/MapMetaData_ctor.cpp` | 2 | 99 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBufferRva00736150.cpp` | 1 | 14 |
| `game/GameEngine/Source/GameLogic/AI/AIAttackMeleeHordeApproachTargetState_onExit.cpp` | 1 | 12 |
| `game/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehavior.cpp` | 1 | 24 |
| `game/GameEngine/Source/GameLogic/Object/ObjectCanCrushOrSquish.cpp` | 1 | 3 |
| `game/GameEngine/Source/GameLogic/AI/TurretAI_setTurretTargetPosition.cpp` | 1 | 1 |
