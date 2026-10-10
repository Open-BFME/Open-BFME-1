# Partial Object snapshot transfer at 0x001D48A0

The complete candidate remains a banked layout view. It is not an exact recovery and does not establish a linked native Object or DamageInfo declaration. The tested base is bf3c61e459d8b5bfa97428b5168e3f5d2a591bc0. The model is gpt-6.1-sol. All raw evidence and unchanged trial sources are under build/target-001d48a0/. No ledger, pin or existing source identity is changed.

## Retry hypothesis and boundary

The earlier attempt measured an incomplete BFME layout and could not finish the state-4 unwind helper. The current neighbours, MakePairIntAsciiString.cpp, DamageInfo constructors, input assignment and the versioned input/output transfer bodies provide independently checkable field and helper evidence. The new hypothesis was that reconstructing the full BFME transfer order with those declarations and the actual two-byte version protocol would improve the earlier normalized shape. The refutation condition was no measured improvement after applying those repairs. This hypothesis improved the measured shape, but did not produce byte equality.

retail.asm.txt decodes the entire 3,988-byte target. checked_callees.log retains its direct-call inventory. The ordinary return is ret 4 at RVA 0x001D5812. Error branches enter exception construction and terminate through _CxxThrowException; the final call ends the target extent. The light-CRC return rejoins ordinary cleanup. There is no unresolved outgoing ordinary branch in that decoded extent. Instruction alignment alone was not used as boundary proof.

The receiver is the Snapshot subobject at Object+0x60. The constructor and the existing 001cee10-object-loadpostprocess.md evidence bind its secondary vtable transfer slot through ILT 0x000441C5 to this target. Neighbours ObjectSetOrRestoreTeam.cpp, Object_rva001D4810_attemptDamage.cpp and ObjectGeometry.cpp corroborate Object offsets for the ID, AI, team, radar, geometry and pending-damage members. The EA chain calls this Object::DoXfer, while the Zero Hour donor calls its counterpart Object::xfer. The bank retains Rva001D48A0::method rather than adopting a disputed native spelling. The Zero Hour body was read directly and its field order was not copied wholesale.

## Container and value evidence

The missing-trigger list at receiver+0x2b0 contains pair<int, AsciiString>. The complete 40-byte helper at RVA 0x001C52F0 takes hidden result storage, a key reference and a string reference. It writes the integer at value+0 and constructs the string at value+4 through the fully decoded StringBase<char> copy at 0x00887B60. The complete list clear at 0x001C6230 traverses both link fields, destroys the payload through 0x001C36A0, and deallocates the node with size 16. The complete 8-byte payload destructor adjusts by 4 and tail-jumps to the string destructor. This establishes both payload fields independently of allocation size and template names. Native STLport 4.6 sources were checked. The 162-byte allocator at 0x0082E540 and 85-byte deallocator at 0x0082E5F0 operate on size-indexed pool lists protected by a mutex. _STLP_USE_NEWALLOC was therefore removed. allocation-decode.log, allocation-callees.log and node-deallocate-*.log retain this evidence.

The pending-damage vector at receiver+0x2ec advances by 0x5c. The complete 125-byte input copy at 0x001C07A0 installs an input vtable and copies the fields at +4, +8, +0xc, +0x10, +0x14, +0x18, +0x1c, +0x1d, +0x20, +0x24, +0x28, +0x2c, +0x30, +0x34, +0x38, +0x3c, +0x40 and +0x44. The complete copy helper at 0x001C2C60 calls input assignment and copies output fields at element+0x50, +0x54 and +0x58. It preserves the vtable fields and padding. These are member copies, not a scalar payload inferred from allocation size.

The input occupies 0x48 bytes at element+4; the output starts at element+0x4c and has a vtable followed by floats at +4 and +8 and a byte at +0xc. input-transfer-decode.log retains all 251 bytes at 0x0037A610, including the light-CRC return and the version-gated final boolean. It establishes a float at input+0x20, a four-byte enum at +0x24 and Coord3 data at +0x2c. output-transfer-decode.log retains all 82 bytes at 0x0037A750 and its ret 4. The bank flattens the input Coord3 into three floats because that trial measures better. This is an explicitly incomplete native-type reconstruction. Emitted DamageInfoInput and DamageInfoOutput virtual method definitions remain unbound and their generated vtable contents have not passed a linked gate.

## ABI and unwind evidence

The native xfer.h declarations and the decoded chained transfer calls establish the returned Xfer reference and pointer argument widths. Direct callee ABIs were checked after resolving their ILT routes. Five thunk declarations initially omitted a leading zero; scoped-gate21.log exposed those misspellings and the later draft corrects them. The actual DamageInfo assignment-copy route uses j_00009025 with the decoded five-argument cdecl protocol. It is represented by an inline bridge rather than a second strong definition.

The complete 30-byte helper at 0x001C2DC0 forwards hidden AsciiString return storage through receiver+0x30 and returns that storage in EAX with ret 4. Its ILT 0x0002D70E resolves to the complete 33-byte helper at 0x001C2D90, which copies the global empty string through StringBase<char>. decode-001c2dc0.txt, checked-001c2dc0.log, state-name-route.log and empty-name-*.log preserve this route. The actual target caller uses the AI member at Object+0x204. The Zero Hour AIUpdate::getCurrentStateName forwards through m_stateMachine, whereas WeaponTemplate::getName returns its member m_name. The existing Weapon_getName_Thunk.cpp donor interpretation is therefore not accepted as independent identity evidence for this caller. No second identity or pin was added. The scoped gate still reports the opaque Rva001C2DC0 declaration as unresolved. Indirect begin/end/skip block calls have their argument order checked in the target, but unused return widths and full target-vtable ownership have not all been established.

