# Caller-decided bodies, caller-decided-3

Retail was linked without identical-COMDAT folding, so each body has one identity. For every body below, `python3 tools/one_identity.py --callers` found exactly one of its row names called by matched C++ callers at retail call sites into the body or its incremental-link entries, and no other real name called there. The other row names are retired. Generated and assembly callers were not counted, bodies with an unread caller object were left out, and so were library and C-level names.

In this batch some callers also call names that carry an address token (`Gen000FD020`, `Rva00026FC6TailBase`, `rva000097CDTarget`, `Gen00706F70` and similar). Such names are placeholders invented during reconstruction, so they were treated like any other placeholder. At `0x000103F7` the retired row was a truncated spelling of the kept name, not a second function. At `0x00473B00`, `0x004B05A0` and `0x0089CC10` every name is invented; only the `bfme` duplicates were dropped, and the bodies still wait for a real name.

| body | kept | C++ call sites | retired |
|---|---|---|---|
| `0x000103F7` | `?_M_bkt_num_key@?$hashtable@U?$pair@$$CBVAsciiString@@PAUAudioEventInfo@@@_STL@@VAsciiString@@U?$hash@VAsciiString@@@rts@@U?$_Select1st@U?$pair@$$CBVAsciiString@@PAUAudioEventInfo@@@_STL@@@2@U?$equal_to@VAsciiString@@@5@V?$allocator@U?$pair@$$CBVAsciiString@@PAUAudioEventInfo@@@_STL@@@2@@_STL@@ABEIABVAsciiString@@I@Z` | 1 | `?_M_bkt_num_key@?$hashtable@U?$pair@$$CBVAsciiString@@PAUAudioEventInfo@@@_STL@@VAsciiString@@U?$hash@VAsciiString@@@rts@@U?$_Select1st@U?$pair@$$CBVAsciiString@@PAUAudioEventInfo@@@_STL@@@2@U?$equal_to@VAsciiString@@@5@V?$allocator@U?$pair` |
| `0x000FD020` | `??1GeometryRecord@@QAE@XZ` | 2 | `?invoke@Rva000FD020@@QAEXXZ` |
| `0x00101EB0` | `??1DieModuleData@@UAE@XZ` | 1 | `??1UpgradeModuleData@@UAE@XZ` |
| `0x0036D980` | `??$__copy@PAUPayload@DeliverPayloadNugget@@PAU12@H@_STL@@YAPAUPayload@DeliverPayloadNugget@@PAU12@00ABUrandom_access_iterator_tag@0@PAH@Z` | 2 | `??$__copy@PAUParticleSysBoneInfo@@PAU1@H@_STL@@YAPAUParticleSysBoneInfo@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z` |
| `0x00473B00` | `?gen00473B00@@YAXPAX0@Z` | 1 | `?bfmeAssign@@YAXPAVBfmeHandleCV@@PBV1@@Z` |
| `0x004B05A0` | `?gen004B05A0@@YAXPAX0@Z` | 1 | `?bfmeAssignAgain@@YAXPAVBfmeHandleCV@@PBV1@@Z` |
| `0x00706F70` | `??4TRoadSegInfo@@QAEAAU0@ABU0@@Z` | 3 | `??0SplitChoiceStruct@AABTreeBuilderClass@@QAE@ABU01@@Z`<br>`??4SplitChoiceStruct@AABTreeNodeClass@@QAEAAU01@ABU01@@Z` |
| `0x0089CC10` | `?get@Rva0089CC10Object@@QBEHXZ` | 1 | `?bfmeSize@Gen_0089CC10@@QBEHXZ` |

Held back for review, because a pin or a vtable supports a name the callers do not use:

- `0x00123620`: a symbols.csv pin routes ??0WeaponBonusUpdateModuleData@@QAE@XZ to this body
- `0x00252F50`: the vtable its constructor installs names TransitionDamageFX
- `0x002AA910`: a symbols.csv pin routes ??1LevelGrantSpecialPower@@MAE@XZ to this body
- `0x002D5280`: the vtable its constructor installs names GarrisonUpgrade
- `0x005D65B0`: a symbols.csv pin routes ?freeZones@ZoneBlock@@IAEXXZ to this body
- `0x00602ED0`: the vtable its constructor installs names ClientUpdateModule
- `0x008E3600`: a symbols.csv pin routes ?Intersection_Test@CollisionMath@@SA_NABVSphereClass@@ABVAABoxClass@@@Z to this body

Translation units deleted because their only row was retired:

- `Code/GameEngine/Source/Common/Audio/AudioEventInfoHashtableBktNumKeyThunk.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Upgrade/UpgradeModuleDataDestructorThunk.cpp`
