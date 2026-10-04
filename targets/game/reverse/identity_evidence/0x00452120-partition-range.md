# 0x00452120: STLport partition range wrapper

The30-byte retail body takes a four-byte predicate value followed by a pointer
to two adjacent iterator values. It loads last from[range+4], then first from
[range], uses the dead range-pointer argument home for an empty category, and
pushes category, predicate, last, first. The call at00452135 reaches ILT43004,
which routes to the208-byte STLport __partition body at00450B90. Four pushes,
add esp,16, and RET establish the cdecl call; EAX preserves the iterator result.
The empty category's concrete original type cannot be distinguished by bytes.

The initial reconstruction used Rva00450B90Item** and Rva00450B90Predicate.
Independent fillMapMask / MapCache::findMap evidence establishes the coherent
const MapMetaData** and Rva0055AE10MapPredicate contract instead. The prefix is
read-only; no vector receiver, capacity field, or original wrapper semantic
owner is established. The address-qualified wrapper name is retained.

The corrected native type contract compiles to all30 bytes including the
proven leaf relocation without _ReadWriteBarrier. The old barrier is removed.
See [the joint three-body proof](00450b90-map-pointer-partition.md) for original
MSVC7.1 and actual Ghidra MCP evidence, the independently false generated pin,
consumer closure, and preservation of the538 incidental range-TU providers.
