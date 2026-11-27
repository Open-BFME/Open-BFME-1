# Generic conversion direction classification repair

**Sicher, scoped:** Rule B presently confuses prebuilt binary ownership with
readable C/C++ ownership. The supplied generic fix reuses progress.source_kind;
there is no RTC/RVA/path exception. The private candidate passes all26 new
end-to-end Git/index regressions. All61 other top-level gate functions/classes
are text-identical. No target source, ledger, claim, Git index or shared compiler
object was changed by this worker. Only private fixture repositories were mutated.

## Semantics and historical evidence

The tool's Rule B contract says that a matched RVA which had a clean-C++ source
must retain one. Its diagnostic says that C++ exact must not regress.
progress.py explicitly classifies prebuilt .lib on the assembly code axis,
separately from authored or vendored readable source. Its CPP_SUFFIXES are
.c/.cc/.cpp/.cxx, lowercased; .asm/.s and .lib are not readable C++ coverage.
Library source directories and prebuilt archive files must not be confused:
a real Runtime.c or Runtime.CXX under Libraries/ or inputs/reference/ remains
clean C/C++ and is still protected.

The old predicate `not source.endswith('.asm')` predates binary-member support:
4834c7f638 (2026-08-11) introduced Rule B; e4c007d4ae (2026-08-12) introduced .lib
member verification; 54523fd179 (2026-08-13) formalized source classification.
The latest code comment, matching documentation and progress semantics do not
state any intentional alternative clean-C++ contract for prebuilt binaries.
The old broad test also misses .s, uppercase assembly and uppercase .LIB.

The official BFME2 donor1e864b34 already uses progress.source_kind=='cpp' in its
Rule B. Its additional generated-import exception is a separate policy and is
explicitly NOT ported here. The inventory test helper which combines CPP+LIB
refers to readable EA library source placed under game/Libraries/, not prebuilt
binary .lib files; that directory-based report does not justify this bug.

## Minimal patch and actual behavior

Production proposal is only tools/conversion_gate.py plus the new regression
file tools/tests/test_conversion_gate_source_kind.py. The gate imports the
existing progress.source_kind and changes the clean-source predicate to
`source_kind(source) == 'cpp'`, keeping the same missing-source and per-row naked
proofs. The shared classifier remains the single source of truth and rejects
unsupported matched-source suffixes loudly. No source_kind/progress change,
new helper classification, flag, allowlist, baseline or no-verify is introduced.

This fixes both directions: binary archive->ASM cannot lose readable C++ which
never existed, and actual C++->archive/.s/.S/.ASM can no longer falsely retain
clean-C++ coverage. Real C/C++->ASM/naked remains refused. A retracted claim is
still distinct from a live owner reversal. Other Rule A include/symlink/emit,
asm-only and Rule C generated-dump rules are unchanged, including their entire
function source text. No generated-import relaxation or35B-specific rule exists.

The26 new cases exercise real Git OLD/NEW blobs and the staged index through the
actual main gate, not a mocked predicate. They cover binary .lib/.LIB->MASM,
binary->real C++, real C++ in game/library/reference->MASM, C++->.lib/.LIB/.s/.S/
.ASM, C++->naked and retracted claims, each staged and committed. Non-UTF8 binary
fixture contents are never treated as readable C++ text. These gate fixtures do
not claim independent archive validity, byte equivalence or native game proof;
those checks remain the responsibility of their existing native gates.

## Red/green and preserved limits

Unmodified frozen baseline b419163a2e274013bc061e1ad8303800a3227026c03b5b1d7bba7b214b983120
with exactly those26 tests:14 failed,12 passed in16.30s. Four false archive->ASM
rejections and ten missed C++->archive/alternate-assembly reversals are red.

Candidate1b6407653866f504c67ec6d69087312a4fb5a4474a5915132752904aaecdf794 with the
new tests, all existing conversion tests and existing progress tests:
**241 passed,2 failed,3 setup errors**,175.19s, process exit1. The26 new tests and
215 old tests pass. This is explicitly NOT a wholly green suite.

A focused rerun of exactly those five failing nodes with the immutable original
baseline reproduces the same2 failures and3 setup errors in2.36s:

* The two existing symlink fixtures fail while calling os.symlink, before any
  gate verdict, with Windows1314 (missing symlink privilege).
* The three existing dump_apply converted fixtures get text=None from
  dump_apply.reproduce before gate judgement, with either tool version.

No guard, source, fixture, baseline or skip was changed to suppress those
failures. Four existing encoding tests dynamically reload the unchanged
production tool path instead of using the private module preloaded for the
suite; their Rule A functions are source-identical. This harness limit is
recorded rather than represented as full native integration proof.

The immutable failure-node comparison and complete commands/results/log hashes
are in PATCH_MANIFEST.json, red.log, suite.log and baseline-five.log. Transport
has independently verified the exact AST delta,19 supported suffix/path cases,
5 unsupported failclosed cases, and found no P1/P2 regression. The review does
not convert the five pre-existing fixture failures into passing tests.

## Root integration

conversion-gate-source-kind.patch is unapplied. PATCH_MANIFEST.json freezes the
baseline/current head, source/progress hashes, candidate, tests and commands.
The candidate is a separate generic tooling correction and earns0 bodies/bytes.
Root should integrate and normally test/commit this tooling alone, preserving
all native checks and the five test limits. Then restore the parked complete
RTC source/row pair and retry ordinary native admission/commit, without a
special-case guard or handwritten metadata repair. This tooling patch itself
makes no claim that the parked native pair is banked or the full game links/runs.
