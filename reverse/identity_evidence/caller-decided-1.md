# Caller-decided bodies, caller-decided-1

Retail was linked without identical-COMDAT folding, so each body has one identity. For every body below, `python3 tools/one_identity.py --callers` found exactly one of its row names called by matched C++ callers at retail call sites into the body or its incremental-link entries, and no other real name called there. The other row names are retired. Generated and assembly callers were not counted, bodies with an unread caller object were left out, and so were library and C-level names.

| body | kept | C++ call sites | retired |
|---|---|---|---|
| `0x000082F6` | `?insert_unique@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@PAVLocomotorTemplate@@@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@PAVLocomotorTemplate@@@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@PAVLocomotorTemplate@@@_STL@@@3@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBW4NameKeyType@@PAVLocomotorTemplate@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBW4NameKeyType@@PAVLocomotorTemplate@@@_STL@@@2@@2@U32@ABU?$pair@$$CBW4NameKeyType@@PAVLocomotorTemplate@@@2@@Z` | 2 | `?insert_unique@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@PAVLocomotorTemplate@@@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@PAVLocomotorTemplate@@@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@PAVL` |
| `0x0002248F` | `?buildTerrainTexture@W3DRadar@@IAEXPAVTerrainLogic@@@Z` | 1 | `?removeGoal@Pathfinder@@QAEXPAVObject@@@Z` |
| `0x00030512` | `?insert_unique@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@M@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@M@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@M@_STL@@@3@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBW4NameKeyType@@M@_STL@@U?$_Nonconst_traits@U?$pair@$$CBW4NameKeyType@@M@_STL@@@2@@2@U32@ABU?$pair@$$CBW4NameKeyType@@M@2@@Z` | 2 | `?insert_unique@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@M@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@M@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@M@_STL@@@3@@_STL@@AAE?AU?$_Rb_tree_iterator@U?$pair@$$CBW4NameKeyType@@M@_STL@@U?$_Nonconst_traits@U?$pair@$$CBW4NameKeyType@@M@_STL@@@2@@2@PAU_Rb_tree_node_base@2@ABU?$pair@$$CBW4NameKeyType@@M@2@@Z` |
| `0x0005E4C0` | `?isEmpty@?$StringBase@D@@QBE_NXZ` | 6 | `?isEmpty@UnicodeString@@QBE_NXZ` |
| `0x00078DF0` | `??1?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@@3@@_STL@@QAE@XZ` | 1 | `??1?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@VObjectCreationList@@@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VObjectCreationList@@@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@VObjectCreationList@@@_STL@@@3@@_STL@@QAE@XZ` |
| `0x0008E280` | `?getTooltipName@MultiplayerColorDefinition@@QBE?AVAsciiString@@XZ` | 4 | `?getName@LANPlayer@@QAE?AVUnicodeString@@XZ` |
| `0x0009B530` | `??$?9G@@YA_NABV?$StringBase@G@@0@Z` | 1 | `??9@YA_NABV?$StringBase@G@@0@Z` |
| `0x0009F290` | `?_M_fill_insert@?$list@VUnicodeString@@V?$allocator@VUnicodeString@@@_STL@@@_STL@@QAEXU?$_List_iterator@VUnicodeString@@U?$_Nonconst_traits@VUnicodeString@@@_STL@@@2@IABVUnicodeString@@@Z` | 2 | `?_M_fill_insert@?$list@URva0009F290Payload@@V?$allocator@URva0009F290Payload@@@_STL@@@_STL@@QAEXU?$_List_iterator@URva0009F290Payload@@U?$_Nonconst_traits@URva0009F290Payload@@@_STL@@@2@IABURva0009F290Payload@@@Z` |
| `0x0009F630` | `??0?$list@VUnicodeString@@V?$allocator@VUnicodeString@@@_STL@@@_STL@@QAE@I@Z` | 1 | `??0?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@I@Z` |
| `0x000A3D50` | `??$?9D@@YA_NABV?$StringBase@D@@0@Z` | 2 | `??9@YA_NABV?$StringBase@D@@0@Z` |
| `0x000A7210` | `??1AnimationSteeringUpdateModuleData@@UAE@XZ` | 1 | `??1PowerPlantUpdateModuleData@@UAE@XZ`<br>`??1W3DPropDrawModuleData@@UAE@XZ` |
| `0x000B8F40` | `?scanScience@INI@@SA?AW4ScienceType@@PBD@Z` | 1 | `?commandButtonTooltip@@YAXPAVGameWindow@@PAVWinInstanceData@@I@Z` |
| `0x000BEC90` | `??0Region3D@@QAE@ABU0@@Z` | 2 | `??4MinMaxAABoxClass@@QAEAAV0@ABV0@@Z`<br>`??4TangentsClass@HermiteSpline3DClass@@QAEAAV01@ABV01@@Z` |
| `0x000C3F00` | `?isAboveTerrainOrWater@Thing@@QBE_NXZ` | 2 | `?isAboveTerrain@Thing@@QBE_NXZ` |
| `0x000C9710` | `?getSupplyBoxValue@Player@@QAEIXZ` | 1 | `?rva000C9710Get@@YAHXZ` |
| `0x000C9B40` | `?getCurrentSelectionAsAIGroup@Player@@QAEXPAVAIGroup@@@Z` | 1 | `?bfmeForward@Gen_000C9B40@@QAEXPAX@Z`<br>`?wrap@Rva000C9B40@@QAEXH@Z` |
| `0x000CB330` | `?getSingleBitFromName@?$BitFlags@$0BB@@@SAHPBD@Z` | 1 | `?getSingleBitFromName@?$BitFlags@$0L@@@SAHPBD@Z` |
| `0x000CDC70` | `?removeTeamFromList@Player@@QAEXPAVTeamPrototype@@@Z` | 1 | `?bfmeGo915A@BfmeThing915A@@QAEXPAX@Z` |
| `0x000CDCC0` | `?healAllObjects@Player@@QAEXXZ` | 1 | `?bfmeGoEZA@BfmeThingEZA@@QAEXXZ` |
| `0x000DA030` | `?getProductionTimeChangePercent@Player@@QBEMABVAsciiString@@@Z` | 1 | `?bfmeGoEZC@BfmeThingEZC@@QAEMPAX@Z` |
| `0x000FBA20` | `?isInRegionNoZ@Region3D@@QBE_NPBUCoord3D@@@Z` | 2 | `?isInRegionNoZ@Region3D@@QBE_NPBVCoord3D@@@Z` |
| `0x00105950` | `?next@LListNode@@QAEPAV1@XZ` | 4 | `?firstNode@LList@@QAEPAVLListNode@@XZ` |
| `0x00122ED0` | `??0KeepObjectDieModuleData@@QAE@XZ` | 1 | `??0DestroyDieModuleData@@QAE@XZ` |
| `0x00125E40` | `??1ConvertToCarBombCrateCollideModuleData@@UAE@XZ` | 1 | `??1HealCrateCollideModuleData@@UAE@XZ`<br>`??1MoneyCrateCollideModuleData@@UAE@XZ`<br>`??1ShroudCrateCollideModuleData@@UAE@XZ` |
| `0x00126F00` | `??1SpawnUnitBehaviorModuleData@@UAE@XZ` | 1 | `??1OathbreakersFadeAwayBehaviorModuleData@@UAE@XZ` |
| `0x00140A60` | `?_M_lower_bound@?$_Rb_tree@$$CBV?$BitFlags@$0L@@@U?$pair@$$CBV?$BitFlags@$0L@@@PBVArmorTemplateSet@@@_STL@@U?$_Select1st@U?$pair@$$CBV?$BitFlags@$0L@@@PBVArmorTemplateSet@@@_STL@@@3@UMapHelper@?$SparseMatchFinder@VArmorTemplateSet@@V?$BitFlags@$0L@@@@@V?$allocator@U?$pair@$$CBV?$BitFlags@$0L@@@PBVArmorTemplateSet@@@_STL@@@3@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBV?$BitFlags@$0L@@@PBVArmorTemplateSet@@@_STL@@@2@ABV?$BitFlags@$0L@@@@Z` | 1 | `?_M_lower_bound@?$_Rb_tree@$$CBV?$BitFlags@$0HF@@@U?$pair@$$CBV?$BitFlags@$0HF@@@PBUModelConditionInfo@@@_STL@@U?$_Select1st@U?$pair@$$CBV?$BitFlags@$0HF@@@PBUModelConditionInfo@@@_STL@@@3@UMapHelper@?$SparseMatchFinder@UModelConditionInfo@@V?$BitFlags@$0HF@@@@@V?$allocator@U?$pair@$$CBV?$BitFlags@$0HF@@@PBUModelConditionInfo@@@_STL@@@3@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBV?$BitFlags@$0HF@@@PBUModelConditionInfo@@@_STL@@@2@ABV?$BitFlags@$0HF@@@@Z` |
| `0x001A2E00` | `?makeAlignToNormalMatrix@@YAXMABUCoord3D@@0AAVMatrix3D@@@Z` | 3 | `?alignToTerrain@@YAXMABUCoord3D@@0AAVMatrix3D@@@Z` |
| `0x001B1FC0` | `?getExperienceValue@ExperienceTracker@@QBEHPBVObject@@@Z` | 1 | `?bfmeGoFAH@BfmeThingFAH@@QAEHPAUBfmeObjFAH@@@Z` |
| `0x001F36A0` | `??1BridgeBehavior@@UAE@XZ` | 1 | `??1BridgeBehavior@@MAE@XZ` |
| `0x001F7140` | `??0ClearanceTestingSlowDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z` | 1 | `??0CountermeasuresBehavior@@QAE@PAVThing@@PBVModuleData@@@Z`<br>`??0NeutronMissileSlowDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z` |
| `0x001FCB50` | `??1GateProxyBehaviorModuleData@@UAE@XZ` | 2 | `??1GateOpenAndCloseBehaviorModuleData@@UAE@XZ` |
| `0x001FCEC0` | `??0GateOpenAndCloseBehaviorModuleData@@QAE@XZ` | 1 | `??0GateProxyBehaviorModuleData@@QAE@XZ` |
| `0x001FE260` | `??1HordeUpdateModuleData@@UAE@XZ` | 1 | `??1GettingBuiltBehaviorModuleData@@UAE@XZ`<br>`??1Rva001FE190ModuleData@@UAE@XZ` |
| `0x00212C10` | `??0BaikonurLaunchPowerModuleData@@QAE@XZ` | 1 | `??0DelayedDeathBodyModuleData@@QAE@XZ` |
| `0x0022A620` | `?set@Rva0022A620Obj@@QAEXVAsciiString@@@Z` | 1 | `?bfmeSet@Gen0022A620@@QAEXVAsciiString@@@Z` |
| `0x002472D0` | `??0HorseHordeContainModuleData@@QAE@XZ` | 1 | `??0AODHordeContainModuleData@@QAE@XZ` |
| `0x0024D190` | `??0HordeGarrisonContainModuleData@@QAE@XZ` | 2 | `??0Rva0024D190@@QAE@XZ` |
| `0x00268F30` | `??1SpecialPowerModule@@MAE@XZ` | 19 | `??1ManTheWallsSpecialPower@@UAE@XZ`<br>`??1ProductionSpeedBonus@@UAE@XZ` |
| `0x00285650` | `??1BattlePlanUpdate@@UAE@XZ` | 1 | `??1BattlePlanUpdate@@MAE@XZ` |
| `0x0028C2A0` | `??0BaseRegenerateUpdateModuleData@@QAE@XZ` | 1 | `??0DelayedWeaponSetUpgradeUpdateModuleData@@QAE@XZ` |
| `0x00297D60` | `??1GrantStealthBehaviorModuleData@@UAE@XZ` | 1 | `??1LargeGroupBonusUpdateModuleData@@UAE@XZ` |
| `0x002B0AD0` | `??0TemporarilyDefectUpdate@@QAE@PAVThing@@PBVModuleData@@@Z` | 1 | `??0PoisonedBehavior@@QAE@PAVThing@@PBVModuleData@@@Z` |
| `0x002B6640` | `??1DozerAIUpdate@@UAE@XZ` | 1 | `??1DozerAIUpdate@@MAE@XZ` |
| `0x002BC190` | `??0FirestormDynamicGeometryInfoUpdateModuleData@@QAE@XZ` | 1 | `??0GiantBirdAIUpdateModuleData@@QAE@XZ` |
| `0x002CAF40` | `??$__copy@U?$_Bit_iter@U_Bit_reference@_STL@@PAU12@@_STL@@U12@H@_STL@@YA?AU?$_Bit_iter@U_Bit_reference@_STL@@PAU12@@0@U10@00ABUrandom_access_iterator_tag@0@PAH@Z` | 3 | `??$__copy@U?$_Bit_iter@_NPB_N@_STL@@U?$_Bit_iter@U_Bit_reference@_STL@@PAU12@@2@H@_STL@@YA?AU?$_Bit_iter@U_Bit_reference@_STL@@PAU12@@0@U?$_Bit_iter@_NPB_N@0@0U10@ABUrandom_access_iterator_tag@0@PAH@Z` |
| `0x003F69A0` | `?setParentCellHierarchical@PathfindCell@@QAEXPAV1@@Z` | 1 | `?setParentCell@PathfindCell@@QAEXPAV1@@Z` |

