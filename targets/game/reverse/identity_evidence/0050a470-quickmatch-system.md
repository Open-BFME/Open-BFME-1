# Quick-match system handler, 0050A470 / 1177 bytes

The old free-function ASM row and bank had a GameWindow* plus three message
arguments. Retail instead saves incoming ECX as the menu, reads only three stack
arguments, and ends RET12 at0050A906. The full body ends0050A909; subsequent
bytes are INT3. The native member therefore takes message, data1 and data2.
Its owner is the existing BfmeAptScreenQuickMatchMenu: the independently matched
573-byte constructor00505830 keys all the same gadgets, including maxPing230,
numPlayers238, ladder240, maxDisconnects248, back260, start268, personalInfo278,
mapSelect280, widening298 and stop2A0. Each pointer follows its key by four bytes.
The already authored populateQuickMatchMapSelectListbox00507F70 uses these same
fields; its independent identity receipt is0x00507f70.md in this directory.
This is the BFME member form of the original WOLQuickMatchMenuSystem algorithm.

The actual messages are create1, destroy2, inputFocus17, buttonSelected4008,
listSelection4014, comboSelection4025 and editDone4030. The old bank's additional
mouse-enter/leave cases are absent from retail. Create and destroy retain
separate native case blocks. Focus writes the accepted byte through data2.
The two previously omitted combo branches call00505550 for maxPing and00505530
for maxDisconnects. Both independently authored26-byte setter bodies take an
ignored pointer and an integer, compare/store21C or224, and RET8.

The bank inherited m_isMatching/m_matchingLevel/m_isStopping/m_selectedMap for
218/21C/220/224. The named constructor proves the adjacent gadget key identities,
and the independent26-byte setters prove these integers are selection values
for maxPing/maxDisconnects, not a matching level or map selection. The boolean
fields gate those corresponding gadget callbacks. Their precise BFME member
names are not independently established, so this TU uses m_rva218/21C/220/224.
Hash-scoped name_corrections entries preserve that evidence-backed correction;
they do not change the existing constructor's source or its claims.

PeerRequest is194 bytes, witnessed by the existing004D51B0 constructor and
00647470 copy family. This handler writes request kind11 (widen search), passes
it by const reference through peer queue slot18, and invokes its destructor
004D52D0. The old bank's kind12 was wrong. The frame is1B8, including this
request, native QuickMatchPreferences, and the UnicodeString temporary.

## Callee and data contracts

All34 distinct targets were decoded before the reconstruction. Strict final
verification is1177/1177,44 REL32 call sites,58 object relocations and no
unresolved symbols. Existing canonical string headers and real UnicodeString
forwarders are used. Existing QuickMatchPreferences and LadderInfo headers
supply their native C++ structures; ladder playersPerTeam is+C and randomMaps18.

The source uses existing address-only ILT symbols where historical ledger
spelling does not expose the required ABI, with no new pins:

*00031E0D ->005063E0 saves menu preferences, a no-argument receiver member.
 The old ledger's34 bytes are only its prologue; fresh decoding reaches the
 actual plain RET at+25E. No callee extent or coverage is changed here.
*00035701 ->005082D0 takes an int side and const LadderInfo*, RET8. Native
 member-pointer expression preserves evaluation of the preference getter and
 the already prepared ladder argument; it does not introduce a wrapper call.
*00021864 ->005053C0 returns the selected ladder pointer; its existing body
 and the newly landed00506720 caller independently establish this contract.
*0002716A ->00505570 is the authored zero-argument start-button updater.
*0002AAB8 ->00509B30 takes the selected GameWindow*; its existing named pin and
 independently decoded call/prologue establish the start-request ABI.
*0001DDA9 ->00505C00 takes the selected control in its one stack slot. Its
 authored92-byte body ignores the argument and RET4, although the old shim
 called that unused argument bool. No bool conversion is emitted by this caller.

The real member populateQuickMatchMapSelectListbox(QuickMatchPreferences&),
existing26-byte setter views, stop handler and back-navigation handler retain
their existing symbols and bodies. This conversion adds no helper claims.

GameSpyColor is VA012B9200 and selected/unselected map colors are indices25/26,
as shown by the actual scaled data load. Image pointers are the independently
address-derived globals012F480C/10. TheImage width field24 is read through the
existing Image accessor. Native reference-returning std::min/std::max with
named input values reproduce the witnessed frame temporaries; no volatile
loads, raw stack references or assembly are used. Static menu state is at
012F4801/09/14 and buddies key012F47F8. The peer queue and ladder list are the
already established globals012F71C8 and012F70E8. No new vtable is emitted.

Scratch receipts: build/four-hour-qmsystem/{retail.asm,callees.txt,probe8.txt,
probe11.txt,probe12.txt,strict2.txt,strict-clean.txt,save-options-retail.asm}.
The old1104-byte/.23 bank was the starting source; the fresh ABI, omitted
branches, correct request kind, header adoption and native min/max lifetimes
resolve its blocker. Model GPT-6; new native credit1177, helper credit0.
