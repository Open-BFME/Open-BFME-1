# 0x00890780 is `DebugIOFlat::~DebugIOFlat` only; `??1DebugIOOds@@UAE@XZ` retired

* **Vtable stored.** The body stores 0x0113517C at entry. That table is pinned
  `??_7DebugIOFlat@@6B@` and the matched `??0DebugIOFlat@@QAE@XZ` (0x00890380)
  installs it; its slots 3 to 5 are the matched `DebugIOFlat::Write`
  (0x00890E60), `DebugIOFlat::EmergencyFlush` (0x008903E0) and
  `DebugIOFlat::Execute` (0x00890810).
* **DebugIOOds's table is 0x01135060.** The matched `??0DebugIOOds@@QAE@XZ`
  (0x0088F990) and `DebugIOOds::Create` (0x0088FA10) install it; slot 3 is the
  matched `DebugIOOds::Write` (0x0088F950).
* **Body.** It walks and frees the split list at `this+4` and the stream list at
  `this+0xC`, calling `OutputStream::Delete` on each stream: Zero Hour's
  `DebugIOFlat::~DebugIOFlat`. Zero Hour's `DebugIOOds` has neither list.
* Retail has no identical-COMDAT folding, so the `DebugIOOds` row, which named
  this body as an ICF alias, was an over-claim. `debug_io_flat.cpp` keeps the
  body under `??1DebugIOFlat@@UAE@XZ`.
