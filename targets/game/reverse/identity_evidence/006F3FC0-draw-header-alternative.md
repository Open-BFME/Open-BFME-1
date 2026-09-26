# W3DDisplay::draw: canonical-header alternative

Retail RVA `0x006F3FC0`, full extent 1,184 bytes. The W3DDisplay vtable at VA
`0x0111EDD0`, slot `0x1C`, contains `0x004093EF`; that ILT jumps to this body.
The final `ret` is at `0x006F445F`.

The existing primary bank remains unchanged. It emits 1,179 bytes with 64
positional differences and uses a volatile cast for its first screenshot-counter
decrement. Earlier attempts to compile it against the reference W3DDisplay
header failed on missing dependencies.

This session's alternative uses the established include set from the owning
W3DDisplay.cpp and successfully compiles against that header. It uses no volatile
access, barrier, inline assembly, instruction bytes, or deliberate padding. The
complete ordinary-C++ body emits 1,186 bytes with 157 masked positional
mismatches; normalized instruction shape is 0.985 with six structural edits.
Its lower score deliberately leaves the primary bank intact. Full source is in
`attempt_history/0x006f3fc0/ecd136968fb8d5681d31ec6d720da4e19af706495e55b6c62a320fb77b7201d2.json`.

The executable references to the counter at VA `0x012F804C` occur only in this
body and the existing 30-byte callback at `0x006EAB10`. That callback is included
in the alternative and independently still reproduces all 30 bytes. Private
storage changes both decrements from direct memory operations to load/decrement/
store sequences, narrowing the question to scheduling. A future landing of this
variant must move the existing callback's ownership, with zero extra progress.

The remaining capture argument difference begins at `+0x391`; receiver/pointer
register ordering differs around `+0x3A1..0x3AF`. The first counter sequence at
`+0x3D0` has a different load/store schedule; branch displacements then drift.
Extern counter storage instead gives 1,174 bytes and 162 positional mismatches.
Typed GlobalData views, locals, multiplication order, getter/setter wrappers,
G5/G6/G7, inline capture helpers, and visible native screenshot-save helpers did
not improve the result. An independent agent reviewed the tail and reproduced
these failures.

The direct-callee inventory contains 17 targets. Four opaque declarations remain
unpinned in this unfinished alternative: no-stack-argument ECX receiver calls
through ILTs `0x22BEC -> 0x6F0300`, `0x48216 -> 0x6F2CC0`, and
`0xA03D -> 0x6EE800`; plus `0x3E13F -> 0x6EB500`, whose body returns AL and pops
four argument bytes. Its exits write AL=1, AL=1, and AL=0 at offsets `0x17E`,
`0x487`, and `0x4AF`. These contracts are recorded for a bounded future repair,
not added as speculative pins. No production source or pin was changed.
