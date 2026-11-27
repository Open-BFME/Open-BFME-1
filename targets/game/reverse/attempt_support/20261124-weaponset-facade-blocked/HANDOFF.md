# WeaponSet379: main exact, additional public-facade COMDAT unowned

One source hypothesis at B1 82d5f9ee33, donor e2e9995995. The native link-near
packet served WeaponSet::updateWeaponSet at 0x001EBBC0/379B. Original lookup
ILT0x0000D486 reaches 0x001E42F0/73B; factory ILT0x000122BF reaches
0x001BDD90/100B. Both actual provider units pass normal54/54+1data+41DIR32.
The factory's existing stale $L315→$L319 metadata is proven dynamically by
the normal11B cleanup check; it is not repaired or called globally clean here.

The only candidate replaces BfmeWeaponStore with a call-only existing
WeaponStore API, uses the original public const findWeaponTemplateByNameKey
facade from Zero Hour Weapon.h:836 / local weapon shim:845, keeps the lookup
protected (IBE), and calls the existing out-of-line factory. It adds no friend,
header, pin, layout assertion, flag, marker, force-inline or inline allocator.
Normal main379/379+3DIR32 passes and raw main bytes remain identical with
exactly two independently witnessed callee-name changes.

The whole normal COFF comparison nevertheless has a real additional5B
COMDAT-ANY function named findWeaponTemplateByNameKey, E900000000 with
REL32+1 to the protected lookup, and one associated FPO record. Runtime/FPO
sections grow5→7. The native object-reference API finds no incoming runtime
edge/root to it inside this TU; its only incoming relocation is debug FPO.
No matching functions.csv/symbols.csv entry, native address candidates or
existing census owner exists. The old index has no global unreferenced receipt
for this new name. Header semantics alone identify no retail address.

FDU returns0/all matched because its qualified-definition parser does not
establish ownership for this in-class inline body. That result is explicitly
not a zero-emission or native-owner proof. link_census.keep_rule962ff allows
an unknown-address COMDAT to be discarded only after the native global
link_references closure establishes unreferenced status. This TU-local fact
and the absent census name are insufficient. The same native comment says
even force-inline leaves such a5B member stub; no speculative variation ran.

The broad existing Weapon.h shim is a Zero Hour class context, not an approved
BFME1 WeaponStore canonical header. Blind adoption would redefine the caller's
other field views and expose known wrong Weapon size/allocator/EH contexts.
The BFME2 canonical header's WeaponSet friendship was read and not copied.
No native owner rule, baseline or verifier is changed to accept this candidate.

The original source and its actual normal object are restored. No candidate
after-link test, source commit, new body or task credit is claimed. A fresh
independently proved retail owner or current native whole-program discard
receipt is required before reconsidering; no5B ILT is renamed or pinned.

Complete actual before/candidate objects, original decoded379/73/100/11B,
full graph diff, source/header hashes and commands are preserved under
W:/OpenBFME/diagnostics/one-per-project-20261124-185505/bfme1.
