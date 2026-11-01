# 0x002A8540 SpecialAbilityUpdate::onExit (814 B)

- Identity: ilt_oracle CONFIRMS `?onExit@SpecialAbilityUpdate@@MAEX_N0@Z` exact
  at 0x002A8540 (ILT slot 11952); the AAE/QAE/IAE/UAE spellings are
  contradicted. Earlier verdicts proved the onExit identity from the matched
  destructor call.
- Body: retail ret 8 at +0x32B (two Bool arguments: `cleanup` drives the
  special-object kill test, `aborted` selects module data +0x22C over +0x228).
- Donor (structure only): Open BFME 2 45afcff3
  `Code/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate.cpp`
  onExit at its retail 0x004502CE. BFME 1 offsets and callees come from the
  BFME 1 retail body and ledger.
- First call (+0x24, ECX = this) goes through ILT 0x0002333A to 0x002A6DE0,
  whose ledger row is `?bfmeGo1274@Gen_002A6DE0@@QAEXXZ`. The replaced bank
  reached it through a generic `call()` member-pointer cast helper
  (BfmeNoArgCall::call over `j_0002333a`); `call` was a cast-helper name,
  not an identity for 0x002A6DE0, so the source now calls the ledger name.
