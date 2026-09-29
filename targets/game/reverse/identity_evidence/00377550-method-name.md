# Method name for 0x00377550

The ledger `targets/game/reverse/functions.csv` still lists the 392-byte body at `0x00377550` as the generated dump `?d_00377550@@YAXXZ`. The earlier bank label `restorePlayer00377550` appears nowhere in game source, retail name pins, or relocation names. The caller scan `tools/callers_of.py 0x00377550` reports that no named caller reaches the body directly.

The bank supports `CastleBehavior` as the owning class. Its receiver follows the `data04` and `object08` layout, and its calls reach the landed `CastleBehavior` status helper. Those facts do not name this private method.

The bank now calls the method `rva00377550`. This address-derived name preserves the unresolved method identity.
