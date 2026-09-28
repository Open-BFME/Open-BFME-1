# `??0WaypointMap@@QAE@XZ` is 0x00453D10, not 0x0019EA30

* **BFME's WaypointMap constructor zeroes `m_numStartSpots`.** The matched
  BFME `??0MapMetaData@@QAE@XZ` (0x004543D0) inlines the `m_waypoints`
  constructor at +0x38: map header (null, `__new_alloc::allocate(0x20)`,
  count 0, colour/parent/left/right) and then `mov [esi+0x44],ebx`, the
  +0xC member zeroed in member order before the +0x48 list. A MapMetaData
  constructor cannot initialise a member of a member, so the zero belongs to
  `WaypointMap() : m_numStartSpots(0)`.
* **0x00453D10 is exactly that constructor out of line.** Its 61 bytes are the
  same header initialisation followed by `mov dword ptr [esi+0xC],0` and
  `mov eax,esi`. Its only call site in retail is 0x00454C61 inside loadMap
  (0x00454B00), through ILT 0x00022840, right after `operator new(0x10)` with
  retail's saved allocation, EH state 4 (delete on throw), null check and
  `xor eax,eax` else-arm: the shape of a NEW expression whose constructor
  MSVC keeps out of line. `MapUtil_loadMap.cpp` compiles `new WaypointMap`
  with the inline constructor above and reproduces both bodies byte for byte.
  0x00453D10 sits inside the MapUtil.cpp address run (0x00453xxx-0x00454xxx)
  with ParseSizeOnly, the MapMetaData constructor and loadMap. Its previous
  name, `?bfmeInitAVC@BfmeThingAVC@@QAEPAV1@XZ`, was a generated placeholder
  with no caller or evidence.
* **0x0019EA30 is not the BFME WaypointMap constructor.** Its 54 bytes are
  byte-identical to `map<AsciiString,Coord3D>::map()` at 0x0019DFE0 and store
  nothing at +0xC. It carried the name only because `INIMapCache.cpp`
  compiles the Zero Hour MapUtil.h, whose WaypointMap has an implicit
  constructor that leaves `m_numStartSpots` unset. No retail E8 site reaches
  0x0019EA30 or its ILT 0x0001AEDD. It is re-homed as
  `?dup_0019EA30@@YAXXZ`, verified through the map constructor COMDAT that
  INIMapCache.cpp already emits.
* Retail has no identical-COMDAT folding, so one name keeps one body.
