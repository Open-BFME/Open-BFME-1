# Empty subsystem slots with address-qualified identities

The actual base table at VA01141640 is installed by the matched native
SubsystemInterface constructor009A1A30 and destructor009A1A40. Its slot7
(+1C) directly holds VA00DA16C0; slot8 (+20) holds VA00DA16D0. This same
pair appears in many independently installed subsystem-family tables,
including01075EE8. Those are entry witnesses, not inferred full method names.

Raw PE and Ghidra agree over all32 bytes at009A16C0: RET followed by15
INT3s, then RET4 followed by13 INT3s. Thus the exact extents are1 and3 bytes.
Neither body computes a result or reads the receiver/argument. The second
opaque method uses an unsigned word only to model its one4-byte callee-cleaned
stack slot; the original argument type remains unknown.

Existing candidate pins call these unidentifiedSlot07/08. We neither add
new pins nor promote those spellings into full-name claims. The canonical
subsystem header intentionally omits these slots; no header or existing
class is changed or redeclared. Rva009A16C0/Rva009A16D0 are separate local
ABI views of the two entries, not claims of distinct original owner classes.
Both leaves are recovered as native empty C++ methods and individually
verified at their own exact extents. callees.py reports no direct calls.

## Two more independently established RET4 entries

The same native-empty-method pattern also covers009D6E00 and00803590.
Each retail/Ghidra window is C2 04 00 followed by13 CC bytes; each receives
one ignored4-byte stack word with no source-type assertion.

- TableVA01144090 slot7 directly holds00DD6E00. Constructor009D8630
  and destructor009D83D0 independently install that table. Xfer-shaped
  neighbors do not prove a full owner/method spelling; Rva009D6E00 stays
  opaque. The same entry is also held by table01075B08 slot7.
- TableVA0112C738 slot1 directly holds00C03590. Constructor00803820 and
  destructor00803890 independently install this table. Existing FESL
  browser-family context supplies the source directory, not a semantic
  method name; Rva00803590 stays opaque.

No callee or data references, new pins, or covered-type declarations are
introduced by these two entries. Both full3-byte extents are individually
gated with add_match; callees.py was run before writing them.
