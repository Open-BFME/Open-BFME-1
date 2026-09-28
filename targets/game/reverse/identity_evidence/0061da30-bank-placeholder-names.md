# 0x0061DA30 banked attempt: Open-BFME5 "BG" placeholders retired

The bank `targets/game/reverse/attempts/0x0061da30.cpp` previously named its
body `?bfmeBaseInitBG@BfmeNamedBG@@QAEXVAsciiStringBG@@@Z`, a TU-local
Open-BFME5 spelling. Neither name is a retail or Zero Hour identity:

- `AsciiStringBG` is a TU-local redeclaration of `AsciiString`
  (`StringBaseNarrowBG` + a copy ctor). The rewritten bank includes the real
  `ascii_string.h` instead, as AGENTS.md requires; `rg AsciiStringBG
  inputs/reference` finds nothing.
- `bfmeBaseInitBG` / `BfmeNamedBG` do not occur in `inputs/reference`. The
  only pins (`symbols.csv`, both at 0x0001BD5B) came from the same Open-BFME5
  lift and say only "the base initialiser the named constructor at 0x0060AAE0
  calls". The body at 0x0061DA30 is a polymorphic constructor: it installs a
  vftable and returns `this`, and
  `??0Rva0060BEB0Object@@QAE@VAsciiString@@@Z` (0x0060BEB0, matched) is
  already recorded as "derived constructor over the 0x0061DA30 base". A
  `void` member function called `bfmeBaseInitBG` misstates its ABI.

No matched caller, emitter or ZH twin gives the class a source-level name.
The seat therefore renamed it to the address-derived constructor
`??0Rva0061DA30Base@@QAE@VAsciiString@@@Z`. The rename applies only to the
banked attempt. The matched sources `BfmeNamedCtorBG.cpp` and
`Rva0060BBD0Ctor.cpp`, and their pins, keep their spellings.
