# DirtySock: six canonical native Windows imports

## Scope and independent native identities

Owning clone `build/link_y4_sleep_fresh_36h`, base `b20cfedf10`.
Scratch receipts and actual selected MAP/PE artifacts: `build/y4_winapi_batch`.

The real retail PE import directory independently identifies each cell below
as a KERNEL32.dll import. Existing canonical DIR32 entries agree. Native
VS2003 PlatformSDK `WinBase.h` declares these exact function signatures; this
is direct vendor-header evidence, not a proposed pin or a guessed layout.

| API | Actual retail IAT VA | Native WinBase.h lines | Native physical signature | Sites |
| --- | --- | --- | --- | ---: |
| DeleteCriticalSection | 0x01358D0C | 2605–2610 | `VOID WINAPI(LPCRITICAL_SECTION)` | 1 |
| InitializeCriticalSection | 0x01358E4C | 2560–2562 | `VOID WINAPI(LPCRITICAL_SECTION)` | 1 |
| EnterCriticalSection | 0x01358D18 | 2567–2569 | `VOID WINAPI(LPCRITICAL_SECTION)` | 2 |
| LeaveCriticalSection | 0x01358E74 | 2574–2576 | `VOID WINAPI(LPCRITICAL_SECTION)` | 2 |
| InterlockedExchange | 0x01358E58 | 1163–1169 (X86 branch) | `LONG WINAPI(LONG volatile*,LONG)` | 4 |
| SetThreadPriority | 0x01358F20 | 2228–2234 | `BOOL WINAPI(HANDLE,int)` | 1 |

The existing pristine Gamespy C windows shim already declares all four
critical-section APIs, supplies DWORD/LONG/BOOL/HANDLE/LPCRITICAL_SECTION and
was already included. Its LONG/int/pointers are all four bytes in the actual
x86 compiler. The missing InterlockedExchange and SetThreadPriority function
prototypes are copied into this TU from their independently read native-header
contracts. WINBASEAPI/WINAPI expand to dllimport/stdcall for normal x86 clients.
The IA64/AMD64 intrinsic branches were inspected and are not this x86 target.
No shared header, shim, compiler flag, global/member type or layout changes.

### Argument representations

- Each critical-section caller reloads its selected node pointer, adds exactly
  `0x0C`, and pushes that address. Explicit casts to the existing native pointer
  type preserve that witnessed address. The local `char[4]` view stays as-is;
  this packet does not claim that view is a complete native object, add field
  accesses, allocate a CRITICAL_SECTION or infer its enclosing object extent.
- InterlockedExchange pushes constant1 and the same four-byte state-word
  address as before: socket/request +`0x54`, selected node +`0x08`. Native
  `LONG volatile*` expresses the existing pointed-at word representation;
  neither the fields nor their physical accesses change. Native signed LONG
  result and old signed int result both occupy EAX and are tested against zero.
- SetThreadPriority loads the existing four-byte thread-handle storage and
  the original priority argument. Its native HANDLE cast preserves the stored
  word and native int preserves the priority. The BOOL result is discarded.
  The thread storage was populated by the actual CreateThread import; its
  callback ABI is outside this repair and its old declaration is untouched.

All8 full caller extents were read using callees.py before the final edit.
Startup FE520's247-byte row includes24 trailing bytes of compiler RTC metadata:
its actual RET is at+222, and the223-byte executable listing reaches it and
reports the APIs. The full247-byte listing warns only while decoding the
non-executable suffix. Both receipts are preserved; all247 bytes and original
self-references remain covered by the gate. No ledger extent is changed.

## Complete source-byte evidence

All six queue keys and all eight affected bodies were claimed together before
source changes. Fresh restored before gate79311 and final after gate65150 both
exit0: **40/40 matched bodies, 113 DIR32**, zero string/float references.

Complete COFF audit checks all40 raw body bytes, every relocation offset/kind
and every external identity. Precisely11 external names change from the six
old address-derived import declarations to their proven native imports; all
other external names stay unchanged. Compiler-local symbol renumbering is
accepted only if section, value, type and storage are identical. Audited changes:

