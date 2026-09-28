# Object::setGeometryInfoZ at 0x001BDF70 (was ?bfmeGoCNG@BfmeThingCNG@@QAEXPAX@Z)

The 53-byte body at 0x001BDF70 (RET 4 at +0x32) was matched as
`BfmeThingCNG::bfmeGoCNG(void *)`, an invented class and a pointer argument.

**Body.** It is Zero Hour's `Object::setGeometryInfoZ(Real newZ)` (GeneralsMD
Object.cpp:788) with BFME's extra helper notification:
- Forward the argument to the geometry at `this+0xAC` through 0x0087F270. That
  body walks the 0x24-byte shape records at +0x2C/+0x30 and stores the argument
  as each active shape's height, which is Zero Hour's
  `m_geometryInfo.setMaxHeightAbovePosition(newZ)`. ObjectGeometry.cpp proves
  that +0xAC..+0x107 is Object's GeometryInfo.
- If the helper at +0x3B8 is set, call `?init@Rva009A2350@@QAEXXZ` on it. The
  matched `?setGeometryInfo@Object@@QAEXABVGeometryInfo@@@Z` (0x001D5D20) notifies
  that same helper.
- If `m_drawable` (+0x80) is set, call it through ILT 0x00013A61, the same
  notification setGeometryInfo sends (Zero Hour's `reactToGeometryChange`).

**Argument type.** The argument is a float. ActiveBody::setCorrectDamageState
(0x00210BF0) calls this body three times:
- at +0x45E, `push ecx; fstp dword ptr [esp]` on the x87 result of
  `GeometryInfo::getMaxHeightAbovePosition`;
- at +0xF7 and +0x4D7, pushing `TheGlobalData+0xBA8` or the template's rubble
  height as float bits.

A `void *` parameter cannot produce the `fstp [esp]` call. The rubble arm around
+0x4A7 is Zero Hour's `ActiveBody::setCorrectDamageState` rubble block, which
calls `getObject()->setGeometryInfoZ(rubbleHeight)` at exactly this point.

**Orphaned pin.** Retiring the old claim also drops
`?bfmeTwoCNG@BfmeACNG@@QAEXXZ` at 0x009A2350. That address is already matched as
`?init@Rva009A2350@@QAEXXZ`, and nothing else referenced the old spelling.

Probe: 53/53 bytes and 3 relocation sites, exact outside the relocation slots, in
ObjectGeometry.cpp beside setGeometryInfo.
