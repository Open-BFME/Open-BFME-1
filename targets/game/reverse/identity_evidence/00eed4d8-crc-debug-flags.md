# Retail debug flags at VA 0x012ED4D8 through 0x012ED4E8

The retail storage and the roles below are conclusive. Existing role-describing spellings are retained where the EA switch strings or retail behavior establish their meaning. VA 0x012ED4E4 corresponds to the Zero Hour global `g_verifyClientCRC`; the other names are existing BFME role spellings, not claims of identical Zero Hour identifiers. The three bytes without an established original identifier retain the existing spellings used by their declaring files. No function identity or instruction is changed. Existing pins and DIR32 spellings remain additive evidence.

## Retail facts

The hash-bound game baseline is SHA256 `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`. Each datum is one byte, lies in retail `.data`, and starts with byte `00`. Every absolute address occurrence in `.text` for this range was validated inside a decoded Ghidra or matched-ledger extent. The scan found 73 operand occurrences and left no unvalidated candidate. Retail has no PE base relocations; the DIR32 evidence comes from the matched COFF relocations joined to these exact retail operands, not an invented PE relocation table. Raw evidence is `build/rlink/crc-flags-1791151166/full-probe.raw.txt` and `retail-probe.raw.txt`.

| VA | Canonical datum | Retail role | Zero Hour identity |
| --- | --- | --- | --- |
| 0x012ED4D8 | `ScriptDebugMessagesDisabled` (bool) | Suppresses ScriptEngine debug messages; -scriptDebugLite and RVA 00063A40 set it. | Not established |
| 0x012ED4D9 | `g_flag12ED4D9` (bool) | Watchdog enable byte; retail -Watchdog sets it and -noWatchdog clears it. | Not established |
| 0x012ED4DA | `g_flag12ED4DA` (bool) | Chooses DebugWindowLite.dll instead of DebugWindow.dll. | Not established |
| 0x012ED4DB | `g_rva00061150` (char) | Third argument of the save-game stream initialization at RVA 001102CD. No Zero Hour global identity is established. | Not established |
| 0x012ED4DC | `g_xObjectCRC` (bool) | -xObjectCRC exclusion switch. | Not established |
| 0x012ED4DD | `g_xPartitionCRC` (bool) | -xPartitionCRC exclusion switch. | Not established |
| 0x012ED4DE | `g_xCollisionCRC` (bool) | -xCollisionCRC exclusion switch. | Not established |
| 0x012ED4DF | `g_xShroudCRC` (bool) | -xShroudCRC exclusion switch. | Not established |
| 0x012ED4E0 | `g_xTaintCRC` (bool) | -xTaintCRC exclusion switch. | Not established |
| 0x012ED4E1 | `g_xTerrainLogicCRC` (bool) | -xTerrainLogicCRC report switch; no writer or actual terrain exclusion was found in retail. | Not established |
| 0x012ED4E2 | `g_xPlayerCRC` (bool) | -xPlayerCRC exclusion switch. | Not established |
| 0x012ED4E3 | `g_xAICRC` (bool) | -xAICRC exclusion switch. | Not established |
| 0x012ED4E4 | `g_verifyClientCRC` (bool) | -verifyClientCRC enables the before/after client CRC comparison. | `g_verifyClientCRC` |
| 0x012ED4E5 | `g_deepCRC` (bool) | -deepCRC mode; registers debug.add l + NETWORK_CRC and conflicts with lite mode. | Not established |
| 0x012ED4E6 | `g_liteCRC` (bool) | -liteCRC mode; also forces all getCRC traversals and is temporarily set around the update CRC. | Not established |
| 0x012ED4E7 | `g_binaryDeepCRC` (char) | -binaryDeepCRC mode gates binary CRC diagnostics in RVA 00388C10. | Not established |
| 0x012ED4E8 | `ignoreCRCMismatches` (bool) | CRC mismatch suppression except the forced CRC frame. | Not established |

## Readers and writers

The instruction sites below are RVAs. `read` and `write` are the decoded memory operand accesses. The raw log includes the exact instruction bytes, surrounding branches, owner extents, ledger rows and each five-byte E9 ILT entry followed to its final body. Indirect virtual-call receivers are described by the bytes without inventing a class identity.

