# `DebugIOCon::~DebugIOCon` at 0x00890F10, not `DebugCmdInterfaceDebug`

* **Vtables stored.** The body stores 0x01135C9C at entry and 0x01135044 before
  it returns. 0x01135044 is `??_7DebugIOInterface@@6B@`, which ten matched rows
  (the DebugIOFlat, DebugIOOds and DebugIONet constructors among them) resolve
  it to. `DebugCmdInterfaceDebug` derives from `DebugCmdInterface`, whose table
  is 0x01133034: the matched `??0DebugCmdInterfaceDebug@@QAE@XZ` (0x00889580)
  stores 0x01133034 and then its own table 0x01133100.
* **0x01135C9C is DebugIOCon's table.** Slot 1 is the matched
  `?Read@DebugIOCon@@UAEHPADH@Z` (0x00890F80) and slot 5 the matched
  `?Execute@DebugIOCon@@UAEXAAVDebug@@PBD_NIPBQBD@Z` (0x00891200). Slot 0 is
  0x00891510, a deleting destructor.
* **Body.** It calls `FreeConsole` when the byte at `this+4` is set. That is Zero
  Hour's `DebugIOCon::~DebugIOCon` (`if (m_allocatedConsole) FreeConsole();`);
  `m_allocatedConsole` is DebugIOCon's first member. Zero Hour's
  `DebugCmdInterfaceDebug` declares no destructor and no data members.
* **The real `~DebugCmdInterfaceDebug`** is 0x0088A6E0: the deleting destructor
  in slot 0 of 0x01133100 (0x0088A6B0) calls it, and it stores 0x01133034.
* **Overturns `caller-decided-2.md`'s verdict for this body.** Its one "C++
  caller" is 0x00891510, the deleting destructor in slot 0 of 0x01135C9C, whose
  row `dup_00891510` compiles `??_GDebugCmdInterfaceDebug` from this same source.
  That caller named the old row's own spelling, so it could not decide against it.
