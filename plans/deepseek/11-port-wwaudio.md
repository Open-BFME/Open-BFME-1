# Agent `port-wwaudio`: port WWAudio (sound wrappers)

**Read `plans/deepseek/README.md` first** — it has the one-time environment setup,
the safe push-to-main ritual, the gotchas you must not re-learn, and the hard
rules. This file is your **exclusive territory**. Your agent name is **`port-wwaudio`**
(use it for `PROGRESS-port-wwaudio.md` and `--author` checks).

## Your territory — own ONLY these

Reference directory: `reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio/`

Attempt these files, in order (create the matching `src/w3d/<lowercase>.cpp` + any
headers they need):

- `AudibleSound.cpp`
- `AudioSaveLoad.cpp`
- `FilteredSound.cpp`
- `Listener.cpp`
- `listenerhandle.cpp`
- `LogicalListener.cpp`
- `LogicalSound.cpp`
- `sound2dhandle.cpp`
- `Sound3D.cpp`
- `sound3dhandle.cpp`
- `SoundBuffer.cpp`
- `soundhandle.cpp`
- `SoundPseudo3D.cpp`
- `SoundScene.cpp`
- `SoundSceneObj.cpp`
- `soundstreamhandle.cpp`
- `Threads.cpp`
- `Utils.cpp`
- `WWAudio.cpp`

You own the `.cpp`/`.h` files you create for these. Do **not** touch any other
`.cpp`, and never edit a header already present in `src/w3d/` (read-only).

## Per-file loop

1. Next file from the list not yet `DONE`/`SKIP` in your PROGRESS file.
2. `cp` the reference `.cpp` to `src/w3d/<lowercase>.cpp`; make line 1 `// cl: /DNDEBUG /MD`.
3. `python3 tools/locate.py src/w3d/<name>.cpp`
   - **Missing include** → copy that header (case-insensitively) from the reference
     WWVegas tree to `src/w3d/<lowercase>`, retry. If it's a **DX8 / Direct3D /
     `<windows.h>`-with-real-Win32 / system** header → **SKIP this file**. Cap at
     ~15 header copies, then SKIP.
   - **`0 located` / everything unlocated** and the file's distinctive strings are
     absent from the exe → the file isn't in this binary → **SKIP**.
   - Any other compile error you can't clear in ~10 min → **SKIP**.
4. `python3 tools/locate.py src/w3d/<name>.cpp --emit`  (appends matched rows).
5. Trim the `.cpp` to ONLY the located functions — delete unlocated/ambiguous
   definitions, keep kept bodies **verbatim**, drop the GPL banner. A definition
   you must keep only to force instantiation gets `// ?<mangled> absent-from-retail`
   on the line above it.
6. `python3 tools/find_declared_unmatched.py --fail src/w3d/<name>.cpp`  (must pass).
7. `./build.sh src/w3d/<name>.cpp`  (must be `OK n/n`).
8. Commit via the README's **SAFE PUSH RITUAL**. Update `PROGRESS-port-wwaudio.md`.

**Worked example already in the repo:** read `src/w3d/hash.cpp` and its git commit
(`git log -p -- src/w3d/hash.cpp`) — a clean 10-function port done exactly this way.
Also `src/w3d/trim.cpp`, `src/w3d/systimer.cpp` for small ones with a shim.

Expect to SKIP the renderer/DX8-heavy files and keep the data/container/math ones.
Skipping cleanly is success — a wrong commit is impossible (the build rejects it).