| Body | Operand offset | Old import | Native import |
| --- | ---: | --- | --- |
| `_Rva007FE210` | +17 | `__imp__Rva01358E58Probe@8` | `__imp__InterlockedExchange@8` |
| `_Rva007FE250` | +134 | `__imp__Rva01358E58Probe@8` | `__imp__InterlockedExchange@8` |
| `_Rva007FE520` | +142 | `__imp__Rva01358F20SetPriority@8` | `__imp__SetThreadPriority@8` |
| `_Rva007FEA20` | +88 | `__imp__Rva01358E4CInit@4` | `__imp__InitializeCriticalSection@4` |
| `_Rva007FEAA0` | +69 | `__imp__Rva01358D0CReset@4` | `__imp__DeleteCriticalSection@4` |
| `_Rva007FEB00` | +105 | `__imp__Rva01358E58Probe@8` | `__imp__InterlockedExchange@8` |
| `_Rva007FEB00` | +135 | `__imp__Rva01358D18Enter@4` | `__imp__EnterCriticalSection@4` |
| `_Rva007FEBD0` | +79 | `__imp__Rva01358D18Enter@4` | `__imp__EnterCriticalSection@4` |
| `_Rva007FEBD0` | +103 | `__imp__Rva01358E58Probe@8` | `__imp__InterlockedExchange@8` |
| `_Rva007FEBD0` | +166 | `__imp__Rva01358E74Leave@4` | `__imp__LeaveCriticalSection@4` |
| `_Rva007FECB0` | +114 | `__imp__Rva01358E74Leave@4` | `__imp__LeaveCriticalSection@4` |

## Independent selected-PE binding controls for each API

Final strict control28294 exits0. Each API gets its own positive, original alias,
missing native import archive and fake canonical IAT control. Exact COFF slices
contain its original argument-producing instructions and FF15 calls. They are
reparsed and compared to the original objects, independently compared to
retail outside actual relocated operands, then compared to the actual selected
PE instructions and MAP-selected operand addresses. For the critical-section
APIs the slices explicitly include node load, +0x0C arithmetic and matching
register push; they do not begin after the address production.

| API | Actual argument+call sites and lengths | Native LINK | Old LINK | Missing LINK | Fake LINK / binding |
| --- | --- | ---: | ---: | ---: | --- |
| DeleteCriticalSection | 0x7feada/15B | 0 | 96 | 96 | 0 / rejected |
| InitializeCriticalSection | 0x7fea6d/15B | 0 | 96 | 96 | 0 / rejected |
| EnterCriticalSection | 0x7feb7c/15B, 0x7fec14/15B | 0 | 96 | 96 | 0 / rejected |
| LeaveCriticalSection | 0x7fec6b/15B, 0x7fed17/15B | 0 | 96 | 96 | 0 / rejected |
| InterlockedExchange | 0x7fe214/17B, 0x7fe2c9/17B, 0x7feb5c/17B, 0x7fec2a/17B | 0 | 96 | 96 | 0 / rejected |
| SetThreadPriority | 0x7fe59f/19B | 0 | 96 | 96 | 0 / rejected |

Each independent native positive selected its canonical MAP symbol at actual
native IAT slot0x10002000, and the selected PE import directory identifies that
same cell as the exact DLL/API being tested. Every actual FF15 operand agrees;
all other relocated operands agree with their selected MAP symbols too.
The fake adversary links but selected_import_audit refuses the slot because it
is not the actual native DLL/name import. LINK0 or a canonical name alone is
not proof. APIs are separately audited; no pin, alias bridge or name-only excuse.

Positives use real native import archives with /NODEFAULTLIB, no /FORCE, no
weak alias and no fake native import. Five APIs need no unrelated scaffold.
SetThreadPriority's only labelled unrelated scaffold is the stored thread word
`_g_Rva0130ACB8Thread`: its selected load operand is checked, but neither its
runtime value nor a native datum provider is claimed. The edge controls do not
assert complete caller linkage or runtime closure.

## Currency and honest gains

Published CloseHandle three paths verified against origin before normal landed
release; normal sequential rebase/check_csv preceded claims. Official
link_check7061 exit0 reports **TU LINKED0 ->0**, 6988 own bytes. Independent
before source equals the published CloseHandle source SHA256
`34b8fb79b454c7a1123035dc09a055da566a2367979e8dc281e7728a11a0b669`; that
package's official after receipt supplies the unchanged before state.

Remaining blockers are explicitly listed in link_check_after.log: the untouched
CreateThread alias/callback contract; Rva007F0000/Rva007F0030; two Winsock helper
aliases; and the listed data/message/global providers. No TU-clean or projected
source-closure gain is claimed. Pin consistency passes; CSV passes171164
functions /89947 symbols /28 data rows. No functions/data/symbol/pin rows change.
**0 new C++ bytes, 0 new datum bytes, 0 whole-TU linked-byte gain**; six incorrect
import identities are repaired at11 actual existing C++ edges.

Scratch controls.json records actual numerical exits, all40 audit, all11 sites,
all selected operands, native/fake binding verdicts and exact input hashes.
