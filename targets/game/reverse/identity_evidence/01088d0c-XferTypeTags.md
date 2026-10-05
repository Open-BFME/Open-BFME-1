# Xfer enum type tags

Corrected: VA 0x01088D0C is the NUL-terminated UpgradeStatusType string, and VA 0x010890F0 is the NUL-terminated GameClientRandomVariable::DistributionType string. Neither is an integer nor a pointer-name array. The existing role spellings are retained and retyped as const char arrays. Their new decorated DIR32 spellings are `?g_bfmeStr1277@@3QBDB` and `?BfmeXferDistributionTypeNames@@3QBDB`; no existing spelling is removed.

### VA 0x01088D0C: g_bfmeStr1277

The retail datum occupies 18 bytes in `.rdata`. The initial bytes are `55 70 67 72 61 64 65 53 74 61 74 75 73 54 79 70`. The full bytes, every record, code references and ILT jump bytes are in `build/rlink/01088d0c-retail.log`. Direct address-reference sites have RVAs 0x0010A66E, 0x0010A828. The next pre-existing named datum is at VA 0x01088D24; the log also records the bytes immediately after the terminator. There is no pre-existing data row overlapping this extent and no other DIR32 address inside it.

Competing initial spellings: `?g_bfmeStr1277@@3PADA` (1 game files), `?g_slot90_0010A660@@3HA` (1 game files). Counts include macro declarations and do not decide identity.

### VA 0x010890F0: BfmeXferDistributionTypeNames

The retail datum occupies 43 bytes in `.rdata`. The initial bytes are `47 61 6d 65 43 6c 69 65 6e 74 52 61 6e 64 6f 6d`. The full bytes, every record, code references and ILT jump bytes are in `build/rlink/010890f0-retail.log`. Direct address-reference sites have RVAs 0x0010C26E, 0x0010C54C. The next pre-existing named datum is at VA 0x01089124; the log also records the bytes immediately after the terminator. There is no pre-existing data row overlapping this extent and no other DIR32 address inside it.

Competing initial spellings: `?BfmeXferDistributionTypeNames@@3PAPBDA` (0 game files), `?g_slot90_0010C260@@3HA` (1 game files). Counts include macro declarations and do not decide identity.

Both users of each address pass the address itself to virtual Xfer slot 0x90, followed by a destination pointer and literal size 4. They never load a pointer from the datum. The member serializer at RVA 0x0010A800 transfers its field at receiver +8, and xferRandomVariable at RVA 0x0010C4D0 transfers its local DistributionType. The Zero Hour Xfer enum transfer contract and ClientRandomValue DistributionType establish the role; the retail NUL-terminated bytes establish the exact tags. These arrays contain no relocation fields. The direct consumers read the tags through Xfer; their writes address the supplied value, not the tags.

A pointer that follows an E9 to a different final body, a token or scalar differing from the saved retail bytes, an interior DIR32 or overlapping data row, or a user passing a different record layout would refute this correction. Function bytes must continue matching in every changed source.

The definitions and complete byte checks are in `build/rlink/add-upgrade-tag.log` and `add-distribution-tag.log`; all source gates are recorded in `final-gate-receipts.json`.
