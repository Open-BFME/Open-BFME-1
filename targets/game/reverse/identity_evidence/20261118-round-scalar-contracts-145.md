# Scalar alias contracts: cohort 145

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
|3031|`game/GameEngine/Source/GameLogic/AI/BfmeAttackQueryCandidateE2B0.cpp`|Int, Bool|2|603|
|3032|`game/GameEngine/Source/Common/RTS/PlayerRelationships.cpp`|Int, Bool|2|169|
|3033|`game/GameEngine/Source/Common/ParseCommandLine.cpp`|Int, Bool|2|482|
|3034|`game/GameEngine/Source/Common/Rva00076B60Constructor.cpp`|Bool, Int|2|135|
|3035|`game/GameEngine/Source/Common/TextureRefAssignOperators.cpp`|Int, UnsignedShort|2|348|
|3036|`game/GameEngineDevice/Source/Win32Device/Common/Win32BIGFileGetInfo.cpp`|Int, Bool|2|282|
|3037|`game/GameEngine/Source/Common/Rva0046F3D0DrawImageAt.cpp`|Int, Real|2|406|
|3038|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsTeamMemberFlags.cpp`|Int, Bool|2|240|
|3039|`game/GameEngine/Source/GameNetwork/Connection_doSend.cpp`|UnsignedByte, Int|2|632|
|3040|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ReplayMenuDeleteCopy.cpp`|Int, Bool|2|1383|
|3041|`game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/BfmeShadowBufferManagerCreate.cpp`|Real, Bool|2|250|
|3042|`game/GameEngine/Source/GameLogic/Object/Update/CommandButtonHuntUpdate_huntSpecialPower.cpp`|Bool, UnsignedInt|2|276|
|3043|`game/GameEngine/Source/Common/Thing/ThingTemplateModuleRemovalParsers.cpp`|Int, Bool|2|574|
|3044|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewDrawablePostDraw.cpp`|Real, UnsignedInt|2|412|
|3045|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineGetQualifiedTriggerAreaByName.cpp`|Bool, Int|2|534|
|3046|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DStreakDrawConstructor.cpp`|Int, Char, Bool|2|365|
|3047|`game/GameEngine/Source/Common/RTS/Team_damageTeamMembers.cpp`|Bool, Real|2|343|
|3048|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/SkirmishScreenStateRebuildColorCombo.cpp`|Bool, Int|2|1431|
|3049|`game/GameEngineDevice/Source/W3DDevice/GameLogic/W3DGhostObjectManagerDoXfer.cpp`|UnsignedInt, UnsignedShort|2|403|
|3050|`game/GameEngine/Source/GameLogic/Object/ObjectAdjustModelConditionThunk.cpp`|UnsignedInt, Bool|2|395|
|3051|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptSaveLoad.cpp`|Int, Bool|2|786|
|3052|`game/GameEngine/Source/GameLogic/Object/Update/StealthUpdateModuleDataConstructor.cpp`|Int, UnsignedInt, Real|2|386|
|3053|`game/GameEngine/Source/GameLogic/AI/AIPlayerIsPossibleToBuildTeam.cpp`|Bool, Int|2|812|
|3054|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/SkirmishScreenStateRva005294F0.cpp`|Bool, Int|2|1239|
|3055|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsCamera.cpp`|Int, Bool|2|190|
|3056|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsCanBuildAtBase.cpp`|Bool, UnsignedShort|2|619|
|3057|`game/GameEngine/Source/GameLogic/AI/AIAttackMeleeHordeWaitState_update.cpp`|Bool, UnsignedInt|2|545|
|3058|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsNamedByType.cpp`|Bool, Int|2|479|
|3059|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DWaypointBufferDrawWaypoints.cpp`|Int, Bool, Real, UnsignedInt|2|698|
|3060|`game/GameEngine/Source/GameLogic/ScriptEngine/LuaScriptEngineParseModelConditionEvent.cpp`|Int, Bool|2|831|
|3061|`game/GameEngine/Source/GameLogic/Object/Behavior/RampageBehaviorCtorThunk.cpp`|Bool, Real|2|903|
|3062|`game/GameEngine/Source/GameLogic/AI/AIPlayer_findFactory.cpp`|Bool, Int, UnsignedInt|2|723|
|3063|`game/GameEngine/Source/GameClient/DrawableDrawVeterancy.cpp`|Int, Bool|2|551|
|3064|`game/GameEngineDevice/Source/W3DDevice/GameClient/MapObjectAmbientAudio00088480.cpp`|Int, Bool|2|1049|
|3065|`game/GameEngine/Source/Common/RTS/PlayerBattlePlanBonuses.cpp`|Bool, Int|2|434|
|3066|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawWeaponBarrelValidation0076F9E0.cpp`|Int, Bool|2|1693|
|3067|`game/GameEngine/Source/GameLogic/AI/AIChargeTargetState_update.cpp`|Bool, Real|2|577|
|3068|`game/GameEngine/Source/GameLogic/Pathfinder/PathfindLayerAllocateCells.cpp`|Int, Real|2|778|
|3069|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/Glo00EF4988RemoveFriends.cpp`|Bool, Int|2|632|
|3070|`game/GameEngine/Source/GameLogic/AI/AIPlayerDozer.cpp`|Bool, Real|2|455|
|3071|`game/GameEngine/Source/GameLogic/Object/Locomotor_rva001BC820.cpp`|Bool, Real|2|1138|
|3072|`game/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetState_computePath_Bfme.cpp`|Bool, Real|2|1149|
|3073|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ScoreScreenFinishSinglePlayerInit.cpp`|Int, Bool|2|1304|
|3074|`game/GameEngine/Source/GameClient/GUI/BfmeOnlineProfileScreenRva00554AA0.cpp`|Int, Real|2|9491|
|3075|`game/GameEngine/Source/GameClient/GUI/GameWindowManagerScriptParseWindow.cpp`|Int, UnsignedInt|2|2064|
|3076|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceCommandDispatch.cpp`|Bool, Int|2|2407|
|3077|`game/GameEngine/Source/GameNetwork/NetPacket_GetBufferSizeNeededForCommand.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Real, Bool|3|643|
|3078|`game/GameEngine/Source/GameNetwork/NetPacket_addGameCommand.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool, Real|3|1271|
|3079|`game/GameEngine/Source/GameNetwork/NetPacket_isRoomForKeepAlive.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|3|252|
|3080|`game/GameEngine/Source/GameNetwork/SkirmishGameInfo_xfer.cpp`|UnsignedByte, UnsignedShort, UnsignedInt, Int, Bool|3|915|
|3081|`game/GameEngine/Source/GameNetwork/NetPacket_addChatFamily.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|3|1405|
|3082|`game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterRenderObjGridAndSkybox.cpp`|Int, Char, UnsignedInt, UnsignedByte, Bool|3|745|
|3083|`game/GameEngine/Source/GameLogic/AI/PathfinderFindGroundPath.cpp`|Int, UnsignedInt, UnsignedShort, Bool, Real|3|3191|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
