# 0x003BBE50: address-derived tree step and call routes

The byte-true dump covers `[0x003BBE50, 0x003BBF33)` (227 bytes) and ends in `ret 4`. The entry reads a one-byte stack argument; the receiver is in `ECX`. It increments `this+0x18`, passes the new count to a tree at `this+0x0C`, checks `Keyboard::isShift` and byte `GlobalData+0x90`, then passes an initialized seven-dword value through the tree. No caller or vtable establishes a semantic owner or method name, so the C++ owner retains `Rva003BBE50`.

The five retail call sites and physical targets are:

| Site | ILT | Physical body | Observed contract |
| --- | --- | --- | --- |
| `+0x22` | `0x00030D23` | `0x00064880` | `Rva00064880Tree::atEnd(unsigned)`, matched body, receiver `this+0x0C`, one stack dword, `ret 4` |
| `+0x3B` | `0x000156B3` | `0x005A3230` | matched `Keyboard::isShift()`, receiver from `TheKeyboard` |
| `+0x9A` | `0x00026887` | `0x00064BF0` | address-derived tree operation, same tree receiver, count and 28-byte output pointer, `ret 8` |
| `+0xB6` | `0x00025531` | `0x000643F0` | pointer-returning `Rva000643F0Value::copyTo`, `ret 4`; see `0x000643f0-copyto-return.md` |
| `+0xD4` | `0x000378F8` | `0x00609800` | three stack dwords consumed by `ret 12`; first two are a copied pair, third is a float bit pattern produced with `FMUL` |

The matched `Rva003BDC50::run` at `0x003BDC50` independently calls ILT `0x000378F8` with a by-value eight-byte pair plus a third dword, using a local address-derived adapter. The new adapter likewise keeps the address token. The matched callee at `0x00609800` reads its three stack dwords and returns with `ret 12`; the exact original source type of the third value remains unknown.

A clean MSVC 7.1 scratch source emits **227/227 exact bytes with nine relocation sites**. The source uses `/EHsc`: that setting produces the four-byte store of the by-value pair's stack address into the dead incoming argument slot at `+0xD0`. It reads the post-call output float through a volatile lvalue and the already-pinned volatile global float through a read-only view; this emits retail's `FLD [stack]` then `FMUL [global]` at `+0x9F`, with one read of each value. These are measured code-generation facts, not claims about the original source qualifiers. The retail call and global addresses above, plus `TheKeyboard=0x012F4C50`, `TheWritableGlobalData=0x012ED5C8`, `g_01075954=0x01075954`, and `g_bfmeStateDF=0x012F7048`, must be verified by the strict scoped gate before replacing the dump row. The strict scoped gate must verify all relocation sites before replacing the dump row.

The scoped gate initially found two unresolved semantic proxy names. Adding `route=` pins at their ILT addresses failed `pin_consistency.py --check`: the physical bodies remain the address-only dump at `0x00064BF0` and the previously matched three-int spelling at `0x00609800`, so such pins would assert unproved identities. The production source instead names the already matched ILT symbols `j_00026887` and `j_000378f8` as **address claims**, and applies the independently observed thiscall signatures through typed member-function pointers. The matched `Rva006092D0State::rva00609360` source uses the same local pattern for ILT `0x00025531`. No new semantic pin is required.
