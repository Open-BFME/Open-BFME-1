# Apt diagnostics readiness at VA 0x01337808

The datum is one zero-initialized `int` (four bytes) in retail `.data`, with no initial pointer relocations. Its established address-derived spelling is `?g_rva00891FA0Ready@@3HA`. The competing `?g_bfmeJ1017Cb@@3PAXA` pointer spelling occurs in one game declaration; the chosen spelling occurs in one game declaration before the correction. No EA variable name is proven.

Retail RVA 0x00892150 takes an `int` stack argument, stores it directly in VA 0x01337808, and clears the diagnostics value at VA 0x013377F4. RVA 0x00891FA0 tests readiness before formatting and sending that value. The insert body at RVA 0x008A0700 tests the same word before calling the distinct callback stored at VA 0x01337840. The readiness word is not that callback. Retail comparisons and stores at RVA 0x00894380 and the remaining readers are retained in the raw address log.

The argument contract is the setter's four-byte integer argument; the receiver contract is a global flag load. The corrected insert declaration uses the same scalar test and leaves all function bytes unchanged. The main diagnostics translation unit owns the definition.

Initial bytes are `00 00 00 00`. There is no data row or DIR32 name strictly inside VA 0x01337808 through 0x0133780B. The next named datum is at VA 0x01337810; its gap does not enlarge this four-byte scalar. A call through this cell, a pointer dereference through its stored value, or changed instructions in a corrected consumer would refute the correction.

Raw evidence is in `build/rlink/identity-types-1791203017/01337808-retail.txt`, `retail-summary.json`, `selected-bodies-fixed.txt`, and `game-hits.txt`. Gate and LINKED receipts are recorded in `build/worker-final.md`. The chosen DIR32 row already exists, so no duplicate row or alias is added.
