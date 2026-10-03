# TeamFactory::createInactiveTeam: native body and BFME ABI

Retail RVA `000F7AB0` is 390 bytes. Its final `ret 8` occupies
`000F7C33..000F7C35`; INT3 padding begins at `000F7C36`. The earlier
return at `000F7B82` is only the singleton arm. Ghidra and raw PE bytes agree.

## Identity and signature correction

GeneralsMD `Source/Common/RTS/Team.cpp:335` provides the same operation:
lookup prototype; throw ERROR_BAD_ARG if absent; reuse an existing singleton
and execute its optional script; otherwise construct Team and execute that
script. BFME adds a second string key and script output-name argument.

The independently matched createTeam body at `000F7CA0` loads both incoming
arguments, pushes them at `000F7CA8/9`, and calls ILT `0000D15C` at
`000F7CAA`. That stub enters `000F7AB0`. Matched findTeam at `000F7F40`
likewise pushes its two strings at `000F7F6A/B` and calls the same stub at
`000F7F6E`. Both C++ callers name createInactiveTeam (one through an existing
private two-argument alias). The parent reads both stack arguments before
lookup and returns with `ret 8` on both paths. Thus the old one-reference
`?createInactiveTeam@TeamFactory@@QAEPAVTeam@@ABVAsciiString@@@Z` ledger
identity is positively wrong; the two-reference spelling is independently
witnessed and already pinned by the matched initTeam caller. No new pin or
alias is introduced. Existing private-route metadata is outside this change.

## Types and references

The 0x110-byte allocation and `Team(TeamPrototype*, unsigned int)` call
through ILT `00031638` to the matched constructor `000F7790` agree with
TeamFactoryCreate.cpp and TeamConstructor.cpp. BFME's Team/TeamFactory layouts
and two-name signatures differ from the available ZH Team.h, so minimal
BFME storage views retain those already witnessed contracts. TeamFactory's
uniqueTeamID offset 0x1C is also witnessed by name_oracle. Prototype accesses
remain raw offsets rather than introducing guessed member names.

Canonical StringInline.h supplies the nontrivial four-byte AsciiString
lifetimes and char releaseBuffer calls at `00887940`. The source includes
Common/Errors.h. Raw ThrowInfo VA `011E0004` -> catchable array `011DFFFC`
-> catchable type `011DFFDC` -> type descriptor `012A716C` names
`.?AW4ErrorCode@@`; the immediate is `DEAD0003` (ERROR_BAD_ARG), not a
plain integer exception.

The ScriptEngine receiver is the established TheScriptEngine pointer at
VA `012F076C`. The limited address-derived virtual view asserts only observed
slot 53 (0xD4; two input string addresses and one output string address,
returned script pointer) and slot 25 (0x64; output-name address, the returned
record's +0x20 pointer, zero). These same call shapes and ASCII output lifetime
are present in matched AIPlayerBuildSpecificAITeam.cpp. The ZH signatures and
the limited local script_engine.h do not provide this BFME ABI; no guessed
virtual method name or full class layout is introduced. Retail actions for
the output locals target AsciiString destruction through ILT 0000D828.

## Native cleanup ownership

Parent prologue handler operand +8 selects `00BFBFDB`, whose FuncInfo is
`00DE94D4`. Three predecessor states are all -1: state0 destroys the first
output string, state1 frees the new-expression allocation, state2 destroys
the second output string. State1 names action `00BFBFC8`: saved allocation
at EBP+8, push, canonical scalar delete `00881EB0`, pop ECX, RET at
`00BFBFD2`; the next independent action begins `00BFBFD3`. It is 11 bytes.
All three native predecessor entries agree; compiler-state selection, not
identical cleanup bytes alone, identifies the dependent action.

The initial native parent probe reproduced all390 bytes modulo16 relocations.
Promotion requires add_match's ordinary complete byte/reference verification;
the old emitted source is removed once that verification succeeds.
