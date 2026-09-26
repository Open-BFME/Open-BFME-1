# LANAPI::OnHasMap at 0x00688CD0

The old `targets/game/reverse/symbols.csv` candidate `?OnHasMap@LANAPI@@UAEXI_N@Z` copied Zero Hour's scalar-IP signature. It identifies the right vtable slot and body, but the first argument's BFME type is wrong.

The byte-matched `LANAPI::handleHasMap` at 0x0068B540 is sourced from `game/GameEngine/Source/GameNetwork/LANAPIGames.cpp`. It constructs a `BfmeNetAddress *` from the sender, compares both its `m_ip` dword and `m_port` word with the eight slot addresses, then calls virtual slot 34 (`+0x88`) with that pointer and `msg->hasMap`. The retail call at +0xE8 pushes the status, pushes the address pointer in EDX, and invokes `[eax+0x88]`.

The slot-34 target at 0x00688CD0 reads the incoming pointer from its stack argument, loads its dword at +0 and word at +4, and ends with `ret 8`. This corroborates the pointer ABI independently of the C++ spelling. The source's two-field `BfmeNetAddress` layout is also used by matched LAN message handlers. The supported candidate is therefore `?OnHasMap@LANAPI@@UAEXPAUBfmeNetAddress@@_N@Z`.

The body remains a generated placeholder. A current native reconstruction is banked at `targets/game/reverse/attempts/0x00688cd0.cpp`; it compiles to 678 bytes against 709 retail bytes and does not establish a byte match. The pin correction only removes the misleading scalar signature and preserves the witnessed address-pair identity.
