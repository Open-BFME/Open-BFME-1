# Upgrade constructor at 0x0010A7A0: wrong AABTree identity

Queue #26, census aafdf413e9. This investigation establishes an independent
BFME1 identity correction lead; production rows/source are unchanged.

## BFME1 evidence

* Matched Player::addUpgrade 0x000D24C0 constructs a20-byte Upgrade through
  ILT0x00005BB4, passes the UpgradeTemplate pointer, then writes its list
  links at +0x0C/+0x10 and status at +8. pin_consistency confirms the sole
  Upgrade ctor pin reaches0x0010A7A0. ilt_oracle CONFIRMED exact,
  p_false=2.02e-03 for `??0Upgrade@@QAE@PBVUpgradeTemplate@@@Z`.
* The29-byte ret4 constructor at0x0010A7A0 stores the template argument at
  +4, zeroes +8/+0xC/+0x10 and writes native vtable VA0x01088D50.
  It is currently rowed as `??0AABTreeLinkClass@@QAE@PAVAABTreeCullSystemClass@@@Z`
  in WWMath/AABTreeLinkClass_Constructor_Thunk.cpp. That real-C++ view matches
  instructions while assigning an incompatible class identity.
* Table0x01088D50 has four entries: ILT2531 ->0x0010ABA0 deleting destructor,
  ILT365F2 ->0x0010A7D0 empty body, ILT3792F ->0x0010A7E0 literal getter,
  ILT24541 ->0x0010A800 transfer body. The getter returns `Upgrade` (existing
  LiteralNameGetters_01.cpp row); the transfer body names `UpgradeStatusType`
  (existing BfmeConv1277.cpp row). These target facts establish the Upgrade
  relation independently of equal donor instructions.
* Native deleting destructor30B calls ILT3B9BC ->0x0010A7F0. That7-byte
  complete destructor writes known Snapshot vtable VA0x01073744 and returns.
  Both remain generated rows. Full native callee inventory was inspected.

## Donor and private candidate

Reviewed BFME2 pinned59e3f8f825b698775df9e1728265fe962a5d0c02 and official
latesta9286edec5374324e40c1f5dd29c3a8ab5582283,
Code/GameEngine/Source/Common/System/UpgradeCtor.cpp. It records the same
previous AABTree misidentity and a29-byte Upgrade ctor, but its addresses,
Snapshot header and class ABI are BFME2 evidence only. Source path maps to
BFME1 game/GameEngine/Source/Common/System/UpgradeCtor.cpp; no source was
installed there and no donor build dependency or pointer was imported.
BFME1 uses its own /DNDEBUG /MD /EHsc MSVC7.1 context.

A private class Upgrade with virtual destructor, the witnessed three virtual
roles and fields(template,status,next,prev), and body
`m_template=upgradeTemplate; m_status=0; m_next=0; m_prev=0;` emits29/29B
EXACT modulo its sole `??_7Upgrade@@6B@` relocation. This is diagnostic only:
no new vtable identity is accepted from a masked relocation. Dependency
inventory could not cache the private trial; no experimental object entered
build/match. The candidate itself is completely specified by this paragraph.

## Concrete blocked prerequisite

`dir32_record.py retire '??_7AABTreeLinkClass@@6B@' --for '??_7Upgrade@@6B@'`
refuses because no matched Upgrade deleting destructor owns the new vtable.
A read-only source_mentions check also finds real AABTreeLinkClass references
in WWMath/aabtreecull.cpp, aabtreecull.h and WWLib/ObjectPoolFreeObjectMemory.cpp,
beyond the wrong29-byte source. Thus merely recovering the generated Upgrade
complete/deleting destructors is insufficient for sanctioned retirement of the
old recorded name; its bare identifier remains live in genuine AAB code.
No record, alias, data row or gate was edited to escape this refusal. Temporary
dependency claims0x10A7F0/0x10ABA0 were released without edits.

Next: reconcile the native Upgrade table and genuine AAB class ownership
through the approved identity/record workflow before replacing the29-byte row.
This is a class/vtable reconciliation prerequisite, not a compiler mismatch.
Normal unchanged PlayerUpgrades plus current constructor gates pass4/4;
stale census indexe9a5ae5b4c reports blocked before and source is unchanged
after. No new native coverage or linked-byte gain is claimed.

## Fresh donor review of earlier queue work

At latesta9286ede, the AICommandInterfaceAttackCommands delta adopts the
AIUpdate header and renames parameters; AIGroupMoveFormation adopts Path/AIPathfind
headers. Neither changes the aiMoveToPosition inlining issue. ObjectOnDie
adopts Damage/ThingTemplate/Player/AI headers and spells kind tests directly;
its BFME2 status operations and layout remain distinct from BFME1's shared-mask
residue. Bfme5ThirtyFour changes names and shared Apt headers; its counted-key
destructor operation is unchanged. These reviewed source deltas do not supply
a supported repair for the first four queue outcomes; they are not recompiled
against BFME1 because no transferable changed body/compiler hypothesis was found.
