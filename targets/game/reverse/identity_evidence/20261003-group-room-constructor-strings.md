# GameSpyGroupRoom constructor: canonical strings and const empty datum

RVA `0x004FF9B0`, 106 bytes, `??0GameSpyGroupRoom@@QAE@XZ`.
The old TU duplicated both strings and incorrectly stated that the Unicode
empty datum had a mutable `@A` export. AGENTS.md requires canonical headers;
`exports.csv` ordinal1340 independently names RVA F36E54 as
`?TheEmptyString@UnicodeString@@2V1@B`. Its declaration is const.

The GeneralsMD PeerDefs.h:91 twin assigns both empty strings and clears the
five integer fields. Retail/Ghidra VA8FF9B0 agree on all106bytes: native
AsciiString at+0, UnicodeString at+4, integer stores at+8 through+18;
RET at RVA4FFA19, thenCC4FFA1A. `tools/callees.py` identifies narrow
set887C90 and wide set888530. The source still uses those exact contracts.

EH independently verifies the ownership: handlerC2D843 -> FuncInfoE1D850;
state0 actionC2D830 destroys the saved receiver through ILTD828 ->5EE90;
state1 actionC2D838 adds4 and routes through ILT3B304 ->5EEA0. No new action
claim or derived class identity is introduced.

Include ascii_string.h/unicode_string.h; retain locally inlined canonical
wide default construction and assignment to match the witnessed calls.
The object now references the export's exact const empty-string spelling,
without a new pin or fallback. Both narrow/wide address operands retain
retail VA1336E50/1336E54. The old inherited owner and member names are
unchanged; the twin independently supports this existing constructor.

Fresh origin/master retains the same row and old local declarations.
The bounded12-second pickaxe expired, so no exact introduction date is
asserted; the claim survives in the August1 cohort. Strict before/after
1/1 and both recordedDIR32references pass. No ledger/extent/coverage,
shared-header or baseline change. Logs: s6_groupctor_before.log and
s6_groupctor_after.log under build/audit_v3; independent EH chain is in
s6_groupctor_eh.txt.
