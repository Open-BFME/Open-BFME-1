# 0x00583680 BannerUI::update (679 B)

Target facts (BFME 1 retail):
- Boundary: EH prologue at 0x00583680, single RET at +0x2A6, 0xCC padding after.
- Identity: BannerUI's vtable 0x0110B828 slot 5 (SubsystemInterface::update in
  the ZH/BFME SubsystemInterface order: dtor, init, reset, update) holds ILT
  0x00036E80, which jumps here. BannerUI's other members (ctor, init/reset
  helpers at 0x005841D0, 0x00584330, 0x00583190) are already matched.
- Layout read from the body: banner entries (28 B stride) at this+0x30/+0x34,
  hidden flag byte +0x3C, pending summary index +0x40; entry +0x00 delete flag,
  +0x04 slot, +0x08 object id, +0x10/+0x14/+0x18 state/progress/timer.
- Strings: "APT:BannerTimer%d" (0x0110B778), L":" (0x010F5A78),
  L"%d%s%02d" (0x0110B760), "BANNERUI:SummaryTitle" (0x0110B744).
- EH map (eh_info.py): AsciiString, two UnicodeStrings, the fetched title,
  then the message object (0x003BD770 dtor) and its 0x010EDAA0 head (0x003BC950).
- Callees all carry ledger names (callees.py): SetBannerState 0x0050D5B0,
  SetBannerProgress 0x0050D6C0, BfmeGlobDXI::bfmeUseDXI 0x00583190 (ILT pin),
  WindowManager::bfme_setAptText 0x0046CBF0, Rva003BD700 ctor 0x003BD700,
  ControlBar::bfmeShowDN (ILT 0x00043702 pin), the three 11-byte logic
  forwarders 0x003838C0/0x003838F0/0x00383910, GameText slot 10.

Donor facts (Open BFME 2 45afcff3, Code/GameEngine/Source/GameClient/GUI/
InGame/Tactical/BannerUI.cpp, BannerUI::update, byte-matched in BFME 2 at
0x002167A3): the per-banner state/progress/timer refresh, the timer string
built from minutes, the language time separator and seconds, and the summary
message. BFME 1 differs (no erase loop, two-argument text setter); those
differences were taken from the BFME 1 bytes, not the donor.

Inference: the timer divisor 5 and the switch mapping (0->0, 2->1, 3->2,
else 3) are read from the code; their meaning is not asserted.
Verification: probe EXACT 679/679 modulo relocations.
