# W3DGadgetRadioButtonDraw at RVA 00796480

## Identity and boundary

The unpacked retail name string at RVA 00D1D6A4 is
`W3DGadgetRadioButtonDraw`. The name-table entry at RVA 00EBA480 contains
`0, 0111D6A4, 00437E98` (key, name VA, function VA).
ILT RVA 00037E98 is E9 to body 00796480. This proves the exact name without
inferring it from behavior. The Zero Hour twin is
GameEngineDevice/Source/W3DDevice/GameClient/GUI/Gadget/W3DRadioButton.cpp:126.

Ghidra creates a 519-byte body at VA 00B96480. Independent retail decoding
ends with POP EDI/ESI/EBP/EBX, ADD ESP,20 and RET at RVA 00796686 (+206).
INT3 starts at 00796687 (+207), proving the 519-byte extent.

## Starting bank and code generation

The saved bank measures 519 bytes, 11 relocation slots and seven differences:
three SIB operand order bytes and four repeated stack/register assignments.
Its history already exhausts many expression and local lifetime variants.
Replacing its coordinate POD with the same two integers and an empty default
constructor removes all seven differences. A copy constructor is unnecessary.
Replacing the text helper with its existing verified version or removing the
bank's pointer-arithmetic spelling alone retains all seven differences.

The production change reuses the existing W3DRadioButtonText.cpp, including
its already matched 289-byte static text helper. A TU-local address-qualified
coordinate derives from canonical ICoord2D and adds only the empty default
constructor. It introduces no fields, initialization stores or escaping
objects. All four local coordinates have their used members assigned before
reads. This is a local source-shaping choice, not a claim that EA gave the
coordinate type this name or constructor. The canonical header is unchanged.

## BFME layout and virtual slots

The established TU uses Zero Hour headers, while the bank already embodied
BFME's inline color-array offsets. Retail independently reads:

- disabled background color/border at window+B8/BC, box color at C4 or D0;
- highlighted background color/border at +124/128, box at +130 or +13C;
- enabled background color/border at +4C/50, box at +58 or +64.

The header's corresponding getters read four bytes earlier. Only those
inline color getters use a window+4 view. All calls on the actual window,
including screen position, size and status, retain the original pointer.
No shifted receiver escapes to a real function or virtual call.

The final nullable text lookup reads instData+19C and invokes vtable slot
+0C. The existing BFMEDisplayString view already documents that ABI in the
same TU. A local WinInstanceData-derived view reuses canonical m_text and
provides the inline member getTextLength with the BFME slot. A free accessor
or direct conditional drops the witnessed MOV ECX,EAX and produces 517 bytes;
the member accessor preserves all 519 bytes. No field or semantic name is
replaced: both local views inherit the canonical types.

## Calls and verification

callees.py and the retail instructions establish:

- ILT 0002F94B -> 004781D0, GameWindow::winGetScreenPosition;
- ILT 00036EBC -> 004782A0, GameWindow::winGetSize;
- ILT 00023DDA -> 00478480, GameWindow::winGetStatus;
- direct 00796310, the existing same-TU drawRadioButtonText helper.

The final helper call supplies window in ECX and instData in EAX, agreeing
with the helper prologue already documented in the source. The old ledger
note has the two registers reversed; its byte-verified helper definition is
unchanged. No new callee or data pin is required.

Strict add_match verification passes both the callback and existing helper
(2/2) and all seven DIR32 references. The pre-existing image callback is not
changed or promoted, and no second helper definition is introduced.

The local construction wrapper is spelled
`DefaultConstructed00796480<ICoord2D>` so the declaration explicitly retains
the canonical coordinate identity. This form also passes 2/2 strict verification
and staged naming checks with no correction entries.
