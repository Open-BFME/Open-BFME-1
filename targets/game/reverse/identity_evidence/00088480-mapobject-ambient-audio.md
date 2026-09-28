# 0x00088480 MapObject ambient-audio body (1019 B)

Class: MapObject. MapObject::duplicate (matched, WorldHeightMap.cpp) calls this
body on the freshly built MapObject through ILT 0x00031FCF; bfmeGoEYE
(BfmeConv888.cpp) stores the mode global 0x012ED5D8 and walks the MapObject list
(next pointer at +0x04, as in the matched MapObject destructor) calling it. The
members it touches (+0x18 thing template, +0x24 properties Dict, +0x44 runtime
flags, +0x54/+0x58 audio handles, +0x5C ref) agree with the matched destructor.

Method name: unproven, kept opaque with the address (ambientAudio00088480). The
" MapObjectAmb %d %s" literal (0x0107C7E4) and the AudioManager addAudioEvent
(+0x44) / getInfoForAudioEvent (+0xAC) calls show only that it builds the object's
ambient audio events.

2026-09-28 rewrite: the earlier bank modelled every callee as a raw j_ thunk with
cast member pointers and named its stack locals (m_current, m_audioInfo,
m_data, slot, call) after roles it guessed. The rewrite replaces that scaffolding
with one ref-counted pointer class (members m_ptr) whose operator=/raw-pointer
ctor are the 0x00087750/0x00087720 bodies, the AsciiString header type in place
of the BFMERetailAsciiString shim, the ledger's own Rva00087BD0::get for the
template's indexed sound lookup, and the ledger's gen00087C30 for the stop call
at 0x00087C30. No descriptive name was replaced by a guess; the old names were
scaffolding for a different decomposition, not evidence about these members.
