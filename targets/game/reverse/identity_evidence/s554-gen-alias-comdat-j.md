# Gen-alias COMDAT homes replaced by real C++ instantiations (s554 batch j)

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
| 0x9b470 | 45 | `?dup_0009b470@@YAXXZ` | game/GameEngine/Source/Common/RTS/Gen_00256a60.cpp | `?push_back@?$list@IV?$allocator@I@_STL@@@_STL@@QAEXABI@Z` |
| 0xa31f0 | 22 | `?dup_000a31f0@@YAXXZ` | game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/GetAdditionalDisconnectsFromUserFile.cpp | `??0?$pair@$$CBHI@_STL@@QAE@ABHABI@Z` |
| 0xa33a0 | 26 | `?dup_000a33a0@@YAXXZ` | game/GameEngine/Source/Common/IntUnsignedMapCopy.cpp | `?_S_minimum@?$_Rb_tree@HU?$pair@$$CBHI@_STL@@U?$_Select1st@U?$pair@$$CBHI@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHI@_STL@@@2@@_STL@@KAPAU?$_Rb_tree_node@U?$pair@$$CBHI@_STL@@@2@PAU32@@Z` |
| 0xa33c0 | 26 | `?dup_000a33c0@@YAXXZ` | game/GameEngine/Source/Common/IntUnsignedMapCopy.cpp | `?_S_maximum@?$_Rb_tree@HU?$pair@$$CBHI@_STL@@U?$_Select1st@U?$pair@$$CBHI@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHI@_STL@@@2@@_STL@@KAPAU?$_Rb_tree_node@U?$pair@$$CBHI@_STL@@@2@PAU32@@Z` |
| 0xa3470 | 22 | `?dup_000a3470@@YAXXZ` | game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/GetAdditionalDisconnectsFromUserFile.cpp | `??0?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBHI@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHI@_STL@@@2@@_STL@@_N@_STL@@QAE@ABU?$_Rb_tree_iterator@U?$pair@$$CBHI@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHI@_STL@@@2@@1@AB_N@Z` |
| 0xb8b70 | 28 | `?dup_000b8b70@@YAXXZ` | game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterRenderObjReadSkyBoxSettings.cpp | `??$find@VAsciiString@@@?$hashtable@U?$pair@$$CBVAsciiString@@PAVSkyboxTextureSet@@@_STL@@VAsciiString@@U?$hash@VAsciiString@@@rts@@U?$_Select1st@U?$pair@$$CBVAsciiString@@PAVSkyboxTextureSet@@@_STL@@@2@U?$equal_to@VAsciiString@@@5@V?$allocator@U?$pair@$$CBVAsciiString@@PAVSkyboxTextureSet@@@_STL@@@2@@_STL@@QAE?AU?$_Ht_iterator@U?$pair@$$CBVAsciiString@@PAVSkyboxTextureSet@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBVAsciiString@@PAVSkyboxTextureSet@@@_STL@@@2@VAsciiString@@U?$hash@VAsciiString@@@rts@@U?$_Select1st@U?$pair@$$CBVAsciiString@@PAVSkyboxTextureSet@@@_STL@@@2@U?$equal_to@VAsciiString@@@6@V?$allocator@U?$pair@$$CBVAsciiString@@PAVSkyboxTextureSet@@@_STL@@@2@@1@ABVAsciiString@@@Z` |
| 0xb8ba0 | 28 | `?dup_000b8ba0@@YAXXZ` | game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterRenderObjReadSkyBoxSettings.cpp | `?find@?$hash_map@VAsciiString@@PAVSkyboxTextureSet@@U?$hash@VAsciiString@@@rts@@U?$equal_to@VAsciiString@@@4@V?$allocator@U?$pair@$$CBVAsciiString@@PAVSkyboxTextureSet@@@_STL@@@_STL@@@_STL@@QAE?AU?$_Ht_iterator@U?$pair@$$CBVAsciiString@@PAVSkyboxTextureSet@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBVAsciiString@@PAVSkyboxTextureSet@@@_STL@@@2@VAsciiString@@U?$hash@VAsciiString@@@rts@@U?$_Select1st@U?$pair@$$CBVAsciiString@@PAVSkyboxTextureSet@@@_STL@@@2@U?$equal_to@VAsciiString@@@6@V?$allocator@U?$pair@$$CBVAsciiString@@PAVSkyboxTextureSet@@@_STL@@@2@@2@ABVAsciiString@@@Z` |
| 0xb9300 | 23 | `?dup_000b9300@@YAXXZ` | game/GameEngine/Source/Common/Bfme/Rva009EC5B0Set.cpp | `?_M_set@?$vector@IV?$allocator@I@_STL@@@_STL@@IAEXPAI00@Z` |
| 0xb9320 | 24 | `?dup_000b9320@@YAXXZ` | game/GameEngine/Source/Common/INI/Rva000BE440ScienceGroups.cpp | `?size@?$vector@V?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@V?$allocator@V?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@2@@_STL@@QBEIXZ` |
| 0xb9340 | 23 | `?dup_000b9340@@YAXXZ` | game/GameEngine/Source/Common/INI/Rva000BE440ScienceGroups.cpp | `?_M_set@?$vector@V?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@V?$allocator@V?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@2@@_STL@@IAEXPAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@2@00@Z` |
| 0xb93d0 | 23 | `?dup_000b93d0@@YAXXZ` | game/GameEngine/Source/Common/INI/Rva000BCFA0ParseUpgradeKeyVector.cpp | `?_M_set@?$vector@PAVUpgradeTemplate@@V?$allocator@PAVUpgradeTemplate@@@_STL@@@_STL@@IAEXPAPAVUpgradeTemplate@@00@Z` |
| 0xb9630 | 29 | `?dup_000b9630@@YAXXZ` | game/GameEngine/Source/Common/Bfme/Rva009EC5B0Set.cpp | `??$fill_n@PAIII@_STL@@YAPAIPAIIABI@Z` |
| 0xb96f0 | 29 | `?dup_000b96f0@@YAXXZ` | game/GameEngine/Source/Common/INI/Rva000BCFA0ParseUpgradeKeyVector.cpp | `??$fill_n@PAPAVUpgradeTemplate@@IPAV1@@_STL@@YAPAPAVUpgradeTemplate@@PAPAV1@IABQAV1@@Z` |
| 0xbef60 | 22 | `?dup_000bef60@@YAXXZ` | game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioCacheReadAudioFile00694230.cpp | `??0?$pair@U?$_Rb_tree_iterator@VAsciiString@@U?$_Nonconst_traits@VAsciiString@@@_STL@@@_STL@@_N@_STL@@QAE@ABU?$_Rb_tree_iterator@VAsciiString@@U?$_Nonconst_traits@VAsciiString@@@_STL@@@1@AB_N@Z` |
| 0xcaa30 | 23 | `?dup_000caa30@@YAXXZ` | game/GameEngine/Source/Common/BfmeConv599.cpp | `?_M_set@?$vector@MV?$allocator@M@_STL@@@_STL@@IAEXPAM00@Z` |
| 0xcb060 | 29 | `?dup_000cb060@@YAXXZ` | game/GameEngine/Source/Common/BfmeConv599.cpp | `??$fill_n@PAMIM@_STL@@YAPAMPAMIABM@Z` |
| 0xcb210 | 26 | `?dup_000cb210@@YAXXZ` | game/GameEngine/Source/Common/NameKeyTypeFloatMap.cpp | `?_S_minimum@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@M@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@M@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@M@_STL@@@3@@_STL@@KAPAU?$_Rb_tree_node@U?$pair@$$CBW4NameKeyType@@M@_STL@@@2@PAU32@@Z` |
| 0xcb230 | 26 | `?dup_000cb230@@YAXXZ` | game/GameEngine/Source/Common/NameKeyTypeFloatMap.cpp | `?_S_maximum@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@M@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@M@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@M@_STL@@@3@@_STL@@KAPAU?$_Rb_tree_node@U?$pair@$$CBW4NameKeyType@@M@_STL@@@2@PAU32@@Z` |
| 0xceb40 | 53 | `?dup_000ceb40@@YAXXZ` | game/GameEngine/Source/Common/RTS/PlayerBfmeLinkedObjLink.cpp | `?insert@?$list@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@QAE?AU?$_List_iterator@PAVObject@@U?$_Nonconst_traits@PAVObject@@@_STL@@@2@U32@ABQAVObject@@@Z` |
| 0xcf020 | 53 | `?dup_000cf020@@YAXXZ` | game/GameEngine/Source/GameLogic/AI/AIPlayerSelectTeamToBuild.cpp | `?insert@?$list@PAVTeamPrototype@@V?$allocator@PAVTeamPrototype@@@_STL@@@_STL@@QAE?AU?$_List_iterator@PAVTeamPrototype@@U?$_Nonconst_traits@PAVTeamPrototype@@@_STL@@@2@U32@ABQAVTeamPrototype@@@Z` |
| 0xcf3e0 | 37 | `?dup_000cf3e0@@YAXXZ` | game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva007739F0ModelVariant.cpp | `?_Unchecked_test@?$bitset@$0BDA@@_STL@@QBE_NI@Z` |
| 0xcffe0 | 45 | `?dup_000cffe0@@YAXXZ` | game/GameEngine/Source/Common/RTS/PlayerBfmeLinkedObjLink.cpp | `?push_back@?$list@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@QAEXABQAVObject@@@Z` |
| 0xd0600 | 45 | `?dup_000d0600@@YAXXZ` | game/GameEngine/Source/GameLogic/AI/AIPlayerSelectTeamToBuild.cpp | `?push_back@?$list@PAVTeamPrototype@@V?$allocator@PAVTeamPrototype@@@_STL@@@_STL@@QAEXABQAVTeamPrototype@@@Z` |
| 0xd0800 | 37 | `?dup_000d0800@@YAXXZ` | game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva007739F0ModelVariant.cpp | `?test@?$bitset@$0BDA@@_STL@@QBE_NI@Z` |
| 0xe6b00 | 41 | `?dup_000e6b00@@YAXXZ` | game/GameEngine/Source/Common/RTS/Science.cpp | `??$__copy_ptrs@PAPAVScienceInfo@@PAPAV1@@_STL@@YAPAPAVScienceInfo@@PAPAV1@00ABU__true_type@0@@Z` |
| 0xe6b50 | 29 | `?dup_000e6b50@@YAXXZ` | game/GameEngine/Source/Common/RTS/Science.cpp | `??$fill_n@PAPAVScienceInfo@@IPAV1@@_STL@@YAPAPAVScienceInfo@@PAPAV1@IABQAV1@@Z` |
| 0xe8bf0 | 22 | `?dup_000e8bf0@@YAXXZ` | game/GameEngine/Source/Common/RTS/ScoreKeeperCounters.cpp | `??0?$pair@QBVThingTemplate@@H@_STL@@QAE@ABQBVThingTemplate@@ABH@Z` |
| 0xe8d40 | 22 | `?dup_000e8d40@@YAXXZ` | game/GameEngine/Source/Common/RTS/ScoreKeeperCounters.cpp | `??0?$pair@U?$_Rb_tree_iterator@U?$pair@QBVThingTemplate@@H@_STL@@U?$_Nonconst_traits@U?$pair@QBVThingTemplate@@H@_STL@@@2@@_STL@@_N@_STL@@QAE@ABU?$_Rb_tree_iterator@U?$pair@QBVThingTemplate@@H@_STL@@U?$_Nonconst_traits@U?$pair@QBVThingTemplate@@H@_STL@@@2@@1@AB_N@Z` |
| 0xeb1e0 | 41 | `?dup_000eb1e0@@YAXXZ` | game/GameEngine/Source/Common/RTS/SpecialPower.cpp | `??$__copy_ptrs@PAPAVSpecialPowerTemplate@@PAPAV1@@_STL@@YAPAPAVSpecialPowerTemplate@@PAPAV1@00ABU__true_type@0@@Z` |
| 0xeb230 | 29 | `?dup_000eb230@@YAXXZ` | game/GameEngine/Source/Common/RTS/SpecialPower.cpp | `??$fill_n@PAPAVSpecialPowerTemplate@@IPAV1@@_STL@@YAPAPAVSpecialPowerTemplate@@PAPAV1@IABQAV1@@Z` |
| 0xf8610 | 26 | `?dup_000f8610@@YAXXZ` | game/GameEngine/Source/Common/BfmeConv443.cpp | `??$__distance@U?$_List_iterator@PAVObject@@U?$_Const_traits@PAVObject@@@_STL@@@_STL@@@_STL@@YAHABU?$_List_iterator@PAVObject@@U?$_Const_traits@PAVObject@@@_STL@@@0@0ABUinput_iterator_tag@0@@Z` |
| 0xf87d0 | 26 | `?dup_000f87d0@@YAXXZ` | game/GameEngine/Source/Common/BfmeConv443.cpp | `??$distance@U?$_List_iterator@PAVObject@@U?$_Const_traits@PAVObject@@@_STL@@@_STL@@@_STL@@YAHABU?$_List_iterator@PAVObject@@U?$_Const_traits@PAVObject@@@_STL@@@0@0@Z` |
| 0xfd890 | 53 | `?dup_000fd890@@YAXXZ` | game/GameEngine/Source/Common/System/BuildAssistant.cpp | `?insert@?$list@PAVObjectSellInfo@@V?$allocator@PAVObjectSellInfo@@@_STL@@@_STL@@QAE?AU?$_List_iterator@PAVObjectSellInfo@@U?$_Nonconst_traits@PAVObjectSellInfo@@@_STL@@@2@U32@ABQAVObjectSellInfo@@@Z` |
| 0xfe170 | 45 | `?dup_000fe170@@YAXXZ` | game/GameEngine/Source/Common/System/BuildAssistant.cpp | `?push_back@?$list@PAVObjectSellInfo@@V?$allocator@PAVObjectSellInfo@@@_STL@@@_STL@@QAEXABQAVObjectSellInfo@@@Z` |
| 0x13a6e0 | 25 | `?dup_0013a6e0@@YAXXZ` | game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp | `?ID@?$VectorClass@VStringClass@@@@UAEHPBVStringClass@@@Z` |
| 0x13b750 | 25 | `?dup_0013b750@@YAXXZ` | game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp | `?ID@?$DynamicVectorClass@VStringClass@@@@UAEHPBVStringClass@@@Z` |
| 0x14bd00 | 53 | `?dup_0014bd00@@YAXXZ` | game/GameEngine/Source/GameLogic/AI/AI_createGroup.cpp | `?insert@?$list@PAVAIGroup@@V?$allocator@PAVAIGroup@@@_STL@@@_STL@@QAE?AU?$_List_iterator@PAVAIGroup@@U?$_Nonconst_traits@PAVAIGroup@@@_STL@@@2@U32@ABQAVAIGroup@@@Z` |
| 0x14c480 | 45 | `?dup_0014c480@@YAXXZ` | game/GameEngine/Source/GameLogic/AI/AI_createGroup.cpp | `?push_back@?$list@PAVAIGroup@@V?$allocator@PAVAIGroup@@@_STL@@@_STL@@QAEXABQAVAIGroup@@@Z` |
| 0x18b400 | 41 | `?dup_0018b400@@YAXXZ` | game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva00755170RenderSynchronization.cpp | `??$__copy_ptrs@PAPAVObject@@PAPAV1@@_STL@@YAPAPAVObject@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x18b440 | 29 | `?dup_0018b440@@YAXXZ` | game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva00755170RenderSynchronization.cpp | `??$fill_n@PAPAVObject@@IPAV1@@_STL@@YAPAPAVObject@@PAPAV1@IABQAV1@@Z` |
| 0x191c10 | 22 | `?dup_00191c10@@YAXXZ` | game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioCacheReadAudioFile00694230.cpp | `??0?$pair@U?$_Rb_tree_iterator@VAsciiString@@U?$_Const_traits@VAsciiString@@@_STL@@@_STL@@_N@_STL@@QAE@ABU?$_Rb_tree_iterator@VAsciiString@@U?$_Const_traits@VAsciiString@@@_STL@@@1@AB_N@Z` |
| 0x1f8780 | 24 | `?dup_001f8780@@YAXXZ` | game/GameEngine/Source/Common/R5VectorDtorEHFramed.cpp | `?size@?$vector@V?$vector@HV?$allocator@H@_STL@@@_STL@@V?$allocator@V?$vector@HV?$allocator@H@_STL@@@_STL@@@2@@_STL@@QBEIXZ` |
| 0x1f87a0 | 23 | `?dup_001f87a0@@YAXXZ` | game/GameEngine/Source/Common/R5VectorDtorEHFramed.cpp | `?_M_set@?$vector@V?$vector@HV?$allocator@H@_STL@@@_STL@@V?$allocator@V?$vector@HV?$allocator@H@_STL@@@_STL@@@2@@_STL@@IAEXPAV?$vector@HV?$allocator@H@_STL@@@2@00@Z` |
| 0x200a40 | 29 | `?dup_00200a40@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/Behavior/InstantDeathBehavior.cpp | `??$fill_n@PAPBVObjectCreationList@@IPBV1@@_STL@@YAPAPBVObjectCreationList@@PAPBV1@IABQBV1@@Z` |
| 0x200a70 | 29 | `?dup_00200a70@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/Behavior/InstantDeathBehavior.cpp | `??$fill_n@PAPBVWeaponTemplate@@IPBV1@@_STL@@YAPAPBVWeaponTemplate@@PAPBV1@IABQBV1@@Z` |
| 0x221150 | 22 | `?dup_00221150@@YAXXZ` | game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doLoadAllTransports.cpp | `??0?$pair@W4ObjectID@@I@_STL@@QAE@ABW4ObjectID@@ABI@Z` |
| 0x2222a0 | 22 | `?dup_002222a0@@YAXXZ` | game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doLoadAllTransports.cpp | `??$make_pair@W4ObjectID@@I@_STL@@YA?AU?$pair@W4ObjectID@@I@0@ABW4ObjectID@@ABI@Z` |
| 0x232ae0 | 22 | `?dup_00232ae0@@YAXXZ` | game/GameEngineDevice/Source/W3DDevice/GameClient/TaintBufferCollectDirtyCells.cpp | `??0?$pair@U?$_Rb_tree_iterator@HU?$_Const_traits@H@_STL@@@_STL@@_N@_STL@@QAE@ABU?$_Rb_tree_iterator@HU?$_Const_traits@H@_STL@@@1@AB_N@Z` |
| 0x2348c0 | 22 | `?dup_002348c0@@YAXXZ` | game/GameEngineDevice/Source/W3DDevice/GameClient/TaintBufferCollectDirtyCells.cpp | `??0?$pair@U?$_Rb_tree_iterator@HU?$_Nonconst_traits@H@_STL@@@_STL@@_N@_STL@@QAE@ABU?$_Rb_tree_iterator@HU?$_Nonconst_traits@H@_STL@@@1@AB_N@Z` |
