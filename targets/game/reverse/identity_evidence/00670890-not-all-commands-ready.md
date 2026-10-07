# 0x00670890 is not FrameDataManager::allCommandsReady

The gen-alias row `?dup_00670890@@YAXXZ` (34 bytes) borrowed
`?allCommandsReady@FrameDataManager@@QAE?AW4FrameDataReturnType@@I_N@Z` (its note
called it an "ICF clone at 0x00670670"; retail has no ICF). Since f4b01f3dc5's
twin rule it failed: its call (+0x1A) goes through ILT 0x00026C79 to 0x00670390,
not to FrameData::allCommandsReady at 0x00670240.

- Bytes: `mov eax,[esp+4]; xor edx,edx; div dword [0x012BA088]; mov eax,[esp+8];
  push eax; mov eax,[ecx+4]; lea edx,[edx+edx*4]; lea ecx,[eax+edx*4];
  call 0x00026C79; ret 8` -- the FrameDataManager ring-wrapper shape
  (frame % FRAME_DATA_LENGTH, m_frameData at +4, 20-byte FrameData stride)
  shared by allCommandsReady 0x00670670 and setFrameCommandCount 0x00670750.
- Position: between getIsQuitting (0x00670880) and getAckCommandCount
  (0x006708C0), inside FrameDataManager.cpp's run 0x00670410..0x00670910.
- Callee: 0x00670390 (40 bytes) sits in FrameData.cpp's run (between
  destroyGameMessages 0x00670370 and getAckCommandCount 0x006703D0); it walks
  the list at FrameData+0x08 and counts entries whose +0x14 field equals its
  argument. It is matched as `?bfmeCountYN@BfmeThingYN@@QBEHH@Z`.

ZH has no such FrameDataManager member, so the wrapper is landed as the
address-derived `FrameDataManager::rva00670890(UnsignedInt, Int)` in
FrameDataManager.cpp, calling the callee by its matched name.
