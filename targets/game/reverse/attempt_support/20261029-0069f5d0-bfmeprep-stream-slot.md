# 0x0069F5D0 `?bfmePrep@Gen_006A6AF0@@QAEXHH@Z` (295 B, ret 8) — bank

Identity: matched callers in `game/GameEngine/Source/Common/Bfme/Rva006A6AF0Grid.cpp`
(0x006A6AF0/0x006AA8F4), Rva006A57D0GridDrain.cpp and Rva006A5870Case4.cpp all
call it through ILT 0x000299A1 as pinned `bfmePrep@Gen_006A6AF0`; the receiver is
MilesAudioManager (mutex/slot layout of MilesAudioManagerStopChain.cpp).

Semantics (retail): `if (m_ad0[index]) { m_ad0[index].clear(); return; }`
`it = getSlot(index, m_ac4[index])` (ILT 0x0001815B, pinned
`getSlot@Rva0069F740Owner`); `if (it == m_list9d0.end()) return;`
`PlayingAudioRef playing = *it; playing->m_35 = 0;` `flag == 0` -> `m_34 = 1`;
else `m_34 = 0; AIL_pause_stream(playing->m_milesHandle, 1);`
`playing->m_28 = (float)m_audioSettings->m_fadeAudioFrames; m_list9d0.erase(it);`
(erase = ILT 0x00020D24, already bound in StopChain's TU).

Best: the stash (StopChain TU copy + this body as
`MilesAudioManager::bfmePrep0069F5D0`; a Gen_006A6AF0 forwarder would carry the
pinned name). 293/295 B, shape 0.979, 2 structural differences:
1. retail hoists the `m_ac4[index]` load above `je` with ESI=index, EDI=this.
   No hoist (direct `getSlot(index, m_ac4[index])`) keeps ESI/EDI right; a
   `current` local before the `if` hoists but swaps ESI/EDI (148 vs 208 diffs).
2. after the call retail loads end() then reads the iterator from its stack
   home `[esp+0x20]` (index param home) into EBX; ours reads `[eax]` into EBP.

Inert/worse: THUNK member-pointer call vs direct pinned call (same); iterator
built from Ref / assigned / RVO'd named iterator (frame grows: 0.838); named
or const-ref Ref (frame grows); explicit out-param thunk (frame grows); Ref
with copy ctor or empty dtor (same); if/else instead of early return; block
scopes; `PlayingAudioRef &slot`; flags /Ob1 context from StopChain.
