# TechAndSupplyImages constructor at 0x00452150

The canonical global `TechAndSupplyImages TheSupplyAndTechImageLocations` is defined in `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SkirmishGameOptionsMenu.cpp` (formerly line 638). Its type contains the two `ICoord2DList` members `m_techPosList` and `m_supplyPosList`, used by that same owner.

MSVC 7.1 emits its native dynamic initializer as `_$E18`: DIR32 relocation to `?TheSupplyAndTechImageLocations@@3VTechAndSupplyImages@@A`, REL32 relocation to `??0TechAndSupplyImages@@QAE@XZ`, and registration of native cleanup `_$E19`.

The 22-byte retail initializer at 0x00C6B7D0 encodes `B9 B0 15 2F 01 E8 B6 34 3B FF`, placing the global at VA 0x012F15B0 and calling ILT 0x0001EC90. `pin_consistency.py --symbol '??0TechAndSupplyImages@@QAE@XZ'` independently follows that retail jump to body 0x00452150. The native initializer reproduces the retail bytes when the constructor resolves through this route.

The prior `??0Rva00452150Owner@@QAE@XZ` row was a 100-byte two-list constructor with an explicitly unidentified owning class. The native global initializer proves the owning type; replace that one row with the native TechAndSupplyImages constructor at the same 0x00452150/100-byte extent. Do not add a second identity or reduce coverage.

Repository source search found the old `Rva00452150Owner` class only in its obsolete defining TU `Rva00452150TwoListCtor.cpp`; no consumer needs a compatibility alias. The native owner uses the existing `BFME_STLP_NODE_ALLOC` convention and static STLport linkage to reproduce the prior two-list allocation shape. Its constructor and the owner's existing destructor both byte-match retail.
