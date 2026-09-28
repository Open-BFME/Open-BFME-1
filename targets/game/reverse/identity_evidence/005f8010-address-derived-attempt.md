# Identity at RVA 0x005F8010

`functions.csv` labels the 976-byte body at RVA `0x005F8010` as `?d_005f8010@@YAXXZ`, a generated dump. `symbols.csv` lists only the generated thunk `?b_005f8010@@YAXXZ` at that address. Neither file provides a semantic function name.

The candidate brief lists no matched caller or vtable owner for this body. It records four remaining reload differences in `Rva005F8010::render`, but those bytes do not prove the owner type.

The earlier bank called the owner `StreakParticles005F8010` and its virtual interface `StreakSlots005F8010`. No caller, vtable slot, or string proves those class identities. The bank now uses `Rva005F8010` and `Rva005F8010Slots`, which keep the retail address in both names.
