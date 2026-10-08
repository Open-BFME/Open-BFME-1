# 0x00219290 is ~CaveContain

The 77-byte row at 0x00219290 was `?bfmeGo966A@BfmeVft966A@@QAEXXZ`, an
anonymous conversion in BfmeConv966.cpp that stored ten pointer slots and
tail-jumped to ILT 0x00039D6A.

- The matched protected scalar-deleting wrapper `??_GCaveContain@@MAEPAXI@Z`
  (0x00219C40, CaveContainDeletingDestructor.cpp) calls its complete
  destructor through ILT 0x0002748F, and 0x0002748F is `jmp 0x00219290`.
- `python3 tools/ilt_oracle.py check '??1CaveContain@@MAE@XZ' 0x00219290`
  reports CONFIRMED (exact); the public `UAE` decoration is CONTRADICTED.
- The ten stored pointers are exactly the vftables dir32_addresses.csv records
  as `??_7CaveContain@@6BCaveContainBase@@@` (0x010AB000 at +0) and
  `...Iface1..9` (0x010AAF38 +0xC, 0x010AAF28 +0x10, 0x010AAD80 +0x20,
  0x010AAD64 +0x24, 0x010AAD60 +0x28, 0x010AAD50 +0x2C, 0x010AAD14 +0x30,
  0x010AAD04 +0x34, 0x010AACF8 +0xD4), and ILT 0x00039D6A is the pinned
  `??1OpenContain@@UAE@XZ`: an empty derived destructor of an OpenContain.
