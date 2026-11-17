# Two explicit FieldParse consumer reconciliations

Tasks576-577 extend the28-source foundation in20261117-fieldparse-header.md.
This is source/type consistency with exact retained ordinary runtime objects.
No new function recovery, linked-byte, crash, leak, RAM,64-bit, FPS or runtime
improvement is claimed.

## Target evidence

The existing matched lookup at00850880 walks16B entries and supplies callback+4,
userData+8 and offset+12. The matched728B dispatcher00851910 passes the four
pointer arguments. The original four local INI shims define this same contract.

BfmeConv2129 replaces its local descriptor with Common/FieldParse.h. The builder
uses the evidenced token,parse,userData,offset member names; all four fields stay
at0/4/8/12. Constant offsets and original zero stores are retained. The original
64B descriptor table and guard/global ownership are unchanged.

INIFontSubstitution preserves the original ILT pointer j_0001eb4b. The actual
retail5B E9 at RVA0001EB4B resolves to004776E0, whose already matched512B body
takes INI*,void*,void*,const void*. An explicit INIFieldParseProc cast replaces
the old void* placeholder. It changes no relocation, alias, pin or provider.
The old unconverted-parser comment is corrected; no donor-derived name is added.

Read-only donor0630f0ef47d0a818bb2e97583b43cfb1ecd35491 contains the analogous
FontSubstitution Size table and four-argument parseFontSizeMapping callback in
Code/Libraries/Source/WWVegas/WWLib/MixFileCreatorParse.cpp. This supplies context;
the BFME1 matched callback, thunk edge and dispatcher establish the target facts.

## Verification

Both new explicit hypotheses pass private before/after compilations and complete
runtime inventory comparisons, including raw directive bytes and all aliases.
All complete original non-FieldParse CodeView contracts remain identical; the
canonical descriptor uses the same four4B slots and evidenced field roles.
Fresh include traces prove the actual BFME1 Common/FieldParse.h is used.
The native consumer/provider gate passes94/94 rows across6 sources
and101 DIR32 references. It includes all three native INI providers and the
actual matched512B callback. No shared header is edited in this second cohort.
Normal commit/push gates and a separate current full-image census remain required.

| Task | Source | Retained bytes |
|---|---|---|
|576|`game/GameEngine/Source/Common/BfmeConv2129.cpp`|97|
|577|`game/GameEngine/Source/GameClient/GUI/INIFontSubstitution.cpp`|249|
