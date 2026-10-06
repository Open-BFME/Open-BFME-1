# U4Assign006057C0's notify call reaches Gen_00409040Registry::m

The assignment operator at 0x006057C0 (51 B, `U4GlobalGuardedNotifies.cpp`)
makes one call: `call 0x000281C8`, an ILT stub whose `jmp` lands on
**0x00409040** (`tools/callees.py 0x006057C0 51`).

| address | ledger | note |
|---|---|---|
| `0x00409040` | `?m@Gen_00409040Registry@@QAEXPAX@Z` (`Gen_00409040Registry_m.cpp`, matched, 103 B; the file links) | thiscall, one pointer argument |
| `0x00409040` | `?noteAssign@U4Notify@@QAEXPAVU4Assign006057C0@@@Z` (symbols.csv pin only) | `pin_consistency`: consistent, owned by the row above |

The TU called the pin-only spelling `U4Notify::noteAssign`, which no object
defines, so the file could not link (link queue #235). Both spellings are an
address-derived view of the same body with the same ABI; the call now names
the matched row. `U4Notify` remains in the TU for the other entry point
(`noteOwner`, 0x004090C0).
