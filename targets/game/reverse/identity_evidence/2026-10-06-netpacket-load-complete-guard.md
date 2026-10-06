# NetPacket load-complete guard at RVA 0x00677CD0

The existing 84-byte claim `?a_00677cd0@@YAXXZ` uses the object symbol
`?isRoomForDisconnectKeepAliveMessage@NetPacket@@IAE_NPAVNetCommandRef@@@Z`
from `NetPacket_isRoomForKeepAlive.cpp`. That is a byte-identical copy, not
the identity of this retail body. The independently named disconnect-keep-alive
guard belongs to RVA 0x00677ED0. Retail did not fold these bodies together.

Two matched C++ callers establish the identity at 0x00677CD0:

| Caller | RVA / size | Retail call | COFF relocation |
| --- | --- | --- | --- |
| `NetPacket::addLoadCompleteMessage` | `0x0067AFD0 / 508` | `0x0067AFF2 -> 0x00029168` | offset `0x23`, REL32, `?isRoomForLoadCompleteMessage@NetPacket@@IAE_NPAVNetCommandRef@@@Z` |
| `NetPacket::addTimeOutGameStartMessage` | `0x0067AD50 / 508` | `0x0067AD72 -> 0x00029168` | offset `0x23`, REL32, the same symbol |

Both callers are owned by `NetPacket_addCommandFamily.cpp`. Their current
census objects independently pass `build.compile_function` and
`build.verified_patch_eligible`. The source calls the load-complete guard
from both methods. The retail ILT entry at 0x00029168 is
`e9 63 eb 64 00`, whose destination is 0x00677CD0.

The guard's extent ends with `setle al` at 0x00677D1E and `ret 4` at
0x00677D21. Padding starts at 0x00677D24, giving exactly 84 bytes from
0x00677CD0. It has no direct callees or relocations.

The existing named definition in `NetPacket.cpp` still uses the Zero Hour
packet's trailing-member offsets. Using its already-established
`BfmeNetPacketFields` view for `m_lastCommandType`, `m_lastRelay`, and
`m_lastPlayerID` produces all 84 retail bytes exactly under the existing
build flags. No new function reconstruction or callee pin is needed.

Replace the opaque claim with
`?isRoomForLoadCompleteMessage@NetPacket@@IAE_NPAVNetCommandRef@@@Z`, owned
by `NetPacket.cpp`, at the same start and extent. Keep the separate
disconnect-keep-alive claim at 0x00677ED0.

Evidence checked against the retail-1.03-unpacked baseline on 2026-10-06;
the baseline worktree commit is `5de5448900`.
