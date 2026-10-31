# lea/push of a stack temporary: retail ECX/EDX, ours EAX (2026-10-31)

Several near-miss bodies have the same residue at one site. They push the address of a
stack temporary for a call. Retail forms that address in ECX or EDX. VC7.1 /O2 forms it
in EAX in every bank tried. Nothing else in the window differs, and in each case EAX is
dead at that point in both builds.

| RVA | Body | Site | Retail | Ours | Temporary |
|---|---|---|---|---|---|
| 0x0022DD10 | TransportContain::onContaining (865 B bank, 2 diffs) | +0x25F | `lea edx,[esp+0x24]; push edx` | eax | list default-allocator argument before `lea ecx,list; call ctor` |
| 0x0043A3B0 | GlobalLanguage::parseFontFileName (MASM dump, 2 diffs) | +0x76 | `lea edx,[esp+0x14]; push edx` | eax | pair source for the list node copy after a null-checked placement new |
| 0x0019F500 | BfmeTableERJ::rva0019F500 (MASM dump, 2 diffs) | +0xDC | `lea ecx` / `push ecx` | eax | path argument after a concat receiver |
| 0x00357FC0 | Parameter::ReadParameter (748 B bank, 6 diffs) | +0x26C | `lea ecx,[esp+0x18]; push ecx` | eax | `throw ERROR_BUG` exception object (`push TI; lea; push; mov [tmp],0xDEAD0001; call _CxxThrowException`) |

## Ruled out (this session, model=claude-opus-5-5)

- 0x0022DD10: a named allocator passed to the list ctor, and a provider local placed
  after the list, both stay at 2 diffs. A provider local placed before the list gives
  867 B/196.
- 0x00357FC0: the BFME 2 ParameterReadParameter.cpp early-return arms (donor
  b5a7b8290a) compile byte-identical to the bank.
- Earlier logs for these rows list named or cast throw values, real STLport list/pair
  construction, and optimisation-flag sweeps, all inert.

## Unconfirmed lead

The same choice shows up as a two-instruction pattern in matched code whenever EAX holds
a live value, for example `push eax; lea ecx,[esp+8]; push ecx` after a call result. So
retail may have had a value live in EAX across these sites that our source drops or
recomputes. For example, 0x0022DD10 calls the same getter twice: once for the test, and
again after the list is built. Look for a source spelling that keeps such a value alive
without adding loads.
