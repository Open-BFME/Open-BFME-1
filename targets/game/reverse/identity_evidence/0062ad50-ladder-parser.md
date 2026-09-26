# parseLadder, RVA 0062AD50

The 3077-byte body is native C++ in `game/GameEngine/Source/GameNetwork/GameSpy/LadderParse.cpp`.
No existing helper body is counted again. The old 3595-byte bank was the starting
source, but retained the Zero Hour faction fallback; retail instead appends the
literal strings `America`, `China`, and `GLA` (VAs 01100C5C, 01100C4C, 01100C40).
This records the executable's parser behavior, not a claim that the legacy
ladder subsystem is exercised in BFME gameplay.

## Identity and complete extent

* Matched `LadderList::checkLadder` (0062BC60, 380 bytes) constructs the by-value
  AsciiString argument at 0062BD2B..0062BD37, calls 0062AD50 at **0062BD3C**,
  and consumes the returned LadderInfo pointer. The earlier pin note's
  0062BCDC was wrong: that instruction sets ECX for a File read.
* The EA LadderDefs parser has the same tag grammar, map checks, field writes,
  and return/cleanup behavior. The 3Ch allocation calls matched LadderInfo
  constructor 0062A910; deletion calls destructor 0062A9E0. Existing layout
  proves Unicode fields 00/04/08, team/win fields 0C/10/14, flags 18..1B,
  lists 1C/20, password/address 24/28, port 2C, URL 30, and index 38.
* Matched MapMetaData constructor 004543D0 and copy constructor 000C1240
  independently establish the two string words and six extent floats before
  `m_numPlayers` at 20h. The parser reads that same field from findMap's result.
* Complete range is [0062AD50,0062B955). The final instruction at 0062B950 is a
  five-byte jump to the shared epilogue at body+92F, followed by INT3 padding
  from 0062B955. It is not a truncated RET-based extent.

## Bounded helper contracts

The canonical AsciiString list __find pin at ILT 00027BAB routes to **004C4530**,
a separately established UTF-16 list search. It cannot be used for this parser.
The existing helper ownership is left intact, and two address-derived typed
views are used only in this translation unit:

* 00080110, 130 bytes: cdecl STLport list iterator search, hidden return pointer,
  first/last iterators by value, AsciiString const reference and iterator tag
  reference. Node next is +0, value +8. The string header has unsigned-short
  length +4 and character data +8; the complete loop uses REPE CMPSB and the
  length difference. The canonical AsciiString::compare body reproduces all
  130 bytes, including both empty-string relocations. Parser+55F calls it
  through ILT 0002D66E.
* 00080590, 46 bytes: cdecl wrapper with the same hidden return and first/last
  iterators/value reference; it supplies the tag reference and calls the above
  helper through ILT 0002D66E. Parser+598 and +850 reach this wrapper through
  ILT 0001F6F9. The complete wrapper independently matches all 46 bytes.

Both signatures use canonical AsciiString and STLport iterator definitions.
The address tokens avoid assigning a new semantic template identity over the
existing legacy view claims. Two pins support the caller; neither adds a
functions.csv helper row or moves existing ownership.

The two remaining out-of-line startsWith calls target StringBase<char>'s
verified 50-byte pointer overload at 00061DF0 through ILT 0001702B. Explicit
base views preserve the correct symbol. Full visible string delegates come
from StringBase.cpp and AsciiStringNative.cpp; no shared header was changed.

## Verification

* Probe: 3077/3077 bytes, 166 relocation slots; exact instruction shape.
* `add_match.py --model GPT-6`: strict main-body gate 1/1 passed.
* Independently selected helper rows: strict gate 2/2 passed, no unresolved
  calls or masked bytes (130+46 concrete bytes). These were verification-only
  rows and were never added to the ledger.
* Pin consistency passed, including route derivation. Progress reports
  +3077 native C++ bytes; helper dependency credit is zero.

## LadderList constructor sibling, 0062C020

The 925-byte constructor is now native in `LadderListConstructor.cpp`, replacing
its sole naked source. Complete extent is [0062C020,0062C3BD): RET at 0062C3BC,
then INT3 padding. The EA LadderList constructor has the same three list
members at 00/04/08, config virtual getter at slot34h, ladder section grammar,
call to independently established parseLadder, and final loadLocalLadders call.
The existing SetUpGameSpy call through the ILT also reaches this constructor;
its old naked caller is supporting xref evidence, not independent source proof.

Canonical string delegates make the first baseline exactly925 bytes with24
register-operand differences in the first comparisons. The full comparison's
`if (result != 0) return result; return myLen-len;` form resolves those bytes,
retaining the same byte/length comparison semantics and complete helper body.
Strict add_match gate passed1/1 with44 relocations; eight literal and three
empty-string references are verified. There are no new pins. Existing legacy
LadderDefs.cpp generated EH helper owners remain unchanged. Native gain925B.