- VA 0x012ED4D8: read bodies `0x0033C8E0`, `0x0033E9A0`, `0x0033EB70`; write bodies `0x00060D00`, `0x00063A40`. Sites: `0x00060D26` (write), `0x00063AC1` (write), `0x0033C8EE` (read), `0x0033E9AE` (read), `0x0033EB70` (read).
- VA 0x012ED4D9: read bodies `0x00079060`; write bodies `0x00060970`, `0x00060980`. Sites: `0x00060975` (write), `0x00060980` (write), `0x0007A9DB` (read).
- VA 0x012ED4DA: read bodies `0x00340B80`; write bodies `0x00060CD0`, `0x00060D00`. Sites: `0x00060CF1` (write), `0x00060D21` (write), `0x00340C13` (read).
- VA 0x012ED4DB: read bodies `0x00110170`; write bodies `0x00061150`. Sites: `0x00061155` (write), `0x001102BC` (read).
- VA 0x012ED4DC: read bodies `0x00383150`, `0x00393880`; write bodies `0x00061180`. Sites: `0x0006118C` (write), `0x003831C4` (read), `0x00393E27` (read).
- VA 0x012ED4DD: read bodies `0x00383150`, `0x00393880`; write bodies `0x000611A0`. Sites: `0x000611AC` (write), `0x00383210` (read), `0x00393E3E` (read).
- VA 0x012ED4DE: read bodies `0x00383150`, `0x00393880`; write bodies `0x000611C0`. Sites: `0x000611CF` (write), `0x0038323C` (read), `0x00393E55` (read).
- VA 0x012ED4DF: read bodies `0x00383150`, `0x00393880`; write bodies `0x000611E0`. Sites: `0x000611EF` (write), `0x00383268` (read), `0x00393E6C` (read).
- VA 0x012ED4E0: read bodies `0x00383150`, `0x00393880`; write bodies `0x00061200`. Sites: `0x0006120F` (write), `0x00383294` (read), `0x00393E83` (read).
- VA 0x012ED4E1: read bodies `0x00393880`; write bodies none. Sites: `0x00393E9A` (read).
- VA 0x012ED4E2: read bodies `0x00383150`, `0x00393880`; write bodies `0x00061220`. Sites: `0x0006122F` (write), `0x003832C0` (read), `0x00393EB1` (read).
- VA 0x012ED4E3: read bodies `0x00383150`, `0x00393880`; write bodies `0x00061240`. Sites: `0x0006124F` (write), `0x003832EC` (read), `0x00393EC8` (read).
- VA 0x012ED4E4: read bodies `0x000652C0`, `0x00065470`, `0x00393880`; write bodies `0x00061470`. Sites: `0x0006147F` (write), `0x000652C0` (read), `0x0006547E` (read), `0x00393EDF` (read).
- VA 0x012ED4E5: read bodies `0x00061380`, `0x0006BD3C`, `0x00079060`, `0x0009A580`, `0x0038DA10`, `0x00393880`, `0x00394260`; write bodies `0x00061300`. Sites: `0x00061313` (write), `0x00061386` (read), `0x0006BDA4` (read), `0x00079301` (read), `0x0009A722` (read), `0x0038DCF3` (read), `0x0038DDC3` (read), `0x00393EF6` (read), `0x00395F6B` (read).
- VA 0x012ED4E6: read bodies `0x00061300`, `0x0006BD3C`, `0x00079060`, `0x0009A580`, `0x00383150`, `0x0038DA10`, `0x00393880`, `0x00394260`; write bodies `0x00061380`, `0x0038DA10`. Sites: `0x0006132C` (read), `0x0006139C` (write), `0x0006BDAD` (read), `0x0007930D` (read), `0x0009A730` (read), `0x00383171` (read), `0x003831BC` (read), `0x00383208` (read), `0x00383234` (read), `0x00383260` (read), `0x0038328C` (read), `0x003832B8` (read), `0x003832E4` (read), `0x0038DD02` (read), `0x0038DD0E` (write), `0x0038DD1C` (write), `0x0038DDCC` (read), `0x00393F0D` (read), `0x00395F85` (read).
- VA 0x012ED4E7: read bodies `0x00388C10`, `0x00393880`; write bodies `0x00061460`. Sites: `0x00061465` (write), `0x003891A4` (read), `0x00393F24` (read).
- VA 0x012ED4E8: read bodies `0x00388C10`, `0x0038B430`; write bodies `0x00061430`. Sites: `0x00061441` (write), `0x00388C38` (read), `0x0038B59C` (read).

