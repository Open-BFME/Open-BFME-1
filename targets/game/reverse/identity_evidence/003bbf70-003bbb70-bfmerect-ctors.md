# 0x003BBF70 / 0x003BBB70: BfmeRectVNE / BfmeRectVNG constructors

Both rows were ledgered as init methods returning `this`
(`?bfmeInitVNE@BfmeRectVNE@@QAEPAV1@IID@Z`,
`?bfmeInitVNG@BfmeRectVNG@@QAEPAV1@IABUBfmeRefVNG@@D@Z`). Retail evidence that
they are constructors (BFME 1 target facts):

- Each body stores the shared base vftable (VA 0x010ED8D4, also installed by
  the matched constructor `??0BfmeRectVNH@@QAE@IABVAsciiString@@D@Z` at
  0x003BC090 through its inlined base `BfmeBaseVNH`), then the base fields
  (+0x04 `unsigned*0.03f` clamped to 1, +0x08 byte), then its own derived
  vftable (0x010ED97C / 0x010ED8F8), and returns `this` in EAX -- the VC7.1
  constructor shape, identical to the matched VNH sibling.
- Their only callers, Glo012F1024Item::j_00015e42 (0x003ADED0, via ILT
  0x00011F72) and j_00021f26 (0x003ADCC0, via ILT 0x000358FF), call them right
  after `operator new(0x10)` inside the new-expression's null test, with EH
  state 0 set around the call and reset to -1 after it (the
  delete-on-constructor-throw cleanup). Only a constructor call in a
  new-expression produces that state pair. Both callers are byte-exact in clean
  C++ calling these as constructors (sibling 0x003ADDB0 calls the already
  matched VNH constructor the same way).

The bodies are unchanged; only the ABI spelling (constructor instead of a
method returning `this`) changes. Class names stay address-family
placeholders. model=claude-opus-5-5 (s500).

## 0x003BBD70 BfmeBoxVNF (same session)

Ledgered as `?bfmeInitVNF@BfmeBoxVNF@@QAEPAV1@IPBUBfmeVecVNF@@HID@Z`; the same
base/derived vftable constructor shape (base 0x010ED8D4, derived
??_7Rva003BD6F0@@6B@). Its only caller, Glo012F1024Item::j_0002a969
(0x003AE030, via ILT 0x0003E405), calls it inside the new-expression null test
with EH state 0 and passes the third argument from a record field through an
x87 `fld`/`fstp` temporary, so that parameter is a float (the body only copies
it to +0x18, byte-identical either way). Now
`??0BfmeBoxVNF@@QAE@IPBUBfmeVecVNF@@MID@Z`.

## ILT 0x00013ABB call

j_0002a969's second loop assigns an 8-byte record member at +0x0C into the new
BfmeRectVNI's +0x0C through ILT 0x00013ABB, which jumps to the 5-byte stub at
0x000650B0 (`jmp` ILT 0x00048013 -> 0x00064E90, the gen-tgrid
`_Rb_tree<int, ...>::operator=`). Its owner types are unproven and the final
body is still a gen row, so no pin is added: the call goes through the gen
thunk name `?j_00013abb@@YAXXZ` with the repo's `union { void (*raw)(); PMF }`
pattern, and the member keeps the address-derived view `Rva00064E90Tree`.
