# Rva0061FDA0Owner::xfer at 0x0061FDA0

The 901-byte body at 0x0061FDA0 was banked as
`?xfer@SkirmishGameInfo@@MAEXPAVXfer@@@Z`. That name was never a proven
identity for this body: it was the twin hypothesis, copied from the landed
SkirmishGameInfo::xfer at 0x0061F930, and the bank header itself says its
field and register shape does not match retail. The landed 0x0061F930 TU now
probes EXACT 901/901 at 0x0061FDA0 modulo relocations, so the instruction
shape is shared. This file records the evidence for the address-derived
replacement `?xfer@Rva0061FDA0Owner@@MAEXPAVXfer@@@Z`.

- **What the body is.** A Snapshot-slot-3 `xfer(Xfer *)`: draft guard, version
  (1,1), preorder/crc/bool/int header, eight GameSlot rows each with
  state/name/accept/mute/color/start/template/team/originals plus the
  getXferMode write-back path, then localIP, extra38, xferMapName
  (0x0010C7E0), mapCRC, mapSize, mapMask, seed. Probe: EXACT 901/901.
- **Why the owner differs.** Retail ctor 0x00619720 stores vtable 0x011171C8
  into this object (immediate at body offset 0x51), while the twin's ctor
  0x00075C10 stores 0x01075E7C at the same offset. dir32 rows:
  `??_7SkirmishGameInfo@@6BSnapshot@@@` -> 0x011171C8 vs
  `??_7Open2SlotOwner75C10@@6BSnapshot@@@` -> 0x01075E7C. Slot 3 of each table
  is an ILT jump (0x011171C8 slot 3 -> jmp to 0x0061FDA0 via ILT 0x0000EB6F;
  0x01075E7C slot 3 -> jmp to 0x0061F930 via ILT 0x00014E5C). Same shape, two
  classes: reusing the twin's class name would be an identity collision that
  add_match refuses.
- **Why the address token stays.** The owning class of vtable 0x011171C8 is
  unproven (no named caller, owning TU, or layout witness names it; AGENTS.md
  3a). The new owner keeps the body address per the opaque-name rule.
- The TU probes EXACT 901/901 under the new name; the twin's matched row at
  0x0061F930 is untouched.
