# RankInfo parser initializer correction

The matched 356-byte `RankInfoStore::friend_parseRankDefinition` at RVA
`0x003A0DA0` passes VA `0x010EC620` to `INI::initFromINI` at both table
operands, body offsets `+0xAD` and `+0x13B`. The final return is at
`0x003A0F03`, followed by INT3 padding. Ghidra memory and the unpacked retail
PE independently agree on the table bytes. This is a data correction; the
function identity and extent are unchanged.

`AGENTS.md` requires real source and byte verification; `docs/matching.md`
requires literal strings to byte-equal their referenced retail strings.
The old source table contained five 16-byte records including its terminator,
but retail contains ten. It used `SkillPointsNeeded`, while retail uses
`SkillPointsNeededDefault`, followed by five additional skill-point keys.

| Key | Offset | Callback VA |
|---|---:|---:|
| RankName | 0x0C | 0x00432C45 |
| SkillPointsNeededDefault | 0x10 | 0x00C52A60 |
| SkillPointsNeededCampaign | 0x14 | 0x00C52A60 |
| SkillPointsNeededGondor | 0x18 | 0x00C52A60 |
| SkillPointsNeededRohan | 0x1C | 0x00C52A60 |
| SkillPointsNeededMordor | 0x20 | 0x00C52A60 |
| SkillPointsNeededIsengard | 0x24 | 0x00C52A60 |
| SciencesGranted | 0x2C | 0x00442609 |
| SciencePurchasePointsGranted | 0x28 | 0x00C52AC0 |

Every user-data word is zero, followed by one all-zero terminator record.
The existing TU-local RankInfo layout already supplies all these offsets.
Use its existing fields; no layout change, guessed member rename, new pin,
or changed function claim is required. The callbacks are existing
`INI::parseAndTranslateLabel`, `parseInt`, `parseScienceVector`, and
`parseUnsignedInt`. The two ILTs independently decode to RVAs `0x000BA9B0`
and `0x000BCD80`; the other pointers reach the existing parser bodies directly.

Validation: the normal scoped build passes all twelve TU claims, three code
string references and seven recorded DIR32 references. A separate read-only
COFF/retail comparison starts at both parser operands, verifies the entire
160-byte table, all nine pointed-to string contents, all nine named callback
bindings (following retail E9 stubs), and all nonrelocation words. It finds
zero differences after the repair. Before it, the 80-byte table had ten
nonrelocation byte differences and five incorrect references within that
shorter span. This separate initializer proof matters: code relocation
verification alone passed before the repair too.
