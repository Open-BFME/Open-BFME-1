# 0x003490C0 scoped ScriptEngine action

The retail body spans 160 bytes and ends in `ret 0xC`. Its three stack
arguments are used as a `const AsciiString&` for a scope latch, a
`ScriptAction*` for execution, and a `Team*` for the controlling-player
lookup, respectively. The body saves `this+0x170AC` and `this+0x1708C`,
constructs a latch on the AsciiString at `this+0x17088`, sets the team and
player fields, calls the action dispatcher with ECX=`this`, restores both
saved fields, and destroys the latch. No named direct caller establishes the
method's original spelling, so its name retains the address token.

The receiver identity comes from the matched `ScriptEngine::executeActions`
callee at 0x00346560, the matched `ScriptEngine::Rva003433F0` and
`Rva00343780` bodies using the same three field offsets and native
`LatchRestore<AsciiString>`, and the Zero Hour `ScriptEngine` source for the
same save/execute/restore pattern. The retail calls through ILTs 0x00039B12
(latch constructor → 0x00339DA0), 0x0002369B (`Team::getControllingPlayer`
→ 0x000EC8F0), 0x0000B811 (`ScriptEngine::executeActions` → 0x00346560),
and 0x00008B84 (latch destructor → 0x00339E20). The latch's matched
constructor and destructor both install/use vtable 0x010E7688, and their
native template identities are pinned by the existing matched sibling.

The first header-based C++ probe compiled to 160 bytes with only four
non-relocation differences: MSVC assigned the saved team and player values
to the opposite callee-saved registers. Declaring the saved team before the
saved player produced 160/160 bytes modulo eight relocation slots. A strict
gate must still prove the four retail call routes and the latch vtable/EH
reference before replacing the generated row. The unrelated old
`BfmeOwnVTY` and `BfmeOwnCD` lexical aliases for the same physical latch
bodies are a separate identity cleanup, not evidence for this method name.
