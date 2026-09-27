# RVA 0x00456A90: map-list population, not MapCache::addMap

Retire `?addMap@MapCache@@AAE_NVAsciiString@@0PAUFileInfo@@_N@Z` over the unchanged 1178-byte extent.
Use `?populateMapListboxRva00456A90@@YAHPAVGameWindow@@IABVAsciiString@@@Z`.
The address token is retained because the original BFME spelling is not proven.

Independent identity and ABI evidence from the retail image:

* VA 0x00856AD5 pushes list length 1000 and the first stack argument, then calls ILT 0x0002D939 -> GadgetListBoxSetListLength at RVA 0x004BB8E0.
* The first argument is again passed to GadgetListBoxGetNumColumns (ILT 0x000267A1 -> 0x004B79B0), image/text entry insertion, item-data assignment, and list selection. It is a GameWindow list box, not a MapCache receiver or by-value string.
* The second argument is tested for flag 0x40 at VA 0x00856C3A and passed to the independently reconstructed map filter at RVA 0x00453480 through ILT 0x0000BCD5.
* The third argument is a const AsciiString reference passed to StringBase<char>::compare at VA 0x00856DDE-0x00856DE6 (ILT 0x000220C5 -> 0x0005FEB0).
* RET at VA 0x00856F29 performs no callee stack cleanup. No incoming ECX receiver is consumed. There are no two by-value AsciiString argument destructors, contradicting the old member signature.
* Star-Bronze, Star-Silver, Star-Gold, SkirmishPreferences::getUserName, and SkirmishBattleHonors::getEnduranceMedal agree with the Zero Hour populateMapListboxNoReset body in GameClient/MapUtil.cpp. BFME uses its vector filter and three-argument free-function ABI instead of the ZH signature.
* The returned integer is the selected list entry, initially -1, not a bool map-cache insertion result.

Layout evidence: matched MapMetaData lifecycle/getFileName bodies establish multiplayer byte +0x24 and AsciiString filename +0x50. Image +0x24 is the layout-oracle-witnessed m_imageSize. SkirmishPreferences constructor and destructor establish size 0x18; new SkirmishBattleHonors requests 0x3c bytes and uses its virtual deleting destructor.

Callee routing: call at VA 0x00856C65 reaches ILT 0x0000BCD5 -> RVA 0x00453480; call at VA 0x00856C7E reaches ILT 0x00029884 -> RVA 0x00456860. The latter is the already matched three-argument pointer-range introsort driver. Its comparator occupies one stack slot; only its first byte is initialized by this caller. The final source reuses the existing filter TU and existing opaque Q3Sort driver spelling. No callee pins were added. The filter stayed byte-exact in the two-function scoped gate.
