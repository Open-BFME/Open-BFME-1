# One small next whole-member recovery: RTC stack checker

Read-only scout on the current B1 library rows and official B2 donor1e864b34.
No compiler, production/Git/claim edits or new coverage. Root has accepted the
proven compiler-ZF MASM exception in principle; reserve both actual RVAs before
any private source/assembler probe.

## Complete reservation scope

| RVA | Full size | Symbol | Proposed B1 owner | Maximum C++ credit |
|---|---:|---|---|---:|
|009F7525|90|@_RTC_CheckStackVars@8|game/Libraries/Source/CRT/VS2003/RtcStack.cpp|1 body/90B|
|009F7502|35|__RTC_CheckEsp|game/masm_dumps/RTC_CheckEsp.asm|0 bodies/0B|

No data, EH tables, shared headers or other source scopes are needed. Existing
callee providers `_RTC_Failure`009F7889/62 and `_RTC_StackFailure`009F7A5B/140 in
RtcError.cpp are read-only dependencies, now authored and normally banked.
Neither this packet nor its callees touch009F9B82..00AD5401/D3DX. No overlap with
Transport's ti_inst or00269C50 work is proposed.

## Original member and ABI authority

Original libc.lib member `..\build\intel\st_obj\stack.obj`, SHA256:

    27d50f13be24c322ef991eb457a85acea2f37e708159d62697e94459638cadd4

It has exactly two runtime sections:35B and90B of.text, no runtime data or EH
sections. Both are COMDAT selection1=NODUPLICATES. The two sections' bytes outside
their actual relocations equal the original retail ranges. The35B section's
REL32 at+20 binds `?_RTC_Failure@@YAXPAXH@Z` to009F7889; the90B section's+63
binds `?_RTC_StackFailure@@YAXPAXPBD@Z` to009F7A5B. The original COFF names,
strong undefined function roles, raw bodies, full extents and actual targets
are all frozen in RTC_STACK_SCOPE.json.

Original CodeView binds:

* `_RTC_CheckStackVars`: procedure type1017,void return,fastcall(cc4),two arguments
  void* and _RTC_framedesc*,90-byte procedure.
* `_RTC_CheckEsp`: type1015,void,cdecl(cc0),zero formal arguments,35-byte procedure.
  Its additional caller-ZF and live-EAX/EDX contract is proved by the actual entry
  and failure path; it cannot be expressed as an ordinary C++ function.
* _RTC_framedesc is8B: signed varCount+0,variable-descriptor pointer+4.
* _RTC_vardesc is12B: signed addr+0,signed size+4,char*name+8.

Public VC7.1 rtcapi.h independently declares the same descriptors,fastcall API
and _ReturnAddress intrinsic declaration. Only SDK declarations and original
object metadata/binary were read; no Microsoft implementation source was used.

## Why the whole pair is necessary

Cpp90 alone leaves __RTC_CheckEsp unresolved, so the link pulls native stack.obj
for35B and also imports its second strong90B definition. This is a real duplicate;
it is not solved by knowing the code bytes match. The original selection1 rule
is explicit evidence against a retain-the-library-sibling partial transfer.

The proper solution is both real source providers, then no reference needs the
original stack.obj member. No archive/index alteration, FORCE, alias, inline
emission trick, pragma or new import provider is needed. Keep this as one
unpublished whole-member change until both owners verify and link together.
There is one new C++ body; the necessary hardware-contract assembly is never
counted as C++ or as an additional recovered high-level body.

The supported B1 native build already dispatches.asm files to VC7/bin/ml.exe
with -nologo,-c,-Cx and explicit output. That assembler exists locally. The
ordinary C++ source uses its original donor profile/O1/G6/Oi/Ob1/MD/GX-; actual
B1 native compilation and code/provider evidence remain work after reservation.

## Current donor and actual link evidence

Current B2 rows own Code/Libraries/Source/CRT/RtcStack.cpp (0075A5C5/90) and
Code/masm_dumps/RTC_CheckEsp.asm (0075A5A2/35). The assembly row records owner
placement approval dated2026-11-04 and explicitly zero C++ credit.

The donor's reverse/attempt_support/0x0075a5c5-crt-stack/readme.md reports both
native sections/relocations and a focused nonexecuted DLL whose map selects the
new objects, with0 duplicates/unresolved. It uses the original CRT archive and
scoped IAT-only import libraries; it is focused closure evidence, not a B1 or
full-game runtime/census result. The earlier real-link-codex-efb5fcbb60-20261104
handoff documents the actual LNK2005 and why placement needed owner approval.
That old refusal was not a failed C++ body; the later complete member/ownership
resolution is the new usable reference recipe.

B1's two failure-reporting callees are now real CPP providers following Root's
completed RTC-error work. This is a concrete dependency change from the earlier
six-member CRT shortlist which parked stack.obj because of its assembly sibling.

## Eligibility and old attempts

Native retirement check is false for both RVAs. progress.source_lane reports
library for both; they currently add no authored C++ bytes. The90-byte body has
no native attempt verdict or stash. CheckEsp has historical blocked C++ attempts
on its three-byte jne/ret prefix: those already prove the flag ABI obstruction.
Do not repeat them, shorten the complete35-byte extent or turn MASM into a
naked C++/emit lift. The hardware exception is the only proposed assembly path.

The prior SourceKind bug in B2's conversion gate was fixed independently there;
B1's current conversion direction uses CPP_SUFFIXES, so.lib is not a preexisting
clean-C++ owner. Existing names and extents can use normal replace-existing
admission. Any TU/placement refusal must still be handled through a documented
native approval route by Root, never a handwritten bypass.

## Proposed next work after Root's reservation

Private copy of both authored donor units into the B1 proper source contexts,
one ordinary compiler/assembler profile, independent descriptor/return-address
and full35-byte flag-contract proof, strict125-byte/relocation comparison and
native source/provider checks. Then a nonexecuted original-archive link closure
must select both new objects and omit the original stack.obj. Do not claim
ordinary source linking from individual row equality.

Root performs normal build.cmd/admission/commit/publication. No existing byte
bank or private trial is an accepted body. Maximum new result here is1 C++
body/90 C++ bytes, with the complete35B compiler helper as required assembly.

RTC_STACK_SCOPE.json is the exact machine-readable claim/TU/data/CV/COMDAT/callee
manifest and carries source/evidence hashes. No additional library leads were
invented to reach a quota: D3DX is excluded; remaining COM class bodies would
require the already forbidden SDK-class duplication; other remaining primitive
CRT library bodies are assembly machinery or Transport's selected family.
