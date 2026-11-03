# 0x00297930 LargeGroupBonusUpdate::update (818 B)

Identity correction: the row was the naked `__emit` lift
`??1LargeGroupBonusUpdate@@UAE@XZ` in `LargeGroupBonusUpdateDestructorThunk.cpp`
(deleted). The body is `?update@LargeGroupBonusUpdate@@UAE?AW4UpdateSleepTime@@XZ`.
The real destructor is the matched `??1LargeGroupBonusUpdate@@MAE@XZ` at
0x002974D0.

## BFME 1 target evidence
- `ilt_oracle.py check ?update@LargeGroupBonusUpdate@@UAE?AW4UpdateSleepTime@@XZ 0x00297930`:
  CONFIRMED (p_false 3.91e-04, exact).
- The update-interface table 0x010BFC5C installed at +0x10 has this body in
  slot 0 through ILT 0x0001CEF9 (earlier verdicts in re_attempts.log). The
  body reads the module data and owner at this-0x0C / this-0x08, as the
  matched BannerCarrierUpdate::update does for its +0x10 interface.
- Boundary: SEH prologue, returns at +0x2F4, +0x31A and +0x331 (final RET);
  818 bytes.
- The behavior-module scan inlined at +0x1CC is the matched file static
  rva00297480 (LargeGroupBonusUpdateDestructor.cpp), whose note says its only
  use is inlined here.
- Callees by ledger name: Overridable::getFinalOverride (ILT 0x22BB),
  Thing::isKindOf (ILT 0x3251F, argument 9), Object::getControllingPlayer,
  Object::unidentified_001BFE20 (ILT 0xD3B9, twice), PartitionFilter::link
  (x3), BfmeWideForwardC::bfmeForwardWideC (the partition range query),
  Object::applyAttributeModifier (ILT 0x37A56) and its partner at 0x001C1E30
  (ILT 0x1EF9C, ledgered as BfmeOwnerXI::bfmeSendXI; same AsciiString
  argument at module data +0x2C).

## Donor evidence (BFME 2, 59e3f8f825)
- `Code/GameEngine/Source/GameLogic/Object/Update/LargeGroupBonusUpdate.cpp`
  `?update@LargeGroupBonusUpdate@@UAE?AW4UpdateSleepTime@@XZ` (BFME 2
  0x00490225, 589 B, matched there): same statement sequence (null owner;
  every-frame kind test or update delay; member / player / alive / not-self
  filter chain; member count via the hit's interface; full group sets both
  flags, else a rub-off search over active bonus holders by 2D squared
  distance; changed state applies or removes the attribute modifier; final
  flag test, interface touch and sleep choice). Module-data field order
  (+0x08 rate, +0x0C member filter, +0x10 count, +0x14 radius, +0x1C rub-off
  radius, +0x2C attribute modifier) is the same in both games.
- Differences adapted from BFME 1 retail: the every-frame test is the final
  template's +0xC8 bit 8 then Thing::isKindOf(9) (BFME 2 tests two template
  bytes), the partition result's next()/destructor are inline over the
  refcounted result record (BFME 2 calls them), the contain-like interface
  counts in slot 84, behavior modules are at Object+0x1F0 and the final flag
  at Object+0x344.

## Compiler notes
- TheGameLogic is read into a local before the isKindOf call (retail holds it
  in ESI across that call); the squared distance is a named temporary (retail
  stores it before the compare, popping the two deltas).
