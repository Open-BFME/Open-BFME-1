# Vector deleting destructor at 0x0005E880

The 84-byte body at 0x0005E880 was filed as `??_ERoadType@@QAEPAXI@Z`. It is a
vector deleting destructor, but not RoadType's.

- Its eh vector destructor iterator call pushes element size 0x24 and the
  destructor operand VA 0x00418FCF. That is ILT 0x00018FCF, which jumps to
  0x0005DBF0 and then to 0x008FC5B0, the 13-byte destructor matched as
  `??1W3DRadarResetSurface@@QAE@XZ`.
- W3DRoadBuffer's own RoadType array code, `allocateRoadBuffers` (0x0070EA90)
  and `freeRoadBuffers` (0x0070E9C0), pushes a different destructor: VA
  0x0041DE49, which is ILT 0x0001DE49 jumping to 0x007070C0, `??1RoadType@@QAE@XZ`.
  RoadType's elements are therefore destroyed by 0x007070C0, and a RoadType
  `??_E` would push that address.
- Retail contains no call to 0x0005E880 or to its ILT thunk 0x00031FED, and no
  data reference to either. So no caller names the element class.

The DIR32 consistency gate flagged the old name: `??1RoadType@@QAE@XZ` resolved
to two addresses, 0x0041DE49 from the W3DRoadBuffer rows and 0x00418FCF from
this body. The body keeps its bytes as `??_EBfmeElementD@@QAEPAXI@Z`. BfmeElementD is the
existing opaque placeholder for exactly this element: 0x24 bytes, with its
destructor pinned at 0x00018FCF (S3ArrayOwnerDestructors.cpp's array owners push
the same VA 0x00418FCF). No semantic class name is claimed.
