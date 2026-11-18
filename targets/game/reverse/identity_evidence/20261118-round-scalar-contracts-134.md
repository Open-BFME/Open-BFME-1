# Scalar alias contracts: cohort 134

One task replaces one consumer file's grouped private primitive typedefs
with the existing EA/BFME1 contract. Individual typedefs are not counted as
separate tasks. Only exact primitive spellings already present in both the
native BFME1 Precompiled/PreRTS.h and the EA BaseType.h qualify. Char remains
char, unsigned types remain unsigned, and no 64-bit/platform modernization is
inferred. Original provider headers are preserved. The narrow shared header
contains only the nine original scalar typedefs, without macros or runtime code.

Actual original source filenames compile into explicit private ordinary and Z7
controls before any edit. After adoption the normal build passes. Its complete
ordinary runtime inventory equals the actual pre-edit object: code, data,
definitions, relocations, raw directives, weak references and aliases. A fresh
actual-source ordinary object also equals the normal build object. All original
complete class contracts and all original enums remain identical in actual
Z7 records. Real-header traces and opened-input hashes are retained.

Additional private functions bind pointers to each adopted alias and return its
sizeof. Complete witness symbol names and bodies must remain identical, proving
primitive type identity and size even for aliases that contribute no runtime
instructions. A negative control changes unused Int from int to unsigned int:
ordinary runtime remains identical, but the exact primitive witness rejects it.
Witness code exists only in explicit diagnostic outputs. It is not game source,
retail identity evidence or authored-byte progress. CPP files included by other
CPPs are excluded unless all parent/namespace contexts are independently proven.

This source consistency work adds no newly reconstructed function bytes and
makes no crash, RAM/leak, FPS, multicore or runtime-start claim. No verifier,
baseline, pin, EH label or alias is weakened or manually altered. Linking is
separate; absent dependency receipts remain UNKNOWN for provider freshness.

