# HordeTransportContain::isValidContainerFor 0x0024BD70: size() through its ILT (wave 42)

Follow-up to 2026-11-04-horde-transport-list-size-relocation.md. The only bad
relocation is REL32 +0x51: retail calls ILT 0x0000C176 (`?j_0000c176@@YAXXZ`,
ledger row, target 0x000F88F0), the source names `_STL::list<int>::size`.

Tried (private edits, reverted): drop the STLport include, keep an opaque
12-byte member view at +0x18 and call the ILT by its defined ?j_ name, the same
way the preflight call uses `j_000237b8` (union of void(*)() and a const member
pointer, called with `this->*`). Result: relocation now correct (`?j_0000c176`
emitted == retail) and every byte is identical EXCEPT the esi/edi role swap
(retail this=edi, object=esi; compiled this=esi, object=edi), so the function
does not byte-match (92 bytes differ only by register encoding).

Variants measured, all keep the swap: direct expression (also hoists the
`this-0x1c` module-data load into edi), local `memberCount`, module data read
after the count, union hoisted to the top beside `preflight`, `static const`
union (worse: call through an indirect pointer), a local `Object *obj`,
view method wrapping the member-pointer call (worse), `__thiscall` function
pointer (C4234, the keyword is unavailable in this cl).

Untested: any lever that raises the use weight of `this` without adding bytes.
Diagnostic source kept at attempt_support/20261108-horde-transport-size-via-ilt.cpp.txt.
model=claude-sonnet-5-5 t=15min boundary=0x0024BD70+112B
