# Native local-effect position helper at RVA 002520B0

The exact retail extent is 407 bytes: the last RET is at 00252246 and the
following bytes are INT3. Ghidra creation at VA006520B0 independently reports
that extent. The GeneralsMD TransitionDamageFX.cpp `getLocalEffectPos` twin
supplies the branch structure; retail's random-call literal at VA010B2528 is
`F:\bfme\Code\gameengine\Source\GameLogic\Object\Damage\TransitionDamageFX.cpp`
and its line argument is339. The source retains an address-derived helper and
partial input view rather than asserting a new exported signature.

The inputs are compiler-private: EDI points to the location record, EBX to the
Drawable bone-query receiver, and ESI to hidden coordinate result storage.
Direct retail calls at002526F5,0025277D and0025282E belong to parent002525E0.
The first explicitly forms EDI from its effect record and ESI from its stack
result storage. The helper consistently consumes those registers, returns ESI
in EAX, and uses plain RET. A noinline static C++ helper plus an explicitly
absent-from-retail emission wrapper reproduces this convention; no assembly
adapter or unverified companion caller is promoted.

Offsets00/04/08/0C are the location selector, narrow string, random selector,
and coordinate, corroborated by the twin and retail accesses. The local view
keeps offset names. The six-argument bone query calls ILT0002319B ->00413850,
whose existing native BFMEDrawableBoneQuery definition establishes its const
thiscall signature and RET18 contract. Its struct-key Coord3D pointer spelling
is retained by including the canonical coordinate header under a local
class-to-struct key view; layout and type name stay unchanged. No new pin or
semantic callee alias was required.

The canonical empty Coord3D constructor/destructor and field-wise copy bodies
are visible locally. Scalar lifetimes optimize away, but the32-element array
uses CRT iterators and callbacks00416C93 ->00083330 (three-byte constructor)
and0041364C ->0005BC40 (one-byte destructor). This recovers the retail18C-byte
frame and all407 bytes; the old POD-coordinate draft lacked these lifetimes.

Parent002520B0 installs handler00C0E7F6, which loads FuncInfo00DFD604 and
unwind map00DFD5FC. State0, predecessor-1, selects action00C0E7E0. Ghidra raw
memory independently confirms the entry at VA011FD600. The action pushes the
real destructor callback, count32, stride12, and EBP-18C; calls iterator009F6D76;
and ends RET00C0E7F5 immediately before its handler. It is22 bytes.

Validation: native parent and its action passed scoped strict byte, call,
string, constant, and DIR32 reference verification. No shared header, pin,
generated source, or verification baseline changed.
