# Correction to n4 data-address notes

The mouse-bank record in a74848e7ec and render-bank record in 2d0cd6ea21
correctly distinguish the following addresses, but the latter instruction to
subtract the image base for *any* landing is too broad:

| Datum | VA | RVA |
| --- | --- | --- |
| mouse-position flag | 012B59B8 | 00EB59B8 |
| render flag | 012BAA54 | 00EBAA54 |
| opaque shader constant | 012D6E08 | 00ED6E08 |

`functions.csv` uses RVAs. `dir32_addresses.csv` records data VAs; legacy
global entries in `symbols.csv` also commonly contain VAs. `data_rows.csv`
has an explicit `address_kind`, and `add_data_match.py` requires either
`--va` or `--rva`. Use the address form required by the particular tool and
ledger, rather than mechanically subtracting the image base from data pins.

No pin was added by either bank. Their byte results and outstanding blockers
are unchanged. The Apt cleanup recovery also demonstrated that consistent
new DIR32 references can verify without adding function pins for globals.
