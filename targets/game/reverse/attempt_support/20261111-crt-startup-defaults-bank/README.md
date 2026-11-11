# CRT startup default providers: banked for the native-C DIR32 gate repair

Input HEAD: `be8a87eedf61e99ccef8fafaf3c9002f0cbd4786`.
The complete admitted source, five data rows, one function row and independent
identity/boundary evidence are preserved in `admitted-providers.patch`.
`StartupDefaults.c.txt` is the exact source, not production recovery credit.
Apply the patch only after checking current ownership and the gate prerequisite;
its saved `landed` log entry records local admission, not a published commit.

Normal admission already established:
- `__matherr`, RVA `009F7FB0`, complete three-byte `xor eax,eax; ret` C callback,
  header-declared `int __cdecl _matherr(struct _exception *)`.
- Five exact four-byte default globals, using `add_data_match.py`:
  `__commode` VA `0134FBA8`, `__adjust_fdiv` VA `013571F8`,
  `___defaultmatherr` VA `012DBDE0`, `__newmode` VA `0134FBA4`,
  `__dowildcard` VA `0134FBA0`. All zero except `___defaultmatherr = 1`.
- The initial tentative C definitions are four-byte COMMONs, including the
  native COMMON `__adjust_fdiv`; the one-valued math flag is strong initialized
  data and stays together with the callback to avoid selecting `merr.obj` twice.
  Before final landing, give the three originally exclusive `.bss` defaults
  strong zero definitions rather than these initial tentative COMMONs; retain
  `_adjust_fdiv` as native COMMON and verify actual selected providers.

The combined ordinary gate verified **2/2 functions and 5/5 data rows**, but
refused the original `_WinMainCRTStartup` callback DIR32 at `+0xC1` despite its
new correct function row. `build.unrecorded_dir32_problem` recognized function
identities only when their COFF spelling ended in `Z` (the C++ type suffix),
so native C `__matherr` could never qualify. All five scalar failures disappeared;
the callback false rejection was the only remaining failure.

Exact logs in this experiment worktree's ignored `build/integration/`:
`startup-entry-byte-gate.log` (before, six missing identities),
`startup-matherr-admit.log`, `startup-defaults-data-admit.log`,
`startup-defaults-tracked-after-gate.log` (one native-C false rejection), and
`startup-defaults-input-proof.json` (retail/archive/member hashes and operands).
The source/ledger patch was removed from the active tree before the separate,
explicitly approved generic tooling repair. No fake data row for code, pin,
alias, baseline exemption, compiler-profile change or archive modification was
attempted. The blocked false-reject verdict was written with `re_log.py`.

After the separate tool repair: reacquire/confirm claims, restore the legitimate
providers with normal tool admission as required, verify the actual startup
consumer and all data/code providers, and perform strict selected-provider and
runtime omission controls. Parent review and ordinary hooks precede publication.
This bank alone establishes neither full game linkage nor runtime reach.

## Separate native-C gate repair validation

Native C names now need one matched, non-generated function placement linking
under their own public name; pin-only candidates, conflicting data owners,
ambiguous homes, unaligned jumps and same-byte different bodies cannot prove
that identity. Placement is the exact body or an aligned native retail ILT
slot whose actual target is that body. Existing C++/ILT behavior is retained.

`test_dir32_native_c_functions.py` against the original HEAD code produces
8 failures / 13 passes; the final frozen guard/exploit selection passes
156 cases with one existing optional unconfigured red-team matrix skipped.
The separate link-cycle/identity/currency/runtime selection passes117/117.
Exact command wrapper: `build/integration/run-native-c-final.sh`.
Reviewed code/test SHA-256 values are in
`build/integration/native-c-final-manifest.json`.

Known pre-existing test-order limitation: explicitly running
`test_dir32_record.py` before `test_dir32_operator_correction.py` in the mixed
selection produces three operator-correction failures on both original HEAD
code and the corrected code. The operator module alone passes17/17; default
file-order guard coverage above also passes. Baseline reproduction command
loads `git show HEAD:tools/build.py` as the build module before the same mixed
pytest selection, without editing the working source. Logs:
`dir32-baseline-operator-reproduction.log`, `dir32-native-c-green.log`, and
`dir32-operator-isolated.log`. No test was whitelisted, skipped or cache rule
changed to hide that limitation.
