# RVA 0x00176A50 is AIAttackMeleeApproachState::computePath

Retail constructor **0x0017F7F0** passes literal **0x0109A718** to the
matched AIInternalMoveToState constructor **0x0014F280** at VA 0x0057F80C.
The exact retail/Ghidra bytes spell `AIAttackMeleeApproachState`. At VA
**0x0057F816** it installs primary table **0x0109A6C0** and zeroes derived
fields +0x50 through +0x64. This directly identifies the owner despite the
constructor's existing synthetic BfmeStateBB label.

Table slot **17 (+0x44)** at **0x0109A704** stores the unique ILT
**0x004179EA** -> body **0x00176A50**. The matched native base constructor
0x0014F280 installs table **0x01095B08**. Its same slot at **0x01095B4C**
routes ILT **0x0042C89A** to independently matched
**AIInternalMoveToState::computePath**, RVA **0x001725B0**. Thus this is the
derived computePath override, without relying on a guessed decompiler name
or Zero Hour class order. The inherited protected virtual Boolean method
contract is `?computePath@AIAttackMeleeApproachState@@MAE_NXZ`.

The body contains path/movement and target checks, produces Boolean AL
results, and takes no explicit arguments, consistent with that contract.
Complete-image scans find no direct caller and exactly this stored ILT
pointer. Its complete 1041-byte boundary ends with plain RET at +0x410,
INT3 at +0x411; earlier return paths are inside the same EH-framed body.

Native identity is resolved, but tools/callees.py lists 23 direct targets,
including unproved helper contracts at 0x001F8AB0 and 0x001F9180 and several
dump-owned dependencies. No source candidate existed to bank. This evidence
commit retains conversion work and changes no source, pin or progress row.
