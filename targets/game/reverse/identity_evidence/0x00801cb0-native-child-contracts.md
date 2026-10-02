# 0x00801CB0 native child contracts

The complete retail body covers RVA 0x00801CB0 through 0x00801EBB (523 bytes). Its final instruction at 0x00801EB8 is `ret 16`. Matched `Rva00802A90Owner::go` calls the body twice through `notify(query, context, flag, id)`.

The former attempt's `Rva7F4CC0Child` is a fabricated common-base wrapper. Its `construct()` method is redirected by `/alternatename` to the dump for the 0x007E86B0 constructor. That constructor installs table VA 0x01129358, zeroes +4, and returns this. Its independently matched object symbol is `SnapshotDupReplica::SnapshotDupReplica` in `SnapshotEnergyDupThunk.cpp`. It does not establish a class named Rva7F4CC0Child. The actual 0x007F4CC0 body is a different 52-byte composite constructor (`Rva7F4CC0ConstructorThunk.cpp`) with the base subobject at +0x14.

The callback's 0x28-byte allocation path calls the 0x007E86B0 base constructor, then installs table VA 0x0112B4B4 and writes +4=1, byte +8=0, +0x24=0. These exact stores independently occur in matched `Rva007F4DA0Ctor.cpp` and the inline member constructor in matched `Rva007F6D60ChildConstructor.cpp`. The reconstruction therefore reuses the established opaque `Rva007F4DA0` child view; it does not rename the old fabricated base wrapper to this derived class.

The alternate path allocates 16 bytes, calls the same base constructor, installs table VA 0x011296B0, and clears +8, +0x0C and +4. This exactly matches the opaque `Rva007F6D60Member2C` view in the matched child constructor. Its subsequent call targets RVA 0x007E86D0. Matched `Y2FeslAddressFormat.cpp` proves that method's `Rva007E8760Addr::parse(const char *, int)` view: it reads two stack arguments, parses four octets into +8, stores the integer into +0x0C and returns with `ret 8`. That parse receiver is an additional ABI view, not a replacement name for the fabricated base wrapper.

The name regression check pairs the removed attempt's Rva7F4CC0Child declaration/use with the new derived constructor and parse receiver. Both pairings are false: the former wrapper's base ABI is preserved by the real matched SnapshotDupReplica constructor, while the derived constructor and parse receiver each have separate independent evidence.

Independent reviewers inspected the actual table entries: VA 0x0112B4B4 points to RVA 0x007F6D40; VA 0x011296B0 points to RVA 0x007E8E70; VA 0x01129358 points to RVA 0x007E87C0. Each table has one function entry followed by string data. The strict scoped gate verifies all 523 bytes, 22 relocation sites and three DIR32 references. No new pins or data rows were added.
