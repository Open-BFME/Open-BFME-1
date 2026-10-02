# getVetUpgradeName, RVA 0x0010AD90

The 173-byte body is the `static AsciiString getVetUpgradeName(VeterancyLevel)`
helper in Zero Hour `GeneralsMD/Code/GameEngine/Source/Common/System/Upgrade.cpp`
(lines 184-191). The reconstructed BFME callers are
`UpgradeTemplate::friend_makeVeterancyUpgrade` at RVA 0x0010B010 and
`UpgradeCenter::findVeterancyUpgrade` at RVA 0x0010B480. The latter lives in
`UpgradeFindVeterancyUpgradeThunk.cpp`; retaining the helper beside its caller
preserves its upstream internal linkage without a synthetic retention wrapper.

Independent retail evidence from
`inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`:

- The body starts at VA 0x0050AD90 after four `CC` bytes and ends with `ret`
  at VA 0x0050AE3C, followed by three `CC` bytes.
- The literal at VA 0x01088D68 is `Upgrade_Veterancy_` (18 characters).
- The table at VA 0x012A9FB4 contains `REGULAR`, `VETERAN`, `ELITE`, `HEROIC`,
  then null, matching the upstream `TheVeterancyNames` table.
- It zero-constructs a local string, sets that prefix, appends the table entry
  using nullable inline `strlen`, copies the local into the hidden result,
  and releases the local.
- `tools/callees.py 0x0010AD90 173` resolves the direct calls to
  `StringBase<char>::set(const char *, int)` (RVA 0x00887D20),
  `concat(const char *, int)` (0x00887D60), copy construction (0x00887B60),
  and `releaseBuffer` (0x00887940). The existing canonical string headers
  provide these declarations; no new callee pins or duplicate class are used.

The identical algorithm with external linkage compiles to 165 bytes and
chooses ESI for the hidden result. Upstream static linkage restores all 173
bytes, including the early EDI result load, the scoped ESI save in the string
scan, its alignment, and the exception-state stores. `noinline` retains the
out-of-line helper called by the existing caller. Full verification must also
check the caller and all relocation targets, not merely this shape comparison.
