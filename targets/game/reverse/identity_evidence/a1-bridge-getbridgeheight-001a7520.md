# Bridge::getBridgeHeight at 0x001A7520

BFME 1 target evidence:
- Retail body 0x001A7520, 664 bytes: `ret 8` at +0x295, int3 from +0x298.
- Its only incoming jump is the incremental-link thunk at 0x0000B802 (ILT slot
  8601). `ilt_oracle.py check` CONFIRMS
  `?getBridgeHeight@Bridge@@QAEMPBVCoord3D@@PAV2@@Z` for that slot and
  CONTRADICTS the struct-keyed `...PBUCoord3D@@PAU2@@Z` spelling and the old
  forwarding-shim pin `?compute@BridgeGetBridgeHeightShim@@...`.
- Callees: Coord3D::normalize 0x000FB930 (twice), PlaneClass::Set 0x001A5DC0,
  PlaneClass::Compute_Intersection 0x001A1CF0.

Donor evidence (BFME 2, open-bfme-2 45afcff3a6):
`Code/GameEngine/Source/GameLogic/Map/BridgeGetBridgeHeight.cpp`, matched there
at BFME 2 retail 0x0027FD2A (713 B) with the same call structure. Ported with
the polygon-area pointer moved to BFME 1's +0x8C; the port compiles byte-exact.

pin-identity-override: ?getBridgeHeight@Bridge@@QAEMPBVCoord3D@@PAV2@@Z 0x001A7520 caller=0x0000B802 the matched ILT thunk row in BridgeMemberThunks.cpp jumps to the body by this name; ilt_oracle CONFIRMS it for slot 8601
