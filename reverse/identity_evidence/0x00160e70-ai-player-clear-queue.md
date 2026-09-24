# 0x00160E70: AIPlayer::clearTeamsInQueue

The existing matched row calls this 27-byte body `BfmeThing920F::bfmeGo920F`, a generic reconstruction name. Its owner and method are independently established:

- Retail `0x00160E70` ends with `ret` at `+0x1A`, followed by padding. It passes the same callback address `0x00560E50` to ILTs `0x000497DD` and `0x00012B20`. `tools/callees.py 0x00160E70 27` resolves them to matched `AIPlayer::removeAll_TeamBuildQueue` at `0x001607C0` and `AIPlayer::removeAll_TeamReadyQueue` at `0x00160990`.
- Matched `AISkirmishPlayer::~AISkirmishPlayer` at `0x00168710` calls ILT `0x00033D9D`, which jumps to `0x00160E70`, before calling the `AIPlayer` base destructor at `0x001613C0`. Both the native and vendored `AISkirmishPlayer.cpp` definitions call `clearTeamsInQueue()` from that destructor. The matched destructor source already documents this route.
- Native `AIPlayer.cpp` and the vendored `AIPlayer.cpp` each define `clearTeamsInQueue()` as precisely those two queue-removal calls with one `deleteQueue` callback. The existing `reverse/symbols.csv` pin independently names `?clearTeamsInQueue@AIPlayer@@IAEXXZ` at `0x00160E70`.

Before changing the ledger, a clean C++ definition added in a scratch copy of `AIPlayerQueueTeardown.cpp` compiled to 27/27 bytes with four relocation sites and `tools/probe.py` reported `EXACT` modulo relocations. The replacement must be verified through `tools/add_match.py --replace-rva 0x00160E70 --correct-identity`, which records the retired name in `deleted_rows.csv`, followed by the scoped byte gate and name checks. This correction changes identity and source placement, not byte coverage. The callback at `0x00160E50` has a separate generic name and is outside this correction.