## Receiver and argument contract

The byte setters at RVAs 00060970, 00060980, 00061150, 00061180, 000611A0, 000611C0, 000611E0, 00061200, 00061220, 00061240, 00061300, 00061380, 00061430, 00061460 and 00061470 have no receiver. They write their respective byte and return integer 1 with a bare RET. Their existing function declarations stay intact. The two script-debug table callbacks also test TheWritableGlobalData and update its witnessed offsets before storing the byte. The retail table at VA 012A6F40 directly pairs -scriptDebug2 with ILT RVA 00030562 to body 00060CD0, -scriptDebugLite with ILT 00009DA4 to 00060D00, -Watchdog with ILT 00017490 to 00060970, and -noWatchdog with ILT 0001FF9B to 00060980. `contracts.raw.txt` records the table and each E9 byte sequence. The retail release table contains no CRC switches, so a parser-to-string relationship is not claimed for the unused CRC setters.

Retail body RVA 00393880 reads bytes DC through E7 and conditionally appends the explicit strings -xObjectCRC, -xPartitionCRC, -xCollisionCRC, -xShroudCRC, -xTaintCRC, -xTerrainLogicCRC, -xPlayerCRC, -xAICRC, -verifyClientCRC, -deepCRC, -liteCRC and -binaryDeepCRC, respectively. The full probe records the exact pushed string addresses and contents. This establishes their roles independently of the reconstructed names. RVA 00383150 uses E6 to bypass the DC, DD, DE, DF, E0, E2 and E3 exclusions. E1 has only its report read, so it is not claimed to control a CRC subsystem traversal.

E4 guards retail bodies 000652C0 and 00065470. Both call ILT RVA 0000B532 (E9 197C3700), whose final body is 00383150, with one zero stream argument. The second compares the result with the constructor snapshot and reports a mismatch. This is the behavior of the Zero Hour g_verifyClientCRC flag in Common/CRCDebug.cpp:60-79, with its definition in Common/CommandLine.cpp:53 and writer parseVerifyClientCRC:275-278. E5 is not established as g_clientDeepCRC: the latter chooses clientPre.crc and clientPost.crc in the reference, while E5 enables BFME NETWORK_CRC logging and is mutually exclusive with E6. The entire reference search output is `reference-all-crc.raw.txt`; the definition and parser reads are `reference-context.raw.txt` and `reference-globals.raw.txt`.

DB is loaded with a byte-width move into a zeroed EDX before being pushed as the third argument of the save stream initialization at RVA 001102CD. It remains char in both the setter owner and save-game declaration. E7 remains char in its setter owner and is declared char by the reporting reader; its other reads are literal retail dump operands. All other definitions are bool. The E7 DIR32 spelling `?g_binaryDeepCRC@@3DA` is added beside the historical bool spelling because the verified setter and reporting reader use char. The unsigned-char E4 declaration in native_desync_report.cpp is retyped to bool and must reproduce the same retail bytes. No boolean value outside the verified zero/one stores is inferred.

## Definitions and placement

