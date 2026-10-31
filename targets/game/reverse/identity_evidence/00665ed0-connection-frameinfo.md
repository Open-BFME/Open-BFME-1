# 0x00665ED0 BFMEConnectionManager::rva00665ED0 (235 B)

- Boundary: ret at +0xEA then int3 (235 B); the body pops no argument and
  never reads a stack slot, so the lift's ZH spelling
  `?sendFrameInfoToPlayer@BFMEConnectionManager@@QAEXH@Z` (one int) is wrong.
  ilt_oracle contradicts both that spelling and the no-argument one, so the
  method keeps an address-derived name.
- Receiver: BFMEConnectionManager (m_localSlot / m_packetRouterSlot reads as
  in the matched native_connection_timing.cpp siblings); allocates a
  NetFrameCommandMsg, sets frame = TheGameLogic frame - 1 and the client
  frame, an ID when DoesCommandRequireACommandID, the local player, and sends
  it to the router or (on the router) to every other slot.
