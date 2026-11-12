# Native security-cookie initializer and source datum

## BFME1 target facts

`___security_init_cookie` is already identified at RVA009F7FC8, complete102B,
from original MSVC71 libc.lib `build\intel\st_obj\seccinit.obj`. This is a same-name
archive-to-source ownership transfer, not a new inferred function identity.
Its eight DIR32 fields are three references to `___security_cookie` and five
KERNEL32 PE imports: GetSystemTimeAsFileTime, GetCurrentProcessId,
GetCurrentThreadId, GetTickCount and QueryPerformanceCounter. No direct calls
or implicit class/parameter conventions occur; the original ATL declaration is
C cdecl void(void).

The cookie is the complete4B native DWORD_PTR at VA012DBDB0, disk bytes
`4e e6 40 bb` (BB40E64E). The original ATL `atlseccook.c` independently defines
this exact compiler-known public name and DEFAULT_SECURITY_COOKIE. Original
`atlmincrt.h` makes DWORD_PTR32-bit for this target. The source provides one
initialized strong4B definition; no numeric address or new pin is used.

## Reference provenance and mapping

BFME2 donor revision76f0baefa6f285d54bc1ca922397674312a5913f, read-only:
`Code/Libraries/Source/CRT/VS2003/security_cookie_init.cpp`. It preserves the
original Microsoft ATL `atlsecinit.c` algorithm and `atlseccook.c` definition;
the original notice remains in the port. BFME1's own canonical inputs are:

- `inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/atlmfc/src/atl/atlmincrt/{atlsecinit.c,atlseccook.c,atlmincrt.h}`
- the same toolchain's `Vc7/PlatformSDK/Include` Windows declarations.

Donor `reference/open-bfme-1/inputs/...` include prefixes map explicitly to
BFME1 `inputs/...`; short cl include paths resolve through the existing build
helper to those exact directories. No donor/nested-reference headers or compiler
are used. Local recipe /O1 /G6 /MD /GX- retains the observed matching compiler
context. Donor `/GS-` produces D4002 (`-G-` ignored) under this compiler; omitting
that unsupported spelling leaves the full102B output unchanged, rather than
claiming a compiler switch took effect when it did not.

The official private bfme2_sweep trial4882e85b87154518a1313d96df6e780e compiled
but rejected dependency stability: its first trace keeps only Path.is_file()
spellings, while second trace also includes Windows case-folded spellings not
present as exact Linux paths (102of109trace lines). This is recorded as a setup/
provenance failure, not evidence against the body. No tool/guard was changed.
Direct isolated local compilation with actual include trace emitted102B with
zero nonrelocation differences; normal source/data gates remain authoritative.

## Current-state reconciliation / limited claim

The old SAME99 diagnostic reports data-stub:___security_cookie three times in
this initializer. Published be8a87ee already supplies native CRT archives, and
its strict link test includes ___security_cookie; do NOT call this a newly
resolved current-head undefined symbol or attribute baseline638041bytes to it.
This repair instead gives the datum a formal typed source owner and moves the
already-proved102B initializer into its original clean C++ source algorithm.
No current-head census/whole-tree cycle, runtime/game execution, aliases, pins,
header changes, generated-code edits or verifier/admission expansion are used.

## Evidence / verification

- `build/integration/security-cookie/before.log`: original archive1/1function,
  eight DIR32 references, zero body findings.
- `build/integration/security-cookie-callees.log`: exact five PE import slots.
- `build/integration/security-cookie/{compile.log,result.json,no-unsupported-gs.log}`:
  private emitted code/recipe and rejected trial explanation.
- `build/integration/security-cookie/include-trace-path-analysis.json`:
  actual compiler path-spelling evidence, no substituted header selection.
- Normal add_match same-name replacement passed1/1function/eightDIR32;
  add_data_match proved initialized4B/sizeof4/zero data relocations. Final
  source gate passes1/1function+1/1data/eightDIR32/zero body findings.
- Two private compile traces resolve to71 unique actual headers with identical
  sets/hashes across both runs; all are within the intended BFME1 toolchain.
  `build/integration/security-cookie/stable-inputs.json` records every raw trace
  spelling and unique Windows-case-insensitive path identity. No tool changed.
- `tools/tests/test_security_cookie_init.py`: five LINK-ONLY controls pass
  (`build/integration/security-cookie/pytest-final.log`): both bases select the
  source initializer/data and original CRT secchk.obj consumer; the native CRT
  alone also resolves both symbols (explicit current-state control); absent
  providers fail and a duplicate strong cookie failsLNK2005. Library hashes
  remain unchanged, no FORCE/aliases, DLLentry0, no linked image executed.
- Initial fixture used wrong Kernel32.lib Linux case and produced four setup
  errors before any link; preserved in pytest-initial-case-error.log. Correct
  actual name is Kernel32.Lib. This was a test setup fix, not a guard bypass.
- ___security_init_cookie has no symbols.csv pin; pin probe reports exactly
  that and no pin is added. The existing ___security_cookie pin is unchanged.
