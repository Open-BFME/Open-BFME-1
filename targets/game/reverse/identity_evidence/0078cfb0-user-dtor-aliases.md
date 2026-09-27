# 0x0078CFB0 / 0x0078D240 are not PopupMessageData's or DynamicAudioEventRTS's destructors

Four alias rows claimed User.cpp's destructor pair for two other classes:
`??1PopupMessageData@@MAE@XZ` and `??1DynamicAudioEventRTS@@MAE@XZ` on 0x0078CFB0,
`??_GPopupMessageData@@MAEPAXI@Z` and `??_GDynamicAudioEventRTS@@MAEPAXI@Z` on 0x0078D240.

* **The pair belongs to table 0x01126DA0.** 0x0078CFB0 stores 0x01126DA0 at entry,
  destroys a UnicodeString at +4, then stores the base table 0x01126D84. Slot 5 of
  0x01126DA0 routes (ILT 0x00039C52) to 0x0078D240, the deleting destructor that
  calls 0x0078CFB0. `User.cpp` claims both as `??1User@@MAE@XZ` and
  `??_GUser@@MAEPAXI@Z`.
* **PopupMessageData's table is 0x010F58C4.** The matched constructor 0x0043F460,
  destructor 0x0043F4B0 and `InGameUI::popupMessage` (0x00442040) install it. Its
  slot 0 routes (ILT 0x000230C4) to 0x0083F480, PopupMessageData's deleting
  destructor. So neither 0x0078CFB0 nor 0x0078D240 can be PopupMessageData's.
* **DynamicAudioEventRTS's table is 0x01082DE0**, which the matched
  `??4AudioArray@@QAEAAV0@ABV0@@Z` (0x00134880) and the DynamicAudioEventRTS INI
  parser (0x000BB9A0) store when they construct one inline.
* Retail has no identical-COMDAT folding, so each of the four rows was an
  over-claim. The DIR32 check showed it: the two `??1` aliases resolved
  `??_7PopupMessageData@@6B@` to 0x01126DA0.
