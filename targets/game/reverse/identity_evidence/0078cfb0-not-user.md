# 0x0078CFB0 / 0x0078D240 are not GameNetwork User's destructors

Both rows were claimed as `??1User@@MAE@XZ` / `??_GUser@@MAEPAXI@Z` from
`User.cpp`. That identity rested on 0x0078CFB0 destroying a UnicodeString at
+4 (see 0078cfb0-user-dtor-aliases.md), read through a lift row that named
0x009409F0 `UnicodeString::releaseBuffer`.

* 0x009409F0 is `Render2DSentenceClass`'s destructor: it installs vtable
  0x0113CEAC, calls `Render2DSentenceClass::Reset`, and tears down three
  DynamicVectorClass members (009409f0-render2dsentence-dtor.md). The real
  wide-string release is 0x008881D0.
* So the member at +4 of this class is a Render2DSentenceClass. ZH `User`
  derives from MemoryPoolObject and holds a UnicodeString there.
* The base table 0x01126D84 has five pure-virtual slots then the deleting
  destructor, and only this hierarchy's functions carry it; it is not a
  MemoryPoolObject table.

Nothing yet names the class, so both rows now carry the address-derived
`Rva0078CFB0SentenceHolder`. Byte-exact 73/73 and 30/30.
