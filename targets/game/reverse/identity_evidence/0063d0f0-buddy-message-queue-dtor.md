# 0x0063D0F0 is `GameSpyBuddyMessageQueue::~GameSpyBuddyMessageQueue`, not GameResultsQueue's

* **Tables stored.** 0x0063D0F0 stores 0x01118E70 at entry and 0x01118E04 before
  it returns. The matched `??0GameSpyBuddyMessageQueue@@QAE@XZ` (0x0063E080,
  BuddyThread.cpp) installs 0x01118E70, so this is that class's destructor and
  0x01118E04 is its base, `GameSpyBuddyMessageQueueInterface` (Zero Hour
  BuddyThread.h): a deleting destructor followed by twelve pure slots, the same
  thirteen-slot count as 0x01118E70.
* **GameResultsQueue is elsewhere.** Slots 11 to 16 of 0x01119380 are the matched
  GameResultsQueue methods `areThreadsRunning`, `addRequest`, `getRequest`,
  `addResponse`, `getResponse` and `areGameResultsBeingSent` (GameResultsThread.cpp).
  The constructor 0x00642300 installs that table, and the destructor 0x00641C60
  stores it, then 0x01119318: `GameResultsInterface`, whose slot 2 is the matched
  `SubsystemInterface::loadIniFilesFromLegend`, as Zero Hour's
  `GameResultsInterface : public SubsystemInterface` requires.
* **The deleting destructors.**
  * 0x0063E170 is slot 0 of 0x01118E70 (ILT 0x0000F13C) and calls 0x0063D0F0
    (ILT 0x0004B402): `??_GGameSpyBuddyMessageQueue@@UAEPAXI@Z`, previously
    claimed as `??_GGameResultsQueue@@UAEPAXI@Z`.
  * 0x0063A700 is slot 0 of 0x01118E04 (ILT 0x00034059) and stores 0x01118E04
    before freeing: `??_GGameSpyBuddyMessageQueueInterface@@UAEPAXI@Z`, previously
    claimed as `??_GGameResultsInterface@@UAEPAXI@Z`.
* **Aliases retired.** `??_GGameSpyBuddyMessageQueue@@UAEPAXI@Z` on 0x005BF290 and
  `??_GGameSpyBuddyMessageQueueInterface@@UAEPAXI@Z` on 0x008E2260 were C++ alias
  rows compiled from other classes (`CategoryModuleTemplate<1>`,
  `CullSystemClass`). A class has one scalar deleting destructor and retail has
  no identical-COMDAT folding, so those two addresses cannot be these classes'.
