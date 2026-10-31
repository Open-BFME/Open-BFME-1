# 0x006C3170 W3DRadar::drawEvents (729 B)

BFME 1 target evidence:
- `tools/ilt_oracle.py check '?drawEvents@W3DRadar@@IAEXHHHHH@Z' 0x6C3170`:
  CONFIRMED (exact). The ledger's ZH four-int spelling
  `?drawEvents@W3DRadar@@IAEXHHHH@Z` is CONTRADICTED, as are the public and
  private five-int spellings.
- Retail ends `ret 0x14` at +0x2D6: five stack ints. The matched radar draw
  0x006C4A50 (Rva006C4A50.cpp) passes five arguments through its typed view
  pin `?drawEvents@Rva006C4A50Owner@@QAEXHHHHH@Z`. The fifth is never read.
- Body: 64 records of stride 0x50 from this+0x28; a static `AudioEventRTS`
  built from the "RadarEvent" literal (0x0111D844) under guard 0x012F7FD0,
  object 0x012F7F48, atexit thunk 0x00C70920; a missing ping handle is fetched
  by type from 0x012F4B98 through 0x006C1C40/1C10/1C70/1CA0/1CD0
  ("PingBeacon"/"PingAttack"/"PingGeneric"/"PingInformation"/"PingUpgrade",
  BfmeConv785.cpp), assigned through 0x006C1B50 and released through
  0x00107550; the inlined Radar::radarToPixel (x*w/128+px, (127-y)*h/128+py)
  feeds the ping's slot-1 call, and the ping's slot-2 call runs once
  TheGameClient's slot-26 frame passes the record's +0x10 frame.

Donor evidence (open-bfme-2 b5a7b8290, Code/GameEngineDevice/Source/W3DDevice/
GameClient/W3DRadarDrawEvents.cpp, BFME 2 `?rva0004E5A2@W3DRadar@@QAEXHHHHH@Z`):
same record layout, ping-name order, `type` read before the sound-played store
and a read/write barrier after it. Structural inference: the ping getter
methods and counted handle keep address-derived names.