- `ScriptDebugMessagesDisabled` is defined once in `game/GameEngine/Source/Common/T3CommandLineParsers.cpp`. This translation unit owns its verified command-line writer or the adjacent per-subsystem setter family.
- `g_flag12ED4D9` is defined once in `game/GameEngine/Source/Common/T3CommandLineParsers.cpp`. This translation unit owns its verified command-line writer or the adjacent per-subsystem setter family.
- `g_flag12ED4DA` is defined once in `game/GameEngine/Source/Common/T3CommandLineParsers.cpp`. This translation unit owns its verified command-line writer or the adjacent per-subsystem setter family.
- `g_rva00061150` is defined once in `game/GameEngine/Source/Common/Rva00061150Set.cpp`. This translation unit owns its verified command-line writer or the adjacent per-subsystem setter family.
- `g_xObjectCRC` is defined once in `game/GameEngine/Source/Common/R2GlobalOptionFlagSetters.cpp`. This translation unit owns its verified command-line writer or the adjacent per-subsystem setter family.
- `g_xPartitionCRC` is defined once in `game/GameEngine/Source/Common/R2GlobalOptionFlagSetters.cpp`. This translation unit owns its verified command-line writer or the adjacent per-subsystem setter family.
- `g_xCollisionCRC` is defined once in `game/GameEngine/Source/Common/R2GlobalOptionFlagSetters.cpp`. This translation unit owns its verified command-line writer or the adjacent per-subsystem setter family.
- `g_xShroudCRC` is defined once in `game/GameEngine/Source/Common/R2GlobalOptionFlagSetters.cpp`. This translation unit owns its verified command-line writer or the adjacent per-subsystem setter family.
- `g_xTaintCRC` is defined once in `game/GameEngine/Source/Common/R2GlobalOptionFlagSetters.cpp`. This translation unit owns its verified command-line writer or the adjacent per-subsystem setter family.
- `g_xTerrainLogicCRC` is defined once in `game/GameEngine/Source/Common/R2GlobalOptionFlagSetters.cpp`. This translation unit owns its verified command-line writer or the adjacent per-subsystem setter family.
- `g_xPlayerCRC` is defined once in `game/GameEngine/Source/Common/R2GlobalOptionFlagSetters.cpp`. This translation unit owns its verified command-line writer or the adjacent per-subsystem setter family.
- `g_xAICRC` is defined once in `game/GameEngine/Source/Common/R2GlobalOptionFlagSetters.cpp`. This translation unit owns its verified command-line writer or the adjacent per-subsystem setter family.
- `g_verifyClientCRC` is defined once in `game/GameEngine/Source/Common/CommandLine.cpp`. This is the Zero Hour defining file, and its definition is made visible in the retail build.
- `g_deepCRC` is defined once in `game/GameEngine/Source/Common/Rva00061300NetworkCrc.cpp`. This translation unit owns its verified command-line writer or the adjacent per-subsystem setter family.
- `g_liteCRC` is defined once in `game/GameEngine/Source/Common/BfmeSetupAPB.cpp`. This translation unit owns its verified command-line writer or the adjacent per-subsystem setter family.
- `g_binaryDeepCRC` is defined once in `game/GameEngine/Source/Common/Rva00061150Set.cpp`. This translation unit owns its verified command-line writer or the adjacent per-subsystem setter family.
- `ignoreCRCMismatches` is defined once in `game/GameEngine/Source/Common/T3CommandLineParsers.cpp`. This translation unit owns its verified command-line writer or the adjacent per-subsystem setter family.

The CRC exclusion flags DC through E3 are grouped in R2GlobalOptionFlagSetters.cpp, which owns their reconstructed parser bodies. No single source parses every flag in the range; the other definitions remain in their verified writer files, and E4 remains in the Zero Hour defining file.

Each one-byte range contains no other integer-addressed DIR32 name strictly inside it. The competing spellings share the same starting address and are retained. The pre-edit data ledger has no overlapping row. `inventory.raw.txt` records this check and every prior pin; `edits-completed.raw.txt` records the appended canonical DIR32 spellings.

## Competing spellings

