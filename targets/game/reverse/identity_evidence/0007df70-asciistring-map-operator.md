# Correct identity at RVA 0x0007DF70

The matched `BfmeAptScreenOptions::save` callback at RVA `0x00560280` declares `PreferenceMap` as `std::map<AsciiString, AsciiString>` in `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/BfmeAptScreenOptionsSave.cpp`. The callback makes 32 calls through the import lookup thunk (ILT) at `0x0003E6DA`. That thunk jumps to `0x0007DF70`.

The 231-byte body at `0x0007DF70` calls the STLport tree lookup and insertion helpers. It also calls `StringBase<char>` copy and release functions. It does not call a `MapMetaData` constructor or destructor.

ILT `0x00039423` sends the insertion call to the matched 629-byte body at `0x0007DBC0`. That body inserts an `AsciiString` key and a mapped slot that occupies four bytes. The map operator[] call passes a mapped string whose pointer is null, so the helper copies those four bytes unchanged.

The old ledger row named this body as `std::map<AsciiString, MapMetaData>::operator[]`. The separate `MapCache` type stores map metadata. Its implementation at `0x000C1D10` uses that mapped type and occupies 250 bytes. The retail binary keeps separate bodies at these two addresses, so the old row named the wrong specialization.
