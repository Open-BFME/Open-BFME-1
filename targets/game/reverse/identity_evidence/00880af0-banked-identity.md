# 00880AF0 bank: scope of the borrowed view

This evidence covers only the replacement of the historical bank at
`targets/game/reverse/attempts/0x00880af0.cpp`. It does not rename the published
point test in `game/GameEngine/Source/Common/BfmeBoxContains.cpp`, change a
function or symbol ledger entry, or establish a different native class identity.

## Exact source snapshots

- Before SHA-256:
  `fa6b70afc883be00a62c8e99ebfd7fb9c7465914acd5895bcd16d1ae90e11909`.
- After SHA-256:
  `b110243b3e1dac171a209c2f16679c983e32588715a33ca7d2580480ad3019e1`.
- The after source is exactly the `source` string stored in
  `targets/game/reverse/attempt_history/0x00880af0/b110243b3e1dac171a209c2f16679c983e32588715a33ca7d2580480ad3019e1.json`.
  That receipt records measured score `0.7365`; it is a nonmatching attempt,
  not authored-byte progress.

## What retail independently establishes

The game baseline is
`inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`, SHA-256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
Addresses below are RVAs; its image base is `0x00400000`.

The body occupies `[0x00880AF0, 0x00880C18)`, 296 bytes, with SHA-256
`ee9de5be710b8d360048331c711f10beb784196edf4b72a39eeae2fbddfeb98c`.
It begins `sub esp,0x18`; a stack argument is loaded at `0x00880AF3`.
It reads float words from both that pointer and entry ECX, at offsets
`0,4,8,0xC,0x10,0x14,0x18,0x1C`. Four x87 comparison sequences control
an AL predicate. The false route writes `xor al,al` at `0x00880BAE`;
the true route writes `mov al,1` at `0x00880C10`. The final `ret 4` starts
at `0x00880C15`, followed by INT3 padding at `0x00880C18`. There are no
direct calls, vtable accesses or symbol-name literals in this body.

The identified direct caller is an address-named assembly dump, not a
matched C++ caller naming `BfmeBoxF0::intersects`. At `0x00880CF3` it takes
one local address, pushes it at `0x00880CFB`, takes a second local address
into ECX at `0x00880CFC`, and calls `0x00880AF0` at `0x00880D04`.
It then restores its own frame and returns without interpreting the result.
The 26-byte window `[0x00880CF3,0x00880D0D)` has SHA-256
`fd67f63de9bdb2c4c95d1c3d543602c6e24782972ea1c3b90eda0be68064f617`.
All 121 opcode lines in the retained body disassembly and all eight lines
in that caller window were compared directly with the baseline PE bytes.

These facts justify a borrowed view of eight accessed floats and a source
bool modelling AL=0/1. They do not establish the original declared parameter
or return types, complete native object size, construction, lifetime, owner
class or private method spelling.

## Why the inherited spelling is not a witnessed identity

The historical bank describes an overlap algorithm and says it reused a
nearby point-test layout. Its corresponding historical partial outcome
calls the body “fully identified” from that algorithm and neighbouring
layout. Neither source supplies an export, a named matched caller, a vtable
owner, or another independent witness of the private class/method spelling.
The current function ledger still identifies this body as
`?d_00880af0@@YAXXZ` in an assembly dump. Searches of `exports.csv`,
`ea_evidence.csv`, `field_names.csv`, `bfme_layouts.json` and
`zh_offsets.json` found no `BfmeBoxF0` witness; `name_oracle.py --class
BfmeBoxF0` returned status 2, “no witnessed layout”.

The arithmetic remains compatible with the box-overlap interpretation.
This correction does not claim the native bytes disprove that algorithm or
prove another class. It removes the historical bank's unsupported promotion
of a plausible algorithm and shared layout into a witnessed identity.
`Rva00880AF0::rva00880AF0` explicitly preserves that uncertainty and the
address. The array and inline dot helper are source views of observed
accesses and local arithmetic, not assertions of native array declarations
or aliases of independently identified retail callees.

The two exact correction pairs are `BfmeBoxF0 -> Rva00880AF0` and
`intersects -> rva00880AF0`. They apply only to the two source hashes above.
Published sibling source and its existing identity are unchanged.
