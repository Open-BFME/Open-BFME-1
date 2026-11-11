# Rva006092D0State: current-retail vtable audit

Base BFME 1 revision: 99ae58b84f9f0c7116febe55e5bf8c443b49faec.
Image: inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe.

The November 1 note `01115ad0-state-vftable-20261101.md` does **not** describe this image's table. Do not apply its proposed UAE-to-QAE destructor correction. The current constructor at RVA 0x0060A023 stores VA 0x01115AD0, and the complete destructor at 0x00609E4F restores it. The image base is 0x00400000, so the table is at **RVA 0x00D15AD0**. The older note describes a different fifteen-entry table beginning with the ModuleData name getter; the cause of that observation is not established. The current image SHA256 is `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.

The current table contains 29 entries (116 bytes); the following dwords are zero. Slot 0 routes through ILT 0x00025D9C to the deleting destructor at 0x0060A130. That wrapper calls the complete destructor through ILT 0x00011356, then conditionally deletes this and returns with RET 4. A virtual destructor is therefore supported, not refuted. The current `??1Rva006092D0State@@UAE@XZ` row remains unchanged.

| Slot | ILT RVA | Body RVA |
| --- | --- | --- |
| 0 | 0x00025D9C | 0x0060A130 |
| 4 | 0x00044968 | 0x006091B0 |
| 12 | 0x0002A99B | 0x006092D0 |
| 13 | 0x0004ACC8 | 0x00609850 |
| 18 | 0x0000439A | 0x00609F40 |
| 19 | 0x00009985 | 0x00609F50 |
| 20 | 0x000481CB | 0x00609F60 |
| 21 | 0x000335DC | 0x00609F70 |
| 22 | 0x0003607A | 0x00609F80 |
| 23 | 0x0002AB67 | 0x00609F90 |
| 24 | 0x00012B7F | 0x00609940 |

Every other slot is `__purecall`, RVA 0x0088C500. The matched mode dispatcher at 0x006092D0 calls offsets +0x68 and +0x6C (slots 26 and 27); these are valid slots in the 29-entry table. The destructor TU's virtual destructor plus 28 declared methods has the right slot count, whereas the constructor TU emits a one-entry table. Neither emits the required complete table. Slot 12 also establishes that the current nonvirtual `setMode` declaration needs reconciliation; several other non-pure slots are still represented by independent opaque class views. A correct compiler-emitted provider needs that family ownership/virtuality reconciliation, not a destructor rename or an invented 15-slot view.

## Validation and remaining work

`link_check.py --census-only` at census 9ac0d06c54 reports the selected table blocker for the constructor (237 own bytes) and both COMDAT/selected blockers for the destructor (215 own bytes). This is historical preview evidence, not a new census gain.

Both existing bodies pass the normal scoped byte gate, 2/2. A separate explicit private compile of the constructor succeeds under MSVC 7.1, producing PE32 COFF (machine 0x014C). Runner: installed Wine 11.16, supervisor-approved private WoW64 prefix `build/wineprefix-sol12h-wow64`, WINEARCH=win64, BUILD_POOL=2. Logs: worktree-local `build/state-baseline-build.log`, `build/state-positive-control.obj`, `build/state-census-before.txt`. No source, signature, pin, alias or ledger identity was changed.

Donor: the earlier note found no analogue at BFME 2 597434797b51; the present correction is established solely from BFME 1 raw retail bytes. This is not a donor transfer. Before implementing, recheck the current donor for the family, then claim the table and all actual providers/consumers. Do not reuse the November 1 table observation as identity evidence.
