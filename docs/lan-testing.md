# Running the LAN tests

Most of this repo's tests need nothing but a checkout:

```bash
python3 -m pytest tools/tests/test_cave.py tools/tests/test_overlay_build.py \
                 tools/tests/test_game_records.py
```

`test_cave` needs the committed baseline exe and `capstone`; `test_overlay_build`
also builds the feature, so it needs wine and the MSVC 7.1 toolchain. Both
disassemble what the build actually produced.
`test_game_records` reads `reverse/game_end/measured.jsonl` and holds every row
against the prediction `tools/tests/rows.py` declared before it ran. None of
them launch the game.

## Producing new measurements

The rows in `measured.jsonl` come from playing real LAN matches with four
clients. That rig is **not in this repo**: it hardcodes a wine layout, a Windows
username and four prebuilt prefixes, so it runs on one machine and would be
dead weight in a clone. It lives at `dginovker/bfme-lan-rig`, and its README
carries the reasoning for its shape.

What it needs, if you are rebuilding one:

* Retail BFME 1.03 under wine, and **one prefix per client with a distinct CD
  key** — never `cp -a` a prefix, the serial at `…\ergc` comes with it.
* **One network stack per client.** The host tracks slot liveness by address
  while every slot is handed the same port, so behind one address the
  announcements attribute to one slot and the rest age out as "player was not
  responding". A bridge plus one veth per client inside an unprivileged user
  namespace is enough — no root.
* **A hostname per namespace that resolves to its own address**, and
  `nsswitch.conf` forced to `hosts: files`; otherwise systemd-resolved answers
  `::1`, the in-game mesh never forms, and the broadcast lobby hides it.
* **A window manager.** On bare Xvfb every synthetic click is silently dropped —
  DirectInput never acquires without something foreground. A wine virtual
  desktop is enough.
* **GPU rendering.** llvmpipe costs ~200% CPU per client and four of them drop
  each other's heartbeats.

## Adding a row

Declare it in `tools/tests/rows.py` **before** running it — shape, each seat's
exit mode and order, the records that seat should end up holding, and the
expected winning team. That is what makes a fixture a measurement rather than a
transcription: the test compares the game against a prediction, not against
itself.

Then play it, append its records to `reverse/game_end/measured.jsonl` with `row`
and `seat` prepended, and run the tests. A row whose measurement contradicts its
declaration is a finding about the engine — correct the declaration in a commit
that says why the original model was wrong, never to make a test pass.

`reverse/game_end/measured.md` lists what the existing rows established.