Held back for review, because vtable slot names support a name the callers do not use:

- `0x00123620`: a symbols.csv pin routes ??0WeaponBonusUpdateModuleData@@QAE@XZ through ILT 0x0003CA01 to this body
- `0x00252F50`: slot 4 of the installed vtable is named as a TransitionDamageFX method
- `0x002D5280`: the installed vtables name getModuleNameKey and upgradeRemovalImplementation as GarrisonUpgrade methods

Translation units deleted because their only row was retired:

- `Code/GameEngine/Source/Common/Rva000C9710Get.cpp`
- `Code/GameEngine/Source/Common/Rva000C9B40Wrap.cpp`
- `Code/GameEngine/Source/Common/System/UnicodeStringIsEmpty.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Behavior/CountermeasuresBehaviorCtorThunk.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Behavior/GateProxyBehaviorModuleDataCtorThunk.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehaviorModuleDataDestructorThunk.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Behavior/OathbreakersFadeAwayBehaviorModuleDataDestructorThunk.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Behavior/PoisonedBehaviorCtorThunk.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Body/DelayedDeathBodyModuleDataCtor.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/HealCrateCollideModuleDataDestructorThunk.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/MoneyCrateCollideModuleDataDestructorThunk.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/ShroudCrateCollideModuleDataDestructorThunk.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Contain/HordeTransportContainModuleDataCtor.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Die/DestroyDieModuleDataConstructor.cpp`
- `Code/GameEngine/Source/GameLogic/Object/STLLocomotorNameKeyTreeInsertUniqueThunk.cpp`
- `Code/GameEngine/Source/GameLogic/Object/SpecialPower/ManTheWallsSpecialPowerDestructorThunk.cpp`
- `Code/GameEngine/Source/GameLogic/Object/SpecialPower/ProductionSpeedBonusDestructorThunk.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdAIUpdateModuleDataConstructor.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Update/DelayedWeaponSetUpgradeUpdateModuleDataCtor.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Update/LargeGroupBonusUpdateModuleDataDestructorThunk.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Update/NeutronMissileSlowDeathBehaviorCtorThunk.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Update/PowerPlantUpdateModuleDataDestructorThunk.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva001FE190ModuleData.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DPropDrawModuleDataDestructorThunk.cpp`
- `Code/Libraries/Source/WWVegas/WWLib/STLNameKeyFloatTreeInsertUniqueThunk.cpp`
