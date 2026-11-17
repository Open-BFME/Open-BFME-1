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
