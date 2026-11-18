# 0x006818B0 BFMENativeNetwork::BFMENativeNetwork

Previously matched as `?construct@BFMENativeNetwork@@QAEPAXXZ`, a member
function standing in for a constructor. Now `??0BFMENativeNetwork@@QAE@XZ`.

BFME 1 target evidence:
- The 73 B body runs the SubsystemInterface base constructor (0x009A1A30),
  installs the vftable 0x0111A968, zero-initializes members, and returns `this`
  in eax: the shape MSVC gives a constructor.
- createTheNetwork (0x00682320) operator-news 0x40 bytes and calls ILT
  0x0001E8F8 -> 0x006818B0 on the result, before storing it in TheNetwork and
  calling init through slot +4. symbols.csv already pins
  `??0BFMENativeNetwork@@QAE@XZ` at ILT 0x0001E8F8.

Naming: BFMENativeNetwork remains the tree's existing address-free class
spelling (the vftable is recorded as ??_7Network@@6B@). This change makes the
row a constructor and does not claim an EA class name.

Link-queue row #211 (census 6c4dd9e650): createTheNetwork.cpp referenced the
constructor, which no row defined.
