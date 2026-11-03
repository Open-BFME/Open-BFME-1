# Gen-alias COMDAT homes replaced by real C++ instantiations (s554 batch h)

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
| 0x7fa80 | 25 | `?dup_0007fa80@@YAXXZ` | game/GameEngine/Source/Common/System/ArchiveFileSystem.cpp | `?_M_empty_initialize@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@V1@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@V1@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@V1@@_STL@@@3@@_STL@@AAEXXZ` |
| 0xa3540 | 41 | `?dup_000a3540@@YAXXZ` | game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva00776AC0ModelTransfer.cpp | `??$__copy_ptrs@PADPAD@_STL@@YAPADPAD00ABU__true_type@0@@Z` |
| 0xa3c00 | 41 | `?dup_000a3c00@@YAXXZ` | game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva00776AC0ModelTransfer.cpp | `??$__uninitialized_copy@PADPAD@_STL@@YAPADPAD00ABU__true_type@0@@Z` |
| 0xa8ae0 | 25 | `?dup_000a8ae0@@YAXXZ` | game/GameEngine/Source/Common/IgnorePreferencesMapCopy.cpp | `?_M_empty_initialize@?$_Rb_tree@HU?$pair@$$CBHVAsciiString@@@_STL@@U?$_Select1st@U?$pair@$$CBHVAsciiString@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHVAsciiString@@@_STL@@@2@@_STL@@AAEXXZ` |
| 0xa8e80 | 26 | `?dup_000a8e80@@YAXXZ` | game/GameEngine/Source/Common/IgnorePreferencesMapCopy.cpp | `?_S_minimum@?$_Rb_tree@HU?$pair@$$CBHVAsciiString@@@_STL@@U?$_Select1st@U?$pair@$$CBHVAsciiString@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHVAsciiString@@@_STL@@@2@@_STL@@KAPAU?$_Rb_tree_node@U?$pair@$$CBHVAsciiString@@@_STL@@@2@PAU32@@Z` |
| 0xa8ea0 | 26 | `?dup_000a8ea0@@YAXXZ` | game/GameEngine/Source/Common/IgnorePreferencesMapCopy.cpp | `?_S_maximum@?$_Rb_tree@HU?$pair@$$CBHVAsciiString@@@_STL@@U?$_Select1st@U?$pair@$$CBHVAsciiString@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHVAsciiString@@@_STL@@@2@@_STL@@KAPAU?$_Rb_tree_node@U?$pair@$$CBHVAsciiString@@@_STL@@@2@PAU32@@Z` |
| 0xcb960 | 26 | `?dup_000cb960@@YAXXZ` | game/GameEngine/Source/GameLogic/ScriptEngine/XferListUnsignedShort.cpp | `??$__distance@U?$_List_iterator@GU?$_Const_traits@G@_STL@@@_STL@@@_STL@@YAHABU?$_List_iterator@GU?$_Const_traits@G@_STL@@@0@0ABUinput_iterator_tag@0@@Z` |
| 0xcd3c0 | 26 | `?dup_000cd3c0@@YAXXZ` | game/GameEngine/Source/GameLogic/ScriptEngine/XferListUnsignedShort.cpp | `??$distance@U?$_List_iterator@GU?$_Const_traits@G@_STL@@@_STL@@@_STL@@YAHABU?$_List_iterator@GU?$_Const_traits@G@_STL@@@0@0@Z` |
| 0xcf730 | 24 | `?dup_000cf730@@YAXXZ` | game/GameEngine/Source/GameLogic/ScriptEngine/XferListUnsignedShort.cpp | `?size@?$list@GV?$allocator@G@_STL@@@_STL@@QBEIXZ` |
| 0xe5d70 | 26 | `?dup_000e5d70@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp | `??$__distance@U?$_List_iterator@W4ObjectID@@U?$_Const_traits@W4ObjectID@@@_STL@@@_STL@@@_STL@@YAHABU?$_List_iterator@W4ObjectID@@U?$_Const_traits@W4ObjectID@@@_STL@@@0@0ABUinput_iterator_tag@0@@Z` |
| 0xe5f00 | 26 | `?dup_000e5f00@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp | `??$distance@U?$_List_iterator@W4ObjectID@@U?$_Const_traits@W4ObjectID@@@_STL@@@_STL@@@_STL@@YAHABU?$_List_iterator@W4ObjectID@@U?$_Const_traits@W4ObjectID@@@_STL@@@0@0@Z` |
| 0xe6020 | 53 | `?dup_000e6020@@YAXXZ` | game/GameEngine/Source/Common/RTS/Team.cpp | `?insert@?$list@W4ObjectID@@V?$allocator@W4ObjectID@@@_STL@@@_STL@@QAE?AU?$_List_iterator@W4ObjectID@@U?$_Nonconst_traits@W4ObjectID@@@_STL@@@2@U32@ABW4ObjectID@@@Z` |
| 0xe6070 | 24 | `?dup_000e6070@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp | `?size@?$list@W4ObjectID@@V?$allocator@W4ObjectID@@@_STL@@@_STL@@QBEIXZ` |
| 0xe6bf0 | 24 | `?dup_000e6bf0@@YAXXZ` | game/GameEngine/Source/Common/RTS/ScienceStoreRootPrereqs.cpp | `??R?$less@W4ScienceType@@@_STL@@QBE_NABW4ScienceType@@0@Z` |
| 0xe6c30 | 22 | `?dup_000e6c30@@YAXXZ` | game/GameEngine/Source/Common/RTS/ScienceStoreRootPrereqs.cpp | `??0?$pair@W4ScienceType@@_N@_STL@@QAE@ABW4ScienceType@@AB_N@Z` |
| 0xe70d0 | 22 | `?dup_000e70d0@@YAXXZ` | game/GameEngine/Source/Common/RTS/ScienceStoreRootPrereqs.cpp | `??0?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBW4ScienceType@@_N@_STL@@U?$_Nonconst_traits@U?$pair@$$CBW4ScienceType@@_N@_STL@@@2@@_STL@@_N@_STL@@QAE@ABU?$_Rb_tree_iterator@U?$pair@$$CBW4ScienceType@@_N@_STL@@U?$_Nonconst_traits@U?$pair@$$CBW4ScienceType@@_N@_STL@@@2@@1@AB_N@Z` |
| 0x124f20 | 25 | `?dup_00124f20@@YAXXZ` | game/GameEngine/Source/Common/Rva00606E60TreeCopyConstructor.cpp | `?_M_empty_initialize@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@VAudioEventRTS@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@VAudioEventRTS@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@VAudioEventRTS@@@_STL@@@3@@_STL@@AAEXXZ` |
| 0x1334b0 | 26 | `?dup_001334b0@@YAXXZ` | game/GameEngine/Source/Common/Rva00606E60TreeCopyConstructor.cpp | `?_S_minimum@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@VAudioEventRTS@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@VAudioEventRTS@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@VAudioEventRTS@@@_STL@@@3@@_STL@@KAPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@VAudioEventRTS@@@_STL@@@2@PAU32@@Z` |
| 0x1334d0 | 26 | `?dup_001334d0@@YAXXZ` | game/GameEngine/Source/Common/Rva00606E60TreeCopyConstructor.cpp | `?_S_maximum@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@VAudioEventRTS@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@VAudioEventRTS@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@VAudioEventRTS@@@_STL@@@3@@_STL@@KAPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@VAudioEventRTS@@@_STL@@@2@PAU32@@Z` |
| 0x16e260 | 41 | `?dup_0016e260@@YAXXZ` | game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/List00754E70InsertDefault.cpp | `??$__copy_ptrs@PBQAVObject@@PAPAV1@@_STL@@YAPAPAVObject@@PBQAV1@0PAPAV1@ABU__true_type@0@@Z` |
| 0x16f6b0 | 41 | `?dup_0016f6b0@@YAXXZ` | game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/List00754E70InsertDefault.cpp | `??$__copy_aux@PBQAVObject@@PAPAV1@@_STL@@YAPAPAVObject@@PBQAV1@0PAPAV1@ABU__true_type@0@@Z` |
| 0x16fef0 | 41 | `?dup_0016fef0@@YAXXZ` | game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/List00754E70InsertDefault.cpp | `??$__uninitialized_copy@PBQAVObject@@PAPAV1@@_STL@@YAPAPAVObject@@PBQAV1@0PAPAV1@ABU__true_type@0@@Z` |
| 0x1c4c30 | 68 | `?dup_001c4c30@@YAXXZ` | game/GameEngine/Source/Common/RTS/Team.cpp | `?set@?$bitset@$0HE@@_STL@@QAEAAV12@IH@Z` |
| 0x1db6b0 | 29 | `?dup_001db6b0@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/ObjectTypes.cpp | `??$__uninitialized_fill_n@PAHIH@_STL@@YAPAHPAHIABHABU__true_type@0@@Z` |
| 0x1db800 | 29 | `?dup_001db800@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/ObjectTypes.cpp | `??$uninitialized_fill_n@PAHIH@_STL@@YAPAHPAHIABH@Z` |
| 0x1db890 | 41 | `?dup_001db890@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/ObjectTypes.cpp | `??$__uninitialized_copy@PAHPAH@_STL@@YAPAHPAH00ABU__true_type@0@@Z` |
| 0x1e1f40 | 23 | `?dup_001e1f40@@YAXXZ` | game/GameEngine/Source/GameClient/LivingWorldEyeTowerDoXfer.cpp | `?_M_set@?$vector@VCoord2D@@V?$allocator@VCoord2D@@@_STL@@@_STL@@IAEXPAVCoord2D@@00@Z` |
| 0x1e2230 | 41 | `?dup_001e2230@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/WeaponStoreDestructor.cpp | `??$__copy_ptrs@PAPAVWeaponTemplate@@PAPAV1@@_STL@@YAPAPAVWeaponTemplate@@PAPAV1@00ABU__true_type@0@@Z` |
| 0x1e5160 | 59 | `?dup_001e5160@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/WeaponStoreDestructor.cpp | `?erase@?$vector@PAVWeaponTemplate@@V?$allocator@PAVWeaponTemplate@@@_STL@@@_STL@@QAEPAPAVWeaponTemplate@@PAPAV3@0@Z` |
| 0x1e56f0 | 42 | `?dup_001e56f0@@YAXXZ` | game/GameEngine/Source/GameLogic/Object/WeaponStoreDestructor.cpp | `?clear@?$vector@PAVWeaponTemplate@@V?$allocator@PAVWeaponTemplate@@@_STL@@@_STL@@QAEXXZ` |
| 0x1f88c0 | 41 | `?dup_001f88c0@@YAXXZ` | game/GameEngine/Source/Common/INI/ParsePrerequisiteUnitThunk.cpp | `??$__copy_ptrs@PBHPAH@_STL@@YAPAHPBH0PAHABU__true_type@0@@Z` |
| 0x1f9100 | 41 | `?dup_001f9100@@YAXXZ` | game/GameEngine/Source/Common/INI/ParsePrerequisiteUnitThunk.cpp | `??$__copy_aux@PBHPAH@_STL@@YAPAHPBH0PAHABU__true_type@0@@Z` |
| 0x1f94d0 | 41 | `?dup_001f94d0@@YAXXZ` | game/GameEngine/Source/Common/INI/ParsePrerequisiteUnitThunk.cpp | `??$__uninitialized_copy@PBHPAH@_STL@@YAPAHPBH0PAHABU__true_type@0@@Z` |
| 0x20ab80 | 26 | `?dup_0020ab80@@YAXXZ` | game/GameEngine/Source/Common/Rva002381C0TemplateCheck.cpp | `??$__distance@U?$_List_iterator@HU?$_Const_traits@H@_STL@@@_STL@@@_STL@@YAHABU?$_List_iterator@HU?$_Const_traits@H@_STL@@@0@0ABUinput_iterator_tag@0@@Z` |
| 0x20ad60 | 26 | `?dup_0020ad60@@YAXXZ` | game/GameEngine/Source/Common/Rva002381C0TemplateCheck.cpp | `??$distance@U?$_List_iterator@HU?$_Const_traits@H@_STL@@@_STL@@@_STL@@YAHABU?$_List_iterator@HU?$_Const_traits@H@_STL@@@0@0@Z` |
| 0x20ae10 | 24 | `?dup_0020ae10@@YAXXZ` | game/GameEngine/Source/Common/Rva002381C0TemplateCheck.cpp | `?size@?$list@HV?$allocator@H@_STL@@@_STL@@QBEIXZ` |
| 0x2334e0 | 41 | `?dup_002334e0@@YAXXZ` | game/GameEngine/Source/Common/ExperienceLevelCopyConstructor.cpp | `??$__copy_ptrs@PAPBVUpgradeTemplate@@PAPBV1@@_STL@@YAPAPBVUpgradeTemplate@@PAPBV1@00ABU__true_type@0@@Z` |
| 0x235630 | 59 | `?dup_00235630@@YAXXZ` | game/GameEngine/Source/Common/ExperienceLevelCopyConstructor.cpp | `?erase@?$vector@PBVUpgradeTemplate@@V?$allocator@PBVUpgradeTemplate@@@_STL@@@_STL@@QAEPAPBVUpgradeTemplate@@PAPBV3@0@Z` |
| 0x235e30 | 42 | `?dup_00235e30@@YAXXZ` | game/GameEngine/Source/Common/ExperienceLevelCopyConstructor.cpp | `?clear@?$vector@PBVUpgradeTemplate@@V?$allocator@PBVUpgradeTemplate@@@_STL@@@_STL@@QAEXXZ` |
| 0x2cb3a0 | 45 | `?dup_002cb3a0@@YAXXZ` | game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp | `?_M_deallocate@?$_Bvector_base@V?$allocator@_N@_STL@@@_STL@@IAEXXZ` |
| 0x2cba40 | 45 | `?dup_002cba40@@YAXXZ` | game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp | `??1?$_Bvector_base@V?$allocator@_N@_STL@@@_STL@@QAE@XZ` |
| 0x2cbef0 | 45 | `?dup_002cbef0@@YAXXZ` | game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp | `??1?$vector@_NV?$allocator@_N@_STL@@@_STL@@QAE@XZ` |
| 0x33a8a0 | 22 | `?dup_0033a8a0@@YAXXZ` | game/GameEngine/Source/GameClient/MapUtil.cpp | `??0?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBVAsciiString@@_N@_STL@@U?$_Nonconst_traits@U?$pair@$$CBVAsciiString@@_N@_STL@@@2@@_STL@@_N@_STL@@QAE@ABU?$_Rb_tree_iterator@U?$pair@$$CBVAsciiString@@_N@_STL@@U?$_Nonconst_traits@U?$pair@$$CBVAsciiString@@_N@_STL@@@2@@1@AB_N@Z` |
| 0x3b74f0 | 50 | `?dup_003b74f0@@YAXXZ` | game/GameEngine/Source/GameClient/LivingWorldEyeTowerDoXfer.cpp | `??$__copy@PAVCoord2D@@PAV1@H@_STL@@YAPAVCoord2D@@PAV1@00ABUrandom_access_iterator_tag@0@PAH@Z` |
| 0x3b7a50 | 52 | `?dup_003b7a50@@YAXXZ` | game/GameEngine/Source/GameClient/LivingWorldEyeTowerDoXfer.cpp | `??$__copy_ptrs@PAVCoord2D@@PAV1@@_STL@@YAPAVCoord2D@@PAV1@00ABU__false_type@0@@Z` |
| 0x44fe70 | 50 | `?dup_0044fe70@@YAXXZ` | game/GameEngine/Source/GameClient/MapUtil.cpp | `??$__copy@PAUICoord2D@@PAU1@H@_STL@@YAPAUICoord2D@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z` |
| 0x450140 | 52 | `?dup_00450140@@YAXXZ` | game/GameEngine/Source/GameClient/MapUtil.cpp | `??$__copy_ptrs@PAUICoord2D@@PAU1@@_STL@@YAPAUICoord2D@@PAU1@00ABU__false_type@0@@Z` |
| 0x4fa6f0 | 97 | `?dup_004fa6f0@@YAXXZ` | game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva00776AC0ModelTransfer.cpp | `??$_M_range_initialize@PAD@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@AAEXPAD0ABUforward_iterator_tag@1@@Z` |
| 0x566820 | 26 | `?dup_00566820@@YAXXZ` | game/GameEngine/Source/Common/System/ArchiveFileSystem.cpp | `?_S_minimum@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@V1@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@V1@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@V1@@_STL@@@3@@_STL@@KAPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@V1@@_STL@@@2@PAU32@@Z` |
| 0x566840 | 26 | `?dup_00566840@@YAXXZ` | game/GameEngine/Source/Common/System/ArchiveFileSystem.cpp | `?_S_maximum@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@V1@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@V1@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@V1@@_STL@@@3@@_STL@@KAPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@V1@@_STL@@@2@PAU32@@Z` |
