# APT: the UI system 2.22 actually uses, and how far into it we can get

BFME1 patch 2.22 has two UI systems in the binary and only one of them is alive.

* **`GameWindow` / `.wnd`** — the Generals-era system. All the code is still
  there (gadgets, `winCreateFromScript`, the FunctionLexicon), but `window.big`
  ships only 18 layouts and they are `controlbar.wnd` plus APT widget shells.
  The menus are gone from it.
* **APT** — EA's Flash player, and what every menu is. `apt/` holds 33 packages;
  `apt/options.big` is the Options screen. `BfmeAptScreenOptions` is a real
  class at RVA `0x0000C059`, alongside `MainMenu`, `QuitMenu`, `SaveLoad`,
  `LanLobby` and a dozen more.

This is also why 044-modpanel could not draw: `W3DDisplay::drawFillRect` is
Generals-era 2D that 2.22 never flushes. Four hook points, all firing, all
silent, with a provably correct call — because the primitive itself is
vestigial.

## The Generals 2D path is dead in 2.22, and that is now settled

Five hook points, in a live replay, on a display whose input works, all firing,
none drawing:

| hook | RVA | fired | drew |
|---|---|---|---|
| `InGameUI::postDraw` entry | `0x004469F0` | 3,600 | nothing |
| `W3DDisplay::draw` entry | `0x006F3FC0` | 3,600 | nothing |
| `GameWindowManager` repaint | `0x006C4A50` | **0** | never called in-game |
| `InGameUI::postDraw` **tail** | `0x004476E2` | 3,600 | nothing |
| `W3DDisplay::draw`, late | `0x006F40DC` | 0 | branch not taken |

Both primitives were tried: `drawFillRect`, and a full `DisplayString` built the
way the engine builds its own — manager, font from `TheGlobalLanguageData`, text,
colour, `draw(x, y)`. Neither reaches the screen. Through the same vtable
pointer, `getWidth`/`getHeight` return the real resolution, so the calls land.

The third row is the tell: **the window manager's repaint is never called
during a game.** There are no GameWindows in-game to repaint, because the HUD is
`AptPalantir`. Together with the menus, the score screen and the spell store,
that accounts for the whole interface.

So an in-game panel that belongs to BFME has to be APT. There is no second
route: the one this project kept reaching for has been vestigial since 2.22.
That is the same conclusion the spellbook question arrives at from the other
direction, and it means one piece of work — the reserialiser — unlocks both.

## Testing without a mouse

The rig cannot click. `RecorderClass::playbackFile` at RVA `0x0009B150` takes an
AsciiString **filename** (not a path -- it hands it to the opener at
`0x00099490`, one of the four callers of `getReplayDir`) and starts the replay
outright. It is the whole of `ReplayMenuSystem`'s Load branch, and
`TheRecorder` is at VA `0x012ED62C`.

047-uiprobe binds it to F9. One keypress goes from the main menu to a running
replay with no menus and no pointer, which is what made the table above
possible. `AptMainMenu::Options`' own handler is on F5 the same way.

## The spike: change a label, repack, load it

Done, and it worked on the first attempt. Two same-length edits inside
`Options.apt`, repacked with `tools/bigpack.py`, dropped in as `apt/options.big`:

| was | became | result on screen |
|---|---|---|
| `$Music` | `Hello!` | the Audio row reads **Hello!** |
| `$Voice` | `$Movie` | the Audio row reads **Movie** |

The screen renders with all its native chrome and the game is stable.

**The important half is the first row.** Labels in the movie are `$`-prefixed
tokens that the runtime resolves against the string table — but a string with
**no `$` renders literally**. So new labels need no CSF entry, no
`lang/english.big` edit, and no localisation plumbing. That removes what looked
like the biggest data obstacle.

## `.big` is fully solved

`tools/bigpack.py` reads and writes the format and **round-trips all 53
archives in a retail install byte-identically**. Run it on any archive to
self-check.

    BIGF | BIG4
    u32 LE  archive size
    u32 BE  file count
    u32 BE  header size
    per file: u32 BE offset, u32 BE size, NUL-terminated name
    gap bytes, then the payloads in table order

Four things vary between archives and all four have to be preserved, or the
repack is wrong in a way the game may or may not survive:

* **the magic** — `apt/*.big` are `BIGF`, `window.big`, `ini.big`, `maps.big`
  and `textures.big` are `BIG4`
* **alignment** — the APT packer starts every payload on a 4-byte boundary;
  everything else is contiguous
* **the gap** between the entry table and the first payload is **not padding**.
  The retail packer writes a marker there (`L219`), and zero-filling it is the
  difference between an identical repack and a wrong one
* **the header-size field** is the first payload offset in some archives and one
  less than it in others

## The APT container

An `apt/<Name>.big` holds `<Name>.apt` (the movie), `<Name>.const` (the
ActionScript constant pool), `<Name>.dat` (three lines of geometry bounds),
`<Name>_geometry/*.ru` (vector shapes) and the screen's textures.

**`.const`** is fully parsed:

    "Apt constant file\x1a"  padded to 0x14
    u32 unknown (0x960 for Options)
    u32 entry count (348)
    u32 table offset (0x20)
    count x { u32 type, u32 value }   type 1 = string, value = file offset
    the string pool

