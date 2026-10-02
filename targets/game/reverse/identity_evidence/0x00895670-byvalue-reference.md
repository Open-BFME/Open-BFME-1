# 0x00895670 incoming reference lifetime

The 68-byte body starts at 0x00895670 and returns with `ret 8` at 0x008956B1, followed by INT3 padding. It stores the first incoming dword into receiver+4, increments its pointed-to count, writes the second argument at receiver+8 and a zero byte at receiver+0x0c, then decrements the incoming reference and destroys/frees it if that decrement reaches zero.

Its only direct call sites are 0x00896EE4 and 0x00896F39, both in the still-generated tracker body at 0x00896AF0. At 0x00896EDA and 0x00896F2F those callers store EBX into a four-byte stack argument. They then increment `[ebx]`, save ESP for EH cleanup, and call the constructor with the other argument already pushed. This is a nontrivial by-value reference argument, not an unowned pointer. The old raw-pointer constructor source mimicked the callee's release manually but omitted this caller contract.

The existing `BfmeRefVGO` class spells the four-byte owning reference in the tracked assignment at 0x00892B90 and other current Apt source. Its copy increments the pointed-to count; its destructor decrements and invokes the existing `BfmeDropObjectA` destructor at 0x00895260 plus `TheBfmeFree(pointer, 0x18)` when required. The corrected constructor therefore takes `BfmeRefVGO` by value, retains its member once, and permits the parameter destructor to supply the existing callee cleanup.

The owner remains `Gen_00895670`; no semantic owner or member identity is inferred. There are no other tracked C++ callers of this constructor and no existing raw-pointer constructor pin in symbols.csv. Changing its sole ledger identity preserves its extent and source coverage. The tracker remains scratch unless its complete intended source passes its own strict gate.
