# Contradicted parser-table bindings at RVA 00123290

Severity: WRONG, independently reproduced from the unpacked retail PE and
Ghidra memory. No production identity change is made by this finding.

The 36-byte builder at RVA `0x00123290` ends at RET `0x001232B3`, followed
by INT3. It adds DieMuxData at object offset 8, then pushes table VA
`0x0108B560` at instruction RVA `0x001232A6` and calls MultiIniFieldParse::add
at RVA `0x00850920`. The table has three 16-byte records plus its terminator:

| Retail string | String VA | Callback VA | Object offset |
|---|---:|---:|---:|
| UpgradeRequired | 0x0108B548 | 0x0044A39A | 0x34 |
| BuildingRequired | 0x0108B534 | 0x00439865 | 0x3C |
| RefundPercent | 0x0107A548 | 0x00C52EE0 | 0x38 |

All user-data words and all four terminator words are zero. The full bytes are:

```
48b50801 9aa34400 00000000 34000000
34b50801 65984300 00000000 3c000000
48a50701 e02ec500 00000000 38000000
00000000 00000000 00000000 00000000
```

Five current semantic claims use this address: buildFieldParse for
CreateCrateDieModuleData, CreateObjectDieModuleData, EjectPilotDieModuleData,
InstantDeathBehaviorModuleData, and RebuildHoleExposeDieModuleData. Their
source tables do not supply these keys. For example, InstantDeath supplies
FX/OCL/Weapon instead. This is positive data evidence against these table
bindings, beyond merely lacking an identity witness.

An independent caller supplies a stronger owner lead: matched
RefundDie::friend_newModuleData at RVA `0x001232C0` allocates 0x40 bytes,
constructs through ILT RVA `0x00014EA2`, and pushes callback VA `0x0040F4BB`
at RVA `0x0012330E` into INI::initFromINIMultiProc (`0x00852130`). The callback
stub bytes `E9 D0 3D 11 00` route exactly to `0x00123290`. Its existing source
names that callback RefundDieFieldParse. RefundDie::onDie at RVA `0x00255BE0`
independently accesses an upgrade pointer at +0x34 (instruction 0x00255C5A),
a building filter at +0x3C (0x00255C71), and a float refund factor at +0x38
(0x00255C98), consistent with the table. This is not an adjacency inference.

The separate RefundDieModuleData constructor view misleadingly spells the
+0x34 word m_refundPercent and the +0x38 word m_refundMinimum. Its zero stores
can still match despite those false member meanings. A canonical layout
repair must include dependent bodies and must not introduce more aliases.

Applicable rules: AGENTS.md says "Retail was linked without identical-COMDAT
folding, so each body has exactly one identity" and "A green byte-match says
nothing about a name". docs/matching.md requires literal strings to byte-equal
their referenced retail strings. Code-only relocation masking is insufficient
to verify any of the five competing parser initializers.

Repair deferred: retiring competing ledger identities and selecting the exact
canonical owner belongs in one evidence-backed ledger repair. This worktree
still has two inherited aliases already removed upstream; the bodies were
held by another worker, and staging any ledger triggers their whole-tree
alias check. Do not bypass that gate or grow its baseline. Preserve this
finding for integration, and reverify both table and caller/layout together.
