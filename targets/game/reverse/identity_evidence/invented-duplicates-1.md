# Invented duplicate names, invented-duplicates-1

Each body below carried at most one real name plus names invented during reconstruction, which contain an address token (`Rva`, `Gen` or `Mem` followed by eight hex digits) or start with `bfme`. Invented names make no identity claim, and one body keeps one name. Where a real name exists it is kept. A definition in a C source is kept over a C++ wrapper name, because C code calls it and the C++ caller count does not see C callers. Otherwise the invented name that matched C++ callers call is kept, and failing that the one carrying the body's own address. Bodies where callers call more than one of the names were left alone.

| body | kept | why | retired |
|---|---|---|---|
| `0x00065290` | `?method@Rva00065290@@QBEHXZ` | address | `?get@Rva00065290Field@@QBEHXZ` |
| `0x00065C50` | `??0XferException@@QAE@ABV0@@Z` | real | `??0Rva00065C50Owner@@QAE@PAX@Z` |
| `0x00097130` | `?get_value@Rva00097130Offset28PointerGetter@@QAEPAIXZ` | address | `?get@Rva00097130AddressPlus1C@@QBEPAXXZ` |
| `0x000C96F0` | `?setListInScoreScreen@Player@@QAEX_N@Z` | real | `?set@Rva000C96F0ByteSlot@@QAEXE@Z` |
| `0x000C9700` | `?getListInScoreScreen@Player@@QAE_NXZ` | real | `?get@Rva000C9700@@QAEEXZ` |
| `0x000C9770` | `?wrap@Rva000C9770@@QAEXH@Z` | address | `?bfmeForward@Gen_000C9770@@QAEXPAX@Z` |
| `0x0014FD90` | `?copyTo@Rva0014FD90CopySource@@QAEXPAURva0014FD90Pair@@@Z` | address | `?bfmeGetPair@Gen_0014FD90@@QBEXPAH@Z` |
| `0x0018CF10` | `?distanceSquaredTo@Rva0018CF10Owner@@QBEMPBURva0018CF10Point@@@Z` | address | `?rva0018CF10@BfmeBoundaryObject3D@@QBEMPBUBfmeBoundaryPoint3D@@@Z` |
| `0x001A2D50` | `?rva001A2D50@@YAXXZ` | address | `?rva001A2D50Clear@@YAXXZ` |
| `0x001B4980` | `?set@Rva001B4980Object@@QAEXHH@Z` | address | `?bfmeArm@Gen_001B4980@@QAEXHH@Z` |
| `0x001BDD60` | `?get@Rva001BDD60DwordField@@QBEHXZ` | address | `?get@Rva001BDD60Dword@@QBEHXZ` |
| `0x001DE0B0` | `?sortCheapToExpensive@SimpleObjectIterator@@CAMPAVClump@1@0@Z` | real | `?rva001DE0B0@@YAMPAVRva001DE0B0Holder@@0@Z` |
| `0x001DE120` | `?sortExpensiveToCheap@SimpleObjectIterator@@CAMPAVClump@1@0@Z` | real | `?rva001DE120@@YAMPAVRva001DE0B0Holder@@0@Z` |
| `0x0022A060` | `?Rva0022A060Noop@@YGXHH@Z` | address | `?method@Rva0022A060Opaque@@QAEXHH@Z` |
| `0x0026BFA0` | `?getByte@Rva0026BFA0ByteGetter@@QBEEXZ` | address | `?getByte@Rva0026BFA0@@QBEEXZ` |
| `0x00273730` | `?bfmePrivateCommand39@AIUpdateInterface@@MAEXPAVObject@@W4CommandSourceType@@@Z` | address | `?bfmeSendXZ@BfmeHostXZ@@QAEXPAXH@Z` |
| `0x002C2E30` | `?aiDoCommand@GiantBirdAIUpdate@@UAEXPBUAICommandParms@@@Z` | real | `?aiDoCommand@Rva002C2E30CommandSubobject@@UAEXPBUAICommandParms@@@Z` |
| `0x002D34F0` | `?invoke@Rva002D34F0@@QAEXXZ` | address | `?bfmeForward@Gen_002D34F0@@QAEXXZ` |
| `0x002DA6D0` | `?test@Rva002DA6D0@@QAEEPAX0@Z` | address | `?bfmeMatch@Gen_002da6d0@@QAE_NPAX0@Z` |
| `0x002DAD40` | `?test@Rva002DAD40@@QAEEPAX0@Z` | address | `?bfmeMatch@Gen_002dad40@@QAE_NPAX0@Z` |
| `0x002DB220` | `?test@Rva002DB220@@QAEEPAX0@Z` | address | `?bfmeMatch@Gen_002db220@@QAE_NPAX0@Z` |
| `0x002DD290` | `?test@Rva002DD290@@QAEEPAX0@Z` | address | `?bfmeMatch@Gen_002dd290@@QAE_NPAX0@Z` |
| `0x002DDC80` | `?test@Rva002DDC80@@QAEEPAX0@Z` | address | `?bfmeMatch@Gen_002ddc80@@QAE_NPAX0@Z` |
| `0x002DDCA0` | `?test@Rva002DDCA0@@QAEEPAX0@Z` | address | `?bfmeMatch@Gen_002ddca0@@QAE_NPAX0@Z` |
| `0x002DE220` | `?test@Rva002DE220@@QAEEPAX0@Z` | address | `?bfmeMatch@Gen_002de220@@QAE_NPAX0@Z` |
| `0x002DF4C0` | `?test@Rva002DF4C0@@QAEEPAX0@Z` | address | `?bfmeMatch@Gen_002df4c0@@QAE_NPAX0@Z` |
| `0x002DF4E0` | `?test@Rva002DF4E0@@QAEEPAX0@Z` | address | `?bfmeMatch@Gen_002df4e0@@QAE_NPAX0@Z` |
| `0x002E2B50` | `?Rva002E2B50Update@@YAHXZ` | address | `?bfmeMark@@YAHXZ` |
| `0x002ED510` | `??0Rva002ED510@@QAE@XZ` | address | `?clearByte@Rva002ED510Object@@QAEPAV1@XZ` |
| `0x002F0DF0` | `?Rva002F0DF0Store@@YGXE@Z` | address | `?bfmeSetOther@@YGXE@Z` |
| `0x00321EE0` | `?get@Rva00321EE0@@QBEHXZ` | address | `?getBit2@Rva00321EE0@@QBEIXZ` |
| `0x00322040` | `?isPositive@Rva00322040@@QBE_NXZ` | address | `?isPositive@Rva00322040Positive@@QAE_NXZ` |
| `0x00336630` | `?add@Rva00336630@@QAEXM@Z` | address | `?addFloat34@Rva00336630@@QAEXM@Z` |
| `0x0033B310` | `?getField0@Container0C@@QAEHH@Z` | real | `?get@Rva0033B310@@QAEHH@Z` |
| `0x0033C010` | `?getField0@Container38@@QAEHH@Z` | real | `?get@Rva0033C010@@QAEHH@Z` |
| `0x0034FF50` | `?checkAndSet@Rva0034FF50@@QAEXXZ` | address | `?maybeReplace@Rva0034FF50Clamp@@QAEXXZ` |
| `0x0037A810` | `?isNonNegative@Rva0037A810Object@@QAE_NH@Z` | address | `?bfmeFirstIsPositive@Gen_0037A810@@QBEHH@Z` |
| `0x0037A830` | `?isNonNegative@Rva0037A830Object@@QAE_NH@Z` | address | `?bfmeSecondIsPositive@Gen_0037A810@@QBEHH@Z` |
| `0x0037D330` | `?get@Rva0037D330FieldGetter@@QBEPAXXZ` | address | `?body@Rva0037D330Body@@QBEHXZ` |
| `0x003C6F60` | `?copyTo@Rva003C6F60Object@@QAEXPAH@Z` | address | `?bfmeGetPair@Gen_003C6F60@@QBEXPAH@Z` |
| `0x003D4E00` | `?copyTo@Rva003D4E00Source@@QAEXPAURva003D4E00Pair@@@Z` | address | `?bfmeGetPair@Gen_003D4E00@@QBEXPAH@Z` |
| `0x003F69C0` | `?set@Rva003F69C0Object@@QAEXPAHH@Z` | address | `?bfmeSetPair@Gen_003F69C0@@QAEXPAHH@Z` |
| `0x004097F0` | `?rva_004097F0@Rva00409850SubObject@@QAEXE@Z` | address | `?set@Rva004097F0@@QAEXE@Z` |
| `0x0043AC90` | `?createAttackHint@InGameUI@@UAEXPBVGameMessage@@@Z` | real | `?method@Rva0043AC90Owner@@QAEXH@Z` |
| `0x0043AD70` | `?set@Rva0043AD70Source@@QAEXE@Z` | address | `?bfmeSetMode@Gen_0043AD70@@QAEXE@Z` |
| `0x0043ADC0` | `?copyTo@Rva0043ADC0Source@@QAEXPAURva0043ADC0Pair@@@Z` | address | `?bfmeGetPair@Gen_0043AD70@@QBEXPAH@Z` |
| `0x0044F5F0` | `?get@Rva0044F5F0ByteGetter@@QBEEXZ` | address | `?body@Rva0044F5F0Body@@QBEEXZ` |
| `0x00465F70` | `?Rva00465F70NoOp@@YAXXZ` | address | `?Rva00465F70Noop@@YAXXZ` |
| `0x00493E90` | `?get@Rva00493E90@@QBEEXZ` | address | `?test@Rva00493E90Bit0@@QBEEXZ` |
| `0x0049C9C0` | `?get@Rva0049C9C0PointerGetter@@QBEPAXXZ` | address | `?get@Rva0049C9C0Dword@@QBEIXZ` |
| `0x005169E0` | `?wrap@Rva005169E0@@QAEEH@Z` | address | `?bfmeForward_005169E0@@YG_NPAX@Z` |
| `0x00581A40` | `?Rva00581A40Noop@@YAXXZ` | address | `?Rva00581A40@@YAXXZ` |
| `0x00581A90` | `?Rva00581A90Noop@@YAXXZ` | address | `?Rva00581A90@@YAXXZ` |
| `0x00581AC0` | `?Rva00581AC0Noop@@YAXXZ` | address | `?Rva00581AC0@@YAXXZ` |
| `0x00581AD0` | `?Rva00581AD0Noop@@YAXXZ` | address | `?Rva00581AD0@@YAXXZ` |
| `0x0058B030` | `?Rva0058B030False@@YA_NXZ` | address | `?body@Rva0058B030Body@@QBEEXZ` |
| `0x005D4B40` | `?getFirstDword@Rva005D4B40FirstDword@@QAEPAXXZ` | address | `?getValue@Rva005D4B40Owner@@QBEIXZ` |
| `0x006155E0` | `?rva006155e0@BfmeLivingWorldManager@@QAEPAVBfmeItemEQV@@PAX@Z` | address | `?bfmeGetEQV_006155E0@BfmeHostEQV@@QAEPAVLivingWorldSound@@ABVAsciiString@@@Z` |
| `0x0063FED0` | `?Rva0063FED0NoOp@@YAXXZ` | address | `?Rva0063FED0Noop@@YAXXZ` |
| `0x00641DA0` | `?Rva00641DA0Noop@@YAXXZ` | address | `?b_00641da0@@YAXXZ` |
| `0x00651F90` | `?Rva00651F90@@YA_NXZ` | address | `?Rva00651F90False@@YAEXZ` |
| `0x00662950` | `?copyTo@Rva00662950Object@@QAEXPAX@Z` | address | `?bfmeGetPair@Gen_00662950@@QBEXPAH@Z` |
| `0x00681D60` | `?get@Rva00681D60DwordGetter@@QBEIXZ` | address | `?get@Rva00681D60Dword@@QBEIXZ` |
| `0x006925D0` | `?forward@Rva006925D0Wrapper@@QAEPAXPAX@Z` | address | `?method@Rva006925D0@@QAE?AU?$_Ht_iterator@U?$pair@$$CBVAsciiString@@PAUAudioEventInfo@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBVAsciiString@@PAUAudioEventInfo@@@_STL@@@2@VAsciiString@@U?$hash@VAsciiString@@@rts@@U?$_Select1st@U?$pair@$$CBVAsciiString@@PAUAudioEventInfo@@@_STL@@@2@U?$equal_to@VAsciiString@@@6@V?$allocator@U?$pair@$$CBVAsciiString@@PAUAudioEventInfo@@@_STL@@@2@@_STL@@XZ` |
| `0x00695DC0` | `?decrement@Rva00695DC0Counter@@QAEXXZ` | address | `?bfmeDropFirst@Gen_00695DC0@@QAEXXZ` |
| `0x00695DE0` | `?decrement@Rva00695DE0Counter@@QAEXXZ` | address | `?bfmeDropSecond@Gen_00695DC0@@QAEXXZ` |
| `0x006BAEE0` | `?createModuleFactory@Win32GameEngine@@UAEPAVModuleFactory@@XZ` | real | `?createTemplate@Rva006BAEE0Factory@@UBEPAVRva006BAEE0Template@@XZ` |
| `0x00744520` | `?Rva00744520Noop@@YAXXZ` | address | `?b_00744520@@YAXXZ` |
| `0x00782D90` | `?Rva00782D90Zero@@YAHXZ` | address | `?body@Rva00782D90Body@@QBEHXZ` |
| `0x007B8120` | `?get@Rva007B8120DwordField@@QBEIXZ` | address | `?get@Rva007B8120DwordField@@QBEHXZ` |
| `0x007D74B0` | `?Rva007D74B0ReadGlobals@@YAHXZ` | address | `?bfmeProbe@@YAHXZ` |
| `0x007E4790` | `?isAtOrAfterPrevious@Rva007E4790@@QBEEXZ` | address | `?bfmeIsLast@Gen_007E4790@@QBEEXZ` |
| `0x008118D0` | `_Rva008118D0` | C definition | `?Rva008118D0@@YAHXZ` |
| `0x008118F0` | `_Rva008118F0` | C definition | `?Rva008118F0@@YAHXZ` |
| `0x00813E30` | `_Rva00813E30` | C definition | `?Rva00813E30Wrap@@YAHPAVRva00813E30Obj@@@Z` |
| `0x00814040` | `_Rva00814040` | C definition | `?Rva00814040Wrap@@YAHPAVRva00814040Obj@@PBXH@Z` |
| `0x00814070` | `_Rva00814070` | C definition | `?Rva00814070Wrap@@YAHPAVRva00814070Obj@@PAXHPAI@Z` |
| `0x008140A0` | `_Rva008140A0` | C definition | `?Rva008140A0Wrap@@YAHPAVRva008140A0Obj@@PAXHPAI@Z` |
| `0x008142B0` | `_Rva008142B0` | C definition | `?Rva008142B0Set@@YAXPAVRva008142B0Obj@@H@Z` |
| `0x008143A0` | `_Rva008143A0` | C definition | `?Rva008143A0Set@@YAXPAVRva008143A0Obj@@H@Z` |
| `0x008154F0` | `_Rva008154F0` | C definition | `?Rva008154F0Set@@YAXPAVRva008154F0Obj@@H@Z` |
| `0x00815730` | `_Rva00815730` | C definition | `?Rva00815730Set@@YAXPAVRva00815730Obj@@H@Z` |
| `0x00891B80` | `?release@Rva00891B80@@QAEXXZ` | address | `?bfmeRelease@Gen_00891B80@@QAEXXZ` |
| `0x00892500` | `?usesInlineBuffer@Rva00892500Object@@QAE_NXZ` | address | `?bfmeIsEmpty@Gen_00892500@@QBE_NXZ` |
| `0x00892550` | `?usesInlineBuffer@Rva00892550Object@@QAE_NXZ` | address | `?bfmeIsEmpty@Gen_00892550@@QBE_NXZ` |
| `0x008AD330` | `?release@Rva008AD330@@QAEXXZ` | address | `?bfmeRelease@Gen_008AD330@@QAEXXZ` |
| `0x0095C7F0` | `?initialize@Rva0095C7F0State@@QAEXXZ` | address | `?bfmeInit@Gen_0095C7F0@@QAEXXZ` |
| `0x00977870` | `?compute@Rva00977870Object@@QAEHXZ` | address | `?bfmeBytes@Gen_00977870@@QBEHXZ` |

