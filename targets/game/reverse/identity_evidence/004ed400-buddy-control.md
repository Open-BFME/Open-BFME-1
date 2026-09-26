# BuddyControlSystem, 004ED400, 1390 bytes

The identity is independently fixed by the already matched WOLBuddyOverlaySystem
and DiplomacySystem calls through the same ILT into 004ED400, and the canonical
Zero Hour body. Reconstruction starts from the existing .62 bank, preserving its
control flow while adopting the now-proven BFME string and buddy layouts. Retail
omits the bank's initial getLocalProfileID guard. Both message cases and all
1390 bytes through RET at +056D match; no tables or padding are counted.

The native body handles edit-done 4030 and right-click 4016. BuddyControls is the
same independently matched 25-byte constructor layout used by updateBuddyInfo:
chat/list/edit pointers and their IDs, then the initialized flag at +18.
BuddyRequest is 0x2B8 bytes, as independently copied by getRequest 0063C770;
message kind 3, recipient +4 and 128-wide-character payload +8. BuddyMessage's
24-byte layout, copy004EA520, destructor004EA4B0, and native string delegates
are established by the landed sibling handlers. Native GameWindow declarations
come from the existing BFME gamewindow header. The legacy embedded window text
view has a separate preprocessor name so it does not replace canonical strings.

The player-list local pointer at +0C and GameInfo in-game flag at +0C are existing
layout witnesses. GameSpyGameSlot_constructor.cpp independently places
m_profileID at +44; the canonical accessor identifies it as the profile ID.
The layout view's first window at +8 and virtual runInit at slot 0 agree with
existing WindowLayout users. Display width/height use unsigned returns from
slots+2C/+30, and the window-manager create-layout/lone-window slots are+6C/+BC.
The 12-byte GameSpyRCMenuData matches the native header and aligned writes.

## One independently proved dependency pin

Strict resolution initially left only list<BuddyMessage>::push_back unresolved.
The independent 48-byte004ECFD0 callee:

* receives the list in ECX and one const element reference, ending in RET 4;
* allocates a 32-byte doubly linked node, with payload at +8;
* calls ILT 00020E69, which jumps to the already matched 66-byte
  `_Construct<BuddyMessage,BuddyMessage>` at 004EA880;
* that constructor wrapper calls the independently matched 120-byte
  BuddyMessage copy at 004EA520, then the append rewires all four list links.

This proves the 24-byte payload identity independently of the desired caller
shape. The one added pin uses the real native list template symbol; the existing
opaque 48-byte helper row retains ownership and contributes no new coverage.
Pin consistency was checked before and after. All remaining direct calls and
data references resolve through existing proven contracts.

No header changes or assembly are introduced. The original naked body is
removed from WOLBuddyOverlay.cpp; its other 35 rows retain their source ownership.
The new 1390-byte native body is the only added coverage.
