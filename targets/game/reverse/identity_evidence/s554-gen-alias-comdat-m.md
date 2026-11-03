# Gen-alias COMDAT homes replaced by real C++ instantiations (s554 batch m)

Each row below was a `?dup_` gen-alias home whose bytes came from a COMDAT
another TU emits under a different name. Retail was linked without
identical-COMDAT folding, so each address has exactly one identity.

Facts per row, from BFME 1 retail and this repo's build:

- the named matched C++ source emits a COMDAT of the row's size whose bytes
  equal retail outside relocation slots (fewer than a quarter of the bytes are
  relocation slots), and build.sh verifies it with its relocations;
- `tools/ilt_oracle.py check NAME RVA` CONFIRMS the decorated name at the
  address (exact thunk-table slot window; chance fit ~6e-4), and it is the
  only CONFIRMED byte-equal candidate across build/match objects;
- no symbols.csv pin gives the address a different real name.

Types in the names come from the sources' existing declarations (Zero Hour
headers or address-derived views).

| RVA | bytes | previous row | source | name |
|---|---|---|---|---|
| 0xcfaa0 | 24 | `?dup_000cfaa0@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/Behavior/PassiveAreaEffectCollect00202490.cpp | `??0?$bitset@$0LA@@_STL@@QAE@XZ` |
| 0xd0eb0 | 45 | `?dup_000d0eb0@@YAXXZ` | game/GameEngine/Source/Common/Containers/Rva000DE460RecordAssignment.cpp | `??$__uninitialized_copy@PBVAsciiString@@PAV1@@_STL@@YAPAVAsciiString@@PBV1@0PAV1@ABU__false_type@0@@Z` |
| 0xe4380 | 24 | `?dup_000e4380@@YAXXZ` | game/GameEngine/Source/Common/INI/ParsePrerequisiteScienceThunk.cpp | `?size@?$vector@UPrereqUnitRec@ProductionPrerequisite@@V?$allocator@UPrereqUnitRec@ProductionPrerequisite@@@_STL@@@_STL@@QBEIXZ` |
| 0xe6f90 | 25 | `?dup_000e6f90@@YAXXZ` | game/GameEngine/Source/Common/RTS/ScienceStoreGetPurchasableSciences.cpp | `?_M_empty_initialize@?$_Rb_tree@W4ScienceType@@U?$pair@$$CBW4ScienceType@@_N@_STL@@U?$_Select1st@U?$pair@$$CBW4ScienceType@@_N@_STL@@@3@U?$less@W4ScienceType@@@3@V?$allocator@U?$pair@$$CBW4ScienceType@@_N@_STL@@@3@@_STL@@AAEXXZ` |
| 0xecae0 | 22 | `?dup_000ecae0@@YAXXZ` | game/GameEngine/Source/Common/RTS/TeamFactoryList.cpp | `??0?$pair@W4NameKeyType@@W41@@_STL@@QAE@ABW4NameKeyType@@0@Z` |
| 0xf8960 | 22 | `?dup_000f8960@@YAXXZ` | game/GameEngine/Source/Common/RTS/TunnelTracker.cpp | `??$?9U?$_List_iterator@PAVObject@@U?$_Nonconst_traits@PAVObject@@@_STL@@@_STL@@@_STL@@YA_NABV?$reverse_iterator@U?$_List_iterator@PAVObject@@U?$_Nonconst_traits@PAVObject@@@_STL@@@_STL@@@0@0@Z` |
| 0xfd7e0 | 53 | `?dup_000fd7e0@@YAXXZ` | game/GameEngine/Source/GameClient/DrawableListInsert.cpp | `?insert@?$list@PAVDrawable@@V?$allocator@PAVDrawable@@@_STL@@@_STL@@QAE?AU?$_List_iterator@PAVDrawable@@U?$_Nonconst_traits@PAVDrawable@@@_STL@@@2@U32@ABQAVDrawable@@@Z` |
| 0x101f50 | 32 | `?dup_00101f50@@YAXXZ` | game/GameEngine/Source/Common/System/CDManager.cpp | `?getDiskName@CDDrive@@UAE?AVAsciiString@@XZ` |
| 0x1238c0 | 29 | `?dup_001238c0@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/DefaultProductionExitUpdateFriendNewModuleDataThunk.cpp | `??0DefaultProductionExitUpdateModuleData@@QAE@XZ` |
| 0x1342f0 | 47 | `?dup_001342f0@@YAXXZ` | game/GameEngine/Source/Common/Thing/ThingTemplateLocomotorBinding.cpp | `?deallocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@_STL@@@_STL@@QAEXPAU?$_Rb_tree_node@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@2@I@Z` |
| 0x13d7e0 | 27 | `?dup_0013d7e0@@YAXXZ` | game/GameEngine/Source/Common/BitFlags29Xfer.cpp | `?_Unchecked_test@?$bitset@$0BN@@_STL@@QBE_NI@Z` |
| 0x13ecb0 | 28 | `?dup_0013ecb0@@YAXXZ` | game/GameEngine/Source/Common/Thing/ThingTemplate_parseArbitraryFXIntoMap.cpp | `??0?$pair@VAsciiString@@PBVFXList@@@_STL@@QAE@ABVAsciiString@@ABQBVFXList@@@Z` |
| 0x193800 | 28 | `?dup_00193800@@YAXXZ` | game/GameEngine/Source/GameLogic/Map/CachedSidesLoader0019EC80.cpp | `??0?$pair@VAsciiString@@PAVSidesList@@@_STL@@QAE@ABVAsciiString@@ABQAVSidesList@@@Z` |
| 0x194f40 | 22 | `?dup_00194f40@@YAXXZ` | game/Libraries/Source/WWVegas/WWLib/RvaHashFindAsciiString.cpp | `??$?9URva000D7250Value@@VAsciiString@@U?$hash@VAsciiString@@@rts@@URva000D7250ExtractKey@@U?$equal_to@VAsciiString@@@_STL@@V?$allocator@URva000D7250Value@@@6@@_STL@@YA_NABU?$_Hashtable_iterator@URva000D7250Value@@VAsciiString@@U?$hash@VAsciiString@@@rts@@URva000D7250ExtractKey@@U?$equal_to@VAsciiString@@@_STL@@V?$allocator@URva000D7250Value@@@7@@0@0@Z` |
| 0x1d5fe0 | 24 | `?dup_001d5fe0@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/AnimSetVectorInsert.cpp | `?size@?$vector@UAnimSet@GenericObjectCreationNugget@@V?$allocator@UAnimSet@GenericObjectCreationNugget@@@_STL@@@_STL@@QBEIXZ` |
| 0x1db610 | 29 | `?dup_001db610@@YAXXZ` | game/GameEngine/Source/Common/ObjectFilterResolveNames.cpp | `??$fill_n@PAPBVThingTemplate@@IPBV1@@_STL@@YAPAPBVThingTemplate@@PAPBV1@IABQBV1@@Z` |
| 0x1e2310 | 29 | `?dup_001e2310@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/Weapon.cpp | `??$fill_n@PAPAVWeaponTemplate@@IPAV1@@_STL@@YAPAPAVWeaponTemplate@@PAPAV1@IABQAV1@@Z` |
| 0x1eed60 | 24 | `?dup_001eed60@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/Behavior/AutoHealBehavior_playerScan.cpp | `??0AutoHealPlayerScanHelper@@QAE@XZ` |
| 0x205e90 | 23 | `?dup_00205e90@@YAXXZ` | game/GameEngine/Source/Common/BfmeVectorFillInsert36.cpp | `?_M_set@?$vector@UGen_t_0074d9c0_p128pod@@V?$allocator@UGen_t_0074d9c0_p128pod@@@_STL@@@_STL@@IAEXPAUGen_t_0074d9c0_p128pod@@00@Z` |
| 0x20adc0 | 53 | `?dup_0020adc0@@YAXXZ` | game/GameEngine/Source/Common/RTS/Team_DoXfer.cpp | `?insert@?$list@HV?$allocator@H@_STL@@@_STL@@QAE?AU?$_List_iterator@HU?$_Nonconst_traits@H@_STL@@@2@U32@ABH@Z` |
| 0x20be90 | 45 | `?dup_0020be90@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehaviorCreateSpawn.cpp | `?push_back@?$list@HV?$allocator@H@_STL@@@_STL@@QAEXABH@Z` |
| 0x20e220 | 23 | `?dup_0020e220@@YAXXZ` | game/GameEngine/Source/Common/R5VectorDtorEHFramedMemberOffset.cpp | `?_M_set@?$vector@UGen000E5300@@V?$allocator@UGen000E5300@@@_STL@@@_STL@@IAEXPAUGen000E5300@@00@Z` |
| 0x2213a0 | 22 | `?dup_002213a0@@YAXXZ` | game/Libraries/Source/WWVegas/WWLib/RvaTreeInsertUniqueSigned.cpp | `??0?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBHURva002253A0Value@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHURva002253A0Value@@@_STL@@@2@@_STL@@_N@_STL@@QAE@ABU?$_Rb_tree_iterator@U?$pair@$$CBHURva002253A0Value@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHURva002253A0Value@@@_STL@@@2@@1@AB_N@Z` |
| 0x232e30 | 23 | `?dup_00232e30@@YAXXZ` | game/GameEngine/Source/Common/GiantBirdAIUpdateDestructorThunk.cpp | `?_M_set@?$vector@UGiantBirdMemberARecord@@V?$allocator@UGiantBirdMemberARecord@@@_STL@@@_STL@@IAEXPAUGiantBirdMemberARecord@@00@Z` |
| 0x233150 | 27 | `?dup_00233150@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/Update/AttributeModifierAuraUpdate.cpp | `?_Unchecked_test@?$bitset@$06@_STL@@QBE_NI@Z` |
| 0x234660 | 25 | `?dup_00234660@@YAXXZ` | game/GameEngineDevice/Source/MilesAudioDevice/Rva00694710AudioWorkerCtor.cpp | `?_M_empty_initialize@?$_Rb_tree@HHU?$_Identity@H@_STL@@U?$less@H@2@V?$allocator@H@2@@_STL@@AAEXXZ` |
| 0x234bc0 | 56 | `?dup_00234bc0@@YAXXZ` | game/GameEngine/Source/Common/Rva003B9690ToggleKeys.cpp | `??$_M_find@H@?$_Rb_tree@HHU?$_Identity@H@_STL@@U?$less@H@2@V?$allocator@H@2@@_STL@@ABEPAU?$_Rb_tree_node@H@1@ABH@Z` |
| 0x2583e0 | 23 | `?dup_002583e0@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/SpecialPower/CashHackSpecialPower.cpp | `??$_Construct@UUpgrades@CashHackSpecialPowerModuleData@@U12@@_STL@@YAXPAUUpgrades@CashHackSpecialPowerModuleData@@ABU12@@Z` |
| 0x262a10 | 23 | `?dup_00262a10@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/SpecialPower/OCLSpecialPower.cpp | `??$_Construct@UUpgrades@OCLSpecialPowerModuleData@@U12@@_STL@@YAXPAUUpgrades@OCLSpecialPowerModuleData@@ABU12@@Z` |
| 0x2af120 | 23 | `?dup_002af120@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdate.cpp | `??$_Construct@UAngleFXInfo@@U1@@_STL@@YAXPAUAngleFXInfo@@ABU1@@Z` |
| 0x2df860 | 24 | `?dup_002df860@@YAXXZ` | game/GameEngine/Source/Common/Rva00196C60.cpp | `?size@?$vector@UVectorPoint0019E880@@V?$allocator@UVectorPoint0019E880@@@_STL@@@_STL@@QBEIXZ` |
| 0x2f1430 | 22 | `?dup_002f1430@@YAXXZ` | game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp | `??0?$pair@W4ObjectID@@H@_STL@@QAE@ABW4ObjectID@@ABH@Z` |
| 0x337a10 | 23 | `?dup_00337a10@@YAXXZ` | game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineRva00349730.cpp | `?_M_set@?$vector@U?$pair@VAsciiString@@PAVObject@@@_STL@@V?$allocator@U?$pair@VAsciiString@@PAVObject@@@_STL@@@2@@_STL@@IAEXPAU?$pair@VAsciiString@@PAVObject@@@2@00@Z` |
| 0x337d30 | 23 | `?dup_00337d30@@YAXXZ` | game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineNamedMapReveal.cpp | `?_M_set@?$vector@UNamedReveal@@V?$allocator@UNamedReveal@@@_STL@@@_STL@@IAEXPAUNamedReveal@@00@Z` |
| 0x33a420 | 25 | `?dup_0033a420@@YAXXZ` | game/GameEngine/Source/GameClient/MapCache_ctor_Thunk.cpp | `?_M_empty_initialize@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@H@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@H@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@H@_STL@@@3@@_STL@@AAEXXZ` |
| 0x367b00 | 23 | `?dup_00367b00@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/Update/AttributeModifierPoolUpdate_applyAttributeModifier.cpp | `?_M_set@?$vector@UAttributeModifierEntry@@V?$allocator@UAttributeModifierEntry@@@_STL@@@_STL@@IAEXPAUAttributeModifierEntry@@00@Z` |
| 0x367b20 | 23 | `?dup_00367b20@@YAXXZ` | game/GameEngine/Source/Common/Rva003A5250VectorDtor.cpp | `?_M_set@?$vector@VRva003A5250Element@@V?$allocator@VRva003A5250Element@@@_STL@@@_STL@@IAEXPAVRva003A5250Element@@00@Z` |
| 0x367c90 | 23 | `?dup_00367c90@@YAXXZ` | game/GameEngine/Source/Common/BfmeConv1024.cpp | `?_M_set_node@?$_Deque_iterator_base@H@_STL@@QAEXPAPAH@Z` |
| 0x378260 | 23 | `?dup_00378260@@YAXXZ` | game/GameEngine/Source/Common/U6StlAllocatorWidths.cpp | `?_M_set@?$vector@UU6Elem00122910@@V?$allocator@UU6Elem00122910@@@_STL@@@_STL@@IAEXPAUU6Elem00122910@@00@Z` |
| 0x37e980 | 60 | `?dup_0037e980@@YAXXZ` | game/GameEngine/Source/GameClient/GUI/WindowVideoManager_getWinStateTwin.cpp | `??$find@PBVGameWindow@@@?$hashtable@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@PBVGameWindow@@UhashConstGameWindowPtr@Rva00498960WindowVideoManager@@U?$_Select1st@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@U?$equal_to@PBVGameWindow@@@2@V?$allocator@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@@_STL@@QAE?AU?$_Ht_iterator@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@U?$_Nonconst_traits@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@PBVGameWindow@@UhashConstGameWindowPtr@Rva00498960WindowVideoManager@@U?$_Select1st@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@U?$equal_to@PBVGameWindow@@@2@V?$allocator@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@@1@ABQBVGameWindow@@@Z` |
| 0x3bd210 | 41 | `?dup_003bd210@@YAXXZ` | game/GameEngine/Source/Common/LargeGroupAudioMapCopy.cpp | `??$__copy_ptrs@PAPAVSoundKeyPair@@PAPAV1@@_STL@@YAPAPAVSoundKeyPair@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x3c06c0 | 42 | `?dup_003c06c0@@YAXXZ` | game/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldPathFinder.cpp | `?clear@?$vector@PAUDistanceNode003C5990@@V?$allocator@PAUDistanceNode003C5990@@@_STL@@@_STL@@QAEXXZ` |
| 0x3c5460 | 42 | `?dup_003c5460@@YAXXZ` | game/GameEngine/Source/Common/BfmeConv1896.cpp | `?clear@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEXXZ` |
| 0x3cc070 | 41 | `?dup_003cc070@@YAXXZ` | game/GameEngine/Source/Common/Rva0035B2A0DequePushBackAux.cpp | `??$__copy_ptrs@PAPAUGen_t_0035b2a0_p4pod@@PAPAU1@@_STL@@YAPAPAUGen_t_0035b2a0_p4pod@@PAPAU1@00ABU__true_type@0@@Z` |
| 0x3cc130 | 41 | `?dup_003cc130@@YAXXZ` | game/GameEngine/Source/Common/Rva0035AEC0DequePushBackAux.cpp | `??$__copy_ptrs@PAPAUGen_t_0035aec0_p4pod@@PAPAU1@@_STL@@YAPAPAUGen_t_0035aec0_p4pod@@PAPAU1@00ABU__true_type@0@@Z` |
| 0x3cc170 | 29 | `?dup_003cc170@@YAXXZ` | game/GameEngine/Source/GameClient/SubtitleManagerAccessors.cpp | `??$fill_n@PAPAVSubtitleEntry@@IPAV1@@_STL@@YAPAPAVSubtitleEntry@@PAPAV1@IABQAV1@@Z` |
| 0x3f7a60 | 39 | `?dup_003f7a60@@YAXXZ` | game/GameEngine/Source/Common/VectorUICoord2DFillInsertThunk.cpp | `??$__uninitialized_fill_n@PAUICoord2D@@IU1@@_STL@@YAPAUICoord2D@@PAU1@IABU1@ABU__false_type@0@@Z` |
