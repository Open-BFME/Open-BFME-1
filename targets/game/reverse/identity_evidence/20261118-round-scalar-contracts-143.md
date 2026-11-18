# Scalar alias contracts: cohort 143

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
|2913|`game/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehaviorCreateSpawn.cpp`|Int, UnsignedInt, Bool, Real|2|785|
|2914|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarMultiSelect.cpp`|Int, UnsignedInt, Real, Bool|2|1288|
|2915|`game/GameEngine/Source/GameNetwork/GameSpy/LobbyUtilsInsertGame.cpp`|Int, UnsignedInt, UnsignedShort, Bool|2|1905|
|2916|`game/GameEngine/Source/GameClient/GUI/parseTextEntryData_Thunk.cpp`|Bool, Int, Short|2|311|
|2917|`game/GameEngine/Source/GameLogic/Object/Update/BfmeAttributeStringRangeEqual.cpp`|Int, UnsignedShort, Bool|2|202|
|2918|`game/GameEngine/Source/Common/ExperienceLevelSystemConstructor.cpp`|Bool, Int, Real|2|344|
|2919|`game/GameEngine/Source/GameClient/System/Anim2DTemplate_parseImageSequence_Thunk.cpp`|Int, UnsignedShort, Bool|2|413|
|2920|`game/GameEngine/Source/GameNetwork/NetGameCommandMsgCtor.cpp`|Int, UnsignedInt, UnsignedShort|2|87|
|2921|`game/GameEngine/Source/Common/System/RAMFileOpen.cpp`|Int, Bool, Char|2|194|
|2922|`game/GameEngine/Source/GameLogic/ScriptEngine/XferListAsciiStringObjectID.cpp`|UnsignedByte, UnsignedInt, Bool|2|442|
|2923|`game/GameEngine/Source/Common/System/XferAsciiStringVector.cpp`|UnsignedByte, UnsignedInt, Bool|2|404|
|2924|`game/GameEngine/Source/Common/Bfme/Rva000F9670ResolveTemplate.cpp`|Int, UnsignedInt, Real|2|157|
|2925|`game/GameEngine/Source/GameLogic/Object/ObjectTypesXfer.cpp`|UnsignedByte, UnsignedShort, Bool|2|396|
|2926|`game/GameEngine/Source/Common/RTS/Rva000F4830TeamCountKind.cpp`|Int, UnsignedInt, Bool|2|162|
|2927|`game/GameEngine/Source/Common/System/XferUnicodeStringVector.cpp`|UnsignedByte, UnsignedInt, Bool|2|404|
|2928|`game/GameEngine/Source/GameClient/GameTextManagerParseCSF.cpp`|Bool, Int, Char|2|683|
|2929|`game/GameEngine/Source/Common/GameLODManagerConstructor.cpp`|Int, Real, Bool|2|566|
|2930|`game/GameEngine/Source/GameClient/GameTextManager_initMapStringFile_Thunk.cpp`|Bool, Int, Char|2|443|
|2931|`game/GameEngine/Source/Common/RvaC4390Second_resolve.cpp`|Int, Bool, UnsignedInt|2|238|
|2932|`game/GameEngine/Source/GameClient/System/Campaign_getNextMission.cpp`|Int, UnsignedInt, UnsignedShort, Bool|2|590|
|2933|`game/GameEngine/Source/GameLogic/Object/Update/RubbleRiseUpdate.cpp`|Int, Bool, Real, UnsignedInt|2|321|
|2934|`game/GameEngine/Source/GameLogic/Object/Update/Rva0026C7C0ToggleMounted.cpp`|Bool, Int, UnsignedInt|2|495|
|2935|`game/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMapValidateName.cpp`|Int, Real, Bool|2|407|
|2936|`game/GameEngine/Source/GameLogic/AI/PathNodeInsertion.cpp`|Int, UnsignedInt, Real, Bool|2|284|
|2937|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsNamedSetModelCondition.cpp`|Int, Bool, UnsignedInt|2|192|
|2938|`game/GameEngine/Source/GameClient/GUI/Shell/Shell_hide.cpp`|Int, UnsignedInt, Bool|2|230|
|2939|`game/GameEngine/Source/Common/RTS/PlayerProductionCost.cpp`|Bool, Int, UnsignedInt, Real|2|117|
|2940|`game/GameEngine/Source/GameClient/DrawableXferDrawableModules.cpp`|UnsignedByte, UnsignedShort, Bool|2|534|
|2941|`game/GameEngine/Source/GameLogic/System/CrateSystem_friend_findCrateTemplate.cpp`|Int, UnsignedInt, UnsignedShort, Bool|2|646|
|2942|`game/GameEngine/Source/GameClient/MapUtil_loadMap.cpp`|Int, UnsignedInt, Bool|2|863|
|2943|`game/GameEngine/Source/GameNetwork/native_desync_report.cpp`|Bool, Int, UnsignedInt|2|558|
|2944|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva00777B50ScriptedModelDrawRecord.cpp`|Int, Real, Bool|2|588|
|2945|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsNamedContain.cpp`|Bool, Int, UnsignedInt|2|116|
|2946|`game/GameEngine/Source/GameLogic/AI/AICommandParmsStorage.cpp`|Int, Real, Bool|2|475|
|2947|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineAttackInfo.cpp`|Int, UnsignedShort, Bool|2|872|
|2948|`game/GameEngine/Source/GameClient/GameTextManager_init.cpp`|Bool, Int, Char|2|708|
|2949|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doMoveUnitTowardsNearest_Thunk.cpp`|Bool, Int, Real|2|322|
|2950|`game/GameEngine/Source/Common/RTS/Money_deposit.cpp`|Int, UnsignedInt, Bool|2|432|
|2951|`game/GameEngine/Source/GameLogic/Map/FootprintIterator001A1460.cpp`|Real, Int, Bool|2|1383|
|2952|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsTeamRecruit.cpp`|Bool, Int, Real|2|384|
|2953|`game/GameEngine/Source/GameLogic/Object/Body/ActiveBodyModuleDataCtor.cpp`|UnsignedInt, Real, Bool|2|260|
|2954|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDebrisDrawDoDrawModule.cpp`|Bool, Int, Real|2|503|
|2955|`game/GameEngine/Source/GameLogic/AI/PathfinderNewMap.cpp`|Int, Real, Bool|2|760|
|2956|`game/GameEngine/Source/GameClient/SubtitleEntryRender_rva004341A0.cpp`|Int, UnsignedInt, Real|2|685|
|2957|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceCommandButton.cpp`|UnsignedInt, Int, Bool|2|590|
|2958|`game/GameEngine/Source/GameClient/GameClientConstructor00433340.cpp`|UnsignedInt, UnsignedShort, Int|2|636|
|2959|`game/GameEngine/Source/GameClient/Input/Mouse_processMouseEvent.cpp`|Int, UnsignedInt, UnsignedByte|2|776|
|2960|`game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterRenderObjSky.cpp`|Int, UnsignedInt, Real|2|2268|
|2961|`game/GameEngine/Source/Common/RTS/TeamPrototypeScripts.cpp`|Bool, Int, UnsignedInt|2|452|
|2962|`game/GameEngine/Source/GameClient/GUI/Gadget/GadgetPushButtonBodies.cpp`|Bool, Int, UnsignedInt|2|327|
|2963|`game/GameEngine/Source/GameLogic/Object/Upgrade/BaseUpgradeUpgradeImplementation.cpp`|Int, UnsignedInt, Real, Bool|2|600|
|2964|`game/GameEngine/Source/GameClient/GUI/WindowManager_update.cpp`|Int, Bool, UnsignedInt|2|844|
|2965|`game/GameEngine/Source/Common/System/RecorderReadReplayHeader.cpp`|Int, UnsignedInt, Bool|2|1397|
|2966|`game/GameEngine/Source/GameLogic/Object/Update/AttributeModifierAuraUpdate.cpp`|Bool, Int, Real|2|1498|
|2967|`game/GameEngine/Source/GameLogic/AI/PathfinderRva003E49F0.cpp`|Int, Bool, Real|2|1446|
|2968|`game/GameEngine/Source/GameLogic/Object/Update/AttributeModifierPoolUpdate_applyAttributeModifier.cpp`|Bool, Int, UnsignedInt|2|1060|
|2969|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewRva00743CE0.cpp`|Int, Bool, Real|2|953|
|2970|`game/GameEngine/Source/GameLogic/AI/AIPlayerCheckReadyTeams.cpp`|Bool, Int, UnsignedInt|2|733|
|2971|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ReplayMenuPopulateReplayFileListbox.cpp`|Int, UnsignedInt, Bool|2|1808|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
