# 0x00203800 PropagandaTowerBehavior::doScan (764 B)

Target facts (BFME 1 retail):
- Boundary: EH prologue at 0x00203800, single RET at +0x2FB, padding after.
- Identity: the matched PropagandaTowerBehavior update entry at 0x00203660
  (PropagandaTowerBehavior_update_BFME.cpp) calls primary vtable slot 12 when
  the scan delay elapses (slot 11 removeAllInfluence, slot 13 effectLogic);
  the installed PropagandaTowerBehavior vtable holds this body at slot 12.
  Earlier verdicts recorded the same identity (?doScan@...@@MAEXXZ).
- Layout from the body: module data +0x04, owner +0x08, tracker list +0x28,
  required upgrade +0x2C (type at +0x04: 0 player upgrade, 1 object upgrade);
  module data radius +0x08, pulse FX +0x14, upgraded pulse FX +0x20; tracker
  vtable 0x010A5580 (??_7ObjectTracker@@6B@), id +0x04, next +0x08.
- Callees by ledger name: Object::getControllingPlayer, Player::hasUpgradeComplete
  (ILT 0x000235BF pin), Object::hasUpgrade, FXList::bfmeIsBlocked, FXList::doFXObj,
  PartitionFilterAcceptByKindOf ctor (ILT 0x000382FD; body 0x000C3DD0),
  PartitionFilter::link, BfmeWideForwardC::bfmeForwardWideC, operator new/delete,
  STLport node deallocate; findObjectByID is inlined (hash at GameLogic+0xB4).

Donor facts (Open BFME 2 45afcff3, Code/GameEngine/Source/GameLogic/Object/
Behavior/PropagandaTowerBehavior.cpp doScan): upgrade-dependent pulse FX,
the four-filter wide partition query with KINDOFMASK_NONE / kind bit 7, the
fresh tracker list, effectLogic(false) for departed objects, freeing the old
list. Same structure as BFME 1; filter, result and lookup views are BFME 1's
(Rva00257DB0PartitionScan.cpp, Rva002622D0Collect.cpp).

Lever: the kind-of filter constructor kept visible and noinline (as in
Rva002622D0Collect.cpp) brings the frame from 0x88 to retail's 0x74.
Verification: probe EXACT 764/764 modulo relocations.
