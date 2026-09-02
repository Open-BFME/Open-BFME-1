# 044-modpanel — a mod panel for every later feature to put a row on

**UNSHIPPED, and not working yet.** The panel is written, it opens and closes on
a key, its rows are live, every engine binding it needs is measured and
verified — and nothing it draws reaches the screen. This README is the map so
the next attempt starts from the wall rather than from the beginning.

## What it is meant to be

One surface, opened with `/`, that any feature can add a row to: a heading, a
key binding, or a live reading. 039 added a pause, 043 added three camera axes,
and the only place any of it was written down was a README.

Extension is a one-line entry in `ROWS`. That is deliberate rather than a
registry features call into: each feature is linked as its own blob with no
linker between them, so a registry would need a rendezvous address in the cave
and could not be checked at build time. A table in one file can be.

## What is measured and verified

Every address below was read off a call site or a constructor, never inferred
from a header's declaration order. That distinction is the whole lesson of 043,
where a slot taken from ZH's ordering crashed twice.

| Thing | Where | How it was established |
|---|---|---|
| `InGameUI::postDraw` | RVA `0x004469F0` | InGameUI vtable `+0x12C`, called from `W3DInGameUI::draw` at RVA `0x006FC07E` |
| InGameUI vtable base | VA `0x010F5B38` | the store the ctor makes at RVA `0x0044B834` |
| `TheDisplay` | VA `0x012F1270` | |
| Display vtable base | VA `0x0111EDD0` | **four ways**: `+0x14` update and `+0x1C` draw match the ledger's `MapTransferLoadScreen` note, `+0x2C`/`+0x30` are the 4-byte dimension getters 040-horplus names independently, `+0x80` is `drawViews@Display` |
| `drawFillRect(x, y, w, h, color)` | `+0xC0` | call site RVA `0x004475AC`; callee's `ret 0x14` matches five stack args |
| `drawOpenRect` / `drawImage` | `+0xBC` / `+0xE0` | |
| `TheDisplayStringManager` | VA `0x012F12CC` | init site RVA `0x0042F656` |
| `newDisplayString` / `freeDisplayString` | `+0x24` / `+0x28` | call sites RVA `0x0040CFC0` ff — **not** the RVA `0x005A5AE0` the ledger pins |
| DisplayString vtable base | VA `0x0111FEA8` | the store the ctor makes at RVA `0x006F4E0C` |
| `setText(UnicodeString)` / `setFont(GameFont *)` | `+0x04` / `+0x18` | call sites RVA `0x0040D109` / `0x0040D0F2` |
| `getSize(Int *, Int *)` | `+0x3C` | writes `[this+0x1F0]` into both outs |
| `draw(Int x, Int y)` | `+0x44` | `ret 8`, so the colour is set separately — **not** ZH's four-argument draw |
| colour setters | `+0x28`, `+0x2C`, `+0x30` | all store into `[this+0x1CC/0x1D0/0x1DC]` and dirty `[this+0x1EC]` |
| `TheFontLibrary` | VA `0x012F1B38` | call site RVA `0x0040D0E4` |
| `FontLibrary::getFont(AsciiString *, Real, Bool)` | ILT RVA `0x0000ABC3` | body RVA `0x004772D0` |
| font description | `TheGlobalLanguageData(0x012F1484) + 0xDC` name, `+0xE0` size, `+0xE4` bold | read together at RVA `0x0040CFD4` |
| `UnicodeString(const WideChar *)` | VA `0x00C88DE0` | the GameEngine one, in `AsciiString`'s TU — **not** the WWLib class of the same mangled name at RVA `0x00065410` |
| `GameWindowManager` vtable base | VA `0x0111D740` | ctor RVA `0x006C05D8` |
| its repaint | `+0x90` → RVA `0x006C4A50` | the tail jump `W3DInGameUI::draw` ends on |

At runtime the panel builds cleanly: a probe recorded `TheDisplay`,
`TheDisplayStringManager`, `TheGlobalLanguageData` and `TheFontLibrary` all
non-null, `getFont` returning a real `GameFont *`, and `newDisplayString`
returning a real `DisplayString *`.

## The wall

`W3DDisplay::drawFillRect` produces nothing on screen, from any moment tried.

045-drawprobe painted one opaque white rect per candidate hook and counted the
calls. In a replay, over one session:

| hook | RVA | fired | drew |
|---|---|---|---|
| `InGameUI::postDraw` entry | `0x004469F0` | 3,360 | nothing |
| `W3DDisplay::draw` entry | `0x006F3FC0` | 3,360 | nothing |
| `W3DDisplay::draw`, before its last call | `0x006F40DC` | **0** | — (branch never taken) |
| `GameWindowManager` repaint entry | `0x006C4A50` | 755 | nothing |

The call itself is not in doubt. In the same payload, through the same vtable
pointer and the same `__fastcall` spelling, `getWidth`/`getHeight` at `+0x2C`
and `+0x30` returned **1680 and 1050** — the real resolution. So the base, the
slots and the calling convention are all right, and `drawFillRect` is reached.

What that leaves: `drawFillRect` queues into the `Render2DClass` at
`W3DDisplay+0x164`, and that batch is either reset after every point tried, or
rendered only inside a bracket none of these points is in — or BFME simply never
renders it, the HUD being drawn by the window manager through a different path
entirely.

## What to try next, in order

1. **Check whether the engine's own `drawFillRect` output is ever visible.**
   `postDraw` calls it four times; if those pixels never appear either, the
   whole primitive is vestigial in BFME and the answer is `drawImage` (what the
   window gadgets use) or text-only.
2. **Text alone may be enough.** `InGameUI::message` renders reliably — proven
   in 043 — so `DisplayString` drawing does reach the screen somewhere. Finding
   *where* the engine draws its message strings gives a hook that is inside the
   working bracket by construction, and a text-only panel in the game's own font
   is still native.
3. **Draw through a real `GameWindow`.** `TheWindowManager` is at VA
   `0x012F1B40` with its vtable at `0x0111D740`. Creating a window at runtime is
   more API surface, but it is the path the HUD itself takes, so it cannot be
   outside the bracket.

Do not spend another round on hook placement alone. Four points, all firing,
all silent, is enough to say the moment is not the variable.
