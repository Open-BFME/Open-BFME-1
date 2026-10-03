# Five historical range-count truncations

These matched rows survive the August1 snapshot with sizes equal to Ghidra
getBody().getNumAddresses(). Current retail decoding and Ghidra entry/end
addresses independently show that each contiguous body extends farther.

Rule: tools/ghidra/README.md45-54 explicitly requires verifying the complete
contiguous retail extent; docs/matching.md refers to that warning. A byte
match of a selected prefix does not prove the entire function.

| RVA | Old size | Complete span | End exclusive | Existing row name |
| --- | ---: | ---: | --- | --- |
| 0x00258D70 | 98 | 101 | 0x258dd5 | `??0CashHackSpecialPowerModuleData@@QAE@XZ` |
| 0x00289E50 | 803 | 806 | 0x28a176 | `??1BroadcastStealthUpdate@@UAE@XZ` |
| 0x00379440 | 320 | 323 | 0x379583 | `??1CreateCrateDie@@UAE@XZ` |
| 0x00265ED0 | 651 | 659 | 0x266163 | `??1SiegeDeployHordeSpecialPower@@UAE@XZ` |
| 0x002AB0F0 | 543 | 549 | 0x2ab315 | `??1SpecialEnemySenseUpdate@@UAE@XZ` |

For each entry, local PE decoding reaches a normal final return followed by
INT3. Their checked-in single-function naked lifts contain exactly the old
number of emitted bytes, so they omit the corresponding retail epilogue.
The CashHack range ends inside MOV EAX,ESI; BroadcastStealth cuts ADD ESP,A4;
CreateCrate omits RET4; SiegeDeploy and SpecialEnemySense cut the FS:[0]
restores. Ghidra get_function_by_address agrees with each final address.
A Ghidra memory read at VA658DC0 also exactly agrees with the local retail.

These are confirmed WRONG extent findings. They remain pending native
recovery or retirement; this audit does not enlarge dump claims, assert their
old names are correct, or count them as converted. No production code or
ledger row changes with these records. Preserve the original evidence in
the session audit and fix each body through normal claims and gates.

The historical agreement paragraph in the inventory README called taking
these sizes safe, contradicting its own explicit warning. Correct that
interpretation while preserving the historical measurement table.

## Retirement follow-up

All five incomplete source/claim pairs were withdrawn independently:
258D70 in3886fee624;289E50 in0f9fd1012d;379440 in96a6763d46;
265ED0 in13619ad0dd;2AB0F0 inf2b95fd660. Normal caller-impact gates
passed for every withdrawal. Complete native recovery remains open, and
none is counted as a conversion. The full RET4 at379580 and RET20 at266160
also contradict the inherited no-argument ordinary-destructor signatures;
no replacement semantic name was invented.
