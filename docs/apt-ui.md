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
