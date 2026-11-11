# Native CRT startup default providers

BFME1 input initially reviewed at `be8a87eedf61e99ccef8fafaf3c9002f0cbd4786`;
provider admission resumed after the separate native-C DIR32 gate repair at
`8337c57e34b8f7be226a42017bb89af2bf8cfebb`.
Retail executable SHA-256:
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
Shipped MSVC 7.1 `msvcrt.lib` SHA-256:
`e888617fbd2e153645b92122deab1c6ec437905431243c43aa7310164c0e7779`.

## Independent BFME1 identity, layout and boundary

The ledgered, native `_WinMainCRTStartup` at RVA `009F72C4` supplies an
independent relocation witness for each provider. At the offsets below its
original `crtexew.obj` DIR32 symbol names the corresponding operand read from
BFME1 retail. These are not identities inferred from equal zero bytes.

| Public COFF name | Retail VA | Startup DIR32 offset | Complete initial value / extent |
| --- | --- | --- | --- |
| `__commode` | `0134FBA8` | `+09C` | four zero bytes |
| `__adjust_fdiv` | `013571F8` | `+0AA` | four zero bytes |
| `___defaultmatherr` | `012DBDE0` | `+0BA` | `01 00 00 00`, four bytes |
| `__newmode` | `0134FBA4` | `+0EB` | four zero bytes |
| `__dowildcard` | `0134FBA0` | `+0F8` | four zero bytes |
| `__matherr` | `00DF7FB0` | `+0C1` | `33 C0 C3`, complete three-byte function |

The callback operand is passed to the native `__setusermatherr` import, not
loaded as a datum. The toolchain's public `math.h` declares
`int __cdecl _matherr(struct _exception *)`; including that header preserves
its exact C ABI and avoids a private exception-type declaration. Retail returns
zero without reading the argument. The previous FF25 import thunk ends exactly
at RVA `009F7FB0`, and the next distinct three-byte function starts at
`009F7FB3`; the callback's RET at `009F7FB2` completes the boundary.
`callees.py 0x009F7FB0 3` reports no calls. `eligibility.py` reports this
unrowed address outside no-ground-truth and not retired.

Retail's zero-filled virtual `.data` tail contains the four zero defaults;
`___defaultmatherr` is initialized file data, not an inferred zero-fill value.
The five objects are separate four-byte native integers, not one structure or
an assumed order inside the new source object. Normal data-row verification
must independently prove every complete size and retail range.

## Original archive contracts

The shipped public symbols come from these native archive members:

- `xncommod.obj`: `__commode`, exclusive four-byte `.bss`.
- `adjustfd.obj`: `__adjust_fdiv`, four-byte COMMON, no initialized section.
- `_newmode.obj`: `__newmode`, exclusive four-byte `.bss`.
- `wildcard.obj`: `__dowildcard`, exclusive four-byte `.bss`.
- `merr.obj`: `___defaultmatherr`, exclusive four-byte `.data` initialized to
  one, and `__matherr`, complete relocation-free three-byte `.text`.

All member names carry the `build\intel\dll_obj\` prefix. `crtexew.obj`
also declares a four-byte COMMON `___defaultmatherr`; the `merr.obj` strong
one-valued definition must override that tentative allocation. Keep the flag
and callback in one new owner so the lazy search does not pull `merr.obj` for
one and introduce a second strong definition of the other. `_adjust_fdiv`
retains its native four-byte COMMON semantics; none of these objects is an
import-address cell. The three exclusive zero defaults use explicit zero
initializers in C so they remain strong definitions, not tentative COMMONs.
Their complete writable four-byte zero state is preserved even if the compiler
puts an explicit zero in object `.data` rather than the archive's `.bss`.
No TU-internal placement or identical object-section layout is asserted.
Pristine archive bytes are not edited.

The new source's purpose/layout is supported independently by BFME1's startup
operands and retail contents. Reviewed BFME2 donor revision
`76f0baefa6f285d54bc1ca922397674312a5913f`,
`Code/Libraries/Source/CRT/StartupDefaults.cpp`, supplies the callback-plus-flag
ownership precedent and public CRT signature, not BFME1 addresses. Unlike the
donor's folded `_setargv`/`_matherr` bodies, BFME1 has two distinct bodies at
`009F7FB0` and `009F7FB3`; no alias or fold is introduced and `_setargv` is not
changed. The existing `_fmode` owner is also left unchanged.

## Acceptance scope

The before gate `./build.sh _WinMainCRTStartup` verifies its 511-byte body but
fails six missing DIR32 identities; this is a genuine startup prerequisite,
not a stale-baseline exemption. Admission must use `add_match.py` for the
callback and `add_data_match.py` for the five datums, then reverify the actual
startup consumer and all providers. Strict selected-provider and runtime
controls must distinguish missing/duplicate providers from a genuine fix.
No new pin, alias, baseline entry, compiler profile or verifier exemption is
part of this repair. Scoped success does not establish a complete game link,
authenticated census, closure credit, or game runtime reach.

## Verified results

The ordinary combined provider/consumer gate passes **2/2 functions, 5/5 data
rows, 28 DIR32 references**, with no body-guard findings. Compiled COFF confirms
exclusive `.bss` definitions for the three zero defaults, four-byte COMMON for
`__adjust_fdiv`, initialized one-valued `.data` for `___defaultmatherr`, and the
separate exact three-byte `__matherr` function. No new DIR32 record or pin is
needed; the separately published generic native-C gate prerequisite supplies
proper function-ledger recognition.

`tools/tests/test_crt_startup.py` runs the actual original CRT entry with this
normally verified source object, shipped msvcrt/oldnames/RunTmChk providers,
and a generated non-game test driver. Eight bounded executions cover both
`0x00400000` and `0x10000000`: initializer -> WinMain -> atexit, native default
values, direct math callback result and startup's imported fdiv-state copy.
The missing-initializer controls exit31; missing-callback controls exit33;
adding the original four-byte COMMON also passes, preserving coalescence.
Both maps select all five strong symbols from the new source and startup from
original `msvcrt:crtexew.obj`; the shared scalar remains `<common>`.
Explicitly linking original `merr.obj` as a second owner fails with two
LNK2005 diagnostics and LNK1169, without FORCE, alternate names or stubs.
All selected DLL/name imports are actual BFME1 imports; original archives
remain byte-identical. This is scoped CRT behavior, never a game boot claim.

Scratch proof, exact archive-member hashes and all commands/results are retained
under the experiment worktree's `build/integration/`. Runtime manifest/maps:
`crt-provider-runtime-complete/test_native_crt_startup_defaul0/`; ordinary gate:
`startup-defaults-final-gate.log`. A bounded historical link preview timed out
before a verdict, so current census/whole-game closure gains remain UNKNOWN.
The control-directory lane handoff names the actual measured commits and
validation outcomes.
