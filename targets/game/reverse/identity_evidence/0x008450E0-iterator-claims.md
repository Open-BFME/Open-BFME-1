# Retire the duplicate U1Probe claims

`one_identity.py --callers` finds no matched C++ caller naming the U1Probe row at
0x008450E0, 0x00845410, 0x00845870, or 0x00845890. The ledger gave each body
two names. `game/GameEngine/Source/Common/U1SmallStateProbes.cpp` defines the
four `U1Probe` classes from synthetic layouts. That source says the owner at
0x00845410 is unidentified. Its other three classes model a pointer load and a
flag store without naming an independently witnessed owner.

`game/stlport/IstreambufIteratorNarrowStreamCtor.cpp` explicitly instantiates
the wide `istreambuf_iterator` constructor at 0x008450E0. Its `wchar_t` value
places `_M_eof` and `_M_have_c` at offsets +6 and +7, matching the body. The
matched wide iterator constructors at 0x00845070 and 0x00845100 show the same
iterator class around that address.

`game/stlport/Rva00845410OstreambufIteratorCtors.cpp` models the three other
bodies as `ostreambuf_iterator` constructors. The first reads a stream buffer
pointer. The other two read `rdbuf()` through the stream's virtual `basic_ios`
base at offset +0x58. The source keeps each RVA in its class name because no
caller distinguishes the narrow and wide instantiations. These names describe
the observed constructor shapes and retain each address. The `U1Probe` names
add no owner evidence, so the ledger and probe source drop those duplicate
claims.
