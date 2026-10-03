# 0085F2B0 is piConnectFillInUserCallbackA

- targets/game/reverse/dir32_addresses.csv records `_piConnectFillInUserCallbackA` at VA 0x00C5F2B0 (= RVA 0x0085F2B0, base 0x400000).
- The retail constructor in peerOperationsListGroupRooms.cpp passes that DIR32 address as the fillInUserCallback argument of chatConnectSecureA/LoginA/PreAuthA.
- The body (piMangleUser of the stored IP with the connection's user id) is the fill-in-user callback shape.
- Neighbours piConnectNickErrorCallbackA (0085F280) and piConnectConnectCallback (0085F1D0) carry their DIR32 names in the ledger.
- The earlier opaque name ?rva0085F2B0 was address-derived only.
