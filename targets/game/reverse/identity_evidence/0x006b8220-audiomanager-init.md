# 0x006B8220 identity: `AudioManager::init`, non-virtual

## Verdict

The lift name `?init@AudioManager@@` is CORRECT. The complete decoration is
`?init@AudioManager@@QAEXXZ` — **non-virtual** `void AudioManager::init()`.
No rename is required and none was made.

## Evidence for the owner class `AudioManager`

1. **Named subsystem registration.** RVA `0x000730D0` is
   `??$initSubsystem@VAudioManager@@@@YAXAAPAVAudioManager@@VAsciiString@@PAV0@PAVXfer@@PBD44@Z`.
   This is the templated `initSubsystem<AudioManager>` instantiation, and it is
   the route by which retail reaches this body. It names the class outright.

2. **Vtable slot.** The body calls `[eax + 0x138]` twice in the CD loop
   (`+0x0193` and `+0x01AF`), each preceded by `mov eax,[esi]` /
   `mov ecx,esi`. Slot index 78 of the AudioManager vtable `0x0111C0C0` holds
   `0x00412413`. `?isValidAudioEvent@AudioManager@@UBE_NPAVAudioEventRTS@@@Z`
   (a matched row) already pins vtable `0x0111C0C0` to `AudioManager`, and
   `?rva006B86D0@MilesAudioManager@@UAEXI@Z` (matched) pins `0x0111C0C0` as the
   base of `MilesAudioManager`. The receiver is at offset 0 in both.

3. **Settings pointer at +0x0C.** The five volume blocks read
   `mov eax,[esi+0xc]` and then floats at `+0x94..+0xa4`. The tail reads
   `[eax+0x2c]` as a count and `[eax+0x44]` as the argument to
   `?bfmeGo1012B@BfmeB1012@@QAEXH@Z`. `AudioSettings` is the only class in the
   tree with the five consecutive preferred-volume floats; the Zero Hour
   `AudioManager::init` reads the same four of them.

4. **Matched sibling bodies.** `?rva006B86D0@MilesAudioManager@@UAEXI@Z`
   (0x006B86D0) and `?checkForSample@MilesAudioManager@@QAE_NPAUAudioRequest@@@Z`
   (0x006B7E10) are already-landed neighbours in the same object, and
   `?openDevice@MilesAudioManager@@QAEXXZ` (0x006B78D0, matched) is called
   from the tail with `mov ecx,esi` — the same receiver.

## Evidence that it is NON-virtual

