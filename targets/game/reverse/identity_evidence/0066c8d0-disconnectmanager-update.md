# 0x0066C8D0 DisconnectManager::update (1122 B)

Identity correction: the row was the naked mnemonic-asm lift `?update@BFMEDisconnectManager@@QAEXPAX@Z`
in `native_connection_timing.cpp`. The body is
`?update@DisconnectManager@@QAEXPAVConnectionManager@@@Z`, now in the official
`DisconnectManager.cpp` beside its matched siblings. That unit's Zero Hour `update` was
`present-unmatched`, and this body replaces it.

## BFME 1 target evidence
- `ilt_oracle.py check ?update@DisconnectManager@@QAEXPAVConnectionManager@@@Z 0x0066C8D0`:
  CONFIRMED (p_false 1.11e-03, exact).
- The matched `ConnectionManager::update` (0x0066AB30) calls ILT 0x00049080, which jumps here.
  It passes `this` as the one stack argument and calls only when its disconnect manager at
  +0x120E0 is non-null. The body ends `ret 4`.
- Boundary: the two `ret 4` exits are at +0x440 and +0x45F, followed by INT3. That gives
  1122 bytes, and the ledger extent is unchanged.
- The body uses DisconnectManager fields:
  - the last-frame pair at +0x04/+0x08;
  - the state at +0x0C;
  - player timeouts at +0x14;
  - the vote matrix at +0x30;
  - the screen-on time at +0x25C;
  - ping counters at +0x260/+0x264.
- It calls these DisconnectManager members through their ILTs: sendKeepAlive, turnOnScreen and
  updateDisconnectStatus.
- These are inlined, as they are in the matched resetPlayerTimeouts and processDisconnectCommand:
  - translatedSlotPosition and resetPlayerTimeout;
  - turnOffScreen, including HideDisconnectWindow;
  - the 0.1 ping-ratio test (`hasPingSuccessRatioAtLeast`).

## Donor evidence (BFME 2, Open-BFME-2 59e3f8f825)
- `Code/GameEngine/Source/GameNetwork/DisconnectManagerO1.cpp` DisconnectManager::update
  (BFME 2 0x004D46FC, 861 B, matched there). It supplies BFME's rewritten stall detection:
  - each stall is charged once, to the slot or to the local slot when the ping ratio is under
    0.1;
  - a stalled flag;
  - the game is left after five local stalls, with fewer than two players, or on the victory
    queries; otherwise the disconnect screen is turned on;
  - the screen is turned off when nothing stalls;
  - the last-frame clock;
  - first-ping-server requests every 3000 ms (5 repetitions, 2000 ms timeout);
  - only answered pings under 2000 ms are counted.

## BFME 1 adaptations (retail body, not donor)
- The per-tick layout refresh at the top is 0x0050E5F0, reached through ILT 0x000036FC with no
  receiver set up. It is pinned this-less as `?bfmeUpdateDisconnectScreen@@YAXXZ`, beside the
  ledger row `?_bfme_updateScreen@DisconnectMenu@@QAEXXZ` (`pin_consistency`: consistent).
  BFME 2 calls its twin `Rva00512CCDShutdown`.
- The load-screen test is GameLogic+0x118. There is no GameLogic+0x114 game-mode test before the
  victory queries; those are TheVictoryConditions slots +0x38, +0x34 and +0x40.
- Leaving the game is TheNetwork slot +0x78.
- The stall counts are words at +0x272, the charged flags bytes at +0x282, and the stalled flag
  is at +0x270 (the same raw offsets `init` uses). The shim's m_pingFrame (+0x268) holds the last
  ping time.
- The unit now compiles with `/D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC` and the
  `zhcanonascii` AsciiString. These give the inline STLport string/list node-allocator teardown
  and the AsciiString text at +8 that the ping-server copy uses. All other rows in the unit stay
  byte-exact.
- The leave branch is written as `if (count >= 5 && TheNetwork) leave; else if (players < 2 ||
  victory) { if (TheNetwork) leave; } else turnOnScreen;`. That spelling reproduces retail's
  merged leave path and its EDX/EAX vtable temporaries. The equivalent nested form leaves 14
  scratch-register bytes.