|Task|Consumer|Grouped aliases|Rows|Retained row bytes|
|---|---|---|---:|---:|
|2408|`game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/RepairDockUpdateAction.cpp`|Real, Bool|1|224|
|2409|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdAIUpdate_rva002c2a60.cpp`|Int, Real|1|338|
|2410|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContain/HordeContain.cpp`|Bool, Int|1|154|
|2411|`game/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModuleDoSpecialPowerUsingWaypoints.cpp`|UnsignedInt, Int, Bool|1|82|
|2412|`game/GameEngine/Source/GameLogic/ScriptEngine/BfmeEnableListenerNotify.cpp`|Bool, Int|1|357|
|2413|`game/GameEngine/Source/GameClient/ParticleSystemFXNuggetConstructor.cpp`|Real, Bool|1|350|
|2414|`game/GameEngine/Source/GameLogic/ScriptEngine/ObjectDoSpecialPower.cpp`|Bool, UnsignedInt|1|183|
|2415|`game/GameEngine/Source/Common/Glo012F1024Entry_select.cpp`|Int, UnsignedInt, Bool|1|262|
|2416|`game/GameEngine/Source/GameClient/System/FXParticleSystem/LifeEventSlot1.cpp`|UnsignedInt, Real|1|184|
|2417|`game/GameEngine/Source/GameClient/GUI/Rva0051E1A0MapRollLoadGame.cpp`|Bool, Real|1|175|
|2418|`game/GameEngine/Source/GameLogic/Object/Contain/Rva00249D70GetStatus.cpp`|Bool, Int|1|98|
|2419|`game/GameEngine/Source/GameClient/GUI/Shell/Shell_ctor_Thunk.cpp`|Bool, UnsignedInt|1|259|
|2420|`game/GameEngine/Source/Common/RTS/Rva000EDCD0TeamEstimatePosition.cpp`|Bool, Real|1|186|
|2421|`game/GameEngine/Source/GameLogic/Object/Update/RubbleRiseUpdateXfer.cpp`|UnsignedInt, Real|1|138|
|2422|`game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_startFacing.cpp`|Int, UnsignedInt, Real, Bool|1|154|
|2423|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsDoTeamRadarCreateEventThunk.cpp`|Bool, Real|1|96|
|2424|`game/GameEngine/Source/GameClient/System/FXParticleSystem/Rva005EE8A0Ctor.cpp`|Real, UnsignedInt|1|285|
|2425|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewSetDefaultViewBfme.cpp`|Real, Bool|1|154|
|2426|`game/GameEngine/Source/GameLogic/Object/Update/Rva0028DDC0ParseRiderInfo.cpp`|Int, UnsignedInt|1|446|
|2427|`game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorAllowedCommon.cpp`|Bool, Int|1|181|
|2428|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedDamage_Thunk.cpp`|Bool, Real|1|86|
|2429|`game/GameEngine/Source/GameLogic/AI/PathfinderCheckForTargetBfme.cpp`|Int, Bool|1|170|
|2430|`game/GameEngine/Source/GameLogic/Object/Die/DieMuxDataIsDieApplicable.cpp`|Bool, Real|1|241|
|2431|`game/GameEngine/Source/GameLogic/System/LookupInitialWalkOnWaypoints.cpp`|Int, UnsignedShort|1|362|
|2432|`game/GameEngine/Source/GameLogic/Object/LocomotorSetXferSelfRva001B74D0.cpp`|UnsignedByte, Bool|1|387|
|2433|`game/GameEngine/Source/GameClient/Drawable/Behavior/AnimationSoundClientBehavior.cpp`|Int, Bool|1|290|
|2434|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewPitchCameraOneFrame.cpp`|Real, Bool|1|168|
|2435|`game/GameEngine/Source/GameLogic/AI/PathfindAdjustDeab0.cpp`|Int, Bool|1|200|
|2436|`game/GameEngine/Source/GameLogic/Object/Object_getHealthBoxDimensions_Thunk.cpp`|Real, Bool|1|234|
|2437|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamNeedsOpenGate_Thunk.cpp`|Bool, Int|1|82|
|2438|`game/GameEngine/Source/GameLogic/Object/SpecialPower/Rva00269340IsReady.cpp`|UnsignedInt, Int|1|121|
|2439|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptScoreScreen.cpp`|Bool, Int|1|338|
|2440|`game/GameEngine/Source/GameLogic/AI/PathfindMoveAlliesCellCallbackEc070.cpp`|Int, Bool|1|140|
|2441|`game/GameEngine/Source/GameLogic/Map/TerrainLogicGetHighestLayer.cpp`|Real, Bool|1|165|
|2442|`game/GameEngine/Source/GameLogic/Object/GhostObject_xfer.cpp`|Int, Real|1|185|
|2443|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doDisplayCountdownTimer.cpp`|Int, Bool|1|235|
|2444|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTruckDrawConstructor.cpp`|Bool, Char|1|359|
|2445|`game/GameEngine/Source/Common/Rva0074A590ParserRegistrationParse.cpp`|Real, Int|1|474|
|2446|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBufferRemovePropsForConstruction.cpp`|Real, Bool|1|300|
|2447|`game/GameEngine/Source/GameClient/GUI/Shell/Shell_popImmediate.cpp`|Bool, Int|1|164|
|2448|`game/GameEngine/Source/GameLogic/Object/Update/SlavedUpdate_setRepairModelConditionStates.cpp`|Int, Bool, UnsignedInt|1|299|
|2449|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsRva002EE060.cpp`|Int, Real|1|118|
|2450|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsUnownedFactionRva00329230.cpp`|Bool, Int|1|360|
|2451|`game/GameEngine/Source/GameLogic/Object/Contain/CaveContain.cpp`|UnsignedInt, Bool|1|208|
|2452|`game/GameEngine/Source/GameLogic/AI/PathfinderSetArea.cpp`|Int, Bool|1|424|
|2453|`game/GameEngine/Source/GameClient/System/CampaignManager_xfer_Bfme.cpp`|UnsignedByte, Int|1|297|
|2454|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ReplayMenuReallyLoadReplay.cpp`|Int, Bool|1|323|
|2455|`game/GameEngine/Source/GameLogic/Object/Contain/HordeSiegeEngineContainIsValidContainerFor.cpp`|Bool, Int|1|147|
|2456|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamAttackNamed_Thunk.cpp`|Int, Bool|1|144|
|2457|`game/GameEngine/Source/GameLogic/AI/PathGetLastValidWaypointPosition.cpp`|UnsignedInt, Real|1|131|
|2458|`game/GameEngine/Source/GameClient/ViewConstructorBfme.cpp`|UnsignedInt, Real|1|211|
|2459|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/Rva00523460ComboSelectByData.cpp`|Bool, Int|1|258|
|2460|`game/GameEngine/Source/Common/Thing/ThingTemplateResolveNames.cpp`|Int, UnsignedInt|1|355|
|2461|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIGiantBirdSwoopStateOnExit.cpp`|Int, UnsignedInt|1|176|
|2462|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceWaypointGoalPathSize.cpp`|Int, UnsignedInt|1|77|
|2463|`game/GameEngine/Source/GameNetwork/ConnectionManager_setFrameGrouping.cpp`|Int, UnsignedInt|1|129|
|2464|`game/GameEngine/Source/GameClient/DrawableSetInstanceMatrixBFME.cpp`|UnsignedInt, Real|1|581|
|2465|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdFollowWaypointPathStateOnExit.cpp`|Int, UnsignedInt|1|172|
|2466|`game/GameEngine/Source/GameLogic/Object/Contain/Rva0023C4D0HordeContainSlot98.cpp`|Bool, UnsignedInt|1|217|
|2467|`game/GameEngine/Source/GameLogic/ScriptEngine/LuaScriptEngineParseTokenFile.cpp`|Int, Bool|1|267|
|2468|`game/GameEngine/Source/GameClient/GUI/parseName_Thunk.cpp`|Int, Bool|1|139|
|2469|`game/GameEngine/Source/GameLogic/Object/Body/Rva00210730BookendSearch.cpp`|Int, UnsignedShort|1|322|
|2470|`game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorRva00371EE0StatusBit.cpp`|Int, Bool|1|342|
|2471|`game/GameEngine/Source/GameLogic/Object/Weapon_computeBonus.cpp`|UnsignedInt, Real|1|96|
|2472|`game/GameEngine/Source/GameLogic/AI/TurretAI_updateTurretAI.cpp`|UnsignedInt, Int|1|261|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