It holds identifiers and FSCommand names — `FSCommand:EnableComponents`,
`OnInitialized`, `gotoAndPlay`, `targetScreenName` — and **not** the visible
labels.

**`.apt`** begins `"Apt Data:6\x1a\0"`, then a u32 pointing past the header, then
a 30-record import table of `{ symbol_name_ptr, character_id, 0, movie_name_ptr }`,
then a string pool. The imports are the reason a new screen would look native
for free — Options builds itself out of shared widget movies:

    GameWindowGadgets : CheckBox, ComboBox, HorzSlider, GadgetBox
    MenuFrameAndBg    : LargeFrameNoTitleShow/Hide, LargeFrameShow/Hide
    MenuExport        : ButtonMainMenu, ButtonShort_Up, Title, frameOuter*, ...

Everything after that is **a memory image addressed by file offset**. That is
the crux: strings can be edited in place, but anything that changes a length
moves every following offset, so *adding* content means a full parse and
reserialise of the movie — character definitions, frame op-code streams and
ActionScript bytecode.

## The movie format is solved: `tools/aptfile.py`

It parses, walks and re-emits **all 33 movies in a retail install
byte-identically**, and every one satisfies the layout invariant
`char_table + 4 * char_count == movie header`. Run it on any `.apt` to
self-check.

    Apt Data:6\x1a\0                     12-byte magic
    import table   count x { u32 movie name, u32 symbol name, u32 char id, u32 }
    string pool
    character table  count x u32 offset -- 0 where the character is imported
    movie header (the type-9 character), immediately after the table
      +0x08 frame count   +0x0c frames    +0x14 char count  +0x18 char table
      +0x1c width         +0x20 height    +0x28 imports     +0x2c import table
    each character   { u32 type, u32 0x09876543, ... }
      1 shape  2 text  3 font  4 button  5 sprite  7 image  9 movie
    frames   count x { u32 op count, u32 ops offset }
    ops      op count x u32 offset, each to a type-tagged op struct
      1 DoAction  2 FrameLabel  3 PlaceObject (0x40 B)  4 RemoveObject
      5 SetBackgroundColor

Nothing in the file says where the movie header is -- it holds the character
table offset, and the character table is what would otherwise tell you where the
movie is. The root is found by scanning for the single `{9, 0x09876543}` a movie
contains.

**It never moves a byte.** New structures are appended past the end and the only
existing bytes patched are fixed-size scalar fields, so a no-op edit is
byte-identical by construction and every offset in the original stays valid.
Adding a PlaceObject means appending the op, appending a fresh op-pointer array
one entry longer, and repointing the frame at it; the old array is orphaned,
which costs a few bytes against moving every offset after it.

That was proved in-game before it was trusted: the three advanced pages
(characters 187, 198 and 209) placed onto the normal tab's resting frame drew
their eleven widgets on the Options screen, in the game's own art. The shipped
048 does not need the edit -- see below -- but the placement worked.

## The Advanced tab was already there

`Options.apt` carries a finished **Custom Graphics** tab at frames 102..121
behind the label `_open_advanced`: eleven widgets, labels, tooltips and an
animated open and close. The engine side is finished too -- a slot per widget on
the screen object, a line each in the load path and in `AptOptions::Save` -- and
so is the navigation:

    AptOptions::showAdvanced   RVA 0x0055DBA0   __thiscall(screen)

which calls `assignOpen("advanced")` on the movie and sets the screen state to 4.
Nothing in the game calls it. `AptOptions::InitGadgets` is the per-gadget
registration callback and its chain runs only at state 4, which is why both
halves of that function matter and why the widgets read null on the normal tab.

So the eleven hidden graphics options cost one call, not a movie edit. See
`mods/features/048-advancedgfx/`.

## What this makes possible, in order of cost

1. **Relabel and repurpose the existing Options screen.** No format surgery at
   all. `Options.apt` already carries 5 sliders, 5 checkboxes, 2 dropdowns and
   3 buttons, all driven by named FSCommands the cave can intercept. Rename
   them to our settings and read the widgets. This is a real settings menu, in
   the real UI, for the cost of string edits and a few hooks.
2. **Grow a label past its slot.** Each token sits in a padded slot with 4-7
   spare bytes (`$Brightness` has 792, because other content follows). Free
   within the slot; beyond it, see 3.
3. **Add rows.** Needs the full APT reader/writer. Tractable — the imports mean
   a new checkbox is a *placement of an already-imported character*, not a new
   character definition — but it is the real work, and it is format archaeology
   rather than game reversing.

Route 1 is the one to build first: it is most of the value for almost none of
the risk, and it proves the FSCommand interception that route 3 would need
anyway.

## Addresses for driving APT from the cave

    WindowManager::showAptScreen(AsciiString name, RefCountClass *listener)  RVA 0x00464ED0
    WindowManager::callFunction (the /_level%d helper)                       RVA 0x004675F0
    WindowManager::bfme_setAptText                                           RVA 0x0046CBF0
    g_theWindowManager                                                    VA 0x012F19E8
    TheWindowManager                                                      VA 0x012F1B40

`showAptScreen` takes the screen **by name**, which is what makes shipping our
own package plausible rather than only editing EA's.
