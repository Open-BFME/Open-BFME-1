# mods/: the rules. `docs/mods.md` is the mechanism.

Mods always stack. There is no mix-and-match and no per-feature build —
`python3 tools/modbuild.py --dist` produces exactly one executable at
`mods/dist/lotrbfme.exe`, and two features claiming the same address is a hard
build error rather than a last-writer-wins merge.

Nothing here is part of the byte-exact decomp. A mod never touches `Code/` or
`reverse/`, so `./build.sh` and both git hooks are unaffected by it — that
separation is what keeps the byte gate meaningful, and it is why this tree sits
outside `Code/` rather than in it.

A feature needs only an address and a struct layout — the target does **not**
have to be decompiled, which is what makes the `.text` still held as raw retail
bytes reachable today. `docs/mods.md` has the mechanism and the gotchas.

`tools/modbuild.py` is the authority on which
features exist. This file deliberately does not list them: it used to, as a
`features = [...]` array in a `.toml` nothing ever parsed, and it was already
wrong by the time anyone noticed. The numeric prefix on a feature directory is
its application order, not decoration.

`010` is deliberately unused: it was reserved for a test-harness feature
(`-noDraw` plus per-frame logic CRC) that turned out not to be needed. Driving
the real game with synthetic clicks and asserting on screenshots covers the
journey, and a feature's own output file covers the outcome.
