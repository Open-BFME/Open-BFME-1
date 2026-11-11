# Native `_setargv` at RVA 009F7FB3

Input BFME1 HEAD: `4352be1ade8363663526157f0f4457e7e24041b9`.
The existing three-byte generated `Gen_009f7fb3::m` identity is not the native
ABI: this is the CRT's public C `int __cdecl _setargv(void)` default entry.

## Independent BFME1 identity and boundary

Original `msvcrt.lib` member `build\intel\dll_obj\crtexew.obj` has a REL32
relocation named `__setargv` at startup offset `+0xB4`. Reading that operand
from the ledgered BFME1 `_WinMainCRTStartup` at RVA009F72C4 resolves **directly
to RVA009F7FB3**, not to an ILT, import, math callback or byte-twin alias.
The caller passes no arguments. The original archive public C symbol is
`__setargv` (source spelling `_setargv`); its complete three-byte implementation
returns integer zero without reading arguments or memory.

The defining archive member is `build\intel\dll_obj\dllargv.obj`, SHA-256
`49c5a9192deeb991a5000df50d84c4baec9f9c7c6955026ed1172ab595dd95b2`.
Its complete executable section is `33 C0 C3`, with no relocations, exactly the
retail extent009F7FB3..009F7FB6. The preceding independently owned math callback
ends at009F7FB3; the following FF25 `__p__commode` import thunk begins at009F7FB6.
Thus these are **two distinct complete physical bodies**, even though both
return zero. `callees.py 0x009F7FB3 3` reports no calls; eligibility reports the
address outside no-ground-truth and not retired. No retained non-generated
source references the old placeholder class name.

## Donor scope and adaptation

Reviewed donor76f0baefa6f285d54bc1ca922397674312a5913f,
`Code/Libraries/Source/CRT/StartupDefaults.cpp`, carries the same native C
signature and keeps the default callback entries in one CRT owner. Unlike that
donor's folded placement, BFME1's `_matherr` and `_setargv` have different entry
addresses. Preserve separate COFF definitions and `/OPT:NOICF`; do not add an
alias, fold, second identity at the math callback or a source pointer cast.
The similarly named `___setargv` in another archive member is a different
symbol and is not part of this repair.

The proper BFME1 source is the already verified native-defaults owner
`game/Libraries/Source/CRT/StartupDefaults.c`. Repoint the one generated shim
row through normal add_match admission; do not edit generated source. Reverify
both C functions, all five existing datums and actual startup consumer. The
existing strict non-game runtime regression must additionally select both
public functions from this owner and prove their linked addresses differ at
both bases. This is a native provider/ABI repair, not a whole-game link,
closure certificate or new percentage claim for already generated C++ bytes.

## Verification

The ordinary combined gate passes3/3 functions, all5 data rows and28 DIR32
references, with no body-guard findings. The updated source-named non-game
runtime regression passes all8 two-base cases, selects both native C publics
from this source and proves their linked addresses differ under `/OPT:NOICF`.
Original omission/duplicate/COMMON controls remain in place. Source/test and
all executable hashes are bound by the runtime manifest; no original archive
is edited. Parent independently reviewed the original and target witnesses,
normal gates, source/test hashes and all eight selected-provider maps.

Exact archive/call proof is retained in ignored
`build/integration/setargv-input-proof.json`; runtime maps/manifest are under
`build/integration/setargv-runtime/test_native_crt_startup_defaul0/`.
The lane control handoff records actual publication and claim release.
