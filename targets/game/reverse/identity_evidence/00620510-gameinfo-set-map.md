# GameInfo::setMap, 00620510

The existing named setMap thunk and authored GameInfo::setMapForwarder0068DF70
supply the member identity and by-value AsciiString ABI. That forwarder calls
00620510 through ILT0001B5DB. The original GameInfo.cpp map-mask/file-check
algorithm agrees with the entire native reconstruction. Complete extent1213
includes the terminal RET4 at+4BA, with no embedded tables.

Retail assigns GameInfo+3C, tests the in-game flag+0C, then calls bool amIHost()
through vtable+10. The independently authored GameInfo constructor00620310/98
and copy constructor004F9A70/134 install VA01102F7C; its slot4 is ILT0001890D.
The original virtual declaration and observed boolean use establish this slot.
The existing constructor independently locates the AsciiString member at+3C.
The mask is+48, agreeing with the newly recovered parser00621C40.

The native body probes the ordinary preview, map.ini, localized strings,
solo.ini, assetusage, readme and the two BFME art/picture previews. Those final
two helpers are independently authored FileTransfer path builders0066D820/300
and0066D9A0/300, whose format literals establish their meaning. Their successful
opens set128/256. Metadata bytes+25 and+26 jointly enable mask512; their semantic
names remain address-derived because the layout oracle has no BFME witness.
The original token/path construction and all string temporary lifetimes remain
native C++, including StringBase's visible find and concatenation helpers.

File::close is virtual slot2 (+8), independently established by the seven File
vtables and authored File.cpp. The older failed reconstruction used slot3.
FileSystem::openFile takes (const char*,int), and retail passes zero as the mode
for all eight opens. MapCache::findMap takes AsciiString by value and returns a
const metadata pointer, as its authored122-byte body00454500 demonstrates.
All six path-builder helpers take AsciiString by value and return it through
the compiler's hidden return pointer. Native StringBase calls use their existing
member signatures. No new symbols pins or numeric-call adapters are needed.

Strict verification:1213/1213 bytes,49 direct calls,76 object relocations and
zero unresolved targets. Non-string DIR32 symbols are TheMapCache VA012F1594
(existing map-cache users) and TheFileSystem VA0134CB48 (existing FileSystem
users); no vtable or other new data symbol is emitted. Scratch receipts:
build/four-hour-setmap/strict-clean.txt, strict-result.json, dir32-data.json,
retail.asm, callees.txt, gameinfo-vtable.txt and probe1.txt. Model GPT-6; t=6min.
The fresh lever was the already independently proven GameInfo layout and File
virtual slots, which directly resolve the prior blocked attempt's objections.
