# Geometry::GetPolygonIndex at RVA 007B7FA0

This is a bounded callee identity repair needed by RenderDynamicMeshVolume at
007BC270. The previous claim was dup_007b7fa0 with
object-symbol=?GetPolygonIndex@Geometry@@QBEPAGJPAF@Z and a reference-source
C++ implementation. No byte coverage is added by this repair.

Independent identity evidence:
- EA Zero Hour W3DVolumetricShadow.cpp defines Geometry::GetPolygonIndex inline
  at line 181. It writes three WORD indices from polygon*3 and returns the
  indices pointer plus polygon, deliberately not polygon*3.
- Retail 007B7FA0 is exactly 63 bytes, loads the index pointer at this+4,
  performs those same three WORD loads/stores, returns indices+polygon and
  ends in ret 8. No virtual dispatch or competing type interpretation is used.
- The existing ledger already compiled that named object symbol to these
  bytes. The source has now been rehomed unchanged in behavior into
  game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/GeometryGetPolygonIndex.cpp
  and the scoped byte gate passes 1/1.
- RenderDynamicMeshVolume at 007BC270+030B calls ILT 0000C563. The retail E9
  resolves to 007B7FA0. Its arguments are polygon zero and the locked index
  buffer, matching the Zero Hour caller and the nonvirtual thiscall ABI.

The new semantic identity therefore rests on independent source, the prior
object-symbol, and the complete callee body, not on a desired caller match.
The thunk pin records route=0x007B7FA0 and must pass pin_consistency --check.
