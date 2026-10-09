# RefundDieModuleData::buildFieldParse at 0x00123290

The 36-byte body at RVA 0x00123290 (ret at +0x23, INT3 after) calls
`DieMuxData::getFieldParse` through ILT 0x00019326, adds that table at offset 8,
then adds the table at VA 0x0108B560 at offset 0. That table has three rows and
a NULL terminator:

| token | parser | offset |
| --- | --- | --- |
| `UpgradeRequired` | ILT 0x0004A39A -> `INI::parseUpgradeTemplate` (0x000BB040) | 0x34 |
| `BuildingRequired` | `iniParseObjectFilter` | 0x3C |
| `RefundPercent` | `INI::parsePercentToReal` | 0x38 |

The only reference to the body is ILT 0x0000F4BB (`e9` to 0x00123290). The only
reference to that thunk in the image is the `push 0x0040F4BB` at VA 0x0052330F,
inside the matched `RefundDie::friend_newModuleData` (0x001232C0, 107 bytes),
which passes it to `INI::initFromINIMultiProc` for a freshly built
`RefundDieModuleData`. `RefundDieFriendNewModuleDataThunk.cpp` already documents
that call. RefundDieModuleData's own constructor (0x00123200) zeroes +0x34 and
+0x38 and builds the member at +0x3C, the three offsets the table writes.

So the body is `RefundDieModuleData::buildFieldParse`. The five rows that named
it before, `CreateCrateDieModuleData`, `CreateObjectDieModuleData`,
`EjectPilotDieModuleData`, `InstantDeathBehaviorModuleData` and
`RebuildHoleExposeDieModuleData`, all matched only because the table address is a
masked relocation. Their sources emit Zero Hour tables (`CreationList`,
`HoleName`, ...) that differ from retail's bytes at 0x0108B560, which the body
guard's `static` check records as gate debt. Retail was linked without
identical-COMDAT folding, so one body has one identity; the other four names are
retired and their bodies remain unclaimed elsewhere.
