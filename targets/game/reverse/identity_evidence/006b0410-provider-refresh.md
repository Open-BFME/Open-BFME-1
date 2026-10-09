# Provider refresh at RVA 006B0410

The recovered symbol remains `?rva006B0410@Rva006B0630Owner@@QAEXE@Z`. Its owner and method retain the existing address identity. The body belongs beside the visible queue helper in `game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManagerStopChain.cpp`; an external declaration of that helper does not preserve the counted local's pointee through the erase and cleanup operations.

## Boundary, callers and ABI

Retail starts with its EH registration at 006B0410 and ends with `ret 4` at 006B05BB. The next bytes are INT3 padding. Every conditional branch in the target stays inside that span, and it has no outgoing tail jump. The complete decode is retained in `build/006b0410-retry/retail-decoded-correct-extents.txt` and the independently checked call inventory in `checked-target-and-helpers.txt` in the same directory.

The complete landed callers at 006B0630 and 006B1E60 call ILT 00034626, whose decoded jump reaches this body. They supply the same receiver and one four-byte stack argument. The second caller uses its requested Boolean; the first passes zero. The target forwards that stack slot to ILT 0001F046, which reaches the recovered `MilesAudioManager::setHardwareAccelerated` at 006A9910. That complete callee tests the low byte and returns with `ret 4`. The existing unsigned-char declaration is therefore retained. The target has no hidden return storage and its callers ignore its result.

Each event call uses the pointee at PlayingAudio+14 without a receiver adjustment. Complete helper decodes establish `hasMoreLoops` at 000B28B0 (Boolean in AL), `advanceNextPlayPortion` at 000B3320 (no stack argument), the filename helper at 000B4840 (no stack argument), and the delay-window helper at 000B2860 (two binary32 stack arguments and `ret 8`). The float at VA 0112E8B0 uses the existing union declaration; the target's other argument is the literal bit pattern 42095555. The inline `clamp` spelling preserves the bank's descriptive name and calls the existing ILT 00001B77.

The complete queue helper at 006ABDA0 takes the address of the four-byte local reference, reads its pointee and updates that pointee and an allocated request. No path stores through the local reference slot or passes its address onward. Its definition is now available in the source TU. The same-receiver release call at 006A59F0 takes one PlayingAudio pointer and uses `ret 4`. That helper's ledger extent includes a switch table: the code is decoded separately through 006A5D64, its three padding bytes precede four table entries at 006A5D68, and all four table destinations are instruction boundaries inside the code. The checked inventory uses the code extent rather than decoding table bytes as instructions.

The no-argument teardown helpers at 0069D830 and 0069AB70 use the unchanged receiver. The room-type helper at 00695AB0 takes one four-byte integer and uses `ret 4`. Full decoded bodies and their return paths are retained in `complete-rest-callees-decoded.txt`.

The final virtual call is independently checked. The constructor-witnessed primary manager vtable at VA 0111C0C0 has slot +14 pointing through ILT 0002BD32 to 006B9C90. That entire body decodes through its final plain `ret`, takes no stack argument and uses the incoming receiver without adjustment. The caller observes no return value. The source keeps `slot14` as an opaque name. `manager-vtable.txt`, `virtual14-decoded.txt` and `checked-virtual14.txt` retain this evidence.

## Values and ownership

The list at receiver+9CC has a sentinel node and two link fields at node+0 and node+4. The actual value-copy sequence at target+72 loads exactly one pointer from node+8, saves it in the local slot and increments the pointed object's count at +4. It does not read a second payload field. The complete inline sequence and the complete copy helper at 006967E0 establish a single counted pointer value; the twelve-byte node allocation is not used to infer that type. There is no container key.

Erasure reconnects the two links, destroys the value at node+8, then deallocates the node using the existing node allocator. The local reference retains the object across this erasure and releases it at the iteration boundary. The independently named returned-handle destructor at 00696870 reads one handle pointer, decrements pointee+4 and invokes virtual slot zero with deleting flag one on a nonpositive count. The PlayingAudio constructor at 006B9F70 installs vtable VA 0111C8C4; its slot zero routes through ILT 000219C2 to the complete scalar-deleting destructor at 006BA0E0. The decoder and checked helper inventories retain all these bodies.

The event's existing byte at +44 has both `m_44` and the bank's `m_flag` spelling through a same-storage union. Neither spelling assigns a stronger semantic identity. The existing `AudioEventRTS` view and all previously used offsets stay intact.

## Exception cleanup

Retail handler C489E0 selects FuncInfo E38418. State 0 has predecessor -1 and destroys the guard at EBP-14 through action C489D0 and ILT 0001E961 to 006915E0. State 1 has predecessor 0 and destroys the counted local at EBP-1C through action C489D8 and ILT 000046F6 to 00696870. The mutex cleanup reads handle+0 and ownership byte+4, conditionally releases the mutex and clears that byte. The saved bank had those fields reversed.

`build/006b0410-retry/audit_eh.py` compares the emitted unwind predecessors, both action adjustments and both complete cleanup bodies against retail. The raw audit and object are retained under the same task directory. This checks cleanup separately from the target's masked byte equality.

## Experiments and refutation

The retry hypothesis was that the now-recovered queue helper's definition would explain the previous EH and register-lifetime blocker. An external-only declaration is the control. The hypothesis would be refuted if definition visibility failed to remove the local-reference reloads and restore the retail frame and registration order. The visible helper does restore them. Replacing the canonical event accessor calls with the earlier unrelated event view reintroduces scheduling differences, so those accessors also matter.

All trial sources and unedited probe outputs are retained under `build/006b0410-retry/`. The original bank is `00-original.cpp`; the mutex-layout and value-copy trials are `01-mutex-layout.cpp` and `02-copy-value.cpp`; the definition-visibility comparison is `07-native-visible.cpp` against `08-native-not-visible.cpp`; `09-canonical-event.cpp` first reaches masked equality. `10-shared-string.cpp` proves the target still matches with the canonical string header, but its copied queue-helper emission differs, so that duplicate TU is not used. The final recovery instead extends the existing stop-chain TU and retains all its established bodies and flags. `13-preserved-names.cpp` rejects calling through the old unrelated event type. `16-private-hardware.cpp` preserves the final measured source and uses the callee's canonical private access, which selects its existing mangled name without a new pin.

The identity would be refuted by a different actual ILT destination, argument cleanup or value-copy payload; the ownership model would be refuted by a cleanup state targeting another slot or another element destructor. The decoded callers, value operations and unwind map agree with the proposed declarations. No STL ledger row, symbol pin, shared header or baseline is changed.

## Verification and collection

The relocation-aware scoped gate in `add-match-gate-final.txt` passes the new body and every pre-existing function in the TU. `final-eh-routes-audit.txt` verifies the cleanup routes and their imported API slots as well as their bytes. `acceptance-decoding-checks.txt` verifies all additional helper inventories, direct branch endpoints and the release helper's switch-table destinations. Declaration, class and pin checks have separate raw logs in the task directory.

The checkout's Git index is read-only. The ordinary working-tree `check_csv.py` invocation fails while reading the unstaged deletion of the bank that `add_match.py` removes. `check-csv-final.txt` retains that failure. `collection-preview.txt` runs every CSV integrity check with exactly that deleted file removed from the prospective source membership and compares both the original bank and original TU with the final source through the repository's name-regression core. Those checks pass. The coordinator must stage the deletion and run the normal staged CSV and naming hooks; the preview does not replace them.
