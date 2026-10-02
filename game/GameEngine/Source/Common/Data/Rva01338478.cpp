// cl: /DNDEBUG /MD
//
// The head pointer of the Apt global intrusive node list at VA 0x01338478.
//
// Evidence: build/report_0x012F7048.md, section "0x01338478 -- head of a
// global intrusive node list".  The node layout and the role are proven by
// matched bodies, not inferred:
//
//   * `?shutdownChain@@YAXXZ` (RVA 0x008C3B60, 55 B,
//     game/GameEngine/Source/Common/SmallGaps/shutdownChain.cpp) walks the list
//     as `mov esi,[ecx+0xc]` (next), `call [eax+0x3c]` (vslot 15), then
//     `push 1 / call [edx+0x34]` (vslot 13, the deleting destructor) and
//     `mov [0x1338478],esi`.
//   * `?insertRva008A9AB0@Rva008C3B60Node@@QAEXXZ` (RVA 0x008A9AB0) is the
//     canonical insert: `mov eax,[0x1338478] / mov [ecx+0xc],eax /
//     mov [0x1338478],ecx`.
//   * `?bfmeAttach@Bfme5AttachNodeA/B` (RVA 0x008A9B90 / 0x008A9BE0,
//     game/GameEngine/Source/Common/Bfme5SharedStringAttach.cpp) do the same.
//
// So the cell is a `Rva008C3B60Node *` (vptr +0, flags dword +4 with bit
// 0x40000000 meaning "in use", refcounted string +8 -- the empty shared string
// at 0x012D5298 -- and next +0xC).
//
// Retail holds zero here: 0x01338478 is past `.data`'s rsize, so the cell is
// zero-filled at load and every one of the 29 stores is a runtime push.
//
// This is a data-only TU because the report could not settle which Apt
// translation unit owns the node pool (candidates: Libraries/Source/Apt/
// Apt.cpp, AptValue.cpp, AptNativeHash.cpp -- adjacency is not proof).
//
// The name is address-derived: nothing in the image, exports.csv or
// ea_evidence.csv names this global.  The class spelling Rva008C3B60Node is
// the proven one already claiming this VA in
// targets/game/reverse/dir32_addresses.csv, so referencing files need only the
// variable renamed.

struct Rva008C3B60Node;

Rva008C3B60Node *g_rva01338478NodeHead = 0;