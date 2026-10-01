# ProtoSSL CA table provider

This repairs the existing `_g_Rva0112CB48` data reference. The name and existing `ProtoSSLCACert` declaration are retained. No original vendor array identity is claimed for the three new address-derived aggregate backing views. No shared header covers this CA record in the available reference tree; the existing C TU owns its declaration. No function, signature, header, pin, or source-ledger row changes.

## Physical record and extent evidence

All addresses below are retail VAs (image base `0x00400000`). The exact existing caller `_Rva0080C960`, RVA `0x0080C960`, spans 3,040 bytes. It advances the CA pointer by 36 bytes, reads country at offset 0 as the sentinel, compares offsets 0/4/8/12/20 against issuer fields, checks the modulus size at 28, and passes the selected record to `Rva0080D6C0`. The latter independently reads modulus pointer at 24, size at 28, and the four exponent bytes at 32 before its RSA initialization call. Offset16 is the existing unit pointer slot; this caller does not inspect it, so the provider makes no new semantic identity claim for that slot.

| Record | country +0 | state +4 | city +8 | organization +12 | unit slot +16 | common +20 | modulus +24 | size +28 | exponent bytes +32 |
|---|---|---|---|---|---|---|---|---|---|
| 0 | `0x12c4414` | `0x12c4418` | `0x12c4424` | `0x12c4434` | `0x12c444c` | `0x12c4464` | `0x112ca48` | 128 | `00000003` |
| 1 | `0x12c4480` | `0x130ace4` | `0x130ace5` | `0x12c4484` | `0x12c449c` | `0x130ace6` | `0x112cac8` | 125 | `00010001` |
| 2 | `0x12c44c4` | `0x12c44c8` | `0x12c44d4` | `0x12c44e4` | `0x12c44fc` | `0x12c4514` | `0x112c9c8` | 128 | `00010001` |

The fourth complete 36-byte record is zero. Immediately after the 144-byte table, VA `0x0112CBD8` begins `a0160801e01ec5000000000000000000`, independently bounding this owned four-record view.

| Owned symbol | VA | Bytes | Evidence |
|---|---|---:|---|
| `_g_Rva0112C9C8` | `0x0112C9C8` | 384 | Three adjacent 128-byte modulus slots; table targets offsets 0, 128, 256. Ends exactly at the table start. The middle slot has a declared usable length125; its three remaining physical bytes are retained without claiming that they are key material. |
| `_g_Rva012C4414` | `0x012C4414` | 282 | Covers every nonempty subject-string target, including original alignment bytes, through the final `OTG Certificate Authority` terminator at `0x012C452D`. Size282 describes this owned aggregate span, not an invented vendor array extent. |
| `_g_Rva0130ACE4` | `0x0130ACE4` | 3 | Three distinct adjacent empty cells targeted by record1 at +4/+8/+20. They lie beyond `.data` raw end and within VirtualSize; memory-mapped retail holds three zeros. No raw-file EOF mapping was used. |
| `_g_Rva0112CB48` | `0x0112CB48` | 144 | Three records plus complete zero sentinel; all21 pointers address the owned backing spans. |

The table remains the existing mutable C record view to preserve the public declaration and caller ABI. This makes no claim about original storage qualifiers. Backing arrays are immutable byte views.

## Verification

- Four official `add_data_match.py --model gpt-6` gates passed:384B,282B,3B,144B. Compiled sizeof proves each declared extent. The table has21DIR32 fields; every field is resolved to its owned external backing array plus a retail-proven offset. No absolute pointer initializer, static literal, or new pin is used.
- `./build.sh game/Libraries/Source/DirtySock/ProtoSSLParseCertificate.c`: function1/1 exact at3040B; data4/4; DIR32two refs; string and constant checks pass. `check_csv.py` and `pin_consistency.py --check` pass.
- Actual strict positive DLL links the complete provider/caller object with native MSVCR71 import libraries and labeled unrelated callee/runtime stubs. All21 linked table fields equal the map address of their real backing definition plus the physical offset. The selected table is not stubbed. Linked caller bytes equal retail outside original relocation fields.
- Negative control compiles the original source and omits only the selected table from allowed external stubs. Strict link exits96 with LNK2019 `_g_Rva0112CB48` in `_Rva0080C960`, followed by LNK1120. This proves the repair provides the previously absent selected datum.
- Queue projection3033B is from historical census `bb1f0edd39`, not fresh whole-image closure. Current exact caller extent is3040B; `link_check.source_bytes` independently reports3033authored bytes after excluding7padding bytes, matching that historical projection. This repair adds813verified data bytes and adds0authored function bytes. No whole-image linked gain is claimed.

Scratch evidence in the isolated checkout: `build/protossl_provider/physical.json`, `scratch_gate.json`, `controls.json`, positive/negative DLL maps and objects. Hashes below retain reproducible retail spans in this tracked proof.

| Span | SHA256 |
|---|---|
| `0x0112C9C8+384` | `1f28c190ef6fc62b6964e6b01fc2583962293daca26e8684ef15623909627ddf` |
| `0x012C4414+282` | `edb788e21e3a9269c7662a0a9c61e337f3c1eb9b6878185f7894c939854c7f73` |
| `0x0130ACE4+3` | `709e80c88487a2411e1ee4dfb9f22a861492d20c4765150c0c794abd70f8147c` |
| `0x0112CB48+144` | `f6faeb2fd156c3261ebf5d2c84c215ff5b82a2bccbe054d7eb5f0e3c0499cbb8` |
