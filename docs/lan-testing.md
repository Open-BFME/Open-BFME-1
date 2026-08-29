# Running the LAN tests

Most of this repo's tests need nothing but a checkout:

```bash
python3 -m pytest tools/tests/test_cave.py tools/tests/test_mods_build.py \
                 tools/tests/test_game_records.py
```

`test_cave` needs the committed baseline exe and `capstone`; `test_mods_build`
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

## How BFME identifies a player on the LAN

The "one network stack per client" rule above is not a quirk of the rig. It
follows from how the engine decides which slot a participant is.

**BFME keys a LAN participant on an address pair: a four-byte IP followed by a
two-byte port, and it compares both halves.** The reference engine this port
derives from compares a bare `m_localIP` and has no port in the comparison at
all.

`LANAPI::RequestGameOptions` is the clearest place to see it. It walks the slot
array looking for itself:

```c
for (player = 0; player < 8; ++player)
    if (slot->m_ip == me->m_ip && slot->m_port == me->m_port)
```

`me` is whatever vtable slot 55 (+0xDC) hands back, not a stored local IP. The
slot array starts at `LANGameInfo+0x88`; each record is 0x68 bytes with the
address pair at its start, and the loop stops at +0x340, which is eight slots.
`LANAPI::RequestSetName` shows the same pair at `LANPlayer+0x14`, assigned eight
bytes at a time, and the three callbacks that carry it are `OnGameOptions` at
vtable +0x98, `OnNameChange` at +0xA4 and `LookupPlayer` at +0xD8.

The consequence for testing: **two clients sharing an address are one
participant to BFME.** Every client is handed the same lobby port, so the IP is
the only half of the pair that separates them — which is exactly the failure the
rig hits without one veth per client, where announcements all attribute to
whichever slot matched first and the rest age out as "player was not
responding". If you are debugging a mesh that will not form, check that each
client really has its own address before looking anywhere else.

Every offset above is read from a body that reproduces retail byte for byte, so
this is what the shipped game does rather than what the reference source says.

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
