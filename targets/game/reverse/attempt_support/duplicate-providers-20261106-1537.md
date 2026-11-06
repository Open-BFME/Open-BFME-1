# Duplicate-provider trials

The retail scope is BFME 1 1.03. The inputs are master `6a6b0b051f`, the
2026-11-05 selection census `31c8ddea62`, and the pinned BFME 2 reference
`dbde7dbe3be16481b2c8d6f2f9577bc322f6b7ce`. Before and after each edit,
`build.cmd <extra.cpp> <retail-owner.cpp>` used the checked-in MSVC
per-source options, including the existing /EHsc flags. All edits below
were restored. The corresponding standalone retail owners were kept.

- Weapon constructor `0x001E52D0`, 158 B. Removing the body from
  `Weapon.cpp` alone dropped three ledger aliases of the emitted
  `WeaponTemplate::getSuspendFXDelay` getter (`dup_000c8c40`,
  `dup_0047a320`, and `dup_005c3090`). Taking the getter's address as a
  discarded expression inside the retained copy constructor restored the
  getter and all 53 rows. Of the other external object definitions,
  378 retained their bytes and relocations, while
  `Weapon::privateFireWeapon` changed. Any next trial must preserve
  the getter and that code body together.
- `wantToSquishTarget` `0x00171FF0`, 174 B. Replacing the second body
  in `AIStates.cpp` with a declaration passed all 105 scoped rows, but
  changed raw code in `AIFollowWaypointPathState::getNextWaypoint` and
  `AIHuntState::onEnter`, `AIPanicState::onEnter`, and
  `AIWanderState::onEnter`. The four relocation lists stayed equal.
  A retry needs to preserve those bodies too.
- `DX8Wrapper::Draw_Triangles` `0x00906D70`, 114 B. Removing the extra
  body in `dxwrapper.cpp` dropped both unwind anchors at
  `0x00C5B511` and `0x00C5B500`. Both are absent from the parent's
  emitted group, even after resolving the renumbered local labels.
  Two of 124 scoped rows failed. Preserve both cleanup bodies before
  retrying this removal.
- Image-row helper `Rva004B5AA0::m` `0x004B5AA0`, 104 B. Removing the
  second definition in `GadgetImageComboBox.cpp` failed one of four
  rows, the retail body of `GadgetImageComboBoxSystem`, with byte and
  REL32 layout differences. The pinned BFME 2 reference has the related
  combo-box handlers. The emitted BFME 1 system handler remains the
  constraint on removing the duplicate.

The test compares individual objects against the retail ledger and their
pre-edit object output. It does not measure linked bytes in a new image.