| VA | Prior COFF spelling | Game files declaring or defining it |
| --- | --- | --- |
| 0x012ED4D8 | `?ScriptDebugMessagesDisabled@@3_NA` | 1 |
| 0x012ED4D8 | `?g_flag12ED4D8@@3_NA` | 3 |
| 0x012ED4D9 | `?g_flag12ED4D9@@3_NA` | 1 |
| 0x012ED4DA | `?g_flag12ED4DA@@3_NA` | 1 |
| 0x012ED4DB | `?g_rva00061150@@3DA` | 2 |
| 0x012ED4DC | `?R2Flag012ED4DC@@3_NA` | 1 |
| 0x012ED4DC | `?g_bfmeCRCSkipObjects@@3_NA` | 1 |
| 0x012ED4DC | `?g_xObjectCRC@@3_NA` | 1 |
| 0x012ED4DD | `?R2Flag012ED4DD@@3_NA` | 1 |
| 0x012ED4DD | `?g_bfmeCRCSkipPartition@@3_NA` | 1 |
| 0x012ED4DD | `?g_xPartitionCRC@@3_NA` | 1 |
| 0x012ED4DE | `?R2Flag012ED4DE@@3_NA` | 1 |
| 0x012ED4DE | `?g_bfmeCRCSkipCollision@@3_NA` | 1 |
| 0x012ED4DE | `?g_xCollisionCRC@@3_NA` | 1 |
| 0x012ED4DF | `?R2Flag012ED4DF@@3_NA` | 1 |
| 0x012ED4DF | `?g_bfmeCRCSkipShroud@@3_NA` | 1 |
| 0x012ED4DF | `?g_xShroudCRC@@3_NA` | 1 |
| 0x012ED4E0 | `?R2Flag012ED4E0@@3_NA` | 1 |
| 0x012ED4E0 | `?g_bfmeCRCSkipTaint@@3_NA` | 1 |
| 0x012ED4E0 | `?g_xTaintCRC@@3_NA` | 1 |
| 0x012ED4E1 | `?g_xTerrainLogicCRC@@3_NA` | 1 |
| 0x012ED4E2 | `?R2Flag012ED4E2@@3_NA` | 1 |
| 0x012ED4E2 | `?g_bfmeCRCSkipPlayers@@3_NA` | 1 |
| 0x012ED4E2 | `?g_xPlayerCRC@@3_NA` | 1 |
| 0x012ED4E3 | `?R2Flag012ED4E3@@3_NA` | 1 |
| 0x012ED4E3 | `?g_bfmeCRCSkipAI@@3_NA` | 1 |
| 0x012ED4E3 | `?g_xAICRC@@3_NA` | 1 |
| 0x012ED4E4 | `?BfmeClientCRCCheckEnabled@@3EA` | 1 |
| 0x012ED4E4 | `?R2Flag012ED4E4@@3_NA` | 1 |
| 0x012ED4E4 | `?g_verifyClientCRC@@3_NA` | 2 |
| 0x012ED4E5 | `?FlagAt012ED4E5@@3_NA` | 1 |
| 0x012ED4E5 | `?g012ED4E5@@3_NA` | 1 |
| 0x012ED4E5 | `?g_bfmeOnAPB@@3_NA` | 2 |
| 0x012ED4E5 | `?g_deepCRC@@3_NA` | 2 |
| 0x012ED4E6 | `?FlagAt012ED4E6@@3_NA` | 1 |
| 0x012ED4E6 | `?g012ED4E6@@3_NA` | 1 |
| 0x012ED4E6 | `?g_bfmeCRCForceAll@@3_NA` | 1 |
| 0x012ED4E6 | `?g_bfmeDoneAPB@@3_NA` | 2 |
| 0x012ED4E6 | `?g_liteCRC@@3_NA` | 2 |
| 0x012ED4E7 | `?g_binaryDeepCRC@@3_NA` | 1 |
| 0x012ED4E7 | `?g_rva00061460@@3DA` | 1 |
| 0x012ED4E8 | `?g_flag12ED4E8@@3_NA` | 1 |
| 0x012ED4E8 | `?ignoreCRCMismatches@@3_NA` | 1 |

These counts include declarations and definitions and are computed from the saved pre-edit game sources in `declaration-counts.raw.txt` and `declaration-counts.json`. Disabled preprocessor branches are included as source declarations. Counts do not establish identity.

## Refutation

A retail instruction accessing a wider overlapping datum, a nonzero initial byte, a DIR32 addend resolving a canonical name to a different address, a table callback whose E9 chain ends at a different writer, or a different report string paired with the byte would refute the storage or role assignment. A Zero Hour definition and parser uniquely tying another name to the same retail behavior would establish a reference counterpart; the existing BFME role names do not claim one. Assigning E5 to g_clientDeepCRC would require a witnessed clientPre.crc/clientPost.crc selector and writer contract; that evidence has not been found. Any changed function byte or scalar extent would refuse the candidate. Unrelated unresolved link symbols do not refute these one-byte definitions; the coordinator requires preserving the candidate when LINKED bytes stay unchanged for those blockers.

Raw probes and gates are retained locally under `build/rlink/crc-flags-1791151166/`. The spelling revision and repeated raw probes and gates are retained under `build/rlink/crc-spellings-1791152592/`. Gate outcomes and LINKED byte measurements are recorded in `build/worker-final.md`.