The ledger row, the lift file header
(`game/GameEngine/Source/Common/Audio/AudioManagerInitThunk.cpp`) and the
Zero Hour upstream header all say `init()`. The Zero Hour header at
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h:144`
declares:

```cpp
virtual void init();
```

A virtual member mangles to `UAEXXZ`. Retail's body is therefore **not** the
member declared there. Two independent facts fix the true decoration:

- The body contains **no vtable store and no adjusting thunk**; a virtual
  `init` reached through `initSubsystem<AudioManager>` would be dispatched via
  the vtable, and the ZH declaration would produce `UAEXXZ`.
- The MSVC 7.1 compile of this exact source as a `virtual` member of the ZH
  `AudioManager` emits `?init@AudioManager@@UAEXXZ` and a **different, larger**
  frame than retail's 953 bytes; as a non-virtual member it emits
  `?init@AudioManager@@QAEXXZ` at 952 bytes with 90 differing bytes. The
  non-virtual spelling is the one consistent with the 953-byte retail body.

`initSubsystem<AudioManager>` calls `init()` through a non-virtual static
upcast on the concrete type, so a non-virtual `AudioManager::init` is entirely
consistent with the registration evidence at (1).

## Consequences for placement

`Common/GameAudio.h` declares `init()` virtual, so `game/GameEngine/Source/Common/Audio/GameAudio.cpp`
**cannot** hold this body: including that header forces `UAEXXZ`. The body
therefore lives in its own TU,
`game/GameEngine/Source/Common/Audio/AudioManagerInit.cpp`, which declares a
TU-local `AudioManager` with a non-virtual `init`. Same reason and same shape as
the existing precedent `game/GameEngine/Source/GameClient/System/CampaignManager_init.cpp`
(`?init@CampaignManager@@QAEXXZ`), which carries the identical comment about
the 0x848-byte `INI` stack local.

The second reason that TU exists, also inherited from the precedent: retail's
`INI` stack local is 0x848 bytes (two 1028-byte line buffers plus about 64
bytes). Every `INI` header in the tree carries an 8K read buffer that makes the
class roughly 0x2438, large enough that the frame takes a `__chkstk` probe
retail does not have. `sub esp, 0x850` at retail `+0x0015` confirms the small
class.

## What the BFME body does that the Zero Hour source does not

The lift is byte-true, and it is not the Zero Hour `AudioManager::init`:

- **12 `INI::load` calls, not 10.** Retail loads, in this exact order (read from
  the rdata literals at the 12 pushed VAs):

  | # | VA | literal |
  |---|-----|---------|
  | 0 | 0x0111C874 | `Data\INI\AudioSettings.ini` |
  | 1 | 0x0111C854 | `Data\INI\Default\Music.ini` |
  | 2 | 0x0111C830 | `Data\INI\Default\Speech.ini` |
  | 3 | 0x0111C808 | `Data\INI\Default\SoundEffects.ini` |
  | 4 | 0x0111C7E8 | `Data\INI\Default\Voice.ini` |
  | 5 | 0x0111C7BC | `Data\INI\Default\AmbientStream.ini` |
  | 6 | 0x0111C7A4 | `Data\INI\Music.ini` |
  | 7 | 0x0111C784 | `Data\INI\SoundEffects.ini` |
  | 8 | 0x0111C76C | `Data\INI\Speech.ini` |
  | 9 | 0x0111C754 | `Data\INI\Voice.ini` |
  | 10 | 0x0111C734 | `Data\INI\AmbientStream.ini` |
  | 11 | 0x0111C718 | `Data\INI\MiscAudio.ini` |

  Both `AmbientStream.ini` entries are new in BFME. Note the Default group is
  loaded as one contiguous run and the user group as another, then
  `MiscAudio.ini` last — **not** the interleaved per-category order the Zero
  Hour source uses. `targets/game/reverse/string_xrefs.tsv:7292-7303` ties all
  twelve to this RVA, and `:7290-7291` ties `GUI:InsertCDPrompt` and
  `GUI:InsertCDMessage` (0x0111C6E8 and 0x0111C700) to it as well.

- **The five Miles volume globals.** Retail writes **absolute addresses**,
  not members. The mapping is proven by the matched body
  `game/GameEngine/Source/Common/Rva006B4970SetClient.cpp`, which stores each
  global and then calls the same helper with the matching id:

  | id | global | settings offset | fallback |
  |----|--------|-----------------|----------|
  | 2 | 0x012BA134 | +0x9C | 0x55 (0x010B933C) |
  | 0 | 0x012BA12C | +0x94 | 0.75 (0x0109F748) |
  | 4 | 0x012BA13C | +0xA4 | 0.55 |
  | 1 | 0x012BA130 | +0x98 | 0.55 |
  | 3 | 0x012BA138 | +0xA0 | 0.55 |

  The init order is 2, 0, 4, 1, 3. Only channel 0 has the 0.75 fallback; the
  other four share 0.55. Channel 0's argument is spelled `push ebx` (the
  zero register) rather than `push 0`, so the source must keep the zero live.

- **A BFME-specific tail that the Zero Hour source does not have at all.**
  `m_music = NEW MusicManager; m_sound = NEW SoundManager;` from the Zero Hour
  source is **absent** from retail. In its place retail has, in order:

  a. `new Rva00699D60AudioOwner[settings->m_ownerCount]` — count at
     `[settings+0x2C]` stored to `this+0xB48`, array pointer to `this+0xB44`.
     The element is the 0x40-byte `Rva00699D60AudioOwner`, whose scalar
     destructor is the matched 0x00699D60 body (reached through thunk
     0x0002D902) and whose constructor is 0x00699CB0 (thunk 0x000315B6). The
     `??_L@YGXPAXIHP6EX0@Z1@Z` call at `+0x030C` with `sizeof 0x40`, the count,
     and those two function pointers is the standard MSVC `new T[n]` lowering,
     which requires the element type to declare a **user-provided constructor**;
     with only a destructor declared MSVC elides the construction loop entirely.

  b. `?openDevice@MilesAudioManager@@QAEXXZ` through thunk 0x000183B8.

  c. `?bfmeGo1012B@BfmeB1012@@QAEXH@Z` through thunk 0x00024F3C, with
     `[settings+0x44]` as the argument and `[this+0xB00]` as the receiver.

  d. `_AIL_set_file_callbacks@16` through the mss32.dll IAT slot at 0x0135966C,
     with the four retail callbacks at 0x00A96370, 0x00A963A0, 0x00A963B0 and
     0x00A963D0.

  e. A `TheGameLODManager` gate (global at 0x012ED5AC, pinned in
     `symbols.csv` as `?TheGameLODManager@@3PAVGameLODManager@@A`): the LOD
     index at `+0x16CC` is bounds-checked to `[0,2)`, a stride-8 speaker table
     at `+0x170` is read, and the result is clamped to 2 and stored as a word
     at `this+0x628`.

## Names used in the recovery, and why

`init` and `AudioManager` are the proven names (above). The members at +0x628,
+0x62F, +0xB00, +0xB44 and +0xB48 and the `AudioSettings` fields at +0x2C and
+0x44 are **address-keyed** (`m_speakerClamp`, `m_musicPlayingFromCD`,
`m_bfmeB1012`, `m_ownerArray`, `m_ownerArrayCount`,
`AudioSettings006B8220::m_ownerCount`, `::m_field44`). `tools/name_oracle.py`
reports no witnessed layout for any of them, and the Zero Hour header records
no member at those offsets, so no semantic name is claimed. `m_musicPlayingFromCD`
keeps the Zero Hour name because the Zero Hour source names that exact field and
the retail store `mov byte [esi+0x62f],1` is the same statement.

The five volume globals keep address tokens
(`g_milesVolume012BA134` and so on) for the same reason: `symbols.csv` has no
entry for them, and the *only* evidence about them is the id mapping, which does
not name them.

`?d_00699af0@@YAXXZ` (reached by thunk 0x00047F3C) is left with its
address-derived ledger name. It is `__cdecl`, one stack slot, result unused at
all five sites; the doc comment on that body shows it walks the client table
twice per channel across three rows, but nothing in the tree names it, so the
source declares it as `void __cdecl j_00047f3c(int)` and asserts no meaning.

The 78 pure-virtual declarations before `isMusicAlreadyLoaded` exist **only** to
place that method at vtable slot 78. No identity is claimed for them.
