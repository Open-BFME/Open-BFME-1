# BFME quick-match update, 00506720 / 4688 bytes

The previous named ASM row started at00506726, six bytes into the actual
function. Retail00506718..1F is INT3 padding;00506720 starts PUSH EBP / MOV
EBP,ESP / AND ESP,-8. Independently, ILT000158DE jumps to00506720. The
function saves incoming ECX and uses it for the layout shutdown callback;
its terminal RET4 is at00507905. The original free-function spelling taking
(WindowLayout*,void*) therefore describes the Zero Hour counterpart, not the
BFME ABI. The replacement keeps the proven update behavior and uses the honest
address-derived Rva00506720Layout owner rather than inventing its BFME class.

The full contiguous extent ends at00507970, including the seven-entry switch
jump table00507908..23, byte dispatch table00507924..34, its alignment padding,
and fourteen-entry jump table00507938..6F. INT3 padding resumes at00507970.
The old4682-byte ASM extent ended at that same point. Thus the replacement
recovers4682 dumped bytes and six formerly unclaimed prologue bytes, not an
overlapping second claim. A narrow ledger-range audit found only the old row
in this range. The table bytes are not executable instructions; probe's end
warning is its linear disassembler reading the last table entry as code.

The QM:* literals, original WOLQuickMatchMenu.cpp algorithm, and independent
quick-match sibling helpers establish the operation. The native reconstruction
handles persistent stats, disconnection, NAT negotiation, staging responses,
quick-match status, map selection and player setup. BFME additionally strips a
nickname suffix into a256-byte stack buffer, constructs the52-byte PlayerInfo,
and stores an8-byte IP/16-bit-port connection record. PeerResponse is330 bytes;
its payload startsF4, QM IPs104, ushort ports124, sides134, colors154 and NAT174.
Player names are the eight STL strings at7C. Landed lobby response-copy owners,
PlayerInfo constructors, PS parser00659670, and current GameInfo parser00621C40
independently establish those layouts. The real stack frame is9BC.

The GameInfo and GameSpyStagingRoom layouts follow the already landed map/parser
family: map3C, seed4C, slot stride78, quick-match byte43C, mode440, ladderIP444,
ladderPort450. The mode is1 for poolSize2,2 for4, and0 otherwise. The window
owner atglobal012F4820 keeps an address-derived name; its294 text window is
passed to addText and29C widening button to winEnable. Its native text-window
accessor restores the compiler's shared message-case tails; the connection
record stores port then IP, which reproduces the final native scheduling.

## Direct-call contracts and legacy conflicts

All61 distinct targets were read before conversion. The strict final caller
contains122 REL32 call sites and313 object relocations, with zero unresolved
symbols and zero differing bytes. No new symbols pins were introduced.

*00505D10/32 is the existing Rva00505D10StringOwner::value: it returns an
 AsciiString copy of receiver+48 through a hidden result pointer, RET4. Use
 that independently authored owner directly. The legacy named GameSpyGameSlot
 login getter at00638030 reads+70 and is not this target.
*00505D40/75 is the existing Gen00505D40::bfmeSet(AsciiString) contract:
 assign receiver+4C and destroy the by-value string. The caller uses that
 existing address-derived view directly rather than emitting a wrapper whose
 name could resolve to a different GameSpyGameSlot implementation.
*ILT0001F4A6 routes to0061E9D0/10: MOV EAX,[ESP+4]; MOV [ECX+4C],EAX;
 RET4. The aligned retail call supplies the integer QM seed, and GameInfo
 parser00621C40 independently establishes+4C. The ledger currently calls this
 W3DVolumetricShadow::setOptimalExtrusionPadding(float), while the named
 GameInfo::setSeed row is at000C8F50. This conversion does not endorse either
 conflicting identity: a typed member-call view uses the existing address-only
 ILT symbol with the proven int ABI. No float conversion and no new pin.
*ILT00021864 routes to005053C0/56. It returns the selected LadderInfo pointer;
 the address at+28 and16-bit port+2C feed existing ladder setters. The legacy
 owner is void-labelled, so a typed pointer-return member view uses this
 existing address-only ILT symbol without claiming a new semantic identity.
*ILT00048E73 routes to005057C0/90, the existing zero-argument layout shutdown
 member. The receiver is the callback's incoming ECX. The typed member view
 preserves that existing route and keeps the enclosing class opaque.
*ILT0003B746 routes to00505C80/79, the authored address-derived visibility
 helper. Its independent native body hides windows28C/294/2A4/29C, calls the
 existing state setter(false), and shows264. The caller uses that existing
 ILT route because the body ledger still has a d_ alias with object-symbol.
*StringBase<char>::compareNoCase(StringBase const&) is visibly defined from
 its real91-byte body00090570: _memicmp the minimum length, then subtract
 lengths on equality. Its own probe is EXACT91/91; visibility removes false
 extra EH states. No helper ownership or coverage is added.

The GameSpyInfo, peer/PS queues and GameLogic virtual slots reuse the independently
verified lobby family views. GameSpyInfo::addText takes UnicodeString by value,
Color and GameWindow*, atEC; startGame is GameSpyStagingRoom slotC. NAT::update
returns NATStateType. SendStatsToOtherPlayers takes const GameInfo*.

## Data identity and verification

The non-string DIR32 inventory has one base per external symbol, no new vtable,
and no new function-address global. Known globals match the landed lobby and
network family: GameLogic012F0898, Shell012F4B58, transition handler012F3330,
peer queue012F71C8, staging room012F7198, GameSpyInfo012F7194, PS queue012F76F0,
config012F70E4, MapCache012F1594, NAT012F770C, GameSpyColor012B9200,
GameText012F147C, NameKeyGenerator012ED600 and WindowManager012F1B40.
The InGameUI message view is at012F148C and the address-derived quick-match
window owner at012F4820. Static quick-match state references are012F4800,
012F4801,012F4804,012F4808 and buddiesID012F47F8; these are translation-unit
locals, consistent with the original sibling source. Empty strings are the
already verified01336E50/54 objects; CRT references are real IAT imports.

Scratch receipts: build/four-hour-quickmatch/{retail.asm,callees.txt,
probe11.txt,probe12.txt,probe14.txt,strict-clean.txt,strict-result.json,
compare-helper.txt,dir32-data.json}. The bank's3944-byte attempt was the starting
algorithm. Complete fresh Ghidra read-only decompilation and retail disassembly
supplied the BFME omissions; byte proof is the scoped compiler gate, not Ghidra.
Model GPT-6. New native credit4688; helper ownership credit0.

Independent agent review re-decoded ILT0001F4A6/0061E9D0 and
ILT00028565/00505D10 and confirmed both complete target extents and ABIs.
The normal add_match gate passed1/1 and verified30 literal plus3 empty-string
references, with no unverified or skipped string references.
