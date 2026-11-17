# Refused compiler pilot: force-inline unused wrong String copies

Input: `f06b09b033d` (continuation task278), with current reviewed provider
snapshot278 and frozen full census43970549635 at `86c8ac5443`.

Read-only discovery found ten source-local AsciiString method definitions
whose current native COMDATs are wrong under RetailTruth and have zero
non-debug relocation references inside their own objects: four `clear`, one
`isNone`, two `toLower`, three `isNotEmpty`.

Hypothesis: adding `__forceinline` to the existing inline method definition
would stop an otherwise unused competing COMDAT from being emitted.
No shared header, method body, declaration name or compiler flags were changed.

Every source and related string-name/family key was reserved before private
experiments. Original ordinary native gates passed. Each old/new private
compile used the original target flags, the same physical wrapper path and
its actual source include context. Separate CodeView controls retained the
complete AsciiString physical contract and method list. Complete runtime
graph checks passed, but **none of the ten candidates removed a wrong
definition**. Therefore all ten were refused as having no demonstrated repair.

Game sources remained unchanged, all pilot leases were released, and zero
completed tasks were added. Useful diagnostics are retained outside the
tracked tree in `diagnostics/continue-20261116-fivehundred/forceinline-pilot/`
and the checkout's `build/codex-20261116-fivehundred/forceinline-pilot/`.
This hypothesis must not be retried unchanged.

Future work needs a different, independently justified emission or call-site
repair. Zero references inside one object does not prove global unreachability;
any actual deletion must still preserve the complete current selected-provider
and consumer contracts. No link gain, executable launch or memory/crash fix
was established by this pilot.

## Declaration-only follow-up at task345

Baseline `f9fe6dc2759`. Ten still-present wrong zero-own-relocation String
copies were rechecked with their source and family/name reservations.
A different bounded hypothesis replaced only each inline method body with
its unchanged declaration. Private compiler controls retained the complete
AsciiString layout and method list. Every ordinary original gate passed.

Eight candidates changed another runtime function, so the full-object proof
refused them. The other two (ThingTemplateResolveNames.cpp and LocalFile.cpp)
retained their owned rows and local runtime graph after removing the targeted
wrong clear copy, but failed the stronger global replacement condition:
Object.cpp still supplied the selected wrong clear body `d08bf29c9c2b`.
The native current index at this boundary contains101 clear copies, all wrong;
there is no measured retail clear replacement to select. Therefore0/10
candidates qualify as an actual provider repair. No source was edited and
all35 scoped leases were released. Zero tasks were counted.

This is evidence against declaration-only deletion as a complete linking
repair, not proof that the wrong outlined copy is unused globally. The
remaining prerequisite is the original StringBase-versus-Ascii caller/provider
binding; existing C++ aliases alone do not create a new retail identity.
Do not repeat these two emission strategies unchanged. The two closest local
candidates simply change `void clear() { ... }` to `void clear();`; their other
class declarations and flags stay unchanged. Full private diagnostics remain
in declaration-only-string-pilot under the session and private build paths.