eh.log retains the retail nine-state unwind map and each complete cleanup action. State 4 calls ILT 0x0002AAA9, which resolves to the complete one-byte ret at 0x000607F0. Its cleanup pushes the two placement-delete arguments and restores eight stack bytes. This resolves the earlier incomplete-helper blocker. emitted-eh23.log reads the actual emitted FuncInfo state count and compares all nine transitions and frame adjustments. Strings occupy cleanup offsets -0x90, -0x9c, -0xa8, -0x94, -0xa4 and -0xb0; the pair cleanup uses -0x84 and destroys its string at +4. The emitted transitions and offsets agree with retail. This is ownership evidence, not acceptance of the complete linked exception map.

## Measurements and rejected shapes

The following values are derived from the raw probe logs. Quality is the repository's finish_measure byte-distance score; normalized shape is a separate diagnostic and is not a byte score. The best active draft is probe23.cpp. The probe18.cpp alternative confines the damage-vector alias to the load branch and has fewer normalized structural differences, but a slightly lower measured byte score. Both sources and all earlier trials remain unchanged in build/.

| Trial | Compiled bytes | Differing bytes | First byte difference | Measured quality | Normalized shape |
| --- | ---: | ---: | --- | ---: | --- |
| probe01 | 4105 | 3342 | 0x1d | 0.1033 | 0.930 with 71 structural differences |
| probe02 | Compiler failure; see the raw log. | | | | |
| probe03 | 4185 | 3462 | 0x1d | 0.0331 | 0.930 with 67 structural differences |
| probe04 | Compiler failure; see the raw log. | | | | |
| probe05 | 3971 | 3099 | 0x2d | 0.2144 | 0.960 with 58 structural differences |
| probe06 | 3987 | 2928 | 0x2d | 0.2653 | 0.964 with 55 structural differences |
| probe07 | 4003 | 2940 | 0x2d | 0.2553 | 0.959 with 53 structural differences |
| probe08 | 3971 | 2671 | 0x2d | 0.3217 | 0.964 with 51 structural differences |
| probe09 | 3971 | 2637 | 0x2d | 0.3302 | 0.967 with 46 structural differences |
| probe10 | 3971 | 2208 | 0xb6 | 0.4378 | 0.973 with 39 structural differences |
| probe11 | 3971 | 2208 | 0xb6 | 0.4378 | 0.973 with 39 structural differences |
| probe12 | 3971 | 2208 | 0xb6 | 0.4378 | 0.973 with 39 structural differences |
| probe13 | 3957 | 1682 | 0xb6 | 0.5627 | 0.987 with 18 structural differences |
| probe14 | Compiler failure; see the raw log. | | | | |
| probe15 | Compiler failure; see the raw log. | | | | |
| probe16 | 3957 | 1679 | 0xb6 | 0.5634 | 0.988 with 16 structural differences |
| probe17 | 3957 | 1679 | 0xb6 | 0.5634 | 0.988 with 16 structural differences |
| probe18 | 3986 | 1740 | 0xb6 | 0.5627 | 0.991 with 11 structural differences |
| probe19 | 3986 | 1740 | 0xb6 | 0.5627 | 0.991 with 11 structural differences |
| probe20 | 3778 | 1516 | 0xb6 | 0.5145 | 0.950 with 16 structural differences |
| probe21 | 3957 | 1679 | 0xb6 | 0.5634 | 0.988 with 16 structural differences |
| probe22 | 3957 | 1679 | 0xb6 | 0.5634 | 0.988 with 16 structural differences |
| probe23 | 3957 | 1679 | 0xb6 | 0.5634 | 0.988 with 16 structural differences |

The mechanical EH trials in eh-trial-00.log through eh-trial-03.log did not alter their instruction result. Native Matrix3D header copying corrected the earlier aggregate-copy shape. Native polymorphic damage input/output copying and the real assignment helper corrected the earlier raw-copy mismatch. Two coordinate accessor spellings in probes 11 and 12 produced no improvement; no further unchanged register spelling is justified. Probe20's nested input Coord3 zero helper reduced the body too far and lowered byte quality, so the flat layout view is retained. Global and helper declaration corrections in probes 21 through 23 repaired relocation bindings without claiming byte equality. The finite shape_family_levers invocation found no applicable automatic register/copy/store/frame choice in this source.

## Remaining blockers and reopening conditions

The first byte difference is the order of two home-slot stores at target+0xb5 and +0xb9. The first structural difference is the AI goal-coordinate load at +0x2d6. Later residues include module-loop alignment at +0x827 and +0x8bb, the four-byte transfer loop at +0x9a1, and damage-vector alias lifetime near +0xa3c. shape23-all.log retains the complete structural comparison. Byte score is still far from exact despite the high normalized shape.

A useful retry needs new source-level lifetime or aggregate evidence for those regions, or independently established native declarations that preserve the complete helper field operations and vtable ownership. The complete helper ABI is known for the unresolved string return, but its accepted symbol binding needs identity review before a landing. Repeating the old version-pair, ABI-only or unchanged coordinate spelling experiment is not justified. The opaque receiver name itself is not a blocker.

check_csv_final.log, pin-consistency.log and class-gate-bank.log passed. probe-bank.log reproduces the candidate's measurement from the actual saved bank. scoped-gate-bank.log failed byte equality and the unresolved string accessor binding. declarations23.log refused the unclaimed target declaration because no source ledger row exists, which is expected for this bank. No full linked gate or exact source recovery is claimed. bank.log records successful banking with measured score 0.5634. The existing attempt log is preserved and re_log.py appended exactly one verdict row. diff-check.log flags the carriage return in that tool-generated appended row as trailing whitespace; the sole-writer rule prevents repairing the log manually. All uncollected scratch and raw outputs remain under build/target-001d48a0/.
