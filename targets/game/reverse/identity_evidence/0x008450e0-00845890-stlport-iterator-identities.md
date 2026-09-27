# Retire the four U1Probe claims on the STLport iterator constructors

The ledger had two real names at each of `0x008450E0`, `0x00845410`,
`0x00845870`, and `0x00845890`. `python3 tools/one_identity.py --list --callers`
reports no matched C++ caller naming either claim at any of these addresses.
Retail was linked without identical-code folding, so byte identity cannot make
both names true.

The `U1Probe_*` classes in
`game/GameEngine/Source/Common/U1SmallStateProbes.cpp` are layout probes, not
identified retail classes. That file explicitly says the owner of
`0x00845410` is unidentified. The `0x00845410` probe reuses the layout from
`0x005C0DE0`; the other three probes model the bytes' pointer loads and stores.
Those facts establish the instruction shape, not a retail `U1Probe` type.

Keep the later claims at `0x00845410`, `0x00845870`, and `0x00845890` under
their `Rva008...OutIter` names. Their source,
`game/stlport/Rva00845410OstreambufIteratorCtors.cpp`, records that the narrow
and wide ostreambuf iterator instantiations are indistinguishable here, so the
names retain each address and claim only the observed constructor signatures.

At `0x008450E0`, keep the STLport `istreambuf_iterator<wchar_t>` constructor.
The retail body reads the stream buffer through the virtual `basic_ios` base,
stores the buffer pointer at `this+0`, writes the EOF flag at `this+6`, clears
the cached-character flag at `this+7`, and returns with `ret 4`. In the vendored
STLport declaration (`inputs/vendor/stlport/stl/_istreambuf_iterator.h`), the
member order is buffer pointer, `_CharT` character, EOF byte, cached-character
byte. The two-byte `wchar_t` therefore places those flags at offsets 6 and 7;
the matching narrow stream constructor at `0x00845150` places them at 5 and 6.
`game/stlport/IstreambufIteratorNarrowStreamCtor.cpp` explicitly instantiates
the wide specialization, and the adjacent iterator family includes the
matched bodies at `0x00845070` and `0x00845100`.

The four address-derived or STLport-backed rows describe the observed bodies;
the old `U1Probe_*` rows assert an owner that the evidence never established.

## Distinct small probes in the same source file

The earlier `U1Probe_005C0DE0`, `isAbsent@U1Probe_005C0E00`,
`u1IsAbsent_005C0FB0`, and `u1IsEmpty_005C1C20` definitions and ledger rows
remain at their original `0x005C...` addresses. They are not being renamed to
the `0x00845...` iterator constructors. `U1Holder_005C1C20` and
`U1PtrFlagged_005C0FB0` describe only those separate small probes. The removed
`U1Carrier_00845870` was a temporary layout adapter used by the retired
`U1Probe_00845...` constructors; it was not evidence for a retail class name.

Some of these short constructors share bytes or simple field patterns with the
iterator bodies. Retail's incremental-link table retains separate entry
addresses and the executable was linked without identical-code folding, so
such a pattern does not transfer an identity between `0x005C...` and
`0x00845...`.
