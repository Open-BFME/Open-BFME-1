# TextTypeTransition canonical UnicodeString (v3, 2026-10-03)

Existing destructor ??1TextTypeTransition@@UAE@XZ at005A0670/133B duplicates
UnicodeString as an opaque four-byte pad despite the canonical unicode_string.h.
This is HYGIENE under AGENTS.md's “never redeclare a type a header already covers”
rule. The automatic adoption scan excludes padded declarations, leaving this old
source untouched by its normal staged enforcement.

Ghidra read_memory and a separate Capstone decode agree on all134 bytes including
padding. Normal calls at005A06C4 and005A06D1 reach StringBase<unsigned short>::
releaseBuffer008881D0 with receivers this+30 and this+2C respectively. The final
RET is005A06F4 followed byCC at005A06F5. The vptr store still binds0110CCFC.

The parent prologue references handler00C384BE -> FuncInfo00E279A4. Its state2->1
action00C384B3 adjusts saved this by30; state1->0 action00C384A8 adjusts by2C.
Both jump via ILT0003B304 to UnicodeString::~UnicodeString0005EEA0. State0->-1
00C384A0 instead reaches the unchanged base-destructor route0001AA9B ->00489260.
These are independently traced ownership/lifetime facts, not adjacency guesses.

The GeneralsMD GameWindowTransitions.h declaration contains m_fullText and
m_partialText in that order; name_oracle independently witnesses BFME m_fullText
at2C. This edit changes only the string declaration/include search path. It
retains the existing owner/base/display-manager views and asserts no new names.

Strict scoped build: existing133-byte body exact, both anchored DIR32 references
pass; no new row, pin, shared header or baseline. Artifacts:
build/audit_v3/s5_texttype_before.cpp and s5_texttype_build.log.
