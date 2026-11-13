# Army spawner string emission repair

The sole change calls the existing visible `StringBase<char>::isEmpty`
specialization directly through AsciiString’s public base. The wrapper already
forwards to that predicate. The normal gate preserves all 785 bytes at
0x00363E30 and all seven DIR32 bindings; no identity or layout changes.
The current COFF symbol inventory contains no AsciiString::isEmpty definition
or reference after the change.

Donor reviewed: 76f0baefa6f285d54bc1ca922397674312a5913f,
`reference/shims/bfme2_ascii/ascii_string.h` and
`reverse/attempt_support/ingame-ui-helpers-link-20261015/readme.md`.
The latter independently describes the same direct-base predicate technique.
No donor paths, flags, addresses, aliases or headers are imported.

Paired `link_check.py --census-only` against index90c15cdeca drops the
AsciiString::isEmpty selected-provider finding: four findings become three.
The list node/create/insert/push_back findings remain; LINKED stays0->0.
Current hook preview is UNKNOWN because source differs from staged state.
No current census closure or newly linked/recovered bytes are claimed.
Diagnostics: build/queue10-20261113/army-link-{before,after}.log.
