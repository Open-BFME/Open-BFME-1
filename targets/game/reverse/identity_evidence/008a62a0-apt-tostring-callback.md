# 0x008A62A0: Apt native `toString` callback binding

The original C++ owner and method spelling remain unresolved. This proves the
script-facing binding, not a rename to an invented C++ `toString` method.

## Independent BFME witnesses

All addresses below are retail RVAs unless explicitly labelled VA. Capstone
inspection used `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`.
Ghidra's byte search for `A0 62 CA 00` independently returned VA `0x00CA7A8F`.

* Matched clean C++ body `0x008A78D0`, currently address-named
  `Rva008A78D0Owner::bfmeGetOrCreateDefault`, compares a property key with the
  native literal at VA `0x0113666C`: its shipped bytes are `toString\0`.
  At `0x008A7A5B` it loads that literal, sets the comparison count to nine,
  and executes `repe cmpsb` at `0x008A7A67`.
* The successful comparison enters the branch which lazily creates the global
  at VA `0x01337ABC`. At `0x008A7A8E` it pushes VA `0x00CA62A0`, then calls
  constructor `0x00899FC0` at `0x008A7A95`. This is a genuine callback argument,
  not a vtable word or an accidental relative-displacement match.
* Independently matched constructor `0x00899FC0` takes its stack argument at
  `0x00899FCC` and stores it at receiver offset `0x20` at `0x00899FD0`.
  It installs table VA `0x01136128` and returns with `ret 4`.
* The callback body itself has a 235-byte extent: final `ret` at `0x008A638A`,
  followed by `int3` at `0x008A638B`. Its return value is the recycled/allocated
  16-byte Apt node populated from helper `0x00898D80`'s refcounted string result.
  Its incoming argument supplies that helper's receiver at `0x008A6334`.

## Identity limits

The lookup owner's name is itself opaque. Native `message` and `name` properties
in that lookup are insufficient to assert a particular ActionScript or C++ class.
The separate 235-byte twin `0x008A6100` is supplied by a different property lookup
at `0x008A7783`; identical instruction shape does not give the twins one identity.
No production rename or pin is proposed. Existing clean callers keep their
address-preserving names; this file records a concrete lead for future owner work.
