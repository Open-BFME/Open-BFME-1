# Adopt the registered Coord3D header in 20 units

Base: `57a3cfe2d2c1bee6e5d87ecbeef1fab4c1e3ab2e`. Native scope: 29 existing rows and 118 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngine/Source/Common/BfmeCalc919G.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/AI/PathfinderClassifyFence.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/AI/Rva0017DB30State_onEnter.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameLogic/Object/Weapon_isGoalPosWithinAttackRange.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/LuaExecuteAction.cpp` | 1 | 13 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_FireSpecialPowerOnNearestObjectType_Rva002F9C60.cpp` | 1 | 11 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayCreate.cpp` | 3 | 12 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdAIUpdate.cpp` | 2 | 5 |
| `game/GameEngine/Source/Common/BfmeConv1098.cpp` | 3 | 5 |
| `game/GameEngine/Source/GameLogic/AI/AIChargeTargetState_onEnter.cpp` | 1 | 9 |
| `game/GameEngine/Source/GameLogic/Object/Weapon_preFireWeapon.cpp` | 1 | 3 |
| `game/GameEngine/Source/GameLogic/AI/Rva00178C30StateOnEnter.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameClient/DrawableVeterancyIcons.cpp` | 1 | 3 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardReturnState_onEnter.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameLogic/AI/AIMoveToPositionAndDieState_update_Bfme.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/AI/PathfinderPickBridge.cpp` | 3 | 18 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdateBuildPath00271010.cpp` | 1 | 6 |
| `game/GameEngine/Source/GameLogic/Object/Object_rva001C7CF0.cpp` | 1 | 14 |
| `game/GameEngine/Source/GameClient/MessageStream/Rva005ACF80SpecialPower.cpp` | 1 | 3 |
| `game/GameEngine/Source/Common/RTS/ActionManagerGetCanAttackObject.cpp` | 3 | 5 |
