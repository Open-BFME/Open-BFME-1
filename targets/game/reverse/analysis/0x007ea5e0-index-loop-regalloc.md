# 0x007EA5E0 — an index loop is what moves EBP/EBX

`Rva007EAServiceList::dispatch` (FESL service-hub notify pass) sat at 85 bytes
against retail's 87 for eight sessions, all filed as
`blocker=regalloc/ebx-ebp-and-slot-load`. The visible symptom was a letter
mirror — retail keeps `this` in EBP and the service stamp in EBX, every build
kept `this` in EBX and the stamp in EBP — plus the two-byte residue that
followed from it: retail loads each slot with `mov eax,[esi]` and copies
`mov ecx,eax` before the service vtable load, the builds load straight into ECX.

The lever is the loop spelling, not a register tactic.

The bank walked the table explicitly:

```cpp
Rva00803080 **p = m_slots;
int n = 8;
do { if (*p != 0) (*p)->slot0(stamp); ++p; } while (--n);
```

With an explicit walk pointer the front end creates the walk pointer and its
counter ahead of the receiver and the stamp, and the allocator hands out
callee-saved registers in that order: `p` -> ESI, `n` -> EDI, `this` -> EBX,
`stamp` -> EBP. Writing the same eight-slot table as the index loop the
neighbouring matched `?add@Rva007EAServiceList@@` / `?remove@...@` bodies use

```cpp
for (int i = 0; i < 8; ++i)
{
    if (m_slots[i] != 0)
        m_slots[i]->slot0(stamp);
}
```

makes VC7.1 strength-reduce `i` into exactly retail's `lea esi,[ebp+0x10]` /
`mov edi,8` / `add esi,4` / `dec edi` walk. The receiver then takes EBP and the
stamp EBX, and the slot load takes EAX and is copied into ECX, which is retail's
second residue. 87/87, no flags, no `volatile`, no asm, no register spelling.

## Why the earlier levers could not reach it

* `tools/rotation_sweep.py --pairs` over the banked draft: ten toggles, all
  37 differing bytes, no move. The rotation lever does not reach callee-saved
  order (docs/shape_levers.md, "Scratch registers rotate").
* Local-alias (`Rva00803080 *s = *p;`), `volatile` slots, an in-class
  `getSlots()`, and `begin()`/`size()` inline accessors all compile
  byte-identically: they change the slot-load temp, not the order the four
  long-lived values are created in.
* Flag sweeps (`/O2 /Os /G5 /G6 /G7 /Ox /Gy /Oy`, dedicated TU) do nothing;
  docs/shape_levers.md records that as measured for the whole allocation class.

## Identity

Class and table come from the matched neighbours: `?add@Rva007EAServiceList@@
QAEXPAVRva00803080@@@Z` at 0x007EA550 and `?remove@Rva007EAServiceList@@
QAEXPAVRva00803080@@` at 0x007EA590 (`game/GameEngine/Source/GameNetwork/
Y2FeslServiceList.cpp`) place eight service pointers at +0x10, and this body
walks the same eight. `tools/pin_consistency.py --symbol "?m@T_007ea5e0@@QAEXXZ"`
reports the existing shim pin consistent with the new row: that is the spelling
`Rva007FA3D0Fesl.cpp` calls through, not a second identity.

`tools/vtable_lookup.py` cannot name the singleton's slots: `Rva007E9B70Get`
returns the address of a BSS object whose vtable is installed at runtime, so
its slots stay `v0`/`v1`/`slot08`/`slot0C`/`slot10`. Slot +0x08 is the clock
several matched FESL sources already call `tick()`/`now()`, which is why the
value pushed to each service is a timestamp and not a context pointer.

Source: `game/GameEngine/Source/GameNetwork/Rva007EA5E0Dispatch.cpp`.
