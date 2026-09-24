# 0x009F4ED0 cleanup layout, still a dump

The 163-byte retail body is called from the matched destructor at `0x009F5970+0x25` and from the matched `T_009F4FB0` path. Its original class name remains ambiguous because the destructor RVA has several aliases. The `cleanup@Gen_dtor_009f2600` pin is an existing address claim, not proof of a unique owner.

The body first walks nodes from `this+0xE4`, clearing the pointer reached through each node's `+0x10` back-link and following `+0x0C`. It then checks the range pointers at `this+0x18/+0x1C` and loops through 17 records of 12 bytes beginning at `this+0x18`. Each nonempty record clears a root slot and dispatches four child slots through the matched `Rva009F40E0Owner::run` at `0x009F40E0`. That callee's source proves a thiscall with `(void **slot, unsigned count)` and a recursively walked four-child table.

The first typed C++ reconstruction in ignored `build/rva009f4ed0-probe.cpp` emitted 174 bytes against retail's 163, with 151 non-relocation differences and the single call relocation displaced. Retail saves `this` in EBP and uses an 8-byte frame; the compiler keeps it in a stack slot and uses a 12-byte frame. Removing redundant source locals did not alter the emitted code. The reconstruction is not a byte claim, and the owner name stays unresolved.
