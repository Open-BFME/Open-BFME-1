# 0x0022CC80 is ~TransportContain

The 77-byte row at 0x0022CC80 was `?bfmeGo966B@BfmeVft966B@@QAEXXZ`, an
anonymous conversion in BfmeConv966.cpp that stored ten pointer slots and
tail-jumped to ILT 0x00039D6A.

- The matched protected scalar-deleting wrapper `??_GTransportContain@@MAEPAXI@Z`
  (0x0022D0B0, TransportContainDeletingDestructor.cpp) calls its complete
  destructor through ILT 0x0003FF49, and 0x0003FF49 is `jmp 0x0022CC80`.
- `python3 tools/ilt_oracle.py check '??1TransportContain@@MAE@XZ' 0x0022CC80`
  reports CONFIRMED (exact); the public `UAE` decoration is CONTRADICTED.
- The ten stored pointers are exactly the vftables dir32_addresses.csv records
  as `??_7TransportContain@@6BTransportContainBase@@@` (0x010AD4E8 at +0) and
  `...Iface1..9` (0x010AD420 +0xC, 0x010AD410 +0x10, 0x010AD268 +0x20,
  0x010AD24C +0x24, 0x010AD248 +0x28, 0x010AD238 +0x2C, 0x010AD1FC +0x30,
  0x010AD1EC +0x34, 0x010AD1E8 +0xD4), and ILT 0x00039D6A is the pinned
  `??1OpenContain@@UAE@XZ`: an empty derived destructor of an OpenContain.
