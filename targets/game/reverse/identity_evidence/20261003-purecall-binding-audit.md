# Compiler purecall binding repair (revalidated 2026-10-04)

`__purecall` is the complete 60-byte reporter at RVA 0088C500, not the
three-byte return-zero stub at 006CF680. This repair gives the already exact
reporter its compiler identity and official `Libraries/Source/debug/debug_purecall.cpp`
placement. It retires only the contradicted `__purecall` claim at 006CF680;
all 199 other identities at that address remain unchanged.

## Independent retail anchor

The complete 31-byte deleting destructor at RVA 006305F0 writes VA 011186B8
into `[esi]` at 006305F8. Its RET 4 at 0063060C ends at 0063060F, followed by
INT3. The 91-entry, 364-byte table at VA 011186B8 begins with VA 0043B8D6 and
0041789B; all remaining 89 entries, offsets +8 through +168, are VA 00C8C500.
This table address is independently anchored by the destructor's direct operand,
not inferred from a table-name pin or adjacent placement.

A fresh MSVC 7.1 compile of PeerDefs.cpp on base 4367e859613f23206efa07fa3134d57d50ca2fe7
emits `??_7GameSpyInfoInterface@@6B@` as 364 bytes with 91 DIR32 relocations.
There are 82 `__purecall` relocations, all at slots holding VA 00C8C500 in retail.
The seven other middle slots, +8C through +A4, name existing
`?_bfme_gsi_slot35@GameSpyInfoInterface@@UAEXXZ` through
`?_bfme_gsi_slot41@GameSpyInfoInterface@@UAEXXZ`. The earlier audit's claim of
89 current COFF `__purecall` relocations was stale. Neither those seven
placeholders nor PeerDefs.cpp or its headers are changed here.

Fresh direct retail reads through `build.read_target_bytes` reproduce the
complete table, all 60 reporter bytes plus four INT3 bytes, the 33-byte
recorder, the complete destructor plus INT3, and the zero stub plus padding.
Retail SHA-256: `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
The table SHA-256 is
`7f093460bf2e257dc8ff302f525b4468fe65cd7f78233ff51bfb7f6177859413`.
A fresh read-only Ghidra MCP session on a separate copy of the newly analyzed
project at 2026-10-04 05:19 UTC independently reproduces all five complete
byte blocks. The reporter, recorder and destructor instruction listings agree
with the direct retail disassembly. The session closes without saving changes.
The reporter has instructions but no function symbol at its start: its
decompile lookup returns `Function or symbol '0x00c8c500' not found.` This
limitation is retained; direct instructions and bytes supply the proof. The
recorder decompilation loses its stack parameter, so the complete raw body
and caller cleanup, rather than its pseudo-C signature, establish the ABI.

## Identity and ABI

Zero Hour `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_purecall.cpp:32-35`
defines `int __cdecl _purecall(void)`, invokes
`DCRASH_RELEASE("Pure virtual function called.")`, then returns zero.
The release macro at `debug_macro.h:355` calls SkipNext, CrashBegin(NULL, 0),
the diagnostic stream and CrashDone(true), agreeing with BFME's dispatch
sequence. The compiler-generated table relocations establish the C-linkage
COFF name `__purecall` independently of byte matching or a proposed name pin.

Direct retail disassembly proves the reporter's direct call targets RVA
008896A0 with one stack argument, 1, and caller cleanup. That complete 33-byte
recorder reads `[ebp+8]`, passes the kind and caller return address to vslot +5C,
and ends with RET. It agrees with the existing
`void _bfme_debugRecordCallsite(int)` declaration. The reporter then loads
pointer cell VA 01336E5C; virtual calls use +60, +6C with (NULL, 0), +38 with
VA 011334F4 (the diagnostic literal), and +4C with true. EAX becomes zero,
and RET at 0088C53B is followed by INT3. The complete body needs no ECX
receiver or stack parameters of its own. The prior local sink views and their
opaque slot names are preserved.

Reporter bytes, excluding padding:

```text
6a01e899d1ffff8b0d5c6e33018b0183c404ff50608b0d5c6e33018b116a006a00ff526c8b1068f43413018bc8ff52388b106a018bc8ff524c33c0c3
```

The removed Except.cpp implementation emitted only `33 C0 C3`, then INT3.
AGENTS.md states retail was linked without identical-COMDAT folding. Sharing
that stub's address cannot substitute for the witnessed debug reporter.
There is no added alias, second reporter identity, or guessed binding.

## Verification and preview limits

Fresh pre-edit builds verify all 193 rows across the old reporter, Except.cpp
and PeerDefs.cpp. `add_match.py --replace-rva --correct-identity` verifies the final C-linkage
provider at its official path: 1/1 row, all 60 bytes, one string and two DIR32
references. Post-edit Except.cpp and PeerDefs.cpp verify 191/191 rows; combined
with the provider this is 192/192. Fresh final COFF inspection finds only the
60-byte C-linkage provider and no competing Except definition. The 199 other
006CF680 ledger records, including their terminators, are byte-identical to
the pre-edit records. The actual `one_identity.surplus` drops 2241 -> 2240,
and only this measured one-count baseline shrink is made.
The final combined scoped gate verifies 193/193 rows across reporter, Except,
PeerDefs and the affected ILT caller `?j_000280a6@@YAXXZ` at 000280A6/5.
Staged check_csv, pin consistency, identity guard, alias guard and EOL guard
pass. The repair is committed through the normal hooks without bypass.

Current `link_check.py` cannot preview these sources because the new execution
environment has no census index. This is a missing measurement, not a pass.
Historical same-path preview at census 1677ebdc33 was 2/3 clean with
782 -> 782 linked source bytes before and 782 -> 779 after retiring the false
three-byte claim. The final new path was absent from that old census. Those
historical numbers are not fresh verification or a claimed whole-file LINKED
gain; a fresh census must measure the new object in its actual link position.
No index provenance or weak-proof roots were changed. No new C++ byte gain
is claimed for this identity repair.
