# AIPlayer::queueSupplyTruck — complete native near match

Retail extent is **0x00165D50 / 2333 bytes**, through RET at +0x91C and
followed by INT3 padding. The old lift row stops at 2330 bytes. Its truncated
name completes to `?queueSupplyTruck@AIPlayer@@IAEXXZ` (protected member).
The sole ILT-mediated caller is AIPlayer::isAGoodIdeaToBuildTeam. The full
Zero Hour queueSupplyTruck algorithm, including the warehouse-key and
"Supply truck - building one at the " strings, independently identifies it.

The bank reproduces all 2333 bytes except the cash multiplication at
+0x376..+0x389: retail loads GlobalData's box value first and multiplies by
warehouse boxes; the compiler loads boxes first and multiplies by the box
value. Probe reports **10 non-relocation byte differences**. One global
DIR32 load moves by six bytes, so this is not a strict executable match.
The bank score is 2323/2333 = 0.99571367338; it claims no progress.

Native recovery details:

- Existing ObjectDlinkPmf.h emits the authentic virtual-base member pointer
  `{ ILT 0x1140, -100, 0 }`; the next-member body reads Object+0x264.
- Native STLport list/hash_map reproduce the team and object-ID traversals.
  Native bitset<192> reproduces all KindOf tests and filter-mask construction.
- Original MAKE_DLINK constructs separate two-pointer link records. Restoring
  their constructors in TeamInQueue reproduces its table-store ordering;
  replacing them with four scalar fields leaves fifteen additional differences.
- Both WorkOrder and TeamInQueue have protected virtual slots in BFME order:
  destructor, loadPostProcess, crc(Xfer*), xfer(Xfer*). Tables 0x01096964 and
  0x01096940 independently establish the order, including the landed
  TeamInQueue destructor/xfer owners.
- Native inline StringBase length/str/concat and custom pool-new forwarding
  recover the original string lifetime and allocation paths.
- BFME findFactory takes `(const ThingTemplate*, bool, int*)`, unlike the
  two-argument Zero Hour source. Its independently native owner is 0x001643B0.
- Object::findModule remains an existing-symbol typed const-thiscall adapter
  through ILT 0x0002AE23 to 0x001BEE60 because ObjectDlinkPmf.h owns the scoped
  Object declaration. Its native 63-byte implementation independently proves
  NameKeyType input and Module* result. No pin or shared header was changed.

Strict relocation resolution: **26 direct call sites, 17 distinct targets,
zero unresolved symbols**, all chosen targets equal the independently decoded
retail REL32 destinations. A second agent reviewed those contracts. Native
helpers/slot signatures were checked against landed siblings. The adjacent
JSON receipt records the bank source hash, call sites, targets, and residue.

Exhausted levers: operand reversal, separate assignment, declaration order,
const locals/references/pointers, helper arguments in both orders, unsigned
and low-32-bit wide multiplication, return-by-reference getter, polymorphic
warehouse view, visible complete findModule body; constructor initializer
and body forms, out-of-line/forced-inline visibility, natural custom-new
forms; finite register/copy/store search (8 trials) and EH search (16 trials); /G5, /G6, /G7, /Oa, /Ow, /Ob1,
/Oi- sweep. Two volatile-load experiments worsened the body and were discarded.
Independent warehouse-member/global-data-member helpers also stayed at ten
bytes. No barriers, assembly, volatile fields, or raw table stores are banked.