Translation units deleted because their only rows were retired:

- `game/GameEngine/Source/Common/Bfme5TinyFive4.cpp`
- `game/GameEngine/Source/Common/BfmeConv2145.cpp`
- `game/GameEngine/Source/Common/Rva000C9700ByteGetter.cpp`
- `game/GameEngine/Source/Common/Rva001DE0B0Compare.cpp`
- `game/GameEngine/Source/Common/Rva00322040Positive.cpp`
- `game/GameEngine/Source/Common/Rva0033B310Arr.cpp`
- `game/GameEngine/Source/Common/Rva0033C010Arr.cpp`
- `game/GameEngine/Source/Common/Rva0034FF50Clamp.cpp`
- `game/GameEngine/Source/Common/Rva004097F0Set.cpp`
- `game/GameEngine/Source/Common/Rva00465F70Noop.cpp`
- `game/GameEngine/Source/Common/Rva00581A40.cpp`
- `game/GameEngine/Source/Common/Rva00581A90.cpp`
- `game/GameEngine/Source/Common/Rva00581AC0.cpp`
- `game/GameEngine/Source/Common/Rva00581AD0.cpp`
- `game/GameEngine/Source/Common/Rva0063FED0Noop.cpp`
- `game/GameEngine/Source/Common/Rva00744520Noop.cpp`
- `game/GameEngine/Source/Common/Rva007B8120DwordField.cpp`
- `game/GameEngine/Source/Common/Rva00813E30Wrap.cpp`
- `game/GameEngine/Source/Common/Rva00814040Wrap.cpp`
- `game/GameEngine/Source/Common/Rva00814070Wrap.cpp`
- `game/GameEngine/Source/Common/Rva008140A0Wrap.cpp`
- `game/GameEngine/Source/Common/Rva008142B0Set.cpp`
- `game/GameEngine/Source/Common/Rva008143A0Set.cpp`
- `game/GameEngine/Source/Common/Rva008154F0Set.cpp`
- `game/GameEngine/Source/Common/Rva00815730Set.cpp`
- `game/GameEngine/Source/GameClient/System/FXParticleSystem/Rva006BAEE0CreateTemplate.cpp`
- `game/GameEngine/Source/GameLogic/Map/Rva001A2D50Clear.cpp`
- `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002C2E30AiDoCommand.cpp`
- `game/GameEngine/Source/GameNetwork/GameSpy/Thread/GameResultsThread_00641DA0.cpp`

Also deleted: the definition of `?bfmeRelease@Gen_00892890@@QAEXXZ` in `game/GameEngine/Source/Common/S3TeardownHelpers.cpp`, which no ledger row claimed any more; `0x00892890` is matched as `??1Rva00892640Item@@QAE@XZ`.
