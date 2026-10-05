# g_feslTransactionIdKey at VA 0x0112C144

The datum is the NUL-terminated FESL message key `TID`, a constant char array of 4 bytes in retail .rdata. Its complete initial bytes are `54494400` and there are no relocations. The chosen spelling is `?g_feslTransactionIdKey@@3QBDB`. This is the existing message-key role with the read-only array type. The integer spelling `g_bfmeKeyVHE` names the same address but does not describe its contents or its uses. The additional g_bfmeName1052 spelling also points at these bytes. The old DIR32 rows remain beside the canonical spelling.

The consumer bodies pass the address directly as the key to message addInt/getInt or their already pinned opaque ABI views, with the integer value or fallback as the other argument. They do not load an int or a pointer from this address. Retail FeslEchoNotifier uses g_feslTransactionIdKey when adding m_transactionId to the message; the other readers and writers are listed with their exact instruction sites and complete ledger-backed disassemblies in `build/rlink/identity-types-1791185133/retail-all.txt`. The descriptor has no receiver. There is no direct write to these read-only bytes among the decoded address references. Writes are to messages using this key.

The terminal NUL determines the string extent. No DIR32 address starts inside the extent and no existing data row overlaps it. Declaration counts for every competing spelling are in `declaration-counts.csv`. The raw data and correction receipts are `keys.txt`, `add-data-0112c144.txt` and the per-source before/after link logs. Every changed source must retain all existing Functions OK rows. The casts in opaque void-pointer call views preserve the caller contract without changing those function identities.

An indirect load from the key cell, a different string, a write into these bytes, a key consumer that interpreted the address as an integer object, or a nested datum start would refute the correction. The descriptive key names are already used in the repository; this correction does not invent a new native FESL class or member identity.

The competing spellings below are counted from original explicit game-source declarations, including macro expansions. Included vendor declarations are separate; the enum classic-table spelling is proven by the vendor header and canonical wide-scan use regardless of its direct game-source count. Raw declaration lines and source paths are retained in `build/rlink/identity-types-1791185133/declaration-counts.txt`; the authoritative count rows are in `declaration-counts.csv`.

| Spelling | Original game CPP declarations (files) |
|---|---|
| `?g_bfmeKeyVHE@@3HA` | 8 |
| `?g_bfmeName1052@@3PADA` | 6 |
| `?g_feslTransactionIdKey@@3PADA` | 1 |
