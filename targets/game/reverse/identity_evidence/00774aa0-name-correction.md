# Naming at 0x00774AA0

The banked source declared local views named `Seat00774AA0Owner`, `Seat00774AA0Receiver`, `SeatBones`, `SeatLogic`, `SeatRecord`, and `SeatState`. Its partial verdict in `re_attempts.log` describes these as typed scratch contracts that reproduce the 144-byte instruction shape. Neither that verdict nor the source cites a BFME class named `Seat`.

Retail starts at 0x00774AA0 and returns at 0x00774B2D. Callers 0x00755F70 and 0x00775470 forward five stack arguments but do not name the target method. The pinned ILT 0x00005BCD proves `addPublicBone` as a callee name only. The matched validator reached through ILT 0x0003A11B also names its callee, not the owner at 0x00774AA0.

The source uses address-derived views for this body because the retail evidence does not name its owner or records. The field name `m_pad` describes reserved bytes without claiming a BFME field name.
